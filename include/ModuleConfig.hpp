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

/* Views configuration section */
#define VIEW_ID_CONFIRMATION_VIEW 1
#define VIEW_ID_DATE_SETUP_VIEW 2
#define VIEW_ID_MENU_VIEW 3
#define VIEW_ID_TIME_SETUP_VIEW 4
#define VIEW_ID_TIME_VIEW 5
#define VIEW_ID_LINES_STATUS_VIEW 6
#define VIEW_ID_LINE_SETTINGS_VIEW 7

/* Alarms configuration */
#define ALARMS_NO_OF_LINES 8
#define ALARMS_NO_OF_CYCLES_PER_LINE 2

#endif