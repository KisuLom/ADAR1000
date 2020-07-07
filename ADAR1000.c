/*
 * ADAR1000.c
 *
 *  Created on: Nov 5, 2019
 *      Author: thuannc
 */

#include "system.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "altera_avalon_pio_regs.h"
#include "ADAR1000.h"

/* I/Q Reg Value for Phase Control */
const unsigned char IReg[128] = {	0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3E, 0x3E, 0x3D, 0x3D, 0x3C, 0x3C, 0x3B, 0x3A, 0x39, 0x38, 0x37,
									0x36, 0x35, 0x34, 0x33, 0x32, 0x30, 0x2F, 0x2E, 0x2C, 0x2B, 0x2A, 0x28, 0x27, 0x25, 0x24, 0x22,
									0x21, 0x01, 0x03, 0x04, 0x06, 0x07, 0x08, 0x0A, 0x0B, 0x0D, 0x0E, 0x0F, 0x11, 0x12, 0x13, 0x14,
									0x16, 0x17, 0x18, 0x19, 0x19, 0x1A, 0x1B, 0x1C, 0x1C, 0x1D, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F,
									0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1E, 0x1E, 0x1D, 0x1D, 0x1C, 0x1C, 0x1B, 0x1A, 0x19, 0x18, 0x17,
									0x16, 0x15, 0x14, 0x13, 0x12, 0x10, 0x0F, 0x0E, 0x0C, 0x0B, 0x0A, 0x08, 0x07, 0x05, 0x04, 0x02,
									0x01, 0x21, 0x23, 0x24, 0x26, 0x27, 0x28, 0x2A, 0x2B, 0x2D, 0x2E, 0x2F, 0x31, 0x32, 0x33, 0x34,
									0x36, 0x37, 0x38, 0x39, 0x39, 0x3A, 0x3B, 0x3C, 0x3C, 0x3D, 0x3E, 0x3E, 0x3E, 0x3F, 0x3F, 0x3F};

const unsigned char QReg[128] = {	0x20, 0x21, 0x23, 0x24, 0x26, 0x27, 0x28, 0x2A, 0x2B, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x33, 0x34,
									0x35, 0x36, 0x37, 0x38, 0x38, 0x39, 0x3A, 0x3A, 0x3B, 0x3C, 0x3C, 0x3C, 0x3D, 0x3D, 0x3D, 0x3D,
									0x3D, 0x3D, 0x3D, 0x3D, 0x3D, 0x3C, 0x3C, 0x3C, 0x3B, 0x3A, 0x3A, 0x39, 0x38, 0x38, 0x37, 0x36,
									0x35, 0x34, 0x33, 0x31, 0x30, 0x2F, 0x2E, 0x2D, 0x2B, 0x2A, 0x28, 0x27, 0x26, 0x24, 0x23, 0x21,
									0x20, 0x01, 0x03, 0x04, 0x06, 0x07, 0x08, 0x0A, 0x0B, 0x0B, 0x0E, 0x0F, 0x10, 0x11, 0x13, 0x14,
									0x15, 0x16, 0x17, 0x18, 0x18, 0x19, 0x1A, 0x1A, 0x1B, 0x1C, 0x1C, 0x1C, 0x1D, 0x1D, 0x1D, 0x1D,
									0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1C, 0x1C, 0x1C, 0x1B, 0x1A, 0x1A, 0x19, 0x18, 0x18, 0x17, 0x16,
									0x15, 0x14, 0x13, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0B, 0x0A, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01};

