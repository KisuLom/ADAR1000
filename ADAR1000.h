/*
 * ADAR1000.h
 *
 *  Created on: Sep 11, 2019
 *      Author: thuannc
 */

#ifndef ADAR1000_H_
#define ADAR1000_H_

// Parameters
#define ADAR_T2RDELAY1		0x01
#define ADAR_T2RDELAY2		0x01
#define ADAR_R2TDELAY1		0x01
#define ADAR_R2TDELAY2		0x01

// Control Variables
#define ADAR1000_SPI_BASE	SPI_ADAR1000_BASE

#define CHIP_ADDR1			1
#define CHIP_ADDR2			2
#define CHIP_ADDR3			3
#define CHIP_ADDR4			4
#define	CHIP_ADDRALL		255

#define SPI_CHANNEL_0 		0
#define SPI_CHANNEL_1 		1
#define SPI_CHANNEL_2 		2
#define SPI_CHANNEL_3 		3

#define LENGTH_ONE_BYTE		1
#define LENGTH_TWO_BYTE		2

#define DIR_TRANSMIT		1
#define DIR_RECEIVE			2
#define DIR_BOTH			3

#define ADC_CLKFREQ_2MHz	0
#define ADC_CLKFREQ_250kHz	1

#define ADC_TEMP			0
#define ADC_POWER_DET1		1
#define ADC_POWER_DET2		2
#define ADC_POWER_DET3		3
#define ADC_POWER_DET4		4
#define ADC_CONV_TIMEOUT	50

#define TRSW_POS			1
#define TRSW_NEG			2

#define POL_HIGH			1
#define POL_LOW				2

#define RETURN_SUCCESS		0
#define RETURN_FAILED		255

// Macro
#define SET_ADDR1			x
#define	RESET_ADDR1			x
#define SET_ADDR0			x
#define RESET_ADDR0			x

/* Registers Address */
#define ADAR_INTERFACE_CONFIG_A		0x000
#define ADAR_INTERFACE_CONFIG_B		0X001
#define ADAR_DEV_CONFIG				0x002
#define ADAR_CHIP_TYPE				0x003
#define ADAR_PRODUCT_ID_H			0x004
#define ADAR_PRODUCT_ID_L			0x005
#define ADAR_SCRATCH_PAD			0x00A
#define ADAR_SPI_REV				0x00B
#define ADAR_VENDOR_ID_H			0x00C
#define ADAR_VENDOR_ID_L			0x00D
#define	ADAR_TRANSFER_REG			0x00F

#define	ADAR_CH1_RX_GAIN			0x010
#define	ADAR_CH2_RX_GAIN			0x011
#define	ADAR_CH3_RX_GAIN			0x012
#define	ADAR_CH4_RX_GAIN			0x013

#define	ADAR_CH1_RX_PHASE_I			0x014
#define	ADAR_CH1_RX_PHASE_Q			0x015
#define	ADAR_CH2_RX_PHASE_I			0x016
#define	ADAR_CH2_RX_PHASE_Q			0x017
#define	ADAR_CH3_RX_PHASE_I			0x018
#define	ADAR_CH3_RX_PHASE_Q			0x019
#define	ADAR_CH4_RX_PHASE_I			0x01A
#define	ADAR_CH4_RX_PHASE_Q			0x01B

#define ADAR_CH1_TX_GAIN			0x01C
#define ADAR_CH2_TX_GAIN			0x01D
#define ADAR_CH3_TX_GAIN			0x01E
#define ADAR_CH4_TX_GAIN			0x01F

#define ADAR_CH1_TX_PHASE_I			0x020
#define ADAR_CH1_TX_PHASE_Q			0x021
#define ADAR_CH2_TX_PHASE_I			0x022
#define ADAR_CH2_TX_PHASE_Q			0x023
#define ADAR_CH3_TX_PHASE_I			0x024
#define ADAR_CH3_TX_PHASE_Q			0x025
#define ADAR_CH4_TX_PHASE_I			0x026
#define ADAR_CH4_TX_PHASE_Q			0x027

#define ADAR_LD_WRK_REGS			0x028

#define	ADAR_CH1_PA_BIAS_ON			0x029
#define	ADAR_CH2_PA_BIAS_ON			0x02A
#define	ADAR_CH3_PA_BIAS_ON			0x02B
#define	ADAR_CH4_PA_BIAS_ON			0x02C

#define ADAR_LNA_BIAS_ON			0x02D
#define	ADAR_RX_ENABLES				0x02E
#define	ADAR_TX_ENABLES				0x02F
#define	ADAR_MISC_ENABLES			0x030
#define	ADAR_SW_CTRL				0x031
#define	ADAR_ADC_CTRL				0x032
#define	ADAR_ADC_OUTPUT				0x033

