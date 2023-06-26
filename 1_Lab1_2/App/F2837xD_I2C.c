//###########################################################################
//
// FILE:   F2837xD_I2C.c
//
// TITLE:  F2837xD I2C Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2837xD Support Library v190 $
// $Release Date: Mon Feb  1 16:51:57 CST 2016 $
// $Copyright: Copyright (C) 2013-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "F2837xD_device.h"     // F2837xD Headerfile Include File
#include "F2837xD_Examples.h"   // F2837xD Examples Include File


//---------------------------------------------------------------------------
// Example: I2cAGpioConfig(), I2cBGpioConfig()
//---------------------------------------------------------------------------
// These functions configures GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

#ifdef CPU1
//************************************************************************************
// 'I2caDataClkPin' should be assign with one of the possible I2C_A SDA - SDL GPIO pin
// Use defined Macros from "F2837xD_I2c_defines.h" for  assignment
//************************************************************************************
void I2cAGpioConfig(Uint16 I2caDataClkPin)
{
	EALLOW;

	switch(I2caDataClkPin)
	{
		case I2C_A_GPIO0_GPIO1:
			/* Enable internal pull-up for the selected I2C pins */
			GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;     // Enable pull-up for GPIO0 (SDAA)
			GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;     // Enable pull-up for GPIO1 (SDLA)
		
			/* Set qualification for the selected I2C pins */
			GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 3;   // Async/no qualification (I/ps sync
			GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 3;   // to SYSCLKOUT by default)

			/* Configure which of the possible GPIO pins will be I2C_A pins using GPIO regs*/
			GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 1;    // Configure GPIO0 for SDAA operation
			GpioCtrlRegs.GPAMUX1.bit.GPIO0  = 2;    // Configure GPIO0 for SDAA operation
		
			GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 1;    // Configure GPIO1 for SDLA operation
			GpioCtrlRegs.GPAMUX1.bit.GPIO1  = 2;    // Configure GPIO1 for SDLA operation
	
			break;
		
		
		case I2C_A_GPIO32_GPIO33:
			/* Enable internal pull-up for the selected I2C pins */
			GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;
			GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;
			
			/* Set qualification for the selected I2C pins */
			GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;
			GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;
			
			/* Configure which of the possible GPIO pins will be I2C_A pins using GPIO regs*/
			GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;
			GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;

			// ADD
			GpioCtrlRegs.GPBPUD.bit.GPIO34 	= 1;  // Enable pullup on GPIO34
			GpioDataRegs.GPBSET.bit.GPIO34	= 1;  // Set High
			GpioCtrlRegs.GPBMUX1.bit.GPIO34 	= 0;  // GPIO34 = GPIO
			GpioCtrlRegs.GPBDIR.bit.GPIO34 	= 1;  // GPIO34 = Output

			break;
			
		case I2C_A_GPIO42_GPIO43:
			/* Enable internal pull-up for the selected I2C pins */
			
			/* Set qualification for the selected I2C pins */
			
			/* Configure which of the possible GPIO pins will be I2C_A pins using GPIO regs*/
			break;
			
		case I2C_A_GPIO91_GPIO92:
			/* Enable internal pull-up for the selected I2C pins */
			GpioCtrlRegs.GPCPUD.bit.GPIO91 = 0;
			GpioCtrlRegs.GPCPUD.bit.GPIO92 = 0;
			
			/* Set qualification for the selected I2C pins */
	   		GpioCtrlRegs.GPCQSEL2.bit.GPIO91 = 3;
	   		GpioCtrlRegs.GPCQSEL2.bit.GPIO92 = 3;
			
			/* Configure which of the possible GPIO pins will be I2C_A pins using GPIO regs*/

	   		GpioCtrlRegs.GPCGMUX2.bit.GPIO91 = 1;	GpioCtrlRegs.GPCMUX2.bit.GPIO91 = 2;
	   		GpioCtrlRegs.GPCGMUX2.bit.GPIO92 = 1;	GpioCtrlRegs.GPCMUX2.bit.GPIO92 = 2;
			break;
			
		case I2C_A_GPIO63104_GPIO105:
			/* Enable internal pull-up for the selected I2C pins */
			
			/* Set qualification for the selected I2C pins */
			
			/* Configure which of the possible GPIO pins will be I2C_A pins using GPIO regs*/
			break;

		default:
			
			break;
			
	} // End of Switch
	EDIS;
	I2CA_Init();
} //////////// End of I2cAGpioConfig ///////////////////////////////////////

