#include QMK_KEYBOARD_H

// Layers
#define _BASE   0
#define _FN     1
#define _MEDIA  2

enum custom_keycodes {
  KC_TRP_GRV,
  KC_BSPC_DEL,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_TRP_GRV:
      if (record->event.pressed) {
        SEND_STRING("```\n\n```" SS_TAP(X_UP));
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
    }
  }
  return true;
};

void keyboard_post_init_user(void) {
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom_teal();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  switch (get_highest_layer(state)) {
    case _BASE:
      rgblight_sethsv_noeeprom_teal();
      break;
    case _FN:
      rgblight_sethsv_noeeprom_orange();
      break;
    case _MEDIA:
      rgblight_sethsv_noeeprom_white();
      break;
    default:
      rgblight_sethsv_noeeprom_teal();
      break;
  }
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_60_ansi_split_bs_rshift(
 //    _0       _1        _2      _3       _4      _5      _6      _7       _8       _9       _A        _B       _C       _D       _E
/*0_*/ KC_ESC,  KC_1,     KC_2,   KC_3,    KC_4,   KC_5,   KC_6,   KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
/*1_*/ KC_TAB,  KC_Q,     KC_W,   KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC, KC_RBRC, KC_BSPC_DEL,
/*2_*/ KC_LCTL, KC_A,     KC_S,   KC_D,    KC_F,   KC_G,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, KC_ENT,
/*3_*/ KC_LSFT, KC_Z,     KC_X,   KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,           KC_RSFT,          MO(_MEDIA),
/*4_*/ KC_LCTL, KC_LALT,          KC_LGUI,                 KC_SPC,                            MO(_FN),  KC_RGUI, KC_RALT, KC_RCTL
  ),

  [_FN] = LAYOUT_60_ansi_split_bs_rshift(
 //    _0            _1          _2          _3          _4          _5          _6          _7          _8          _9             _A             _B             _C             _D         _E
/*0_*/ KC_GRAVE,     KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,      KC_F6,      KC_F7,      KC_F8,      KC_F9,         KC_F10,        KC_F11,        KC_F12,        KC_INS,    KC_TRP_GRV,
/*1_*/ RCMD(KC_TAB), RCMD(KC_Q), RCMD(KC_W), RCMD(KC_E), RCMD(KC_R), RCMD(KC_T), RCMD(KC_Y), KC_PGUP,    RCMD(KC_I), RCMD(KC_O),    RCMD(KC_P),    RCMD(KC_LBRC), RCMD(KC_RBRC), KC_DEL,
/*2_*/ KC_LCTL,      RCMD(KC_A), RCMD(KC_S), KC_PGDN,    RCMD(KC_F), RCMD(KC_G), KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,      RCMD(KC_SCLN), RCMD(KC_QUOT), RCMD(KC_ENT),
/*3_*/ KC_TRNS,                  RCMD(KC_Z), RCMD(KC_X), RCMD(KC_C), RCMD(KC_V), RCMD(KC_B), RCMD(KC_N), RCMD(KC_M), RCMD(KC_COMM), RCMD(KC_DOT),  RCMD(KC_SLSH), RCMD(KC_RSFT),            MO(_MEDIA),
/*4_*/ KC_LCTL,        KC_LALT,       KC_LGUI,                                KC_SPC,                                KC_TRNS,       KC_RGUI,       KC_RALT,       KC_RCTL
  ),

  [_MEDIA] = LAYOUT_60_ansi_split_bs_rshift(
 //    _0       _1       _2       _3       _4        _5       _6       _7       _8       _9       _A       _B       _C       _D         _E
/*0_*/ KC_SLEP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,
/*1_*/ KC_TRNS, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MAGIC_TOGGLE_NKRO,
/*2_*/ KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
/*3_*/ KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
/*4_*/ KC_TRNS, KC_TRNS,          KC_TRNS,                    KC_TRNS,                            KC_TRNS, KC_TRNS,          KC_TRNS,   KC_TRNS
  )
};
