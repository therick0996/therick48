#include QMK_KEYBOARD_H

// Layers
#define _QW         0
#define _LOWER      1
#define _RAISE      2
#define _FUNCTION   3
#define _LWL0       4
#define _LWL1       5
#define _FUNCTION2  6

// Macro keycodes
  enum custom_keycodes {
  INS_ROW = SAFE_RANGE,
  DEL_ROW,
  INS_COL,
  DEL_COL
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
  MAKE1,
  MAKE2,
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
void make_therick48_finished (qk_tap_dance_state_t *state, void *user_data);
void make_therick48_reset (qk_tap_dance_state_t *state, void *user_data);

void make_nori_finished (qk_tap_dance_state_t *state, void *user_data);
void make_nori_reset (qk_tap_dance_state_t *state, void *user_data);

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
  [PIPE]    = ACTION_TAP_DANCE_DOUBLE(KC_BSLS, KC_PIPE),
  // [TILDE]   = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILDE),
  [MAKE1]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_therick48_finished, make_therick48_reset),
  [MAKE2]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_nori_finished, make_nori_reset),
  [EMAIL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, email_finished, email_reset),
  [SUM]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sum_finished, sum_reset),
  [LBKTS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbkts_finished, lbkts_reset),
  [RBKTS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbkts_finished, rbkts_reset),
  [TILDE]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tilde_finished, tilde_reset),
};

// Readability keycodes
#define _______		  KC_TRNS

// Layer codes
#define LOWER 		  MO(_LOWER)
#define RAISE 		  MO(_RAISE)
#define FUNCTION    MO(_FUNCTION)
#define FUNCTION2   MO(_FUNCTION2)

//#define LWR_BS 		  LT(_LOWER, KC_BSPC)
//#define RSE_SPC 	  LT(_RAISE, KC_SPC)
//#define FN_TAB		  LT(_FN, KC_TAB)
//#define FN_ESC		  LT(_FN, KC_ESC)
//#define LWL0_TAB	  LT(_LWL0, KC_TAB)
//#define LWL0_ESC	  LT(_LWL0, KC_ESC)
//#define LWL0_SPC 	  LT(_LWL0, KC_SPC)
//#define LWL1_PSLS	  LT(_LWL1, KC_PSLS)
//#define LWL1_PENT	  LT(_LWL1, KC_PENT)
//#define LWL1_BS		  LT(_LWL1, KC_BSPC)
//#define LWL1_END    LT(_LWL1, KC_END)
//#define FN2_BS      LT(_FN2, KC_BSPC)
//#define FN_SPC      LT(_FN, KC_SPC)

#define LWR(kc)     LT(_LOWER, KC_##kc)
#define RSE(kc)     LT(_RAISE, KC_##kc)
#define FN(kc)      LT(_FUNCTION, KC_##kc)
#define FN2(kc)     LT(_FUNCTION2, KC_##kc)
#define LWL0(kc)    LT(_LWL0, KC_##kc)
#define LWL1(kc)    LT(_LWL1, KC_##kc)

// Dual key codes
#define CTL(kc)     LCTL_T(KC_##kc) // Control when held, KC when pressed
#define GUI(kc)     LGUI_T(KC_##kc) // GUI when held, KC when pressed
#define SFT(kc)     LSFT_T(KC_##kc) // Shift when held, KC when pressed
#define ALT(kc)     LALT_T(KC_##kc) // Alt when held, KC when pressed
#define HPR_(kc)    HYPR_T(KC_##kc) // Hyper when held, KC when pressed

// macOS specific stuff
#define WHLSCR      LGUI(LSFT(KC_3))  // Capture whole screen
#define PRNTSCR     LGUI(LSFT(KC_4))  // Select screen
#define PRNTSCRC    LGUI(LSFT(LCTL(KC_4)))  // Select screen copy

