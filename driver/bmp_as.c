// *************************************************************************************************
//
//	Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
//	 
//	 
//	  Redistribution and use in source and binary forms, with or without 
//	  modification, are permitted provided that the following conditions 
//	  are met:
//	
//	    Redistributions of source code must retain the above copyright 
//	    notice, this list of conditions and the following disclaimer.
//	 
//	    Redistributions in binary form must reproduce the above copyright
//	    notice, this list of conditions and the following disclaimer in the 
//	    documentation and/or other materials provided with the   
//	    distribution.
//	 
//	    Neither the name of Texas Instruments Incorporated nor the names of
//	    its contributors may be used to endorse or promote products derived
//	    from this software without specific prior written permission.
//	
//	  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//	  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//	  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//	  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//	  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//	  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//	  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//	  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//	  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//	  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//	  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// Bosch BMA250 acceleration sensor driver functions
// *************************************************************************************************


// *************************************************************************************************
// Include section

// system
#include "project.h"

// logic
#include "simpliciti.h"

// driver
#include "bmp_as.h"
#include "as.h"
#include "timer.h"
#include "display.h"


// *************************************************************************************************
// Prototypes section

// *************************************************************************************************
// Defines section

// =================================================================================================
// BMA250 acceleration sensor configuration
// =================================================================================================
// DCO frequency division factor determining speed of the acceleration sensor SPI interface
// Speed in Hz = 12MHz / AS_BR_DIVIDER (max. 10MHz)
#define BMP_AS_BR_DIVIDER  (2u)

// Acceleration measurement range in g
// Valid ranges are: 2, 4, 8, 16 
#define BMP_AS_RANGE       (2u)

// Use in-sensor filtering
// unfiltered data is always sampled at 2kHz
#define BMP_AS_FILTERING

// Bandwidth for filtered acceleration data in Hz (Sampling rate is twice the bandwidth)
// Valid bandwidths are: 8, 16, 31, 63, 125, 250, 500, 1000
#define BMP_AS_BANDWIDTH   (63u)

// Sleep phase duration in ms
// Valid sleep phase durations are: 1, 2, 4, 6, 10, 25, 50
#define BMP_AS_SLEEPPHASE   (6u)


// *************************************************************************************************
// Global Variable section

// *************************************************************************************************
// Extern section


