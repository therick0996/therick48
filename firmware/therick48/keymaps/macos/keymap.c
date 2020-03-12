
#include QMK_KEYBOARD_H

// Layers
#define _QW			    0
#define _LOWER		  1
#define _RAISE		  2
#define _FN			    3
#define _LWL0 		  4
#define _LWL1		    5
#define _FN2        6

// Macro keycodes
/*
  enum custom_keycodes {
  MAKE = SAFE_RANGE,
}; */

typedef struct {
  bool is_press_action;
  int state;
} xtap;

enum {
  SINGLE_TAP =      1,
  SINGLE_HOLD =     2,
  DOUBLE_TAP =      3,
  DOUBLE_HOLD =     4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP =      6,
  TRIPLE_HOLD =     7
};

// Tap dance enums
enum {
  // Simple 
  LCRLY = 0,
  RCRLY,
  PIPE,
  TILDE,
  // Complex
  LBKTS,
  RBKTS,
  QUOT,
  EMAIL
};

//Tap dance dance states
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
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//This works well if you want this key to work as a "fast modifier". It favors being held over being tapped.
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
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap.
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//for complex tap dances. Put it here so it can be used in any keymap
void quot_finished (qk_tap_dance_state_t *state, void *user_data);
void quot_reset (qk_tap_dance_state_t *state, void *user_data);

void email_finished (qk_tap_dance_state_t *state, void *user_data);
void email_reset (qk_tap_dance_state_t *state, void *user_data);

void lbkts_finished (qk_tap_dance_state_t *state, void *user_data);
void lbkts_reset (qk_tap_dance_state_t *state, void *user_data);

void rbkts_finished (qk_tap_dance_state_t *state, void *user_data);
void rbkts_reset (qk_tap_dance_state_t *state, void *user_data);

// Tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
//  [LBKTS]   = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_LBRC),
//  [RBKTS]   = ACTION_TAP_DANCE_DOUBLE(KC_RPRN, KC_RBRC),
  [LCRLY]   = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_LCBR),
  [RCRLY]   = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_RCBR),
  [PIPE]    = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_PIPE),
  [TILDE]   = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, KC_TILDE),
  [QUOT]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, quot_finished, quot_reset),
  [EMAIL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, email_finished, email_reset),
  [MAKE]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, make_finished, make_reset),
  [LBKTS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lbkts_finished, lbkts_reset),
  [RBKTS]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rbkts_finished, rbkts_reset),
};

// Readability keycodes
#define _______		  KC_TRNS

// Layer codes
#define LOWER 		  MO(_LOWER)
#define RAISE 		  MO(_RAISE)
#define FN 		  	  MO(_FN)
#define FN2         MO(_FN2)

#define KC_DQT      LSFT(KC_QUOT)

#define LWR_BS 		  LT(_LOWER, KC_BSPC)
#define RSE_SPC 	  LT(_RAISE, KC_SPC)
#define FN_TAB		  LT(_FN, KC_TAB)
#define FN_ESC		  LT(_FN, KC_ESC)
#define LWL0_TAB	  LT(_LWL0, KC_TAB)
#define LWL0_ESC	  LT(_LWL0, KC_ESC)
#define LWL0_SPC 	  LT(_LWL0, KC_SPC)
#define LWL1_PSLS	  LT(_LWL1, KC_PSLS)
#define LWL1_PENT	  LT(_LWL1, KC_PENT)
#define LWL1_BS		  LT(_LWL1, KC_BSPC)
#define LWL1_END    LT(_LWL1, KC_END)

// Dual key codes
#define CTL_A 		  CTL_T(KC_A)
#define CTL_F 		  CTL_T(KC_F)
#define CTL_J		    CTL_T(KC_J)
#define CTL_Z		    CTL_T(KC_Z)
#define CTL_LEFT	  CTL_T(KC_LEFT)
#define CTL_RGHT 	  CTL_T(KC_RIGHT)
#define CTL_HOME	  CTL_T(KC_HOME)
#define CTL_END		  CTL_T(KC_END)
#define CTL_SLS		  CTL_T(KC_SLSH)
#define CTL_VOLU    CTL_T(KC_VOLU)

