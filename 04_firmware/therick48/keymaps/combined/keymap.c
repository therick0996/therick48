#include QMK_KEYBOARD_H

// Layers
#define _BASEWIN        0
#define _LOWERWIN       1
#define _RAISEWIN       2
#define _FUNCTIONWIN    3
#define _LWL0WIN 		    4
#define _LWL1WIN		    5
#define _FUNCTION2WIN   6

#define _BASEMAC        7
#define _LOWERMAC       8
#define _RAISEMAC       9
#define _FUNCTIONMAC    10
#define _LWL0MAC        11
#define _LWL1MAC        12
#define _FUNCTION2MAC   13

// Macro keycodes
  enum custom_keycodes {
  INS_ROW_W = SAFE_RANGE,
  DEL_ROW_W,
  INS_COL_W,
  DEL_COL_W,
  INS_ROW_M,
  DEL_ROW_M,
  INS_COL_M,
  DEL_COL_M
};

typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP =      1,
  SINGLE_HOLD =     2,
  DOUBLE_TAP =      3,
  DOUBLE_HOLD =     4,
  DOUBLE_SINGLE_TAP = 5, // Send two single taps
  TRIPLE_TAP =      6,
  TRIPLE_HOLD =     7
};

// Tap dance enums
enum {
  // Simple 
  LCRLY = 0,
  RCRLY,
  PIPE,
  // TILDE,
  // Complex
  FIRMWARE,
  // MAKE2,
  EMAIL,
  SUM,
  LBKTS,
  RBKTS,
  TILDE
};

// Tap dance dance states
// To activate SINGLE_HOLD, you will need to hold for 200ms first.
// This tap dance favors keys that are used frequently in typing like 'f'
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->interrupted) {
      //     if (!state->pressed) return SINGLE_TAP;
      //need "permissive hold" here.
      //     else return SINsGLE_HOLD;
      //If the interrupting key is released before the tap-dance key, then it is a single HOLD
      //However, if the tap-dance key is released first, then it is a single TAP
      //But how to get access to the state of the interrupting key????
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  // with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8; //magic number. At some point this method will expand to work for more presses
}

// This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
int hold_cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  // If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  // with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; // Magic number. At some point this method will expand to work for more presses
}

// For complex tap dances. Put it here so it can be used in any keymap
void make_firmware_finished (qk_tap_dance_state_t *state, void *user_data);
void make_firmware_reset (qk_tap_dance_state_t *state, void *user_data);

/* void make_nori_finished (qk_tap_dance_state_t *state, void *user_data);
void make_nori_reset (qk_tap_dance_state_t *state, void *user_data); */

void email_finished (qk_tap_dance_state_t *state, void *user_data);
void email_reset (qk_tap_dance_state_t *state, void *user_data);

void sum_finished (qk_tap_dance_state_t *state, void *user_data);
void sum_reset (qk_tap_dance_state_t *state, void *user_data);

void lbkts_finished (qk_tap_dance_state_t *state, void *user_data);
void lbkts_reset (qk_tap_dance_state_t *state, void *user_data);

void rbkts_finished (qk_tap_dance_state_t *state, void *user_data);
void rbkts_reset (qk_tap_dance_state_t *state, void *user_data);

void tilde_finished (qk_tap_dance_state_t *state, void *user_data);
void tilde_reset (qk_tap_dance_state_t *state, void *user_data);

// Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [PIPE]      = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
  // [TILDE]   = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILDE),
  [EMAIL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, email_finished, email_reset),
  [FIRMWARE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_firmware_finished, make_firmware_reset),
  // [MAKE2]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_nori_finished, make_nori_reset),
  [SUM]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sum_finished, sum_reset),
  [LBKTS]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbkts_finished, lbkts_reset),
  [RBKTS]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbkts_finished, rbkts_reset),
  [TILDE]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tilde_finished, tilde_reset),
};

// Readability keycodes
#define _______		  KC_TRNS

// Layer codes Windows
#define LOWER_W       MO(_LOWERWIN)
#define RAISE_W       MO(_RAISEWIN)
#define FUN_W         MO(_FUNCTIONWIN)
#define FUN2_W        MO(_FUNCTION2WIN)

