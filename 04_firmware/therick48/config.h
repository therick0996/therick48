

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    therick
#define PRODUCT         therick48
#define DESCRIPTION     Blatant copy of Planck

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 14

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

#define MATRIX_ROW_PINS { F7, F6, D4, D6 }
#define MATRIX_COL_PINS { C6, D7, D5, B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, B6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* encoder support */
#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }

#define ENCODERS_PAD_C { D1 }
#define ENCODERS_PAD_D { D0 }

#define ENCODER_RESOLUTION 4

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
