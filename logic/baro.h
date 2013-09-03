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

#ifndef BARO_H_
#define BARO_H_

// *************************************************************************************************
// Include section

// *************************************************************************************************
// Prototypes section
extern u8 is_barometer_measurement(void);
extern void start_barometer_measurement(void);
extern void stop_barometer_measurement(void);
extern void do_barometer_measurement(u8 filter);

// menu functions
extern void display_barometer(u8 line, u8 update);

// *************************************************************************************************
// Defines section
#define BAROMETER_MEASUREMENT_TIMEOUT    (1 * 60u) // Stop barometer measurement after 1 minute to
                                                   // save battery

// *************************************************************************************************
// Global Variable section
struct baro
{
    menu_t state;                                  // MENU_ITEM_NOT_VISIBLE, MENU_ITEM_VISIBLE
    u32 pressure;                                  // Pressure (Pa)
    s16 barometer;                                  // Altitude (m)
    s16 barometer_offset;                           // Altitude offset stored during calibration
    u16 timeout;                                   // Timeout
};
extern struct baro sBaro;

// *************************************************************************************************
// Extern section

#endif                                             /*ALTITUDE_H_ */