#define LWR_W(kc)     LT(_LOWERWIN, KC_##kc)
#define RSE_W(kc)     LT(_RAISEWIN, KC_##kc)
#define FN2_W(kc)     LT(_FUNCTION2WIN, KC_##kc)
#define FN_W(kc)      LT(_FUNCTIONWIN, KC_##kc)
#define LWL0_W(kc)    LT(_LWL0WIN, KC_##kc)
#define LWL1_W(kc)    LT(_LWL1WIN, KC_##kc)

// Layer codes macOS
#define LOWER_M       MO(_LOWERMAC)
#define RAISE_M       MO(_RAISEMAC)
#define FUN_M         MO(_FUNCTIONMAC)
#define FUN2_M        MO(_FUNCTION2MAC)

#define LWR_M(kc)     LT(_LOWERMAC, KC_##kc)
#define RSE_M(kc)     LT(_RAISEMAC, KC_##kc)
#define FN2_M(kc)     LT(_FUNCTION2MAC, KC_##kc)
#define FN_M(kc)      LT(_FUNCTIONMAC, KC_##kc)
#define LWL0_M(kc)    LT(_LWL0MAC, KC_##kc)
#define LWL1_M(kc)    LT(_LWL1MAC, KC_##kc)

// Dual key codes
#define CTL(kc)       LCTL_T(KC_##kc) // Control when held, KC when pressed
#define GUI(kc)       LGUI_T(KC_##kc) // GUI when held, KC when pressed
#define SFT(kc)       LSFT_T(KC_##kc) // Shift when held, KC when pressed
#define ALT(kc)       LALT_T(KC_##kc) // Alt when held, KC when pressed

// Screenshots
#define PRNTSCR_W     LGUI(LSFT(KC_S))

#define WHLSCR_M      LGUI(LSFT(KC_3))  // Capture whole screen
#define PRNTSCR_M     LGUI(LSFT(KC_4))  // Select screen
#define PRNTSCRC_M    LGUI(LSFT(LCTL(KC_4)))  // Select screen copy

//Chrome Tabs
#define TAB_LEFT_W    LCTL(KC_PGDN)
#define TAB_RIGHT_W   LCTL(KC_PGUP)
#define TAB_LEFT_M    LGUI(LALT(KC_LEFT))  // Go to next tab
#define TAB_RIGHT_M   LGUI(LALT(KC_RIGHT))  // Go to previous tab

// Google Sheets shortcuts
#define SHT_LEFT_W    LALT(KC_UP)  // Go to next sheet in Sheets
#define SHT_RIGHT_W   LALT(KC_DOWN)  // Go to previous sheet in Sheets

#define HIDE_ROW_W    LCTL(LALT(KC_9))  // Hide row
#define UNHIDE_ROW_W  LCTL(LSFT(KC_9))  // Unhide row
#define HIDE_COL_W    LCTL(LALT(KC_0))  // Hide column
#define UNHIDE_COL_W  LCTL(LSFT(KC_0))  // Unhide column

#define SHT_LEFT_M    LALT(KC_UP)  // Go to next sheet in Sheets
#define SHT_RIGHT_M   LALT(KC_DOWN)  // Go to previous sheet in Sheets
#define G_HOME_M      LGUI(KC_HOME)  // GUI + Home

#define HIDE_ROW_M    LGUI(LALT(KC_9))  // Hide row
#define UNHIDE_ROW_M  LGUI(LSFT(KC_9))  // Unhide row
#define HIDE_COL_M    LGUI(LALT(KC_0))  // Hide column
#define UNHIDE_COL_M  LGUI(LSFT(KC_0))  // Unhide column

// Other
#define CTL_HOME      LCTL(KC_HOME) // Ctrl + Home
#define GUI_HOME      LGUI(KC_HOME) // CMD + Home
#define SA_BS 		    MT(MOD_LSFT | MOD_LALT, KC_BSPC)

// Begin keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Windows

