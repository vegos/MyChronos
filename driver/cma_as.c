// *************************************************************************************************
//
//      Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
//
//
//        Redistribution and use in source and binary forms, with or without
//        modification, are permitted provided that the following conditions
//        are met:
//
//          Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//
//          Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the
//          distribution.
//
//          Neither the name of Texas Instruments Incorporated nor the names of
//          its contributors may be used to endorse or promote products derived
//          from this software without specific prior written permission.
//
//        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
//        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
//        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//        A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//        OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//        SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//        LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//        DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//        THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//        (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//        OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// *************************************************************************************************
// VTI CMA3000-D0x acceleration sensor driver functions
// *************************************************************************************************

// *************************************************************************************************
// Include section

// system
#include "project.h"

// logic
#include "simpliciti.h"

// driver
#include "cma_as.h"
#include "as.h"
#include "timer.h"
#include "display.h"

// *************************************************************************************************
// Prototypes section

// *************************************************************************************************
// Defines section

// =================================================================================================
// CMA3000-D0x acceleration sensor configuration
// =================================================================================================
// DCO frequency division factor determining speed of the acceleration sensor SPI interface
// Speed in Hz = 12MHz / AS_BR_DIVIDER (max. 500kHz)
#define CMA_AS_BR_DIVIDER    (30u)

// Acceleration measurement range in g
// Valid ranges are: 2 and 8
#define CMA_AS_RANGE         (2u)

// Sample rate for acceleration values in Hz
// Valid sample rates for 2g range are:     100, 400
// Valid sample rates for 8g range are: 40, 100, 400
#define CMA_AS_SAMPLE_RATE   (100u)

// *************************************************************************************************
// Global Variable section

// *************************************************************************************************
// Extern section


// *************************************************************************************************
// @fn          cma_as_start
// @brief       Power-up and initialize acceleration sensor
// @param       none
// @return      none
// *************************************************************************************************
void cma_as_start(void)
{
    volatile u16 Counter_u16;
    u8 bConfig;

    // Initialize SPI interface to acceleration sensor
    AS_SPI_CTL0 |= UCSYNC | UCMST | UCMSB        // SPI master, 8 data bits,  MSB first,
                   | UCCKPH;                     //  clock idle low, data output on falling
                                                 // edge
    AS_SPI_CTL1 |= UCSSEL1;                      // SMCLK as clock source
    AS_SPI_BR0 = CMA_AS_BR_DIVIDER;              // Low byte of division factor for baud rate
    AS_SPI_BR1 = 0x00;                           // High byte of division factor for baud
                                                 // rate
    AS_SPI_CTL1 &= ~UCSWRST;                     // Start SPI hardware

    // Configure interface pins
    as_start();

    // Configure sensor and start to sample data
#if (CMA_AS_RANGE == 2)
    bConfig = 0x80;
#    if (CMA_AS_SAMPLE_RATE == 100)
    bConfig |= 0x02;
#    elif (CMA_AS_SAMPLE_RATE == 400)
    bConfig |= 0x04;
#    else
#        error "Sample rate not supported"
#    endif
#elif (CMA_AS_RANGE == 8)
    bConfig = 0x00;
#    if (CMA_AS_SAMPLE_RATE == 40)
    bConfig |= 0x06;
#    elif (CMA_AS_SAMPLE_RATE == 100)
    bConfig |= 0x02;
#    elif (CMA_AS_SAMPLE_RATE == 400)
    bConfig |= 0x04;
#    else
#        error "Sample rate not supported"
#    endif
#else
#    error "Measurement range not supported"
#endif

    // Reset sensor
    cma_as_write_register(0x04, 0x02);
    cma_as_write_register(0x04, 0x0A);
    cma_as_write_register(0x04, 0x04);

    // Wait 5 ms before starting sensor output
    Timer0_A4_Delay(CONV_MS_TO_TICKS(5));

    // Set 2g measurement range, start to output data with 100Hz rate
    cma_as_write_register(0x02, bConfig);
}

// *************************************************************************************************
// @fn          cma_as_stop
// @brief       Power down acceleration sensor
// @param       none
// @return      none
// *************************************************************************************************
void cma_as_stop(void)
{
	as_stop();
}

// *************************************************************************************************
// @fn          cma_as_read_register
// @brief       Read a byte from the acceleration sensor
// @param       u8 bAddress             Register address
// @return      u8 0 or bResult         Register content
//                                      If the returned value is 0 there was an error.
// *************************************************************************************************
u8 cma_as_read_register(u8 bAddress)
{
    bAddress <<= 2;                              // Address to be shifted left by 2 and
                                                 // RW bit to be reset

    return as_read_register(bAddress);
}

// *************************************************************************************************
// @fn          cma_as_write_register
// @brief       Write a byte to the acceleration sensor
// @param       u8 bAddress             Register address
//              u8 bData                Data to write
// @return      u8 0 or bResult         Register content
//                                      If the returned value is 0 there was an error.
// *************************************************************************************************
u8 cma_as_write_register(u8 bAddress, u8 bData)
{
    bAddress <<= 2;                              // Address to be shifted left by 1
    bAddress |= BIT1;                            // RW bit to be set

    return as_write_register(bAddress, bData);
}

// *************************************************************************************************
// @fn          cma_as_get_data
// @brief       Service routine to read acceleration values.
// @param       none
// @return      none
// *************************************************************************************************
void cma_as_get_data(u8 * data)
{
    // Exit if sensor is not powered up
    if ((AS_PWR_OUT & AS_PWR_PIN) != AS_PWR_PIN)
        return;

    // Store X/Y/Z acceleration data in buffer
    *(data + 0) = cma_as_read_register(0x06);
    *(data + 1) = cma_as_read_register(0x07);
    *(data + 2) = cma_as_read_register(0x08);
}