//Chrome tabs
#define TAB_LEFT    LGUI(LALT(KC_LEFT))  // Go to next tab
#define TAB_RIGHT   LGUI(LALT(KC_RIGHT))  // Go to previous tab

// Google Sheets shortcuts
#define SHT_LEFT    LALT(KC_UP)  // Go to next sheet in Sheets
#define SHT_RIGHT   LALT(KC_DOWN)  // Go to previous sheet in Sheets
#define G_HOME      LGUI(KC_HOME)  // GUI + Home

#define HIDE_ROW    LGUI(LALT(KC_9))  // Hide row
#define UNHIDE_ROW  LGUI(LSFT(KC_9))  // Unhide row
#define HIDE_COL    LGUI(LALT(KC_0))  // Hide column
#define UNHIDE_COL  LGUI(LSFT(KC_0))  // Unhide column

// Other 
#define GUI_HOME    LGUI(KC_HOME) // CMD + Home
#define SA_BS 		  MT(MOD_LSFT | MOD_LALT, KC_BSPC)

// Begin keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QW QWERTY
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

  [_QW] = LAYOUT_ortho_4x12(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
    FN(TAB),    ALT(A),     KC_S,       KC_D,       GUI(F),     KC_G,       KC_H,       GUI(J),     KC_K,       KC_L,       KC_SCLN,    SFT(QUOT),
    KC_LSFT,    GUI(Z),     SFT(X),     KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    SFT(ENT),
    KC_LGUI,    KC_LSFT,    KC_LCTRL,   KC_LALT,    LWR(BSPC),  FN2(BSPC),  FN(SPC),    RSE(SPC),   KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT
  ),