/* Base Windows
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    Esc    |     Q     |     W     |     E     |     R     |     T     |     Y     |     U     |     I     |     O     |     P     |    Del    |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |  Fn Tab   |     A     |     S     |     D     |     F     |     G     |     H     |     J     |     K     |     L     |     ;     |     '     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   Shift   |     Z     |     X     |     C     |     V     |     B     |     N     |     M     |     ,     |     .     |     /     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Ctrl   |   Shift   |    GUI    |    Alt    |  Lwr BS   |  FUN2 BS  |   Space   |  Rse Spc  |   Left    |   Down    |     Up    |   Right   |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_BASEWIN] = LAYOUT_ortho_4x12(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
    FN_W(TAB),  KC_A,       KC_S,       KC_D,       CTL(F),     KC_G,       KC_H,       CTL(J),     KC_K,       KC_L,       KC_SCLN,    SFT(QUOT),
    KC_LSFT,    CTL(Z),     SFT(X),     KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    SFT(ENT),
    KC_LCTL,    KC_LSFT,    KC_LGUI,    KC_LALT,    LWR_W(BSPC),FN2_W(BSPC),FN_W(SPC),  RSE_W(SPC), KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT
  ),

/* Lower Windows
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |   ( [ {   |   ) ] }   |     -     |     =     |    ***    |    ***    |    BS     |     7     |     8     |     9     |     -     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   LWL0    |   Home    |   Pg Dn   |   Pg Up   | End LWL1  |    BS     |    F4     |    F2     |     4     |     5     |     6     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |   Left    |    Down   |    Up     |   Right   |    ***    |           |   Calc    |     1     |     2     |     3     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Lower   |           |           |   LWL0    |     0     |     .     |     *     |     /     |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_LOWERWIN] = LAYOUT_ortho_4x12(
    _______,    TD(LBKTS),  TD(RBKTS),  KC_MINS,    TD(SUM),    KC_NO,      KC_NO,      KC_BSPC,     KC_P7,     KC_P8,      KC_P9,      KC_PMNS,
    LWL0_W(TAB),CTL(HOME),  KC_PGDN,    KC_PGUP,    LWL1_W(END),KC_BSPC,    KC_F4,      KC_F2,       KC_P4,     KC_P5,      KC_P6,      KC_PPLS,
    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      _______,    KC_CALC,     KC_P1,     KC_P2,      KC_P3,      KC_PENT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    LWL0_W(SPC), KC_P0,     KC_PAST,    KC_PDOT,    KC_PSLS
  ),

    /* LWL0 Windows
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |           |           |           |           |           |           |           |           |    BS     |     /     |     *     |    Del    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   LWL0    |   Ctrl    |   Shift   |    Del    |   Del     |           |           |           |   Left    |   Down    |     Up    |   Right   |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |  TG(Lwr)  |   LWL0    |           |           |           |   LWL1    |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL0WIN] = LAYOUT_ortho_4x12(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_BSPC,    KC_PSLS,    KC_PAST,    KC_DEL,
        _______,    KC_LCTL,    KC_LSFT,    KC_DEL,     KC_DEL,     _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
        _______,    _______,    _______,    _______,    _______,    _______,    TG(1),	    _______,    _______,    _______,    _______,    _______
      ),

    /* LWL1 Windows
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |   RESET   |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           | Ctl+Home  |  Prt Scr  |           |   LWL1    |           |           |           |     $     |     ,     |     %     |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   Caps    |           |           |           |           |           |           |           |     !     |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   macOS   |           |           |           |           |           |           |           |           |           |  NumLock  |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL1WIN] = LAYOUT_ortho_4x12(
        RESET,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    CTL_HOME,   PRNTSCR_W,  _______,    _______,    _______,    _______,    _______,    KC_DLR,     KC_COMM,    KC_PERC,    _______,
        KC_CAPS,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_EXLM,    _______,    _______,    _______,
        TG(7),      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    _______
      ),

/* Raise Windows
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    ` ~    |     1     |     2     |     3     |     4     |     5     |     6     |     7     |     8     |     9     |     0     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |     !     |     @     |     #     |     $     |     %     |     ^     |     &     |     *     |     (     |     )     |     _     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |     `     |           |           |           |  Insert   |           |     [     |     ]     |    \ |    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |  TG(Lwr)  |   Raise   |   Play    |   Vol-    |   Vol+    |   Mute    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_RAISEWIN] = LAYOUT_ortho_4x12(
    TD(TILDE),  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
    _______,    KC_EXLM,    TD(EMAIL),  KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_UNDS,
    _______,    _______,    _______,    _______,    _______,    _______,    KC_INS,     _______,    KC_LBRC,    KC_RBRC,    TD(PIPE),   _______,
    _______,    _______,    _______,    _______,    _______,    _______,    TG(1),      _______,    KC_MPLY,    KC_VOLD,    KC_VOLU,    KC_MUTE
  ),

/* FN Windows
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |    F1     |    F2     |    F3     |    F4     |    F5     |    F6     |    F7     |    F8     |    F9     |   F10     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Fn     |   Ctrl    |   Shift   |    Del    |   Del     |           |           |   Left    |    Down   |    Up     |   Right   |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           | Firmware  |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Enter   |           |           |           |           |           |   F11     |    F12    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_FUNCTIONWIN] = LAYOUT_ortho_4x12(
    _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
    _______,    KC_LCTL,    KC_LSFT,    KC_DEL,     KC_DEL,     _______,    _______,    ALT(LEFT),  KC_DOWN,    KC_UP,      ALT(RIGHT), KC_ENT,
    _______,    _______,    _______,    _______,    TD(FIRMWARE),_______,    _______,    CTL(HOME),  SFT(PGDN),  SFT(PGUP),  CTL(END),   _______,
    _______,    _______,    _______,    _______,    KC_ENT,     _______,    _______,    _______,    _______,    _______,    KC_F11,     KC_F12 
  ),

/* FN2 Windows
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |  Tab Left | Tab Right | Sht Left  | Sht Right |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |  Del Col  |  Ins Col  |  Del Row  |  Ins Row  |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |  Hide Col | Unhide Col|  Hide Row | Unhide Row|           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/ 

  [_FUNCTION2WIN] = LAYOUT_ortho_4x12(
    _______,    TAB_LEFT_W, TAB_RIGHT_W,SHT_LEFT_W, SHT_RIGHT_W,_______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    DEL_COL_W,  INS_COL_W,  DEL_ROW_W,  INS_ROW_W,  _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    HIDE_COL_W, UNHIDE_COL_W,HIDE_ROW_W,UNHIDE_ROW_W,_______,   _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  ),

// macOS

/* Base macOS
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    Esc    |     Q     |     W     |     E     |     R     |     T     |     Y     |     U     |     I     |     O     |     P     |    Del    |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |  Fn Tab   |     A     |     S     |     D     |     F     |     G     |     H     |     J     |     K     |     L     |     ;     |     '     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   Shift   |     Z     |     X     |     C     |     V     |     B     |     N     |     M     |     ,     |     .     |     /     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    GUI    |   Shift   |   Ctrl    |   Option  |  Lwr BS   |  FN2 BS   | FN Space  |  Rse Spc  |   Left    |   Down    |     Up    |   Right   |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/ 

  [_BASEMAC] = LAYOUT_ortho_4x12(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
    FN_M(TAB),  ALT(A),     KC_S,       KC_D,       GUI(F),     KC_G,       KC_H,       GUI(J),     KC_K,       KC_L,       KC_SCLN,    SFT(QUOT),
    KC_LSFT,    GUI(Z),     SFT(X),     KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    SFT(ENT),
    KC_LGUI,    KC_LSFT,    KC_LCTRL,   KC_LALT,    LWR_M(BSPC),FN2_M(BSPC),FN_M(SPC),  RSE_M(SPC), KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT
  ),

/* Lower macOS
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |   ( [ {   |   ) ] }   |     -     |     =     |    ***    |    ***    |    BS     |     7     |     8     |     9     |     -     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   LWL0    |   Home    |   Pg Dn   |   Pg Up   |    End    |           |    F4     |    F2     |     4     |     5     |     6     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |   Left    |    Down   |    Up     |   Right   |    ***    |           | Button 1  |     1     |     2     |     3     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Lower   |           |           |   LWL0    |     0     |     *     |     .     |     /     |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_LOWERMAC] = LAYOUT_ortho_4x12(
    _______,    TD(LBKTS),  TD(RBKTS),  KC_MINS,    TD(SUM),    KC_NO,      KC_NO,      KC_BSPC,     KC_P7,     KC_P8,      KC_P9,      KC_PMNS,
    LWL0_M(TAB),GUI(HOME),  KC_PGDN,    KC_PGUP,    LWL1_M(END),_______,    KC_F4,      KC_F2,       KC_P4,     KC_P5,      KC_P6,      KC_PPLS,
    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      _______,    KC_BTN1,     KC_P1,     KC_P2,      KC_P3,      KC_PENT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    LWL0_M(SPC), KC_P0,     KC_PAST,    KC_PDOT,    KC_PSLS
  ),

    /* LWL0 macOS
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |           |           |           |           |           |           |           |           |    BS     |     /     |     *     |    Del    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   LWL0    |   GUI     |   Shift   |    Alt    |    Del    |           |           |           |   Left    |   Down    |     Up    |   Right   |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |   Lower   |           |  TG(Lwr)  |   LWL0    |           |           |           |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL0MAC] = LAYOUT_ortho_4x12(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_BSPC,    KC_PSLS,    KC_PAST,    KC_DEL,
        _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
        _______,    _______,    _______,    _______,    _______,    _______,    TG(8),	    _______,    _______,    _______,    _______,    _______
      ),

    /* LWL1 macOS
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |   RESET   |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           | GUI+Home  | Prt Sel C | Prnt Sel  |   LWL1    |           |           |           |     $     |     ,     |     %     |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      | Caps Lock | Prnt Scr  |           |           |           |           |           |           |     !     |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      | Windows   |           |           |           |           |           |           |           |           |           |  NumLock  |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL1MAC] = LAYOUT_ortho_4x12(
        RESET,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    GUI_HOME,   PRNTSCRC_M, PRNTSCR_M,  _______,    _______,    _______,    _______,    KC_DLR,     KC_COMM,    KC_PERC,    _______,
        KC_CAPS,    WHLSCR_M,   _______,    _______,    _______,    _______,    _______,    _______,    KC_EXLM,    _______,    _______,    _______,
        TG(7),      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    _______
      ),

/* Raise macOS
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    ` ~    |     1     |     2     |     3     |     4     |     5     |     6     |     7     |     8     |     9     |     0     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |     !     |     @     |     #     |     $     |     %     |     ^     |     &     |     *     |     (     |     )     |     _     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |     [     |     ]     |    \ |    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |  TG(Lwr)  |   Raise   |   Play    |   Vol-    |   Vol+    |   Mute    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_RAISEMAC] = LAYOUT_ortho_4x12(
    TD(TILDE),  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
    _______,    KC_EXLM,    TD(EMAIL),  KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_UNDS,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LBRC,    KC_RBRC,    TD(PIPE),   _______,
    _______,    _______,    _______,    _______,    _______,    _______,    TG(8),      _______,    KC_MPLY,    KC_VOLD,    KC_VOLU,    KC_MUTE
  ),

/* FN macOS
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |    F1     |    F2     |    F3     |    F4     |    F5     |    F6     |    F7     |    F8     |    F9     |   F10     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Fn     |    GUI    |   Shift   |  Option   |    Del    |           |           |   Left    |    Down   |    Up     |   Right   |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           | Firmware  |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Enter   |           |           |           |           |           |   F11     |    F12    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_FUNCTIONMAC] = LAYOUT_ortho_4x12(
    _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
    _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    _______,    CTL(LEFT),  KC_DOWN,    KC_UP,      CTL(RIGHT), KC_ENT,
    _______,    _______,    _______,    _______,    TD(FIRMWARE),_______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     _______,
    _______,    _______,    _______,    _______,    KC_ENT,     _______,    _______,    _______,    _______,    _______,    KC_F11,     KC_F12 
  ),

/* FN2 macOS
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |     ~     |  Tab Left | Tab Right | Sht Left  | Sht Right |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |  Del Col  |  Ins Col  |  Del Row  |  Ins Row  |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |  Hide Col | Unhide Col|  Hide Row | Unhide Row|           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/ 

  [_FUNCTION2MAC] = LAYOUT_ortho_4x12(
    KC_GRAVE,   TAB_LEFT_M, TAB_RIGHT_M,SHT_LEFT_M, SHT_RIGHT_M,_______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    DEL_COL_M,  INS_COL_M,  DEL_ROW_M,  INS_ROW_M,  _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    HIDE_COL_M, UNHIDE_COL_M,HIDE_ROW_M,UNHIDE_ROW_M,_______,   _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  ) 

};
// End Keymaps

const uint16_t PROGMEM fn_actions[] = {

};

/* uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case CTL_T(KC_A):
 	 return 500;
	case SFT_T(KC_S):
	 return 500;
    default:
      return TAPPING_TERM;
  }
} */ 

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Windows
    case INS_ROW_W: // Insert row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LALT(SS_LSFT("i") SS_DELAY(250)) "r"); // Alt+Shift+i, r
      } else { // when keycode is released
      }
      break;

    case DEL_ROW_W: // Delete row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LALT(SS_LSFT("e") SS_DELAY(250)) "d"); // Alt+Shift+e, d
      } else { // when keycode is released
      }
      break;

    case INS_COL_W: // Insert column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LALT(SS_LSFT("i") SS_DELAY(250)) "c"); // Alt+Shift+i, c
      } else { // when keycode is released
      }
      break;    

    case DEL_COL_W: // zDelete column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LALT(SS_LSFT("e") SS_DELAY(250)) "e"); // Alt+Shift+e, e
      } else { // when keycode is released
      }
      break;

    // macOS
    case INS_ROW_M: // Insert row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("i") SS_DELAY(250)) "r"); // Ctrl+Alt+i, r
      } else { // when keycode is released
      }
      break;

    case DEL_ROW_M: // Delete row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("e") SS_DELAY(250)) "d"); // Ctrl+Alt+e, d
      } else { // when keycode is released
      }
      break;

    case INS_COL_M: // Insert column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("i") SS_DELAY(250)) "c"); // Ctrl+Alt+i, c
      } else { // when keycode is released
      }
      break;    

    case DEL_COL_M: // Delete column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("e") SS_DELAY(250)) "e"); // Ctrl+Alt+e, e
      } else { // when keycode is released
      }
      break;
  }
  return true;
};

