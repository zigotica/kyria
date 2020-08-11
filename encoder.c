#include QMK_KEYBOARD_H

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Arrows up/down (scroll, move line, ...)
        if (clockwise) {
          tap_code(KC_DOWN);
        } else {
          tap_code(KC_UP);
        }
    }
}