/* Lower
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

  [_LOWER] = LAYOUT_ortho_4x12(
    _______,    TD(LBKTS),  TD(RBKTS),  KC_MINS,    TD(SUM),    KC_NO,      KC_NO,      KC_BSPC,     KC_P7,     KC_P8,      KC_P9,      KC_PMNS,
    LWL0(TAB),  GUI(HOME),  KC_PGDN,    KC_PGUP,    LWL1(END),  _______,    KC_F4,      KC_F2,       KC_P4,     KC_P5,      KC_P6,      KC_PPLS,
    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      _______,    KC_BTN1,     KC_P1,     KC_P2,      KC_P3,      KC_PENT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    LWL0(SPC),   KC_P0,     KC_PAST,    KC_PDOT,    KC_PSLS
  ),

    /* LWL0
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

      [_LWL0] = LAYOUT_ortho_4x12(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_BSPC,    KC_PSLS,    KC_PAST,    KC_DEL,
        _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
        _______,    _______,    _______,    _______,    _______,    _______,    TG(1),	    _______,    _______,    _______,    _______,    _______
      ),

    /* LWL1
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |   RESET   |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           | GUI+Home  | Prt Sel C | Prnt Sel  |   LWL1    |           |           |           |     $     |     ,     |     %     |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      | Caps Lock | Prnt Scr  |           |           |           |           |           |           |     !     |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |  NumLock  |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL1] = LAYOUT_ortho_4x12(
        RESET,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    GUI_HOME,   PRNTSCRC,   PRNTSCR,    _______,    _______,    _______,    _______,    KC_DLR,     KC_COMM,    KC_PERC,    _______,
        KC_CAPS,    WHLSCR,     _______,    _______,    _______,    _______,    _______,    _______,    KC_EXLM,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    _______
      ),

/* Raise
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

  [_RAISE] = LAYOUT_ortho_4x12(
    TD(TILDE),  KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       _______,
    _______,    KC_EXLM,    TD(EMAIL),  KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_UNDS,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_LBRC,    KC_RBRC,    TD(PIPE),   _______,
    _______,    _______,    _______,    _______,    _______,    _______,    TG(1),      _______,    GUI(MPLY),  ALT(VOLD),  CTL(VOLU),   KC_MUTE
  ),

/* FN
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |    F1     |    F2     |    F3     |    F4     |    F5     |    F6     |    F7     |    F8     |    F9     |   F10     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Fn     |    GUI    |   Shift   |  Option   |    Del    |           |           |   Left    |    Down   |    Up     |   Right   |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |  MAKE1    |   MAKE2   |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Enter   |           |           |           |           |           |   F11     |    F12    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_FUNCTION] = LAYOUT_ortho_4x12(
    _______,    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     _______,
    _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    _______,    CTL(LEFT),  KC_DOWN,    KC_UP,      CTL(RIGHT), KC_ENT,
    _______,    _______,    _______,    TD(MAKE1),  TD(MAKE2),  _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     _______,
    _______,    _______,    _______,    _______,    KC_ENT,     _______,    _______,    _______,    _______,    _______,    KC_F11,     KC_F12 
  ),

/* FN2
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

  [_FUNCTION2] = LAYOUT_ortho_4x12(
    KC_GRAVE,   TAB_LEFT,   TAB_RIGHT,  SHT_LEFT,   SHT_RIGHT,  _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    DEL_COL,    INS_COL,    DEL_ROW,    INS_ROW,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    HIDE_COL,   UNHIDE_COL, HIDE_ROW,   UNHIDE_ROW, _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  ) 

};
// End Keymaps

const uint16_t PROGMEM fn_actions[] = {

};

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case INS_ROW: // Insert row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("i") SS_DELAY(250)) "r"); // Ctrl+Alt+i, r
      } else { // when keycode is released
      }
      break;

    case DEL_ROW: // Delete row in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("e") SS_DELAY(250)) "d"); // Ctrl+Alt+e, d
      } else { // when keycode is released
      }
      break;

    case INS_COL: // Insert column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("i") SS_DELAY(250)) "c"); // Ctrl+Alt+i, c
      } else { // when keycode is released
      }
      break;    

    case DEL_COL: // Delete column in Sheets
      if (record->event.pressed) { // when keycode is pressed
        SEND_STRING(SS_LCTL(SS_LALT("e") SS_DELAY(250)) "e"); // Ctrl+Alt+e, e
      } else { // when keycode is released
      }
      break;
  }
  return true;
};

// Tap dance stuff
static xtap make_therick48_state = {
  .is_press_action = true,
  .state = 0
};

static xtap make_nori_state = {
  .is_press_action = true,
  .state = 0
};

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

//*************** MAKE *******************//
void make_therick48_finished (qk_tap_dance_state_t *state, void *user_data) {
  make_therick48_state.state = cur_dance(state); // Use the dance that favors being held
  switch (make_therick48_state.state) {
    case SINGLE_TAP: SEND_STRING("make therick48:default:dfu"); break; // send therick48 default make code
    case DOUBLE_TAP: SEND_STRING("make therick48:macos:dfu"); break; // send therick48 macos make code
  }
}

void make_therick48_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (make_therick48_state.state) {
    case SINGLE_TAP: ; break;
    case DOUBLE_TAP: ; break;
  }
  make_therick48_state.state = 0;
}

void make_nori_finished (qk_tap_dance_state_t *state, void *user_data) {
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
}
//*************** MAKE *******************//

//*************** EMAIL *******************//
void email_finished (qk_tap_dance_state_t *state, void *user_data) {
  email_state.state = cur_dance(state); // Use the dance that favors being held
  switch (email_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_2); break; //send @
    case DOUBLE_TAP: SEND_STRING("rick.c.kremer@gmail.com"); break; //send email address
    case TRIPLE_TAP: SEND_STRING("rkremer@bushelpowered.com"); //send work email
  }
}

void email_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (email_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_2); break; //unregister @
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
  rbkts_state.state = cur_dance(state); // Use the dance that favors being held
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
    case TRIPLE_TAP: SEND_STRING("```"); // send ```
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


/* FN3
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
  [_FN3] = LAYOUT_ortho_4x12(
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  ) */