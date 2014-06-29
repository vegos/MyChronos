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
// VTI SCP1000-D0x pressure sensor driver functions
// *************************************************************************************************

// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "cma_ps.h"
#include "ps.h"
#include "timer.h"

// *************************************************************************************************
// Prototypes section
u16 cma_ps_read_register(u8 address, u8 mode);
u8 cma_ps_write_register(u8 address, u8 data);

// *************************************************************************************************
// Defines section

// *************************************************************************************************
// Global Variable section

// *************************************************************************************************
// Extern section

// *************************************************************************************************
// @fn          cma_ps_init
// @brief       Init pressure sensor I/O
// @param       none
// @return      none
// *************************************************************************************************
void cma_ps_init(void)
{
    volatile u8 success, status, eeprom, timeout;

    ps_init();

    // Reset pressure sensor -> powerdown sensor
    success = cma_ps_write_register(0x06, 0x01);

    // 100msec delay
    Timer0_A4_Delay(CONV_MS_TO_TICKS(100));

    // Check if STATUS register BIT0 is cleared
    status = cma_ps_read_register(0x07, PS_I2C_8BIT_ACCESS);
    if (((status & BIT0) == 0) && (status != 0))
    {
        // Check EEPROM checksum in DATARD8 register
        eeprom = cma_ps_read_register(0x7F, PS_I2C_8BIT_ACCESS);
        if (eeprom == 0x01)
            ps_ok = 1;
        else
            ps_ok = 0;
    }
}

// *************************************************************************************************
// @fn          cma_ps_start
// @brief       Init pressure sensor registers and start sampling
// @param       none
// @return      u8                      1=Sensor started, 0=Sensor did not start
// *************************************************************************************************
void cma_ps_start(void)
{
    // Start sampling data in ultra low power mode
    cma_ps_write_register(0x03, 0x0B);
}

// *************************************************************************************************
// @fn          cma_ps_stop
// @brief       Power down pressure sensor
// @param       none
// @return      none
// *************************************************************************************************
void cma_ps_stop(void)
{
    // Put sensor to standby
    cma_ps_write_register(0x03, 0x00);
}

// *************************************************************************************************
// @fn          cma_ps_write_register
// @brief       Write a byte to the pressure sensor
// @param       u8 address              Register address
//              u8 data                 Data to write
// @return      u8
// *************************************************************************************************
u8 cma_ps_write_register(u8 address, u8 data)
{
	return ps_write_register(0x11 << 1, address, data);
}

// *************************************************************************************************
// @fn          cma_ps_read_register
// @brief       Read a byte from the pressure sensor
// @param       u8 address              Register address
//              u8 mode                 PS_TWI_8BIT_ACCESS, PS_TWI_16BIT_ACCESS
// @return      u16                     Register content
// *************************************************************************************************
u16 cma_ps_read_register(u8 address, u8 mode)
{
	return ps_read_register(0x11 << 1, address, mode);
}

// *************************************************************************************************
// @fn          cma_ps_get_pa
// @brief       Read out pressure. Format is Pa. Range is 30000 .. 120000 Pa.
// @param       none
// @return      u32                     15-bit pressure sensor value (Pa)
// *************************************************************************************************
u32 cma_ps_get_pa(void)
{
    volatile u32 data = 0;

    // Get 3 MSB from DATARD8 register
    data = cma_ps_read_register(0x7F, PS_I2C_8BIT_ACCESS);
    data = ((data & 0x07) << 8) << 8;

    // Get 16 LSB from DATARD16 register
    data |= cma_ps_read_register(0x80, PS_I2C_16BIT_ACCESS);

    // Convert decimal value to Pa
    data = (data >> 2);

    return (data);
}

// *************************************************************************************************
// @fn          cma_ps_get_temp
// @brief       Read out temperature.
// @param       none
// @return      u16                     13-bit temperature value in xx.x K format
// *************************************************************************************************
u16 cma_ps_get_temp(void)
{
    volatile u16 data = 0;
    u16 temp = 0;
    u8 is_negative = 0;
    u16 kelvin;

    // Get 13 bit from TEMPOUT register
    data = cma_ps_read_register(0x81, PS_I2C_16BIT_ACCESS);

    // Convert negative temperatures
    if ((data & BIT(13)) == BIT(13))
    {
        // Sign extend temperature
        data |= 0xC000;
        // Convert two's complement
        data = ~data;
        data += 1;
        is_negative = 1;
    }

    temp = data / 2;

    // Convert from °C to K
    if (is_negative)
        kelvin = 2732 - temp;
    else
        kelvin = temp + 2732;

    return (kelvin);
}

