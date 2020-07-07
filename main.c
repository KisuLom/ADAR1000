/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include "system.h"
#include "sys/alt_irq.h"
#include "sys/alt_flash.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_uart.h"
#include "altera_avalon_uart_regs.h"
#include "ADAR1000.h"

// Luu y khi thao tac voi Flash
// + Truoc khi ghi can phai xoa block, ghi block nao thi xoa block do
// + Su dung ham alt_write_flash_block de ghi tung byte vao block
// + Nhung sau lan doc dau tien thi cac lenh ghi ko co hieu luc nua
// + Ham block: block_offset: la dia chi byte dau tien cua block chu ko phai index cua block, data_offset la dia chi byte can ghi
// + Luon luon phai xoa block NGAY truoc khi ghi, ko xoa truoc, neu xoa truoc thi du lieu ghi vao bi sai

#define ATSTATE				256
#define PSSTATE				128

#define DIR_TRANSMIT		1
#define DIR_RECEIVE			2

#define SPI_CHANNEL			0
#define ENABLE				1
#define DISABLE				0

#define ASCII_MODE_MEAS		0x00
#define ASCII_MODE_CALIB	0x01
#define ASCII_MODE_TEST		0x02

#define ASCII_STARTOFMSG 	0xFE
#define ASCII_ENDOFMSG		0xFF

#define COUNTMAX_MEAS				6
#define COUNTMAX_CALIB				9
#define COUNTMAX_TEST				7

#define FLASH_OFFSET_1_TRANSMIT		0x000
#define FLASH_OFFSET_1_RECEIVE		0x080
#define FLASH_OFFSET_2_TRANSMIT		0x100
#define FLASH_OFFSET_2_RECEIVE		0x180
#define FLASH_OFFSET_3_TRANSMIT		0x200
#define FLASH_OFFSET_3_RECEIVE		0x280
#define FLASH_OFFSET_4_TRANSMIT		0x300
#define FLASH_OFFSET_4_RECEIVE		0x380

unsigned char Reg_Val;

unsigned char meas_mode;
unsigned char calib_mode;
unsigned char test_mode;

unsigned char sw;
unsigned char chip_idx;

unsigned char freq_idx;
unsigned char phase_idx;
unsigned char gain_idx;
unsigned char dir;
int old_flash_base = 0xFFFF;

unsigned char gain_d, gain_c;
unsigned char phase_d, phase_c;
unsigned char uart_recv_buf[20];

int block_offset;
int data_offset;

//alt_flash_fd *fd;
int BASE;

void key_init(unsigned long base);
void key_clear_int_flag(unsigned long base);
unsigned char key_get_int_src(unsigned long base);
void uart_init(unsigned long base);
void uart_sendString(unsigned long base, unsigned char* str);

void handle_key_interrupt(void* context);
void handle_uartrx_interrupt(void* context);

int main(){
	int flash_write_return, flash_read_return;
	unsigned char src_addr[2];
	unsigned char dest_addr[100];
	alt_ic_isr_register(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ, handle_key_interrupt, NULL, NULL);
	alt_ic_isr_register(UART_IRQ_INTERRUPT_CONTROLLER_ID, UART_IRQ, handle_uartrx_interrupt, NULL, NULL);

	alt_flash_fd *fd;
	flash_region* regions;
	int number_of_regions;

	fd = alt_flash_open_dev("/dev/flash_n25q512_avl_mem");
	alt_get_flash_info(fd, &regions, &number_of_regions);

	key_init(KEY_BASE);
	key_clear_int_flag(KEY_BASE);

	uart_init(UART_BASE);

	printf("Start!\n");

	ADAR1000_init(SPI_CHANNEL);

	meas_mode = DISABLE;
	calib_mode = DISABLE;
	test_mode = DISABLE;

	phase_idx = 0;
	gain_idx = 0;

	IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~0xAA);
//	while(1){
//		uart_sendString(UART_BASE, "NO\n");
//		uart_sendString(UART_BASE, "xx\n");
//		uart_sendString(UART_BASE, "aa\n");
//		uart_sendString(UART_BASE, "gg");
//	}


//	flash_read_return = alt_read_flash(fd,  0x00000, dest_addr, 100);

