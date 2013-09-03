// *************************************************************************************************
// Include section

// system
#include "project.h"

// driver
#include "baro.h"
#include "display.h"
#include "display.h"
#include "ps.h"
#include "bmp_ps.h"
#include "cma_ps.h"
#include "ports.h"
#include "timer.h"

// logic
#include "user.h"

// *************************************************************************************************
// Defines section

// *************************************************************************************************
// Global Variable section
struct baro sBaro;

// *************************************************************************************************
// Extern section



// *************************************************************************************************
// @fn          is_barometer_measurement
// @brief       Altitude measurement check
// @param       none
// @return      u8              1=Measurement ongoing, 0=measurement off
// *************************************************************************************************
u8 is_barometer_measurement(void)
{
    return ((sBaro.state == MENU_ITEM_VISIBLE) && (sBaro.timeout > 0));
}

// *************************************************************************************************
// @fn          start_barometer_measurement
// @brief       Start barometer measurement
// @param       none
// @return      none
// *************************************************************************************************
void start_barometer_measurement(void)
{
    // Show warning if pressure sensor was not initialised properly
    if (!ps_ok)
    {
        display_chars(LCD_SEG_L1_2_0, (u8 *) "ERR", SEG_ON);
        return;
    }

    // Start barometer measurement if timeout has elapsed
    if (sBaro.timeout == 0)
    {
        // Enable EOC IRQ on rising edge
    	PS_INT_IFG &= ~PS_INT_PIN;
    	PS_INT_IE |= PS_INT_PIN;

        // Start pressure sensor
    	if (bmp_used)
    	{
            bmp_ps_start();
    	}
    	else
    	{
            cma_ps_start();
    	}

        // Set timeout counter only if sensor status was OK
        sBaro.timeout = BAROMETER_MEASUREMENT_TIMEOUT;

        // Get updated barometer
        while ((PS_INT_IN & PS_INT_PIN) == 0) ;
        do_barometer_measurement(FILTER_OFF);
    }
}

// *************************************************************************************************
// @fn          stop_barometer_measurement
// @brief       Stop barometer measurement
// @param       none
// @return      none
// *************************************************************************************************
void stop_barometer_measurement(void)
{
    // Return if pressure sensor was not initialised properly
    if (!ps_ok)
        return;

    // Stop pressure sensor
	if (bmp_used)
	{
        bmp_ps_stop();
	}
	else
	{
        cma_ps_stop();
	}

    // Disable DRDY IRQ
    PS_INT_IE &= ~PS_INT_PIN;
    PS_INT_IFG &= ~PS_INT_PIN;

    // Clear timeout counter
    sBaro.timeout = 0;
}

// *************************************************************************************************
// @fn          do_barometer_measurement
// @brief       Perform single barometer measurement
// @param       u8 filter       Filter option
// @return      none
// *************************************************************************************************
void do_barometer_measurement(u8 filter)
{
    volatile u32 pressure;

    // If sensor is not ready, skip data read
    if ((PS_INT_IN & PS_INT_PIN) == 0)
        return;

    // Get pressure (format is 1Pa) from sensor
	if (bmp_used)
	{
	    // Start sampling data in ultra low power mode
	    bmp_ps_write_register(BMP_085_CTRL_MEAS_REG, BMP_085_P_MEASURE);
	    // Get updated barometer
	    while ((PS_INT_IN & PS_INT_PIN) == 0) ;

	    pressure = bmp_ps_get_pa();
	}
	else
	{
        pressure = cma_ps_get_pa();
	}

	sBaro.pressure = pressure * 0.01;
}


// *************************************************************************************************
// @fn          display_barometer
// @brief       Display routine. Supports display in meters and feet.
// @param       u8 line                 LINE1
//                              u8 update               DISPLAY_LINE_UPDATE_FULL,
// DISPLAY_LINE_UPDATE_PARTIAL, DISPLAY_LINE_CLEAR
// @return      none
// *************************************************************************************************
void display_barometer(u8 line, u8 update)
{
    u8 *str;

    // redraw whole screen
    if (update == DISPLAY_LINE_UPDATE_FULL)
    {
        // Enable pressure measurement
        sBaro.state = MENU_ITEM_VISIBLE;

        // Start measurement
        start_barometer_measurement();

        display_symbol(LCD_UNIT_L1_M, SEG_OFF);
        display_symbol(LCD_UNIT_L1_FT, SEG_OFF);
        // Display barometer
        display_barometer(LINE1, DISPLAY_LINE_UPDATE_PARTIAL);
    }
    else if (update == DISPLAY_LINE_UPDATE_PARTIAL)
    {
        // Update display only while measurement is active
//        if (sBaro.timeout > 0)
//        {
            // Display barometer in xxxx m format, allow 3 leading blank digits
        	str = int_to_array(sBaro.pressure, 4, 3);
            display_symbol(LCD_SYMB_ARROW_UP, SEG_OFF);
            display_symbol(LCD_SYMB_ARROW_DOWN, SEG_OFF);
            display_chars(LCD_SEG_L1_3_0, str, SEG_ON);
//        }
    }
    else if (update == DISPLAY_LINE_CLEAR)
    {
        // Disable pressure measurement
        sBaro.state = MENU_ITEM_NOT_VISIBLE;

        // Stop measurement
        stop_barometer_measurement();

        // Clean up function-specific segments before leaving function
        display_symbol(LCD_UNIT_L1_M, SEG_OFF);
        display_symbol(LCD_UNIT_L1_FT, SEG_OFF);
        display_symbol(LCD_SYMB_ARROW_UP, SEG_OFF);
        display_symbol(LCD_SYMB_ARROW_DOWN, SEG_OFF);
    }
}