// *************************************************************************************************
// @fn          bmp_as_start
// @brief       Power-up and initialize acceleration sensor
// @param       none
// @return      none
// *************************************************************************************************
void bmp_as_start(void)
{
	u8 bGRange;                                  // g Range;
	u8 bBwd;                                     // Bandwidth
	u8 bSleep;                                   // Sleep phase
	
	// Initialize SPI interface to acceleration sensor
	AS_SPI_CTL0 |= UCSYNC | UCMST | UCMSB        // SPI master, 8 data bits,  MSB first,
	               | UCCKPH;                     //  clock idle low, data output on falling edge
	AS_SPI_CTL1 |= UCSSEL1;                      // SMCLK as clock source
	AS_SPI_BR0   = BMP_AS_BR_DIVIDER;            // Low byte of division factor for baud rate
	AS_SPI_BR1   = 0x00;                         // High byte of division factor for baud rate
	AS_SPI_CTL1 &= ~UCSWRST;                     // Start SPI hardware
  
    // Configure interface pins
    as_start();
	
	// Configure sensor and start to sample data
#if (BMP_AS_RANGE == 2)
	bGRange = 0x03;
#elif (BMP_AS_RANGE == 4)
	bGRange = 0x05;
#elif (BMP_AS_RANGE == 8)
	bGRange = 0x08;
#elif (BMP_AS_RANGE == 16)
	bGRange = 0x0C;
#else
	#error "Measurement range not supported"
#endif
  
#if (BMP_AS_BANDWIDTH == 8)
	bBwd = 0x08;
#elif (BMP_AS_BANDWIDTH == 16)
	bBwd = 0x09;
#elif (BMP_AS_BANDWIDTH == 31)
	bBwd = 0x0A;
#elif (BMP_AS_BANDWIDTH == 63)
	bBwd = 0x0B;
#elif (BMP_AS_BANDWIDTH == 125)
	bBwd = 0x0C;
#elif (BMP_AS_BANDWIDTH == 250)
	bBwd = 0x0D;
#elif (BMP_AS_BANDWIDTH == 500)
	bBwd = 0x0E;
#elif (BMP_AS_BANDWIDTH == 1000)
	bBwd = 0x0F;
#else
	#error "Sample rate not supported"
#endif
	
#if (BMP_AS_SLEEPPHASE == 1)
	bSleep = 0x4C;
#elif (BMP_AS_SLEEPPHASE == 2)
	bSleep = 0x4E;
#elif (BMP_AS_SLEEPPHASE == 4)
	bSleep = 0x50;
#elif (BMP_AS_SLEEPPHASE == 6)
	bSleep = 0x52;
#elif (BMP_AS_SLEEPPHASE == 10)
	bSleep = 0x54;
#elif (BMP_AS_SLEEPPHASE == 25)
	bSleep = 0x56;
#elif (BMP_AS_SLEEPPHASE == 50)
	bSleep = 0x58;
#else
	#error "Sleep phase duration not supported"
#endif

	// write sensor configuration
	bmp_as_write_register(BMP_GRANGE, bGRange);  // Set measurement range
	bmp_as_write_register(BMP_BWD, bBwd);        // Set filter bandwidth
	bmp_as_write_register(BMP_PM, bSleep);       // Set filter bandwidth


#ifndef BMP_AS_FILTERING
	bmp_as_write_register(BMP_SCR, 0x80);        // acquire unfiltered acceleration data
#endif
	// configure sensor interrupt
	bmp_as_write_register(BMP_IMR2, 0x01);       // map new data interrupt to INT1 pin
	bmp_as_write_register(BMP_ISR2, 0x10);       // enable new data interrupt
	
	// enable CC430 interrupt pin for data read out from acceleration sensor
	AS_INT_IFG &= ~AS_INT_PIN;                   // Reset flag
	AS_INT_IE  |=  AS_INT_PIN;                   // Enable interrupt
}



// *************************************************************************************************
// @fn          bmp_as_stop
// @brief       Power down acceleration sensor
// @param       none
// @return      none
// *************************************************************************************************
void bmp_as_stop(void)
{
	as_stop();
}


// *************************************************************************************************
// @fn          bmp_as_read_register
// @brief       Read a byte from the acceleration sensor
// @param       u8 bAddress		        Register address
// @return      u8					    Register content
// *************************************************************************************************
u8 bmp_as_read_register(u8 bAddress)
{
  bAddress |= BIT7;                   // set R/W bit for reading

  return as_read_register(bAddress);
}

// *************************************************************************************************
// @fn          bmp_as_write_register
// @brief  		Write a byte to the acceleration sensor
// @param       u8 bAddress		        Register address
//				u8 bData			    Data to write
// @return      u8					
// *************************************************************************************************
u8 bmp_as_write_register(u8 bAddress, u8 bData)
{
  bAddress &= ~BIT8;                   // R/W bit to be not set
  
  return as_write_register(bAddress, bData);
}


// *************************************************************************************************
// @fn          bmp_as_get_data
// @brief       Service routine to read acceleration values.
// @param       none
// @return      none
// *************************************************************************************************
void bmp_as_get_data(u8 * data)
{
	// Exit if sensor is not powered up
	if ((AS_PWR_OUT & AS_PWR_PIN) != AS_PWR_PIN) return;
  
  	// Dummy read LSB from LSB acceleration data to update MSB (BMA250 datasheet 4.4.1)
  	*(data+1) = bmp_as_read_register(BMP_ACC_X_LSB);
	*(data+0) = bmp_as_read_register(BMP_ACC_Y_LSB);
	*(data+2) = bmp_as_read_register(BMP_ACC_Z_LSB);
  	// Store X/Y/Z MSB acceleration data in buffer
	*(data+1) = bmp_as_read_register(BMP_ACC_X_MSB);
	*(data+0) = bmp_as_read_register(BMP_ACC_Y_MSB);
	*(data+2) = bmp_as_read_register(BMP_ACC_Z_MSB);
}