// Tap dance stuff
static xtap make_firmware_state = {
  .is_press_action = true,
  .state = 0
};

/* static xtap make_nori_state = {
  .is_press_action = true,
  .state = 0
}; */

static xtap email_state = {
  .is_press_action = true,
  .state = 0
};

static xtap sum_state = {
  .is_press_action = true,
  .state = 0
};

static xtap lbkts_state = {
  .is_press_action = true,
  .state = 0
};

static xtap rbkts_state = {
  .is_press_action = true,
  .state = 0
};

static xtap tilde_state = {
  .is_press_action = true,
  .state = 0
};

//************ FLASH FIRMWARE *************//
void make_firmware_finished (qk_tap_dance_state_t *state, void *user_data) {
  make_firmware_state.state = cur_dance(state); // Use the dance that favors being held
  switch (make_firmware_state.state) {
    case SINGLE_TAP: SEND_STRING("make therick48:combined:dfu"); break; // send therick48 make code
    case DOUBLE_TAP: SEND_STRING("make nori:combined:avrdude"); break; // send nori macos make code
  }
}

void make_firmware_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (make_firmware_state.state) {
    case SINGLE_TAP: ; break;
    case DOUBLE_TAP: ; break;
  }
  make_firmware_state.state = 0;
}

/* void make_nori_finished (qk_tap_dance_state_t *state, void *user_data) {
  make_nori_state.state = cur_dance(state); // Use the dance that favors being held
  switch (make_nori_state.state) {
    case SINGLE_TAP: SEND_STRING("make nori:default:avrdude"); break; // send nori default make code
    case DOUBLE_TAP: SEND_STRING("make nori:macos:avrdude"); break; // send nori macos make code
  }
}

void make_nori_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (make_nori_state.state) {
    case SINGLE_TAP: ; break;
    case DOUBLE_TAP: ; break;
  }
  make_nori_state.state = 0;
} */
//************ FLASH FIRMWARE *************//