//************************************************************************************
// 'I2cbDataClkPin' should be assign with one of the possible I2C_B SDA - SDL GPIO pin
// Use defined Macros from "F2837xD_I2c_defines.h" for assignment
//************************************************************************************
void I2cBGpioConfig(Uint16 I2cbDataClkPin)
{
	EALLOW;

	switch(I2cbDataClkPin)
	{
		case I2C_B_GPIO2_GPIO3:
			/* Enable internal pull-up for the selected I2C pins */
			GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;     // Enable pull-up for GPIO0 (SDAB)
			GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;     // Enable pull-up for GPIO1 (SDLB)
		
			/* Set qualification for the selected I2C pins */
			GpioCtrlRegs.GPAQSEL1.bit.GPIO2 = 3;   // Async/no qualification (I/ps sync
			GpioCtrlRegs.GPAQSEL1.bit.GPIO3 = 3;   // to SYSCLKOUT by default)

			/* Configure which of the possible GPIO pins will be I2C_B pins using GPIO regs*/
			GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 1;    // Configure GPIO0 for SDAB operation
			GpioCtrlRegs.GPAMUX1.bit.GPIO2  = 2;    // Configure GPIO0 for SDAB operation
		
			GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 1;    // Configure GPIO1 for SDLB operation
			GpioCtrlRegs.GPAMUX1.bit.GPIO3  = 2;    // Configure GPIO1 for SDLB operation
			
			break;

		case I2C_B_GPIO134_GPIO35:
			/* Enable internal pull-up for the selected I2C pins */

			/* Set qualification for the selected I2C pins */

			/* Configure which of the possible GPIO pins will be I2C_B pins using GPIO regs*/
			break;

		case I2C_B_GPIO40_GPIO41:
			/* Enable internal pull-up for the selected I2C pins */

			/* Set qualification for the selected I2C pins */

			/* Configure which of the possible GPIO pins will be I2C_B pins using GPIO regs*/
			break;

		case I2C_B_GPIO66_GPIO69:
			/* Enable internal pull-up for the selected I2C pins */
			GpioCtrlRegs.GPCPUD.bit.GPIO66 = 0;	//SDAB
			GpioCtrlRegs.GPCPUD.bit.GPIO69 = 0;	//SCLB

			/* Set qualification for the selected I2C pins */
			GpioCtrlRegs.GPCQSEL1.bit.GPIO66 = 3;
			GpioCtrlRegs.GPCQSEL1.bit.GPIO69 = 3;

			/* Configure which of the possible GPIO pins will be I2C_B pins using GPIO regs*/
			GpioCtrlRegs.GPCGMUX1.bit.GPIO66 = 1;	//0x6
			GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 2;

			GpioCtrlRegs.GPCGMUX1.bit.GPIO69 = 1;	//0x6
			GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 2;
			break;

		default:
			break;

	}
	EDIS;
}
//////////// End of I2cBGpioConfig///////////////////////////////////////

void I2CA_Init(void)
{
	// Initialize I2C interface
	// Put I2C module in the reset state
	I2caRegs.I2CMDR.bit.IRS = 0;

	// Set Slave Address according to AT24C16 device
	I2caRegs.I2CSAR.all = 0x0050;

	// Set I2C module clock input
	I2caRegs.I2CPSC.all = 14; // need 7-12 Mhz on module clk (150/15 = 10MHz)

	// 400KHz clock speed in SCL for master mode(2.5us period)
	// Clock Pulse Width Low  : 1.5us
	// Clock Pulse Width High : 1.0us
	// F28335의 I2C User Guide에서 Master Clock 주기를 구하는 공식을 참조바람.
	I2caRegs.I2CCLKL = 10;
	I2caRegs.I2CCLKH = 5;

	// Disable I2C interrupt
	I2caRegs.I2CIER.all = 0x0;

	// Enable TX and RX FIFO in I2C module
	I2caRegs.I2CFFTX.all = 0x6000; // Enable FIFO mode and TXFIFO
	I2caRegs.I2CFFRX.all = 0x2040; // Enable RXFIFO, clear RXFFINT

	// Enable I2C module
	I2caRegs.I2CMDR.all = 0x20;
}

