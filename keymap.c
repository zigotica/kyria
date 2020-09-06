#include QMK_KEYBOARD_H


enum layers {
    _TRIA = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};


// TAP DANCE SEQUENCES AND SHORTCUTS
// -----------------------------------------------------------
void ios_media(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_MPLY);
    } else if (state->count == 2) {
        tap_code(KC_MNXT);
    } else if (state->count == 3) {
        tap_code(KC_MPRV);
    } else {
        reset_tap_dance(state);
    }
}

#define ZK_MEDIA TD(0)
#define ZK_SEMI TD(1)
#define ZK_COLON TD(2)
#define ZK_BRC TD(3)
#define ZK_PRN TD(4)

qk_tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_FN(ios_media),
    [1] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCOLON),
    [2] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLON),
    [3] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [4] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
};


// LEADER KEY SHORTCUTS
// -----------------------------------------------------------
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // LEAD then T: COMMAND + SHIFT + T
    SEQ_ONE_KEY(KC_T) {
      SEND_STRING(SS_LGUI(SS_LSFT("t")));
    }

    // LEAD then Z: save and exit Vim
    SEQ_ONE_KEY(KC_Z) {
      SEND_STRING(SS_TAP(X_ESC) SS_LSFT("zz"));
    }
    // LEAD then Q: exit Vim (without saving)
    SEQ_ONE_KEY(KC_Q) {
      SEND_STRING(SS_TAP(X_ESC) SS_LSFT("zq"));
    }
  }
}

// OLED
// -----------------------------------------------------------
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria v1.2\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _TRIA:
            oled_write_P(PSTR("TRIA\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("FNC\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
// ENCODER
// -----------------------------------------------------------
void encoder_update_user(uint8_t index, bool clockwise)
{
  // check if shift is pressed
  const uint16_t shift_on = keyboard_report->mods & (MOD_BIT(KC_LSFT));

  if (index == 0) {
    // Volume control
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) {
    // Arrows up/down (scroll, move line, ...)
    if (shift_on) {
      unregister_code(KC_LSFT);
      if (clockwise) {
        tap_code(KC_RIGHT);
      } else {
        tap_code(KC_LEFT);
      }
      // reattach the mod so we can keep rotating
      register_code(KC_LSFT);
    } else {
      if (clockwise) {
        tap_code(KC_DOWN);
      } else {
        tap_code(KC_UP);
      }
    }
  }
}
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: TRIA
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * | MEDIA  |  ` ~ |   W  |  X   |   D  |  Y   |                              |   F  |   H  |   B  |   P  | ' "  |RSHF/ENC|
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  TAB   |   T  |   R  |  I   |   A  |  G   |                              |   K  |   L  |   S  |   N  |   M  |  =  +  |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift | [  { |   Q  |  U   |   O  |  Z   |  (   | \  | |  |      | LEAD |   J  |   C  |   V  | ,  < | . >  |  -  _  |
 * |        | TD ]}|      |      |      |      | TD ) |      |  |      |      |      |      |      | TD ; | TD : |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      | CTRL | CMD  | Space| Esc  |  | Enter| E    | BACK | AltGr| /  ? |
 *                        |      |      |      | Lower| Raise|  | Raise| Lower|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_TRIA] = LAYOUT(
      ZK_MEDIA,   KC_GRV, KC_W, KC_X, KC_D, KC_Y,                                                                         KC_F, KC_H, KC_B, KC_P, KC_QUOT,    KC_RSFT, 
      KC_TAB,       KC_T, KC_R, KC_I, KC_A, KC_G,                                                                         KC_K, KC_L, KC_S, KC_N, KC_M,        KC_EQL, 
      KC_LSFT,    ZK_BRC, KC_Q, KC_U, KC_O, KC_Z,    ZK_PRN, KC_BSLS,                     KC_NO, KC_LEAD,                 KC_J, KC_C, KC_V, ZK_SEMI, ZK_COLON, KC_MINS, 
                     KC_NO , KC_LCTL, KC_LGUI, LT(_LOWER, KC_SPC), LT(_RAISE, KC_ESC),   LT(_RAISE, KC_ENT) , LT(_LOWER, KC_E), KC_BSPC, KC_RALT, KC_SLSH 
    ),

/*
 * Lower Layer: Numbers and Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |      |      |  #   |  %   |      |                              |      |  7   |  8   |  9   |      |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  $   |  ^   |  !   |  &   |      |                              |      |  4   |  5   |  6   |  *   |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |  @   |      |      |      |  |      |      |  0   |  1   |  2   |  3   |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | DEL  |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      _______, _______, _______, KC_HASH, KC_PERC, _______,                                                   _______, KC_7, KC_8, KC_9, _______, _______,
      _______, KC_DLR,  KC_CIRC, KC_EXLM, KC_AMPR, _______,                                                   _______, KC_4, KC_5, KC_6, KC_ASTR, _______,
      _______, _______, _______, _______, KC_AT, KC_RBRACKET, KC_RIGHT_PAREN, _______,     _______, _______, KC_0,   KC_1, KC_2, KC_3, _______, _______,
                                 _______, _______, _______, _______, _______,                _______, _______, KC_DEL, _______, _______
    ),

/*
 * Raise Layer: Navigation
 *
 * ,-------------------------------------------.                              ,--------------------------------------------.
 * |        |      |      |      |      |      |                              |       |      |      |      |      |        |
 * |--------+------+------+------+------+------|                              |-------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |KC_WH_U|      | Up   |      |      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+-------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |KC_WH_D| Left | Down | Right|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+-------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      | DEL   |      |      |
 *                        `----------------------------------'  `-----------------------------------'
 */
    [_RAISE] = LAYOUT(
      _______,   _______, _______, _______, _______, _______,                                       _______, _______, _______, _______,  _______, _______,
      _______, _______, _______, _______, _______, _______,                                         KC_WH_U, _______, KC_UP,   _______,  _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, KC_WH_D, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,
                                 _______, _______, _______, _______, _______,     _______, _______, KC_DEL, _______,  _______
    ),

/*
 * Function Layer
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_ADJUST] = LAYOUT(
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};



layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