//*************** EMAIL *******************//
void email_finished (qk_tap_dance_state_t *state, void *user_data) {
  email_state.state = cur_dance(state); // Use the dance that favors being held
  switch (email_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_2); break; //send @
    case DOUBLE_TAP: SEND_STRING("rick.c.kremer@gmail.com"); break; // send email address
    case TRIPLE_TAP: SEND_STRING("rkremer@bushelpowered.com"); // send work email
  }
}

void email_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (email_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_2); break; // unregister @
    case DOUBLE_TAP: ; break;
    case TRIPLE_TAP: ; break;
  }
  email_state.state = 0;
}
//*************** EMAIL *******************//

//**************** SUM ********************//
void sum_finished (qk_tap_dance_state_t *state, void *user_data) {
  sum_state.state = cur_dance(state); // Use the dance that favors being held
  switch (sum_state.state) {
    case SINGLE_TAP: register_code(KC_EQL); break; // send =
    case DOUBLE_TAP: SEND_STRING("=sum("); break; // =sum(
    case TRIPLE_TAP: SEND_STRING("=iferror(vlookup("); // send =iferror(vlookup(
  }
}

void sum_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (sum_state.state) {
    case SINGLE_TAP: unregister_code(KC_EQL); break; // unregister =
    case DOUBLE_TAP: ; break;
    case TRIPLE_TAP: ; break;
  }
  sum_state.state = 0;
}
//**************** SUM ********************//