#define GUI_A 		  LGUI_T(KC_A)
#define GUI_F 		  LGUI_T(KC_F)
#define GUI_J		    LGUI_T(KC_J)
#define GUI_Z		    LGUI_T(KC_Z)
#define GUI_LEFT	  LGUI_T(KC_LEFT)
#define GUI_RGHT 	  LGUI_T(KC_RIGHT)
#define GUI_HOME	  LGUI_T(KC_HOME)
#define GUI_END		  LGUI_T(KC_END)
#define GUI_SLS		  LGUI_T(KC_SLSH)
#define GUI_BS		  LGUI_T(KC_BSPC)
#define GUI_MPLY    LGUI_T(KC_MPLY)

#define SFT_S 		  SFT_T(KC_S)
#define SFT_X		    SFT_T(KC_X)
#define SFT_SPC		  SFT_T(KC_SPC)
#define SFT_ENT		  SFT_T(KC_ENT)
#define SFT_DOT		  SFT_T(KC_DOT)
#define SFT_QUOT	  SFT_T(KC_QUOT)
#define SFT_DOWN	  SFT_T(KC_DOWN)
#define SFT_UP 		  SFT_T(KC_UP)
#define SFT_PGDN	  SFT_T(KC_PGDN)
#define SFT_PGUP	  SFT_T(KC_PGUP)
#define SFT_CAPS	  SFT_T(KC_LCAP)
#define SFT_MUTE    SFT_T(KC_MUTE)
#define SFT_VOLD    SFT_T(KC_VOLD)

#define ALT_LEFT    ALT_T(KC_LEFT)
#define ALT_DN      ALT_T(KC_DOWN)
#define ALT_UP      ALT_T(KC_UP)
#define ALT_RGHT    ALT_T(KC_RIGHT)
#define ALT_MUTE    LALT_T(KC_MUTE)
#define ALT_VOLD    LALT_T(KC_VOLD)

#define HPR_SPC     HYPR_T(KC_SPC)

// macOS specific stuff
#define WHLSCR      LGUI(LSFT(KC_3))  //Capture whole screen
#define PRNTSCR     LGUI(LSFT(KC_4))  //Select screen
#define PRNTSCRC    LGUI(LSFT(LCTL(KC_4)))  //Select screen copy
#define NOTIFCENT   HYPR(KC_M)  //Open notification center
#define MSNCTRL     LCTL(KC_UP) //Open mission control

#define SA_BS 		  MT(MOD_LSFT | MOD_LALT, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QW QWERTY
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    Esc    |     Q     |     W     |     E     |     R     |     T     |     Y     |     U     |     I     |     O     |     P     |    Del    |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |  Fn Tab   |     A     |     S     |     D     |     F     |     G     |     H     |     J     |     K     |     L     |     ;     |     '     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   Shift   |     Z     |     X     |     C     |     V     |     B     |     N     |     M     |     ,     |     .     |     /     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    GUI    |   Shift   |   Ctrl    |    Alt    |  Lwr BS   |    GUI    |   Space   |  Rse Spc  |   Left    |   Down    |     Up    |   Right   |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/ 

  [_QW] = LAYOUT_ortho_4x12(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
    FN_TAB,     KC_A,       KC_S,       KC_D,       GUI_F,      KC_G,       KC_H,       GUI_J,      KC_K,       KC_L,       KC_SCLN,    TD(QUOT),
    KC_LSFT,    GUI_Z,      SFT_X,      KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     TD(PIPE),   KC_ENT,
    KC_LGUI,    KC_LSFT,    KC_LCTRL,   KC_LALT,    LWR_BS,     GUI_BS,     HPR_SPC,    RSE_SPC,    GUI_LEFT,   ALT_DN,     ALT_UP,     GUI_RGHT
  ),

