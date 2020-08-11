#include QMK_KEYBOARD_H

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
