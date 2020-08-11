#pragma once

#define ZK_MEDIA TD(0)
#define ZK_SEMI TD(1)
#define ZK_COLON TD(2)

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

qk_tap_dance_action_t tap_dance_actions[] = {
    [0] = ACTION_TAP_DANCE_FN(ios_media),
    [1] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_SCOLON),
    [2] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COLON),
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

    // LEAD then ZZ: save and exit Vim
    SEQ_TWO_KEYS(KC_Z, KC_Z) {
        SEND_STRING(SS_TAP(X_ESC) SS_LSFT("zz"));
    }
    // LEAD then ZQ: exit Vim (without saving)
    SEQ_TWO_KEYS(KC_Z, KC_Q) {
        SEND_STRING(SS_TAP(X_ESC) SS_LSFT("zq"));
    }
  }
}