void ADAR1000_init(unsigned char spi_channel){
//	unsigned char lRegVal;

	ADAR1000_resetWholeChip(spi_channel, CHIP_ADDR1);
	ADAR1000_resetWholeChip(spi_channel, CHIP_ADDR2);
	ADAR1000_resetWholeChip(spi_channel, CHIP_ADDR3);
	ADAR1000_resetWholeChip(spi_channel, CHIP_ADDR4);

	ADAR1000_onSPI4Wire(spi_channel);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_CHIP_TYPE);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_PRODUCT_ID_H);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_PRODUCT_ID_L);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_DEV_CONFIG);

	ADAR1000_setBeamOverSPI(spi_channel, CHIP_ADDR1);
	ADAR1000_setBeamOverSPI(spi_channel, CHIP_ADDR2);
	ADAR1000_setBeamOverSPI(spi_channel, CHIP_ADDR3);
	ADAR1000_setBeamOverSPI(spi_channel, CHIP_ADDR4);

	ADAR1000_enableTRSPI(spi_channel, CHIP_ADDR1);
	ADAR1000_enableTRSPI(spi_channel, CHIP_ADDR2);
	ADAR1000_enableTRSPI(spi_channel, CHIP_ADDR3);
	ADAR1000_enableTRSPI(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_SW_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_SW_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_SW_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_SW_CTRL);

	ADAR1000_setTRDelayCtrl(spi_channel, CHIP_ADDR1, ADAR_T2RDELAY1, ADAR_T2RDELAY2, ADAR_R2TDELAY1, ADAR_R2TDELAY2);
	ADAR1000_setTRDelayCtrl(spi_channel, CHIP_ADDR2, ADAR_T2RDELAY1, ADAR_T2RDELAY2, ADAR_R2TDELAY1, ADAR_R2TDELAY2);
	ADAR1000_setTRDelayCtrl(spi_channel, CHIP_ADDR3, ADAR_T2RDELAY1, ADAR_T2RDELAY2, ADAR_R2TDELAY1, ADAR_R2TDELAY2);
	ADAR1000_setTRDelayCtrl(spi_channel, CHIP_ADDR4, ADAR_T2RDELAY1, ADAR_T2RDELAY2, ADAR_R2TDELAY1, ADAR_R2TDELAY2);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_RX_TO_TX_DELAY_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_RX_TO_TX_DELAY_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_RX_TO_TX_DELAY_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_RX_TO_TX_DELAY_CTRL);

//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);

	ADAR1000_enableNominalPowerMode(spi_channel, CHIP_ADDR1);
	ADAR1000_enableNominalPowerMode(spi_channel, CHIP_ADDR2);
	ADAR1000_enableNominalPowerMode(spi_channel, CHIP_ADDR3);
	ADAR1000_enableNominalPowerMode(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_BIAS_CURRENT_RX_LNA);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_BIAS_CURRENT_RX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_BIAS_CURRENT_TX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_BIAS_CURRENT_TX_DRV);
//
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_BIAS_CURRENT_RX_LNA);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_BIAS_CURRENT_RX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_BIAS_CURRENT_TX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_BIAS_CURRENT_TX_DRV);
//
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_BIAS_CURRENT_RX_LNA);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_BIAS_CURRENT_RX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_BIAS_CURRENT_TX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_BIAS_CURRENT_TX_DRV);
//
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_BIAS_CURRENT_RX_LNA);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_BIAS_CURRENT_RX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_BIAS_CURRENT_TX);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_BIAS_CURRENT_TX_DRV);

	ADAR1000_disablePowerDetector(spi_channel, CHIP_ADDR1);
	ADAR1000_disablePowerDetector(spi_channel, CHIP_ADDR2);
	ADAR1000_disablePowerDetector(spi_channel, CHIP_ADDR3);
	ADAR1000_disablePowerDetector(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MISC_ENABLES);

	ADAR1000_disableExtPABias(spi_channel, CHIP_ADDR1);
	ADAR1000_disableExtPABias(spi_channel, CHIP_ADDR2);
	ADAR1000_disableExtPABias(spi_channel, CHIP_ADDR3);
	ADAR1000_disableExtPABias(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MISC_ENABLES);

	ADAR1000_disableExtLNABias(spi_channel, CHIP_ADDR1);
	ADAR1000_disableExtLNABias(spi_channel, CHIP_ADDR2);
	ADAR1000_disableExtLNABias(spi_channel, CHIP_ADDR3);
	ADAR1000_disableExtLNABias(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MISC_ENABLES);

	ADAR1000_disableExtTRSW(spi_channel, CHIP_ADDR1);
	ADAR1000_disableExtTRSW(spi_channel, CHIP_ADDR2);
	ADAR1000_disableExtTRSW(spi_channel, CHIP_ADDR3);
	ADAR1000_disableExtTRSW(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MISC_ENABLES);

	ADAR1000_disableExtTRPOL(spi_channel, CHIP_ADDR1);
	ADAR1000_disableExtTRPOL(spi_channel, CHIP_ADDR2);
	ADAR1000_disableExtTRPOL(spi_channel, CHIP_ADDR3);
	ADAR1000_disableExtTRPOL(spi_channel, CHIP_ADDR4);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_MISC_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MISC_ENABLES);

	ADAR1000_switchTR(spi_channel, CHIP_ADDR1, DIR_TRANSMIT);
	ADAR1000_switchTR(spi_channel, CHIP_ADDR2, DIR_TRANSMIT);
	ADAR1000_switchTR(spi_channel, CHIP_ADDR3, DIR_TRANSMIT);
	ADAR1000_switchTR(spi_channel, CHIP_ADDR4, DIR_TRANSMIT);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_SW_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_TX_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_RX_ENABLES);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MISC_ENABLES);