//************* BRACKETS ******************//
// Left brackets 
void lbkts_finished (qk_tap_dance_state_t *state, void *user_data) {
  lbkts_state.state = cur_dance(state); // Use the dance that favors being held
  switch (lbkts_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break; // send (
    case DOUBLE_TAP: register_code(KC_LBRC); break; // send [
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); // send {
  }
}

void lbkts_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lbkts_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_9); break; // unregister (
    case DOUBLE_TAP: unregister_code(KC_LBRC); break; // unregister [
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_LBRC); // unregsister {
  }
  lbkts_state.state = 0;
}

// Right brackets
void rbkts_finished (qk_tap_dance_state_t *state, void *user_data) {
  rbkts_state.state = cur_dance(state); //Use the dance that favors being held
  switch (rbkts_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0); break; // send )
    case DOUBLE_TAP: register_code(KC_RBRC); break; // send ]
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(KC_RBRC); // send }
  }
}

void rbkts_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rbkts_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_0); break; // unregister )
    case DOUBLE_TAP: unregister_code(KC_RBRC); break; // unregister ]
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_RBRC); // unregsister }
  }
  rbkts_state.state = 0;
}
//************* BRACKETS ******************//

//*************** TILDE *******************//
void tilde_finished (qk_tap_dance_state_t *state, void *user_data) {
  tilde_state.state = cur_dance(state); // Use the dance that favors being held
  switch (tilde_state.state) {
    case SINGLE_TAP: register_code(KC_GRAVE); break; // send `
    case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_GRAVE); break; // send ~
    case TRIPLE_TAP: SEND_STRING("```"); // ```
  }
}

void tilde_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tilde_state.state) {
    case SINGLE_TAP: unregister_code(KC_GRAVE); break; // unregister `
    case DOUBLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_GRAVE); break; // unregister ~
    case TRIPLE_TAP: ; break;
  }
  tilde_state.state = 0;
}
//*************** TILDE *******************//

/* FN2
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |           |           |           |           |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/ 
/*
  [_FN2] = LAYOUT_ortho_4x12(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  ) */