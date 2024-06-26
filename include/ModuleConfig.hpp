#ifndef MODULE_CONFIG_HPP
#define MODULE_CONFIG_HPP

/*
    Global configuration settings for the clock module (this device).
*/

/* Global configuration section */

#define USE_SERIAL

#define STATE_MACHINE_UPDATE_TIME_INTERVAL_MS 35

/* Keyboard configuration section */

#define BUTTON_BACK_IO_LINE 12
#define BUTTON_UP_IO_LINE 11
#define BUTTON_DOWN_IO_LINE 13
#define BUTTON_NEXT_IO_LINE 0

/* LCD configuration section */

#define LCD_MAX_COLS 16U
#define LCD_MAX_ROWS 2U

#define LCD_TIME_VIEW_UPDATE_INTERVAL_MS 500U

#define RS_IO_LINE 7U
#define EN_IO_LINE 6U
#define D4_IO_LINE 5U
#define D5_IO_LINE 4U
#define D6_IO_LINE 3U
#define D7_IO_LINE 2U

/* RCT configuration section */
#define DAT_IO 9
#define CLK 10
#define RST_CE 8

/* PFC IO ports expander*/
#define PFC_I2C_ADDRESS 0x20

/* Views configuration section */
#define VIEW_ID_CONFIRMATION_VIEW 0
#define VIEW_ID_DATE_SETUP_VIEW 1
#define VIEW_ID_MENU_VIEW 2
#define VIEW_ID_TIME_SETUP_VIEW 3
#define VIEW_ID_TIME_VIEW 4
#define VIEW_ID_LINES_STATUS_VIEW 5
#define VIEW_ID_LINE_SETTINGS_VIEW 6

#define MAX_VIEWS_COUNT 7

/* Alarms configuration, do not exceed, may not work then*/

/// Start with small values, for example 1 and 1 then increase
/// till device stop work - usually there is no display at power up.
/// When device fails, decrease ALARMS_NO_OF_LINES or ALARMS_NO_OF_CYCLES_PER_LINE
/// until device works again.
#define ALARMS_NO_OF_LINES 8
#define ALARMS_NO_OF_CYCLES_PER_LINE 5

/* Helpers */
#define HOURS_MAX_VALUE 23U
#define HOURS_MIN_VALUE 0U
#define MINUTES_MAX_VALUE 59U
#define MINUTES_MIN_VALUE 0U

#endif