//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR1, ADAR_MEM_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR2, ADAR_MEM_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR3, ADAR_MEM_CTRL);
//	lRegVal = ADAR1000_readRegister(spi_channel, CHIP_ADDR4, ADAR_MEM_CTRL);

//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
//
//	ADAR1000_switchTR(spi_channel, CHIP_ADDR1, DIR_RECEIVE);
//	ADAR1000_switchTR(spi_channel, CHIP_ADDR2, DIR_RECEIVE);
//	ADAR1000_switchTR(spi_channel, CHIP_ADDR3, DIR_RECEIVE);
//	ADAR1000_switchTR(spi_channel, CHIP_ADDR4, DIR_RECEIVE);
//
//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
//	lRegVal = ADAR1000_readTemp(spi_channel);
}

void ADAR1000_resetWholeChip(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = ADAR_INTERFACE_CONFIG_A;
	unsigned char lReg_Val = 0x81;
	ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE);
}

void ADAR1000_onSPI4Wire(unsigned char spi_channel){
	unsigned short lReg_Addr = ADAR_INTERFACE_CONFIG_A;
	unsigned char lReg_Val = 0x3C;
//	unsigned char lReg_Val = 0x18;
	ADAR1000_writeRegister(spi_channel, CHIP_ADDRALL, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE);
}