//	src_addr[0] = 0x34;
//	src_addr[1] = 0x35;
//	BASE = 0x10000;
//	alt_erase_flash_block(fd, BASE, 0x10000);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE, src_addr, 2);
////	flash_write_return = alt_write_flash_block(fd, BASE, BASE+2, src_addr, 2);
//	flash_read_return = alt_read_flash(fd,  BASE, dest_addr, 2);
//
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE+2, src_addr, 2);
//	flash_read_return = alt_read_flash(fd,  BASE+2, dest_addr+2, 2);
//
//	src_addr[0] = 0x33;
//	src_addr[1] = 0x34;
//	BASE = 0x10000;
//	alt_erase_flash_block(fd, 0x10000, 0x10000);
////	alt_erase_flash_block(fd, 0x20000, 0x10000);
////	alt_erase_flash_block(fd, 0x30000, 0x10000);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE, src_addr, 2);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE+2, src_addr, 2);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE+4, src_addr, 2);
////	flash_read_return = alt_read_flash(fd,  BASE, dest_addr, 6);
//	src_addr[0] = 0x35;
//	src_addr[1] = 0x36;
////	flash_write_return = alt_write_flash_block(fd, BASE, BASE+6, src_addr, 2);
////	flash_write_return = alt_write_flash_block(fd, BASE, BASE+8, src_addr, 2);
////	flash_write_return = alt_write_flash_block(fd, BASE, BASE+10, src_addr, 2);
////	flash_read_return = alt_read_flash(fd,  BASE+6, dest_addr, 6);
////	flash_read_return = alt_read_flash(fd,  BASE, dest_addr, 6);
//	BASE = 0x20000;
//	alt_erase_flash_block(fd, BASE, 0x10000);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE, src_addr, 2);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE+2, src_addr, 2);
//	flash_write_return = alt_write_flash_block(fd, BASE, BASE+4, src_addr, 2);
//	BASE = 0x10000;
//	flash_read_return = alt_read_flash(fd,  BASE, dest_addr, 6);
//	BASE = 0x20000;
//	flash_read_return = alt_read_flash(fd,  BASE, dest_addr+6, 6);
//	while(1){
//		for (int i = 0; i < 10; i++){
////			alt_write_flash(fd,  i * 0x10000, src_addr, 2);
//			alt_erase_flash_block(fd, regions->offset + i*0x10000, 0x10000);
//			src_addr[0] = 0x3; src_addr[1] = 0x4;
//			flash_write_return = alt_write_flash_block(fd, regions->offset + i*0x10000, i*0x10000, src_addr, 2);
////			flash_read_return = alt_read_flash(fd,  i*0x10000+2, dest_addr+i*4, 2);
//			src_addr[0] = 0x6; src_addr[1] = 0x5;
//			flash_write_return = alt_write_flash_block(fd, regions->offset + i*0x10000, i*0x10000+2, src_addr, 2);
//			flash_read_return = alt_read_flash(fd,  i*0x10000, dest_addr+i*4, 4);
//		}
////		for (int i = 0; i < 10; i++){
////			flash_read_return = alt_read_flash(fd,  i * 0x10000, dest_addr+i*2, 2);
////		}
//	}
//
//	chip_idx = CHIP_ADDR1;
//	freq_idx = 3;
//	gain_c = 13; phase_c = 14;
//	gain_d = 0; phase_d = 0;
//
//	while(1){
//		switch(chip_idx){
//			case CHIP_ADDR1: regions->offset = FLASH_OFFSET_1; break;
//			case CHIP_ADDR2: regions->offset = FLASH_OFFSET_2; break;
//			case CHIP_ADDR3: regions->offset = FLASH_OFFSET_3; break;
//			case CHIP_ADDR4: regions->offset = FLASH_OFFSET_4; break;
//		}
//		src_addr[0] = gain_c;
//		src_addr[1] = phase_c;
//		data_offset = (gain_d * PSSTATE + phase_d)*2;
//		x = (regions->offset + freq_idx) * 0x10000 + data_offset;
//		regions->offset = regions->offset + freq_idx;
////		alt_write_flash_block(fd, regions->offset, x, src_addr, 2);
////		alt_write_flash_block(fd, regions->offset, regions->offset + data_offset, src_addr, 2);
////		alt_write_flash(fd,  (regions->offset + freq_idx) * 0x10000 + data_offset, src_addr, 2);
//		alt_write_flash(fd,  x, src_addr, 2);
//
////		data_offset = (gain_d * PSSTATE + phase_d)*2;
////		alt_read_flash(fd, (regions->offset + freq_idx) * 0x10000 + data_offset, dest_addr, 2);
//		alt_read_flash(fd, x, dest_addr, 2);
//	}

	while(1){
		sw = IORD_ALTERA_AVALON_PIO_DATA(SW_BASE);
		if (meas_mode == ENABLE){
			meas_mode = DISABLE;
			if (phase_idx >= 128) phase_idx = 0;
			if (gain_idx >= 256) gain_idx = 0;
			if (dir == DIR_TRANSMIT){
				IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~phase_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT, 255-gain_idx);

				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT, phase_idx);

				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT);

				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT);
			} else if (dir == DIR_RECEIVE){
				IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~(phase_idx | 0x80));
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE, 255-gain_idx);

				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE, phase_idx);

				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE);

				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE);
			}
			uart_sendString(UART_BASE, "OK\n");
		}
		if (calib_mode == ENABLE){
			calib_mode = DISABLE;
			IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~phase_c);
			switch(chip_idx){
				case CHIP_ADDR1:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_1_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_1_RECEIVE * regions->block_size;
				break;
				case CHIP_ADDR2:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_2_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_2_RECEIVE * regions->block_size;
				break;
				case CHIP_ADDR3:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_3_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_3_RECEIVE * regions->block_size;
				break;
				case CHIP_ADDR4:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_4_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_4_RECEIVE * regions->block_size;
				break;
			}
			block_offset = regions->offset + freq_idx * regions->block_size;
			if (old_flash_base != block_offset){
				alt_erase_flash_block(fd, block_offset, regions->block_size);
			}
			old_flash_base = block_offset;
			src_addr[0] = gain_c;
			src_addr[1] = phase_c;
			data_offset = (gain_d * PSSTATE + phase_d)*2;
			flash_write_return = alt_write_flash_block(fd, block_offset, block_offset + data_offset, src_addr, 2);
			if (!flash_write_return) uart_sendString(UART_BASE, "OK\n");
			else uart_sendString(UART_BASE, "NO\n");
		}
		if (test_mode == ENABLE){
			test_mode = DISABLE;
			switch(chip_idx){
				case CHIP_ADDR1:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_1_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_1_RECEIVE * regions->block_size;
				break;
				case CHIP_ADDR2:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_2_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_2_RECEIVE * regions->block_size;
				break;
				case CHIP_ADDR3:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_3_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_3_RECEIVE * regions->block_size;
				break;
				case CHIP_ADDR4:
					if (dir == DIR_TRANSMIT) regions->offset = FLASH_OFFSET_4_TRANSMIT * regions->block_size;
					if (dir == DIR_RECEIVE) regions->offset = FLASH_OFFSET_4_RECEIVE * regions->block_size;
				break;
			}
			block_offset = regions->offset + freq_idx * regions->block_size;
			data_offset = (gain_d * PSSTATE + phase_d)*2;
			alt_read_flash(fd, block_offset + data_offset, dest_addr, 2);
			gain_idx = dest_addr[0];
			phase_idx = dest_addr[1];

			if (dir == DIR_TRANSMIT){
				IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~phase_d);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT, 255-gain_idx);

				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT, phase_idx);

				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT);

				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR1, DIR_TRANSMIT);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR2, DIR_TRANSMIT);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR3, DIR_TRANSMIT);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR4, DIR_TRANSMIT);
			} else if (dir == DIR_RECEIVE){
				IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~(phase_d | 0x80));
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE, 255-gain_idx);
				ADAR1000_setGain(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE, 255-gain_idx);

				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE, phase_idx);
				ADAR1000_setPhaseShift(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE, phase_idx);

				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE);
				ADAR1000_loadGainPhase(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE);

				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR1, DIR_RECEIVE);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR2, DIR_RECEIVE);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR3, DIR_RECEIVE);
				ADAR1000_switchTR(SPI_CHANNEL, CHIP_ADDR4, DIR_RECEIVE);
			}
			uart_sendString(UART_BASE, "OK\n");
		}
	}
	alt_flash_close_dev(fd);
	printf("Stop!\n");
	return 0;
}