/* Lower
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |     (     |     )     |     -     |     =     |    ***    |    ***    |    BS     |     7     |     8     |     9     |     -     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   LWL0    |   Home    |   Pg Dn   |   Pg Up   |    End    |    BS     |    F4     |    F2     |     4     |     5     |     6     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |   Left    |    Down   |    Up     |   Right   |    ***    |           | NotifCent |     1     |     2     |     3     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Lower   |           |           |   LWL0    |     0     |     .     |     *     |     /     |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_LOWER] = LAYOUT_ortho_4x12(
    _______,    TD(LBKTS),  TD(RBKTS),  TD(LCRLY),  TD(RCRLY),  KC_NO,      KC_NO,      KC_BSPC,     KC_P7,     KC_P8,      KC_P9,      KC_PMNS,
    LWL0_TAB,   KC_HOME,    KC_PGDN,    KC_PGUP,    LWL1_END,   KC_BSPC,    KC_F4,      KC_F2,       KC_P4,     KC_P5,      KC_P6,      KC_PPLS,
    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      _______,    NOTIFCENT,   KC_P1,     KC_P2,      KC_P3,      KC_PENT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    LWL0_SPC,    KC_P0,     KC_PDOT,    KC_PAST,    KC_PSLS
  ),

    /* LWL0
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |           |           |           |           |           |           |           |           |    BS     |           |           |    Del    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   LWL0    |   GUI     |   Shift   |    Alt    |    Del    |           |           |           |   Left    |   Down    |     Up    |   Right   |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |   MAKE    |   Home    |   Pg Dn   |   Pg Up   |    End    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |   Lower   |           |  TG(Lwr)  |   LWL0    |           |           |           |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL0] = LAYOUT_ortho_4x12(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_BSPC,    _______,    _______,    KC_DEL,
        _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    _______,    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    MAKE,       KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,
        _______,    _______,    _______,    _______,    _______,    _______,    TG(1),	    _______,    _______,    _______,    _______,    _______
      ),

    /* LWL1
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |   RESET   |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |   LWL1    |           |           |           |     $     |     ,     |     %     |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |  NumLock  |           |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL1] = LAYOUT_ortho_4x12(
        RESET,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_DLR,     KC_COMM,    KC_PERC,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    _______
      ),

/* Raise
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |     1     |     2     |     3     |     4     |     5     |     6     |     7     |     8     |     9     |     0     |     -     |     =     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |     !     |     @     |     #     |     $     |     %     |     ^     |     &     |     *     |     (     |     )     |     _     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Caps   |     `     |           |           |           |           |           |           |     [     |     ]     |     \     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |  TG(Lwr)  |   Raise   |   Play    |   Vol-    |   Vol+    |   Mute    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_RAISE] = LAYOUT_ortho_4x12(
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,
    KC_EXLM,    TD(EMAIL),  KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_UNDS,    KC_PLUS,
    SFT_CAPS,   TD(TILDE),  _______,    _______,    _______,    _______,    _______,    _______,    KC_LBRC,    KC_LBRC,    KC_RBRC,    FN2,
    _______,    _______,    _______,    _______,    _______,    _______,    TG(1),      _______,    GUI_MPLY,   ALT_VOLD,   CTL_VOLU,   KC_MUTE
  ),

/* FN
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    F1     |    F2     |    F3     |    F4     |    F5     |    F6     |    F7     |    F8     |    F9     |   F10     |   F11     |    F12    |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Fn     |    GUI    |   Shift   |  Option   |    Del    |           |           |   Left    |    Down   |    Up     |   Right   |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |   WEMAIL  |   EMAIL   |   MAKE    |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Enter   |           |           |           |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_FN] = LAYOUT_ortho_4x12(
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
    _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    _______,    CTL_LEFT,   KC_DOWN,    KC_UP,      CTL_RGHT,   KC_ENT,
    _______,    _______,    _______,    _______,    MAKE,       _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     _______,
    _______,    _______,    _______,    _______,    KC_ENT,     _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  ),

/* FN2
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  | Bright Up | Bright Dn | Miss Ctrl |           |           |           |  Rewind   |   Play    | Fast Fwd  |   Mute    |  Vol Up   |  Vol Dn   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           | Prnt Scrn | Prnt Sel  | Prt Sel C |           |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |    FN2    |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/ 

  [_FN2] = LAYOUT_ortho_4x12(
    KC_BRID,    KC_BRIU,    MSNCTRL,    _______,    _______,    _______,    KC_MRWD,    KC_MPLY,    KC_MFFD,    KC_MUTE,    KC_VOLD,    KC_VOLU,
    _______,    WHLSCR,     PRNTSCR,    PRNTSCRC,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______ 
  )

};


const uint16_t PROGMEM fn_actions[] = {

};

uint16_t get_tapping_term(uint16_t keycode) {
  switch (keycode) {
    case CTL_T(KC_A):
 	 return 500;
	case SFT_T(KC_S):
	 return 500;
    default:
      return TAPPING_TERM;
  }
}

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MAKE:
      if (record->event.pressed) {
        // when keycode is pressed
        SEND_STRING("make nori:macos:avrdude");
      } else {
        // when keycode is released
      }
      break;
  }
  return true;
};

// Tap dance stuff
static xtap quot_state = {
  .is_press_action = true,
  .state = 0
};

static xtap email_state = {
  .is_press_action = true,
  .state = 0
};

static xtap make_state = {
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

//*************** SUPER QUOTE *******************//
// Assumption: we don't care about trying to hit '' quickly
void quot_finished (qk_tap_dance_state_t *state, void *user_data) {
  quot_state.state = cur_dance(state); //Use the dance that favors being held
  switch (quot_state.state) {
    case SINGLE_TAP: register_code(KC_QUOT); break; //send quote
    case SINGLE_HOLD: register_code(KC_LSFT); break; //hold shift
    case DOUBLE_TAP: register_code(KC_LSFT); register_code(KC_QUOT); //send double quote
  }
}

