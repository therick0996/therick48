
#include QMK_KEYBOARD_H

// Layers
#define _QW			    0
#define _LOWER		  1
#define _RAISE		  2
#define _FN			    3
#define _LWL0 		  4
#define _LWL1		    5
#define _FN2        6

// Custom keycodes
enum custom_keycodes {
  EMAIL = SAFE_RANGE,
  WEMAIL,

};

// Readability keycodes
#define _______		  KC_TRNS

// Layer codes
#define LOWER 		  MO(_LOWER)
#define RAISE 		  MO(_RAISE)
#define FN 		  	  MO(_FN)
#define FN2         MO(_FN2)

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
#define SFT_CAPS	  SFT_T(KC_CAPSLOCK)
#define SFT_MUTE    SFT_T(KC_MUTE)
#define SFT_VOLD    SFT_T(KC_VOLD)

#define ALT_LEFT    ALT_T(KC_LEFT)
#define ALT_RGHT    ALT_T(KC_RIGHT)
#define ALT_UP      ALT_T(KC_UP)
#define ALT_MUTE    LALT_T(KC_MUTE)
#define ALT_VOLD    LALT_T(KC_VOLD)

#define HPR_SPC     HYPR_T(KC_SPC)

//MacOS Specific Stuff Workarounds
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
  |    Fn 2   |   Ctrl    |    Alt    |    GUI    |  Lwr BS   |    BS     |   Space   |  Rse Spc  |   Left    |   Down    |     Up    |   Right   |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_QW] = LAYOUT_ortho_4x12(
    KC_ESC,     KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,       KC_DEL,
    FN_TAB,     KC_A,       KC_S,       KC_D,       GUI_F,      KC_G,       KC_H,       GUI_J,      KC_K,       KC_L,       KC_SCLN,    SFT_QUOT,
    KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,       KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_ENT,
    FN2,        KC_LCTL,    KC_LALT,    KC_LGUI,    LWR_BS,     GUI_BS,     HPR_SPC,    RSE_SPC,    CTL_LEFT,   KC_DOWN,    KC_UP,      CTL_RGHT
  ),

/* Lower
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |           |     (     |     )     |     -     |     =     |    ***    |    ***    |    BS     |     7     |     8     |     9     |     -     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |   LWL0    |   Home    |   Pg Dn   |   Pg Up   |    End    |    BS     |    F4     |    F2     |     4     |     5     |     6     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |   Left    |    Down   |    Up     |   Right   |    ***    |   Raise   | NotifCent |     1     |     2     |     3     |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Lower   |           |           |   LWL0    |     0     |     .     |     *     |     /     |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_LOWER] = LAYOUT_ortho_4x12(
    _______,    KC_LPRN,    KC_RPRN,    KC_MINS,    KC_EQL,     KC_NO,      KC_NO,      KC_BSPC,     KC_P7,     KC_P8,      KC_P9,      KC_PMNS,
    LWL0_TAB,   KC_HOME,    KC_PGDN,    KC_PGUP,    LWL1_END,   KC_BSPC,    KC_F4,      KC_F2,       KC_P4,     KC_P5,      KC_P6,      KC_PPLS,
    _______,    KC_LEFT,    KC_DOWN,    KC_UP,      KC_RGHT,    KC_NO,      MO(2),      NOTIFCENT,   KC_P1,     KC_P2,      KC_P3,      KC_PENT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    LWL0_SPC,    KC_P0,     KC_PDOT,    KC_PAST,    KC_PSLS
  ),

    /* LWL0
      .-----------------------------------------------------------------------------------------------------------------------------------------------.
      |           |           |           |           |           |           |           |           |    BS     |     /     |     *     |    Del    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   LWL0    |   GUI     |   Shift   |    Alt    |    Del    |           |           |           |   Left    |   Down    |     Up    |   Right   |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |   LWL0    |           |           |           |           |
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
      |           |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |   RESET   |           |           |           |           |   LWL1    |           |           |     $     |     ,     |     %     |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |           |           |
      |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
      |           |           |           |           |           |           |           |           |           |           |  NumLock  |   LWL1    |
      '-----------------------------------------------------------------------------------------------------------------------------------------------'
    */

      [_LWL1] = LAYOUT_ortho_4x12(
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        RESET,      _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_DLR,     KC_COMM,    KC_PERC,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
        _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_NLCK,    _______
      ),