unsigned char ADAR1000_writeRegister(unsigned char spi_channel, unsigned char chip_addr, unsigned short reg_addr, unsigned char *data, unsigned char length){
	unsigned short lReg_Addr = 0;
	unsigned char lMsg[20];
	switch (chip_addr){
		case CHIP_ADDR1:
			lReg_Addr = (reg_addr & 0x7FF) | 0x0000;	// Bit[14:11] = 0000 to set first chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x00);
		break;
		case CHIP_ADDR2:
			lReg_Addr = (reg_addr & 0x7FF) | 0x2000;	// Bit[14:11] = 0100 to set second chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x01);
		break;
		case CHIP_ADDR3:
			lReg_Addr = (reg_addr & 0x7FF) | 0x4000;	// Bit[14:11] = 1000 to set third chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x02);
		break;
		case CHIP_ADDR4:
			lReg_Addr = (reg_addr & 0x7FF) | 0x6000;	// Bit[14:11] = 1100 to set fourth chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x03);
		break;
		case CHIP_ADDRALL:
			lReg_Addr = (reg_addr & 0x7FF) | 0x0800;	// Bit[14:11] = 0001 to set all chip, I'm not sure about the FirstRegister address, not recommend to use this
		break;
		default:
			return RETURN_FAILED;
	}

	*(lMsg+0) = (unsigned char)(lReg_Addr >> 8);
	*(lMsg+1) = (unsigned char)(lReg_Addr & 0x00FF);
	for (int i=0; i<length; i++){
		*(lMsg+2+i) = *(data+i);
	}

	alt_avalon_spi_command(ADAR1000_SPI_BASE, spi_channel, length+2, lMsg, 0, NULL, 0);
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_readRegister(unsigned char spi_channel, unsigned char chip_addr, unsigned short reg_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lMsg_Write[2];
	unsigned char lMsg_Read[1];
	switch (chip_addr){
		case CHIP_ADDR1:
			lReg_Addr = (reg_addr & 0x7FF) | 0x0000;	// Bit[14:11] = 0000 to read first chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x00);
		break;
		case CHIP_ADDR2:
			lReg_Addr = (reg_addr & 0x7FF) | 0x2000;	// Bit[14:11] = 0100 to read second chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x01);
		break;
		case CHIP_ADDR3:
			lReg_Addr = (reg_addr & 0x7FF) | 0x4000;	// Bit[14:11] = 1000 to read third chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x02);
		break;
		case CHIP_ADDR4:
			lReg_Addr = (reg_addr & 0x7FF) | 0x6000;	// Bit[14:11] = 1100 to read fourth chip
			IOWR_ALTERA_AVALON_PIO_DATA(ADDR_BASE, 0x03);
		break;
	}

	*(lMsg_Write+0) = (unsigned char)(lReg_Addr >> 8) | 0x80;
	*(lMsg_Write+1) = (unsigned char)(lReg_Addr & 0x00FF);

	alt_avalon_spi_command(ADAR1000_SPI_BASE, spi_channel, 2, lMsg_Write, 1, lMsg_Read, 0);
	return lMsg_Read[0];
}

unsigned char ADAR1000_setBeamOverSPI(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_MEM_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
	lReg_Val = lReg_Val | (1<<6) | (1<<5) | (1<<1) | (1<<0);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_setPhaseShift(unsigned char spi_channel, unsigned char chip_addr, unsigned char TRdir, unsigned char ps_idx){
	unsigned short lReg_Addr_I = 0;
	unsigned short lReg_Addr_Q = 0;
	unsigned char lIReg_Val = 0;
	unsigned char lQReg_Val = 0;
	switch (chip_addr){
		case CHIP_ADDR1:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr_I = ADAR_CH1_TX_PHASE_I;
				lReg_Addr_Q = ADAR_CH1_TX_PHASE_Q;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr_I = ADAR_CH1_RX_PHASE_I;
				lReg_Addr_Q = ADAR_CH1_RX_PHASE_Q;
			}
		break;
		case CHIP_ADDR2:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr_I = ADAR_CH2_TX_PHASE_I;
				lReg_Addr_Q = ADAR_CH2_TX_PHASE_Q;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr_I = ADAR_CH2_RX_PHASE_I;
				lReg_Addr_Q = ADAR_CH2_RX_PHASE_Q;
			}
		break;
		case CHIP_ADDR3:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr_I = ADAR_CH3_TX_PHASE_I;
				lReg_Addr_Q = ADAR_CH3_TX_PHASE_Q;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr_I = ADAR_CH3_RX_PHASE_I;
				lReg_Addr_Q = ADAR_CH3_RX_PHASE_Q;
			}
		break;
		case CHIP_ADDR4:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr_I = ADAR_CH4_TX_PHASE_I;
				lReg_Addr_Q = ADAR_CH4_TX_PHASE_Q;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr_I = ADAR_CH4_RX_PHASE_I;
				lReg_Addr_Q = ADAR_CH4_RX_PHASE_Q;
			}
		break;
		default:
			return RETURN_FAILED;
	}

	if (ps_idx >=0 && ps_idx <128){
		lIReg_Val = IReg[ps_idx];
		lQReg_Val = QReg[ps_idx];
	}else return RETURN_FAILED;

	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr_I, &lIReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr_Q, &lQReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

	return RETURN_SUCCESS;
}