#pragma CODE_SECTION(Write_EEPROM_Data, "ramfuncs");
void Write_EEPROM_Data(int16 uCSBit, int16 uAddr, int16 uData)
{
    Uint16 uSlaveAddr;

	nWP_DISABLE;							// WP = 0;

	uSlaveAddr = 0x50 | (uCSBit & 0x07);

	// Wait until the STP bit is cleared from any previous master communication.
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Wait until bus-free status
	while(I2caRegs.I2CSTR.bit.BB == 1);


	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 3;

	// Setup data to send
	I2caRegs.I2CDXR.all = (uAddr >> 8) & 0x0ff; // Address High Byte
	I2caRegs.I2CDXR.all = uAddr & 0x0ff;        // Address Low Byte
	I2caRegs.I2CDXR.all = uData;		        // Write Data

	// Send start as master transmitter with STT(=1), STP(=1), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6E20;

	// Wait until STOP condition is detected and clear STOP condition bit
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;

	// Wait the Write-Cycle Time for EEPROM
	// refer to 24LC512 datasheet
	//delay_ms(5);
	DELAY_US(2);
	nWP_ENABLE;
}
void Read_EEPROM_Data(int16 uCSBit, int16 uAddr, int16 *pData)
{
    Uint16 uSlaveAddr;

	uSlaveAddr = 0x50 | (uCSBit & 0x07);

	// Wait until the STP bit is cleared from any previous master communication.
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Wait until bus-free status
	while(I2caRegs.I2CSTR.bit.BB == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 2;

	// Setup data to send
	I2caRegs.I2CDXR.all = (uAddr >> 8) & 0x0ff; // Address High Byte
	I2caRegs.I2CDXR.all = uAddr & 0x0ff;        // Address Low Byte

	// Send start as master transmitter with FREE(=1), STT(=1), STP(=0), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6620;

	// Wait until ARDY status bit is set
	while(I2caRegs.I2CSTR.bit.ARDY == 0);

	// Wait until the STP bit is cleared
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to read
	I2caRegs.I2CCNT = 1;

	// Send start as master receiver with FREE(=1), STT(=1), STP(=1), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6C20;

	// Wait until STOP condition is detected and clear STOP condition bit
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;

	*pData = (BYTE)(I2caRegs.I2CDRR.all & 0xff);
}

void SevenWordWrite_EEPROM_Data(int16 uCSBit, int16 uStartAddr, int16 *pDataWordArray, int16 uDataWordSize)
{
    Uint16 uSlaveAddr, i;

	nWP_DISABLE;							// WP = 0;


	uSlaveAddr = 0x50 | (uCSBit & 0x07);

	// Wait until the STP bit is cleared from any previous master communication.
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Wait until bus-free status
	while(I2caRegs.I2CSTR.bit.BB == 1);


	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 2*uDataWordSize + 2;

	// Setup data to send
	//while(I2caRegs.I2CFFTX.bit.TXFFST != 0);         // TXFIFO empty?
	I2caRegs.I2CDXR.all = ((2*uStartAddr) >> 8) & 0x0ff; // Address High Byte
	I2caRegs.I2CDXR.all = (2*uStartAddr) & 0x0ff;        // Address Low Byte
	for (i=0; i<uDataWordSize; i++)
	{
		I2caRegs.I2CDXR.all= (*(pDataWordArray+i))&0xff;
		I2caRegs.I2CDXR.all= (*(pDataWordArray+i))>>8;
	}

	// Send start as master transmitter with STT(=1), STP(=1), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6E20;

	// Wait until STOP condition is detected and clear STOP condition bit
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;

	// Wait the Write-Cycle Time for EEPROM
	// refer to 24LC512 datasheet
	DELAY_US(5);
	nWP_ENABLE;
}

// #pragma CODE_SECTION(SevenWordRead_EEPROM_Data, "ramfuncs");
void SevenWordRead_EEPROM_Data(int16 uCSBit, int16 uStartAddr, int16 *pDataWordArray, int16 uDataWordSize)
{
    Uint16 uSlaveAddr, i;

	uSlaveAddr = 0x50 | (uCSBit & 0x07);

	// Wait until the STP bit is cleared from any previous master communication.
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Wait until bus-free status
	while(I2caRegs.I2CSTR.bit.BB == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 2;   // 2

	// Setup data to send
	I2caRegs.I2CDXR.all = ((2*uStartAddr) >> 8) & 0x0ff; // Address High Byte
	I2caRegs.I2CDXR.all = (2*uStartAddr) & 0x0ff;        // Address Low Byte

	// Send start as master transmitter with FREE(=1), STT(=1), STP(=0), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6620;

	// Wait until ARDY status bit is set
	while(I2caRegs.I2CSTR.bit.ARDY == 0);

	// Wait until the STP bit is cleared
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to read
	I2caRegs.I2CCNT = 2*uDataWordSize;

	// Send start as master receiver with FREE(=1), STT(=1), STP(=1), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6C20;

	// Wait until STOP condition is detected and clear STOP condition bit
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;

	for (i=0; i<uDataWordSize; i++) {
	    Uint16 lo, hi;
	    lo = (I2caRegs.I2CDRR.all & 0xff);
		hi = (I2caRegs.I2CDRR.all & 0xff);
		*(pDataWordArray + i) = lo + (hi << 8);
	}
}


//// RTC

// Initialize I2C for serial RTC(DS1307) access
void Change_I2C_RTC(void)
{
	// Set Slave Address according to DS1307 device
	I2caRegs.I2CSAR.all = 0x0068;

	// Set I2C module clock input
	// I2caRegs.I2CPSC.all = 14; // need 7-12 Mhz on module clk (150/15 = 10MHz)

	// 100KHz clock speed in SCL for master mode(10us period)
	// Clock Pulse Width Low  : 4.9us
	// Clock Pulse Width High : 4.1us
	// F28335의 I2C User Guide에서 Master Clock 주기를 구하는 공식을 참조바람.
	I2caRegs.I2CCLKL = 49;
	I2caRegs.I2CCLKH = 41;
}

void Recover_I2C_EEPROM(void)
{
	// Set Slave Address according to 24LC512 device
	I2caRegs.I2CSAR.all = 0x0050;

	// Set I2C module clock input
	// I2caRegs.I2CPSC.all = 14; // need 7-12 Mhz on module clk (150/15 = 10MHz)

	// 400KHz clock speed in SCL for master mode(2.5us period)
	// Clock Pulse Width Low  : 1.5us
	// Clock Pulse Width High : 1us
	// F28335의 I2C User Guide에서 Master Clock 주기를 구하는 공식을 참조바람.
	I2caRegs.I2CCLKL = 15;
	I2caRegs.I2CCLKH = 10;
}

// refer to single byte write mode of DS1307
void Write_RTC_Data(Uint16 uAddr, Uint16 uData)
{
	Uint16 uSlaveAddr;

	uSlaveAddr = 0x68;

	// Wait until the STP bit is cleared from any previous master communication.
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Wait until bus-free status
	while(I2caRegs.I2CSTR.bit.BB == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 2;

	// Setup data to send
	I2caRegs.I2CDXR.all = uAddr & 0x0ff;        // Address
	I2caRegs.I2CDXR.all = uData;		        // Write Data

	// Send start as master transmitter with STT(=1), STP(=1), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6E20;

	// Wait until STOP condition is detected and clear STOP condition bit
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;

	// Wait the Write-Cycle Time for DS1307
	// refer to DS1307 datasheet
	DELAY_US(1);
}

// refer to single byte random read mode of DS1307
void Read_RTC_Data(Uint16 uAddr, Uint16 *pData)
{
    Uint16 uSlaveAddr;

	uSlaveAddr = 0x68;

	// Wait until the STP bit is cleared from any previous master communication.
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Wait until bus-free status
	while(I2caRegs.I2CSTR.bit.BB == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to send
	I2caRegs.I2CCNT = 1;

	// Setup data to send
	I2caRegs.I2CDXR.all = uAddr & 0x0ff;        // Address

	// Send start as master transmitter with FREE(=1), STT(=1), STP(=0), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6620;

	// Wait until ARDY status bit is set
	while(I2caRegs.I2CSTR.bit.ARDY == 0);

	// Wait until the STP bit is cleared
	while(I2caRegs.I2CMDR.bit.STP == 1);

	// Set Device(Slave) Address
	I2caRegs.I2CSAR.all = uSlaveAddr;

	// Setup number of bytes to read
	I2caRegs.I2CCNT = 1;

	// Send start as master receiver with FREE(=1), STT(=1), STP(=1), XA(=0), RM(=0)
	I2caRegs.I2CMDR.all = 0x6C20;

	// Wait until STOP condition is detected and clear STOP condition bit
	while(I2caRegs.I2CSTR.bit.SCD == 0);
	I2caRegs.I2CSTR.bit.SCD = 1;

	*pData = (BYTE)(I2caRegs.I2CDRR.all & 0xff);
}


#endif


//===========================================================================
// End of file.
//===========================================================================