/* Raise
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |     1     |     2     |     3     |     4     |     5     |     6     |     7     |     8     |     9     |     0     |     -     |     =     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |     !     |     @     |     #     |     $     |     %     |     ^     |     &     |     *     |     (     |     )     |     _     |     +     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |     `     |           |           |           |           |           |           |     [     |     ]     |     \     |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |  TG(Lwr)  |   Raise   |   Play    |   Vol-    |   Vol+    |   Mute    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_RAISE] = LAYOUT_ortho_4x12(
    KC_1,       KC_2,       KC_3,       KC_4,       KC_5,       KC_6,       KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,
    KC_EXLM,    KC_AT,      KC_HASH,    KC_DLR,     KC_PERC,    KC_CIRC,    KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RPRN,    KC_UNDS,    KC_PLUS,
    _______,    KC_GRAVE,   _______,    _______,    _______,    _______,    _______,    _______,    KC_LBRC,    KC_RBRC,    KC_BSLS,    _______,
    _______,    _______,    _______,    _______,    _______,    _______,    TG(1),      _______,    GUI_MPLY,   SFT_VOLD,   CTL_VOLU,   ALT_MUTE
  ),

/* FN
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  |    F1     |    F2     |    F3     |    F4     |    F5     |    F6     |    F7     |    F8     |    F9     |   F10     |   F11     |    BS     |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |    Fn     |    GUI    |   Shift   |  Option   |    Del    |           |    F2     |   Left    |    Down   |    Up     |   Right   |   Enter   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |   Enter   |           |           |           |   Home    |   Pg Dn   |   Pg Up   |    End    |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_FN] = LAYOUT_ortho_4x12(
    KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,     KC_F12,
    _______,    KC_LGUI,    KC_LSFT,    KC_LALT,    KC_DEL,     _______,    KC_F2,      CTL_LEFT,   KC_DOWN,    KC_UP,      CTL_RGHT,   KC_ENT,
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     _______,
    _______,    _______,    _______,    _______,    KC_ENT,     _______,    _______,    _______,    KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END 
  ),

/* FN2
  .-----------------------------------------------------------------------------------------------------------------------------------------------.
  | Bright Up | Bright Dn | Miss Ctrl |           |           |           |  Rewind   |   Play    | Fast Fwd  |   Mute    |  Vol Up   |  Vol Dn   |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           | Prnt Scrn | Prnt Sel  | Prt Sel C |           |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |   EMAIL   |  WEMAIL   |           |           |           |           |           |           |           |           |           |
  |-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------|
  |           |           |           |           |           |           |           |           |           |           |           |           |
  '-----------------------------------------------------------------------------------------------------------------------------------------------'
*/

  [_FN2] = LAYOUT_ortho_4x12(
    KC_BRID,    KC_BRIU,    MSNCTRL,    _______,    _______,    _______,    KC_MRWD,    KC_MPLY,    KC_MFFD,    KC_MUTE,    KC_VOLD,    KC_VOLU,
    _______,    WHLSCR,     PRNTSCR,    PRNTSCRC,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
    _______,    EMAIL,      WEMAIL,     _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,
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
    case EMAIL:
      if (record->event.pressed) {
        // when keycode EMAIL is pressed
        SEND_STRING("rick.c.kremer@gmail.com");
      } else {
        // when keycode EMAIL is released
      }
      break;

    case WEMAIL:
      if (record->event.pressed) {
        // when keycode WEMAIL is pressed
        SEND_STRING("rkremer@nd.gov");
      } else {
        // when keycode WEMAIL is released
      }
      break;

  }
  return true;
};


/*const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  keyevent_t event = record->event;
    (void)event;

  switch (id) {

  }
  return MACRO_NONE;
}


void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
*/