unsigned char ADAR1000_setGain(unsigned char spi_channel, unsigned char chip_addr, unsigned char TRdir, unsigned char gain_idx){
	// Read Figure 91 in Datasheet for detail.
	// From -16dB to 0dB equivalents to from 11 to 128 in 7 LSB bits, not linearity, need to be calibrated
	// Bit 7 of CHx_ATTN_RX and CHx_ATTN_Tx is high means attenuator is bypassed and vice versa.
	// Finally, from -31dB to 0dB equivalents to from 10 to 255 in 8 bits of GAIN CTRL register
	// Remember that, MSB bit (8th bit) is shared between both Tx and Rx paths.
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	switch (chip_addr){
		case CHIP_ADDR1:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr = ADAR_CH1_TX_GAIN;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr = ADAR_CH1_RX_GAIN;
			}
		break;
		case CHIP_ADDR2:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr = ADAR_CH2_TX_GAIN;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr = ADAR_CH2_RX_GAIN;
			}
		break;
		case CHIP_ADDR3:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr = ADAR_CH3_TX_GAIN;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr = ADAR_CH3_RX_GAIN;
			}
		break;
		case CHIP_ADDR4:
			if(TRdir == DIR_TRANSMIT){
				lReg_Addr = ADAR_CH4_TX_GAIN;
			}
			if(TRdir == DIR_RECEIVE){
				lReg_Addr = ADAR_CH4_RX_GAIN;
			}
		break;
		default:
			return RETURN_FAILED;
	}

	lReg_Val = gain_idx;		// Read Figure 91

	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

	return RETURN_SUCCESS;
}

