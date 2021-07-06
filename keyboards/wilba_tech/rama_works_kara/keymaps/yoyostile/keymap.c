#include QMK_KEYBOARD_H
#include <time.h>
#include <stdlib.h>

// Layers
#define _BASE   0
#define _FN     1
#define _MEDIA  2

enum custom_keycodes {
  KC_TRP_GRV = SAFE_RANGE,
  KC_BSPC_DEL,
  KC_OSX_LOCK,
  KC_BYEBUG,
  KC_SHIT_TALK,
};

static bool shit_talk = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRP_GRV:
      if (record->event.pressed) {
        SEND_STRING("```");
        tap_code16(S(KC_ENTER));
        tap_code16(S(KC_ENTER));
        SEND_STRING("```");
        tap_code(KC_UP);
      }
      break;
    case KC_BSPC_DEL: {
      static uint16_t kc;
      kc = KC_BSPC;

      if (get_mods() & MOD_MASK_SHIFT) {
        kc = KC_DEL;
      }

      if (record->event.pressed) {
        register_code(kc);
      } else {
        unregister_code(kc);
      }
      break;
    };
    case KC_OSX_LOCK:
      tap_code16(LCMD(C(KC_Q)));
      break;
    case KC_BYEBUG:
      if (record->event.pressed) {
        SEND_STRING("require \"byebug\"; byebug");
      }
      break;
    case KC_SHIT_TALK:
      if (record->event.pressed) {
        shit_talk = !shit_talk;
      }
      return false;
    case KC_A:
    case KC_B:
    case KC_C:
    case KC_D:
    case KC_E:
    case KC_F:
    case KC_G:
    case KC_H:
    case KC_I:
    case KC_J:
    case KC_K:
    case KC_L:
    case KC_M:
    case KC_N:
    case KC_O:
    case KC_P:
    case KC_Q:
    case KC_R:
    case KC_S:
    case KC_T:
    case KC_U:
    case KC_V:
    case KC_W:
    case KC_X:
    case KC_Y:
    case KC_Z: {
      if (shit_talk) {
        if (record->event.pressed) {
          int r = rand();
          tap_code16((r % 2 == 0) ? S(keycode) : keycode);
        }
        return false;
      }
    };
  }

  return true;
};

void keyboard_post_init_user(void) {
  srand(time(NULL));
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_60_hhkb(
 //    _0       _1        _2      _3       _4      _5      _6      _7       _8       _9       _A        _B       _C       _D       _E
/*0_*/ KC_ESC,  KC_1,     KC_2,   KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSLS,  KC_GRV,
/*1_*/ KC_TAB,  KC_Q,     KC_W,   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSPC_DEL,
/*2_*/ KC_LCTL, KC_A,     KC_S,   KC_D,    KC_F,   KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
/*3_*/ KC_LSFT, KC_Z,     KC_X,   KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, MO(_MEDIA),
/*4_*/     KC_LALT, KC_LGUI,                                  KC_SPC,                               MO(_FN), KC_RGUI),

  [_FN] = LAYOUT_60_hhkb(
 //    _0            _1          _2          _3          _4          _5          _6          _7          _8             _9             _A             _B             _C             _D             _E
/*0_*/ KC_GRAVE,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,         KC_F9,         KC_F10,        KC_F11,        KC_F12,        KC_INS,        KC_TRP_GRV,
/*1_*/ RCMD(KC_TAB), RCMD(KC_Q), RCMD(KC_W), RCMD(KC_E), RCMD(KC_R), RCMD(KC_T), RCMD(KC_Y), KC_PGUP,    RCMD(KC_I),    RCMD(KC_O),    RCMD(KC_P),    RCMD(KC_LBRC), RCMD(KC_RBRC), KC_DEL,
/*2_*/ KC_LCTL,      RCMD(KC_A), RCMD(KC_S), KC_PGDN,    RCMD(KC_F), RCMD(KC_G), KC_LEFT,    KC_DOWN,    KC_UP,         KC_RIGHT,      RCMD(KC_SCLN), RCMD(KC_QUOT), RCMD(KC_ENT),
/*3_*/ KC_SHIT_TALK,      RCMD(KC_Z), RCMD(KC_X), RCMD(KC_C), RCMD(KC_V), KC_BYEBUG,  RCMD(KC_N), RCMD(KC_M), RCMD(KC_COMM), RCMD(KC_DOT),  RCMD(KC_SLSH), RCMD(KC_RSFT), MO(_MEDIA),
/*4_*/ KC_LALT, KC_LGUI,                               KC_SPC,                                 KC_TRNS,   KC_RGUI),


  [_MEDIA] = LAYOUT_60_hhkb(
 //    _0           _1       _2       _3       _4        _5       _6       _7       _8       _9       _A       _B       _C       _D         _E
/*0_*/ KC_OSX_LOCK, RESET, EF_DEC, EF_INC, H1_DEC,  H1_INC, H2_DEC, H2_INC, KC_TRNS, KC_TRNS, KC_TRNS, BR_DEC, BR_INC, KC_TRNS,   KC_TRNS,
/*1_*/ KC_TRNS, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, S1_DEC, S1_INC,  S2_DEC, S2_INC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, ES_DEC, ES_INC, KC_TRNS,
/*2_*/ KC_CAPS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
/*3_*/ KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,
/*4_*/ EEPROM_RESET, KC_TRNS,                               KC_TRNS,                               KC_TRNS, KC_TRNS)
};