void quot_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (quot_state.state) {
    case SINGLE_TAP: unregister_code(KC_QUOT); break; //unregister quote
    case SINGLE_HOLD: unregister_code(KC_LSFT); break; //unregister shift
    case DOUBLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_QUOT); break;
  }
  quot_state.state = 0;
}
//*************** SUPER QUOTE *******************//

//*************** EMAIL *******************//
void email_finished (qk_tap_dance_state_t *state, void *user_data) {
  email_state.state = cur_dance(state); //Use the dance that favors being held
  switch (email_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_2); break; //send @
    case DOUBLE_TAP: SEND_STRING("rick.c.kremer@gmail.com"); break; //send email address
    case TRIPLE_TAP: SEND_STRING("rkremer@nd.gov"); //send work email
  }
}

void email_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (email_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_2); break; //unregister @
    case DOUBLE_TAP: ; break;
    case TRIPLE_TAP: ;break;
  }
  email_state.state = 0;
}
//*************** EMAIL *******************//

//*************** BRACKETS *******************//
//Left brackets
void lbkts_finished (qk_tap_dance_state_t *state, void *user_data) {
  lbkts_state.state = cur_dance(state); //Use the dance that favors being held
  switch (lbkts_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_9); break; //send (
    case DOUBLE_TAP: register_code(KC_LBRC); break; //send [
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(KC_LBRC); //send {
  }
}

void lbkts_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lbkts_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_9); break; //unregister (
    case DOUBLE_TAP: unregister_code(KC_LBRC); break; //unregister [
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_LBRC); //unregsister {
  }
  lbkts_state.state = 0;
}

//Right brackets
void rbkts_finished (qk_tap_dance_state_t *state, void *user_data) {
  rbkts_state.state = cur_dance(state); //Use the dance that favors being held
  switch (rbkts_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(KC_0); break; //send (
    case DOUBLE_TAP: register_code(KC_RBRC); break; //send [
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(KC_RBRC); //send {
  }
}

void rbkts_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rbkts_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_0); break; //unregister (
    case DOUBLE_TAP: unregister_code(KC_RBRC); break; //unregister [
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(KC_RBRC); //unregsister {
  }
  rbkts_state.state = 0;
}
//*************** BRACKETS *******************//