void key_init(unsigned long base){
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(base, 1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(base, 0);	// Reset the edge capture register by writing to this register
}
void key_clear_int_flag(unsigned long base){
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(base, 0);	// Write to the edge capture register to reset it
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(base);	// Read the PIO to delay ISR exit. This step is necessary
}
unsigned char key_get_int_src(unsigned long base){
	return IORD_ALTERA_AVALON_PIO_EDGE_CAP(base);
}

void uart_init(unsigned long base){
	IOWR_ALTERA_AVALON_UART_CONTROL(base, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);
}

void uart_sendString(unsigned long base, unsigned char* str){
	while(*str){
		while(!(IORD_ALTERA_AVALON_UART_STATUS(base) & ALTERA_AVALON_UART_STATUS_TRDY_MSK));
		IOWR_ALTERA_AVALON_UART_TXDATA(base, *str);
		str++;
	}
}
void handle_key_interrupt(void* context){
	if (key_get_int_src(KEY_BASE) & 0x01){
		usleep(10000);
		if(!(IORD_ALTERA_AVALON_PIO_DATA(KEY_BASE)& 0x01)){
			meas_mode = ENABLE;
			phase_idx = phase_idx + 1;
//			gain_idx = gain_idx + 1;
		}
		sw = IORD_ALTERA_AVALON_PIO_DATA(SW_BASE);
		if (sw == 0x00) dir = DIR_TRANSMIT;
		if (sw == 0x01) dir = DIR_RECEIVE;
	}
	key_clear_int_flag(KEY_BASE);
}

void handle_uartrx_interrupt(void* context){
	static unsigned char count = 0;
	static unsigned char countmax = 0;
	static unsigned char prv_data = 0;
	static unsigned char data = 0;

	unsigned char checksum_xor, checksum_and;
	if(IORD_ALTERA_AVALON_UART_STATUS(UART_BASE) & ALTERA_AVALON_UART_STATUS_RRDY_MSK){
		prv_data = data;
		data = IORD_ALTERA_AVALON_UART_RXDATA(UART_BASE);
		if (countmax == 0){
			if ((prv_data == ASCII_STARTOFMSG) && (data == ASCII_MODE_MEAS)) {
				countmax = COUNTMAX_MEAS;
				count = 0;
			}
			else if ((prv_data == ASCII_STARTOFMSG) && (data == ASCII_MODE_TEST)){
				countmax = COUNTMAX_TEST;
				count = 0;
			}
			else if ((prv_data == ASCII_STARTOFMSG) && (data == ASCII_MODE_CALIB)) {
				countmax = COUNTMAX_CALIB;
				count = 0;
			}
		} else if (countmax == COUNTMAX_MEAS){
			uart_recv_buf[count] = data;
			count++;
			if (count == countmax){
				checksum_xor = uart_recv_buf[0] ^ uart_recv_buf[1] ^ uart_recv_buf[2] ^ uart_recv_buf[3];
				checksum_and = uart_recv_buf[0] & uart_recv_buf[1] & uart_recv_buf[2] & uart_recv_buf[3];
				if (checksum_xor == uart_recv_buf[4] && checksum_and == uart_recv_buf[5]){
					chip_idx = uart_recv_buf[0];
					dir = uart_recv_buf[1];
					gain_idx = uart_recv_buf[2];
					phase_idx = uart_recv_buf[3];
					meas_mode = ENABLE;
					countmax = 0;
//					uart_sendString(UART_BASE, "OK\n");
//					IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, ~phase_idx);
				}
				else {
					countmax = 0;
					uart_sendString(UART_BASE, "NO\n");
				}
			}
		} else if (countmax == COUNTMAX_CALIB){
			uart_recv_buf[count] = data;
			count++;
			if (count == countmax){
				checksum_xor = uart_recv_buf[0] ^ uart_recv_buf[1] ^ uart_recv_buf[2] ^ uart_recv_buf[3] ^ uart_recv_buf[4] ^ uart_recv_buf[5] ^ uart_recv_buf[6];
				checksum_and = uart_recv_buf[0] & uart_recv_buf[1] & uart_recv_buf[2] & uart_recv_buf[3] & uart_recv_buf[4] & uart_recv_buf[5] & uart_recv_buf[6];
				if (checksum_xor == uart_recv_buf[7] && checksum_and == uart_recv_buf[8]){
					freq_idx = uart_recv_buf[0];
					chip_idx = uart_recv_buf[1];
					dir = uart_recv_buf[2];
					gain_d = uart_recv_buf[3];
					phase_d = uart_recv_buf[4];
					gain_c = uart_recv_buf[5];
					phase_c = uart_recv_buf[6];
					calib_mode = ENABLE;
					countmax = 0;
//					uart_sendString(UART_BASE, "OK\n");
				}
				else {
					countmax = 0;
					uart_sendString(UART_BASE, "NO\n");
				}
			}
		} else if (countmax == COUNTMAX_TEST){
			uart_recv_buf[count] = data;
			count++;
			if (count == countmax){
				checksum_xor = uart_recv_buf[0] ^ uart_recv_buf[1] ^ uart_recv_buf[2] ^ uart_recv_buf[3] ^ uart_recv_buf[4];
				checksum_and = uart_recv_buf[0] & uart_recv_buf[1] & uart_recv_buf[2] & uart_recv_buf[3] & uart_recv_buf[4];
				if (checksum_xor == uart_recv_buf[5] && checksum_and == uart_recv_buf[6]){
					freq_idx = uart_recv_buf[0];
					chip_idx = uart_recv_buf[1];
					dir = uart_recv_buf[2];
					gain_d = uart_recv_buf[3];
					phase_d = uart_recv_buf[4];
					test_mode = ENABLE;
					countmax = 0;
//					uart_sendString(UART_BASE, "OK\n");
				}
				else {
					countmax = 0;
					uart_sendString(UART_BASE, "NO\n");
				}
			}
		}
	}
}