unsigned char ADAR1000_loadGainPhase(unsigned char spi_channel, unsigned char chip_addr, unsigned char TRdir){
	// Not sure about the chip_addr. LOAD to one chip may affect to other chips. However, SPI Cmd requires chip_addr information. Just test.
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;

	lReg_Addr = ADAR_LD_WRK_REGS;

	if(TRdir == DIR_TRANSMIT) lReg_Val = 0x02;	// See the LD_WRK_REGS(0x0028) Register in datasheet for detail
	if(TRdir == DIR_RECEIVE) lReg_Val = 0x01;
	if(TRdir == DIR_BOTH) lReg_Val = 0x03;

	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

	// May be need a positive pulse to complete the LOAD Action
//	lReg_Val = 0x00;
//	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enablePowerDetector(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;

	lReg_Addr = ADAR_MISC_ENABLES;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
	switch (chip_addr){
		case CHIP_ADDR1:
			lReg_Val = lReg_Val | 1<<3;
		break;
		case CHIP_ADDR2:
			lReg_Val = lReg_Val | 1<<2;
		break;
		case CHIP_ADDR3:
			lReg_Val = lReg_Val | 1<<1;
		break;
		case CHIP_ADDR4:
			lReg_Val = lReg_Val | 1<<0;
		break;
		default:
			return RETURN_FAILED;
	}
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_disablePowerDetector(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;

	lReg_Addr = ADAR_MISC_ENABLES;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
	switch (chip_addr){
		case CHIP_ADDR1:
			lReg_Val = lReg_Val & ~(1<<3);
		break;
		case CHIP_ADDR2:
			lReg_Val = lReg_Val & ~(1<<2);
		break;
		case CHIP_ADDR3:
			lReg_Val = lReg_Val & ~(1<<1);
		break;
		case CHIP_ADDR4:
			lReg_Val = lReg_Val & ~(1<<0);
		break;
		default:
			return RETURN_FAILED;
	}
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_readADC(unsigned char spi_channel, unsigned char chip_addr, unsigned char adc_clk, unsigned char adc_inputselect){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;

	lReg_Addr = ADAR_ADC_CTRL;

	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

	if (adc_clk == ADC_CLKFREQ_2MHz) lReg_Val = lReg_Val & ~(1<<7);
	else if (adc_clk == ADC_CLKFREQ_250kHz) lReg_Val = lReg_Val | (1<<7);

	lReg_Val = lReg_Val | (1<<6);		// Enable ADC_EN
	lReg_Val = lReg_Val | (1<<5);		// Enable CLK_EN
	lReg_Val = lReg_Val | (1<<4);		// Trigger Conversion Cycle

	switch (adc_inputselect){
		case ADC_TEMP:
			lReg_Val = lReg_Val & 0b11110001;
			lReg_Val = lReg_Val | 0b00000000;
		break;
		case ADC_POWER_DET1:
			lReg_Val = lReg_Val & 0b11110011;
			lReg_Val = lReg_Val | 0b00000010;
		break;
		case ADC_POWER_DET2:
			lReg_Val = lReg_Val & 0b11110101;
			lReg_Val = lReg_Val | 0b00000100;
		break;
		case ADC_POWER_DET3:
			lReg_Val = lReg_Val & 0b11110111;
			lReg_Val = lReg_Val | 0b00000110;
		break;
		case ADC_POWER_DET4:
			lReg_Val = lReg_Val & 0b11111001;
			lReg_Val = lReg_Val | 0b00001000;
		break;
		default:
			return RETURN_FAILED;
	}
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

	for (int i = 0; i <= ADC_CONV_TIMEOUT; i++){
		if ((ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & 0x01) == 0x01) break;
		if (i == ADC_CONV_TIMEOUT) return RETURN_FAILED;
	}

	lReg_Addr = ADAR_ADC_OUTPUT;
	return ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
}

unsigned char ADAR1000_readPower(unsigned char spi_channel, unsigned char chip_addr){
	unsigned char adc_inputselect = 0;
	unsigned char add_val = 0;
	ADAR1000_enablePowerDetector(spi_channel, chip_addr);

	add_val = ADAR1000_readRegister(spi_channel, chip_addr, ADAR_MISC_ENABLES);

	switch (chip_addr){
		case CHIP_ADDR1:
		adc_inputselect = ADC_POWER_DET1;
		break;
		case CHIP_ADDR2:
		adc_inputselect = ADC_POWER_DET2;
		break;
		case CHIP_ADDR3:
		adc_inputselect = ADC_POWER_DET3;
		break;
		case CHIP_ADDR4:
		adc_inputselect = ADC_POWER_DET4;
		break;
		default:
			return RETURN_FAILED;
	}
	add_val = ADAR1000_readADC(spi_channel, chip_addr, ADC_CLKFREQ_2MHz, adc_inputselect);
	ADAR1000_disablePowerDetector(spi_channel, chip_addr);
	return add_val;
}

unsigned char ADAR1000_readTemp(unsigned char spi_channel){		// Figure 80 in datasheet
	unsigned char adc_inputselect = ADC_TEMP;
	unsigned char add_val = 0;
	add_val = ADAR1000_readADC(spi_channel, CHIP_ADDR1, ADC_CLKFREQ_2MHz, adc_inputselect);
	return add_val;
}

unsigned char ADAR1000_setTRDelayCtrl(unsigned char spi_channel, unsigned char chip_addr, unsigned char T2Rdelay1, unsigned char T2Rdelay2, unsigned char R2Tdelay1, unsigned char R2Tdelay2){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_TX_TO_RX_DELAY_CTRL;
	lReg_Val = (T2Rdelay1 & 0x0F) << 4 | (T2Rdelay2 & 0x0F);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_RX_TO_TX_DELAY_CTRL;
	lReg_Val = (R2Tdelay1 & 0x0F) << 4 | (R2Tdelay2 & 0x0F);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableTRSPI(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
	lReg_Val = lReg_Val & ~(1<<2);		// Control TR through SPI
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableTRInput(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
	lReg_Val = lReg_Val | (1<<2);		// Control TR through GPIO
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_switchTR(unsigned char spi_channel, unsigned char chip_addr, unsigned char dir){
	unsigned short lReg_Addr = 0;
	unsigned short lReg_Addr2 = 0;
	unsigned char lReg_Val = 0;
	unsigned char lReg_Val2 = 0;

	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr);
	if (dir == DIR_TRANSMIT){
		lReg_Addr2 = ADAR_RX_ENABLES;		// We must turn off Receive Channel Subcircuits before turn on Transmit Channel Subcircuits and vice versa.
		lReg_Val2 = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr2);
		if (chip_addr == CHIP_ADDR1) lReg_Val2 = lReg_Val2 & ~(1<<6);
		else if (chip_addr == CHIP_ADDR2) lReg_Val2 = lReg_Val2 & ~(1<<5);
		else if (chip_addr == CHIP_ADDR3) lReg_Val2 = lReg_Val2 & ~(1<<4);
		else if (chip_addr == CHIP_ADDR4) lReg_Val2 = lReg_Val2 & ~(1<<3);
		if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr2, &lReg_Val2, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

		lReg_Addr2 = ADAR_TX_ENABLES;
		lReg_Val2 = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr2);
		lReg_Val2 = lReg_Val2 | 0x07; 		// Enables the Transmit Channel Drivers, Vector Modulators, VGAs
		if (chip_addr == CHIP_ADDR1) lReg_Val2 = lReg_Val2 | (1<<6);
		else if (chip_addr == CHIP_ADDR2) lReg_Val2 = lReg_Val2 | (1<<5);
		else if (chip_addr == CHIP_ADDR3) lReg_Val2 = lReg_Val2 | (1<<4);
		else if (chip_addr == CHIP_ADDR4) lReg_Val2 = lReg_Val2 | (1<<3);
		if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr2, &lReg_Val2, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

		lReg_Val = lReg_Val | (1<<1);		// State of SPI Control: 0 = receive and 1 = transmit
		lReg_Val = lReg_Val | (1<<6);		// Enable Transmit Channel Subcircuits
		lReg_Val = lReg_Val & ~(1<<5);		// Disable Receive Channel Subcircuits
		if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	}
	else if (dir == DIR_RECEIVE){
		lReg_Addr2 = ADAR_TX_ENABLES;		// We must turn off Receive Channel Subcircuits before turn on Transmit Channel Subcircuits and vice versa.
		lReg_Val2 = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr2);
		if (chip_addr == CHIP_ADDR1) lReg_Val2 = lReg_Val2 & ~(1<<6);
		else if (chip_addr == CHIP_ADDR2) lReg_Val2 = lReg_Val2 & ~(1<<5);
		else if (chip_addr == CHIP_ADDR3) lReg_Val2 = lReg_Val2 & ~(1<<4);
		else if (chip_addr == CHIP_ADDR4) lReg_Val2 = lReg_Val2 & ~(1<<3);
		if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr2, &lReg_Val2, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

		lReg_Addr2 = ADAR_RX_ENABLES;
		lReg_Val2 = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr2);
		lReg_Val2 = lReg_Val2 | 0x07; 		// Enables the Transmit Channel Drivers, Vector Modulators, VGAs
		if (chip_addr == CHIP_ADDR1) lReg_Val2 = lReg_Val2 | (1<<6);
		else if (chip_addr == CHIP_ADDR2) lReg_Val2 = lReg_Val2 | (1<<5);
		else if (chip_addr == CHIP_ADDR3) lReg_Val2 = lReg_Val2 | (1<<4);
		else if (chip_addr == CHIP_ADDR4) lReg_Val2 = lReg_Val2 | (1<<3);
		if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr2, &lReg_Val2, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;

		lReg_Val = lReg_Val & ~(1<<1);		// State of SPI Control: 0 = receive and 1 = transmit
		lReg_Val = lReg_Val & ~(1<<6);		// Disable Transmit Channel Subcircuits
		lReg_Val = lReg_Val | (1<<5);		// Enable Receive Channel Subcircuits
		if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	}
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableNominalPowerMode(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_BIAS_CURRENT_RX_LNA;
	lReg_Val = 0x08;				// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_BIAS_CURRENT_RX;
	lReg_Val = (0x0A<<3) | 0x05;	// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_BIAS_CURRENT_TX;
	lReg_Val = (0x05<<3) | 0x05;	// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_BIAS_CURRENT_TX_DRV;
	lReg_Val = 0x06;				// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableLowPowerMode(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_BIAS_CURRENT_RX_LNA;
	lReg_Val = 0x05;				// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_BIAS_CURRENT_RX;
	lReg_Val = (0x03<<3) | 0x02;	// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_BIAS_CURRENT_TX;
	lReg_Val = (0x05<<3) | 0x02;	// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	lReg_Addr = ADAR_BIAS_CURRENT_TX_DRV;
	lReg_Val = 0x03;				// See Table 6 in datasheet for detail
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_setExtPABiasON(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	if (chip_addr == CHIP_ADDR1) lReg_Addr = ADAR_CH1_PA_BIAS_ON;
	else if (chip_addr == CHIP_ADDR2) lReg_Addr = ADAR_CH2_PA_BIAS_ON;
	else if (chip_addr == CHIP_ADDR3) lReg_Addr = ADAR_CH3_PA_BIAS_ON;
	else if (chip_addr == CHIP_ADDR4) lReg_Addr = ADAR_CH4_PA_BIAS_ON;
	lReg_Val = dac_val;
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_setExtPABiasOFF(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	if (chip_addr == CHIP_ADDR1) lReg_Addr = ADAR_CH1_PA_BIAS_OFF;
	else if (chip_addr == CHIP_ADDR2) lReg_Addr = ADAR_CH2_PA_BIAS_OFF;
	else if (chip_addr == CHIP_ADDR3) lReg_Addr = ADAR_CH3_PA_BIAS_OFF;
	else if (chip_addr == CHIP_ADDR4) lReg_Addr = ADAR_CH4_PA_BIAS_OFF;
	lReg_Val = dac_val;
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableExtPABias(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_MISC_ENABLES;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) | (1<<6);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_disableExtPABias(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_MISC_ENABLES;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & ~(1<<6);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_setExtLNABiasON(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_LNA_BIAS_ON;
	lReg_Val = dac_val;
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_setExtLNABiasOFF(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_LNA_BIAS_OFF;
	lReg_Val = dac_val;
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableExtLNABias(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_MISC_ENABLES;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) | (1<<4);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_disableExtLNABias(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_MISC_ENABLES;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & ~(1<<4);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_switchExtTRSWPOSNEG(unsigned char spi_channel, unsigned char chip_addr, unsigned char dir){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_MISC_ENABLES;
	if (dir == TRSW_POS) lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) | (1<<7);
	else if (dir == TRSW_NEG) lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & ~(1<<7);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableExtTRSW(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) | (1<<4);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_disableExtTRSW(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & ~(1<<4);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_switchExtTRPOL(unsigned char spi_channel, unsigned char chip_addr, unsigned char dir){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	if (dir == POL_HIGH) lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) | (1<<0);
	else if (dir == POL_LOW) lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & ~(1<<0);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_enableExtTRPOL(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) | (1<<3);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}

unsigned char ADAR1000_disableExtTRPOL(unsigned char spi_channel, unsigned char chip_addr){
	unsigned short lReg_Addr = 0;
	unsigned char lReg_Val = 0;
	lReg_Addr = ADAR_SW_CTRL;
	lReg_Val = ADAR1000_readRegister(spi_channel, chip_addr, lReg_Addr) & ~(1<<3);
	if (ADAR1000_writeRegister(spi_channel, chip_addr, lReg_Addr, &lReg_Val, LENGTH_ONE_BYTE) == RETURN_FAILED) return RETURN_FAILED;
	return RETURN_SUCCESS;
}