#define	ADAR_BIAS_CURRENT_RX_LNA	0x034
#define	ADAR_BIAS_CURRENT_RX		0x035
#define	ADAR_BIAS_CURRENT_TX		0x036
#define	ADAR_BIAS_CURRENT_TX_DRV	0x037

#define ADAR_MEM_CTRL				0x038

#define ADAR_RX_CHX_MEM				0x039
#define ADAR_RX_CH1_MEM				0x03D
#define ADAR_RX_CH2_MEM				0x03E
#define ADAR_RX_CH3_MEM				0x03F
#define	ADAR_RX_CH4_MEM				0x040

#define ADAR_TX_CHX_MEM				0x03A
#define ADAR_TX_CH1_MEM				0x041
#define ADAR_TX_CH2_MEM				0x042
#define ADAR_TX_CH3_MEM				0x043
#define	ADAR_TX_CH4_MEM				0x044

#define	ADAR_REV_ID					0x045

#define	ADAR_CH1_PA_BIAS_OFF		0x046
#define	ADAR_CH2_PA_BIAS_OFF		0x047
#define	ADAR_CH3_PA_BIAS_OFF		0x048
#define	ADAR_CH4_PA_BIAS_OFF		0x049

#define	ADAR_LNA_BIAS_OFF			0x04A
#define	ADAR_TX_TO_RX_DELAY_CTRL	0x04B
#define	ADAR_RX_TO_TX_DELAY_CTRL	0x04C

#define	ADAR_TX_BEAM_STEP_START		0x04D
#define	ADAR_TX_BEAM_STEP_STOP		0x04E
#define	ADAR_RX_BEAM_STEP_START		0x04F
#define	ADAR_RX_BEAM_STEP_STOP		0x050

#define ADAR_RX_BIAS_RAM_CTL		0x051
#define	ADAR_TX_BIAS_RAM_CTL		0x052

#define	ADAR_LDO_TRIM_CTL_0			0x400
#define	ADAR_LDO_TROL_CTL_1			0x401

// Functions
void ADAR1000_init(unsigned char spi_channel);

void ADAR1000_resetWholeChip(unsigned char spi_channel, unsigned char chip_addr);
void ADAR1000_onSPI4Wire(unsigned char spi_channel);

unsigned char ADAR1000_writeRegister(unsigned char spi_channel, unsigned char chip_addr, unsigned short reg_addr, unsigned char *data, unsigned char length);
unsigned char ADAR1000_readRegister(unsigned char spi_channel, unsigned char chip_addr, unsigned short reg_addr);

unsigned char ADAR1000_setPhaseShift(unsigned char spi_channel, unsigned char chip_addr, unsigned char TRdir, unsigned char ps_idx);
unsigned char ADAR1000_setGain(unsigned char spi_channel, unsigned char chip_addr, unsigned char TRdir, unsigned char gain_idx);
unsigned char ADAR1000_loadGainPhase(unsigned char spi_channel, unsigned char chip_addr, unsigned char TRdir);
unsigned char ADAR1000_setBeamOverSPI(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_enablePowerDetector(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_disablePowerDetector(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_readADC(unsigned char spi_channel, unsigned char chip_addr, unsigned char adc_clk, unsigned char adc_inputselect);
unsigned char ADAR1000_readPower(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_readTemp(unsigned char spi_channel);

unsigned char ADAR1000_setTRDelayCtrl(unsigned char spi_channel, unsigned char chip_addr, unsigned char T2Rdelay1, unsigned char T2Rdelay2, unsigned char R2Tdelay1, unsigned char R2Tdelay2);

unsigned char ADAR1000_enableTRSPI(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_enableTRInput(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_switchTR(unsigned char spi_channel, unsigned char chip_addr, unsigned char dir);

unsigned char ADAR1000_enableNominalPowerMode(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_enableLowPowerMode(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_setExtPABiasON(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val);
unsigned char ADAR1000_setExtPABiasOFF(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val);
unsigned char ADAR1000_enableExtPABias(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_disableExtPABias(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_setExtLNABiasON(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val);
unsigned char ADAR1000_setExtLNABiasOFF(unsigned char spi_channel, unsigned char chip_addr, unsigned char dac_val);
unsigned char ADAR1000_enableExtLNABias(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_disableExtLNABias(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_switchExtTRSWPOSNEG(unsigned char spi_channel, unsigned char chip_addr, unsigned char dir);
unsigned char ADAR1000_enableExtTRSW(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_disableExtTRSW(unsigned char spi_channel, unsigned char chip_addr);

unsigned char ADAR1000_switchExtTRPOL(unsigned char spi_channel, unsigned char chip_addr, unsigned char pol_dir);
unsigned char ADAR1000_enableExtTRPOL(unsigned char spi_channel, unsigned char chip_addr);
unsigned char ADAR1000_disableExtTRPOL(unsigned char spi_channel, unsigned char chip_addr);

#endif /* ADAR1000_H_ */
