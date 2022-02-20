#include QMK_KEYBOARD_H
#include "version.h" // do i still need this?

// Use callum-oakley's one-shot implementation, to avoid OSM bug in stock firmware.
// See https://github.com/qmk/qmk_firmware/issues/3963
#include "../../../users/callum/oneshot.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)

void keyboard_post_init_user(void) {
  debug_enable=true; // is this needed when rulefile has constant?
//  need someithing else in here? not seeing output in qmktoolbox anymore
}

// This has to come before `keycodes` and `process_record_user()`.
enum custom_keycodes {
    RGB_SLD = EZ_SAFE_RANGE,
    ST_MACRO_0,
    ST_MACRO_1,
};

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ergodox_pretty(
        KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,                                           KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_0,           KC_MINUS,       KC_EQUAL,
        KC_GRAVE,       KC_Q,           KC_W,           KC_F,           KC_P,           KC_G,           KC_LCBR,                                        KC_RCBR,        KC_J,           KC_L,           KC_U,           KC_Y,           KC_SCOLON,      KC_BSLASH,
        KC_TAB,         KC_A,           KC_R,           KC_S,           KC_T,           KC_D,                                                                           KC_H,           KC_N,           KC_E,           KC_I,           KC_O,           KC_QUOTE,

        // callum oneshot
//        OS_SHFT,  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRACKET,                                    KC_RBRACKET,    KC_K,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       OS_SHFT,
//        OS_CTRL,  KC_TRANSPARENT, KC_TRANSPARENT, OS_ALT, OS_CMD,                                                                                                  OS_CMD,  OS_ALT,  KC_TRANSPARENT, KC_TRANSPARENT, OS_CTRL,

        // native oneshot
        OSM(MOD_LSFT),  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRACKET,                                    KC_RBRACKET,    KC_K,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       OSM(MOD_RSFT),
        OSM(MOD_LCTL),  KC_TRANSPARENT, KC_TRANSPARENT, OSM(MOD_LALT),  OSM(MOD_LGUI),                                                                                                  OSM(MOD_RGUI),  OSM(MOD_RALT),  KC_TRANSPARENT, KC_TRANSPARENT, OSM(MOD_RCTL),

        // native w/ callum cmd - macros work here?
         // but then stops all input after a few minutes? but that happens w/ other stuff too?
//        OSM(MOD_LSFT),  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRACKET,                                    KC_RBRACKET,    KC_K,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       OSM(MOD_RSFT),
//        OSM(MOD_LCTL),  KC_TRANSPARENT, KC_TRANSPARENT, OSM(MOD_LALT),  OS_CMD,                                                                                                  OS_CMD,  OSM(MOD_RALT),  KC_TRANSPARENT, KC_TRANSPARENT, OSM(MOD_RCTL),

// callum oneshot w/ native cmd
//        OS_SHFT,  KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_LBRACKET,                                    KC_RBRACKET,    KC_K,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       OS_SHFT,
//        OS_CTRL,  KC_TRANSPARENT, KC_TRANSPARENT, OS_ALT, OSM(MOD_LGUI),                                                                                                  OSM(MOD_RGUI),  OS_ALT,  KC_TRANSPARENT, KC_TRANSPARENT, OS_CTRL,


                                                                                                    OSL(2),         KC_PGUP,        KC_LEFT,        KC_RIGHT,
                                                                                                                    KC_PGDOWN,      KC_UP,
                                                                                    KC_BSPACE,      OSL(1),         KC_DELETE,      KC_DOWN,        KC_ENTER,       KC_SPACE
    ),
    [1] = LAYOUT_ergodox_pretty(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN3,     KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PGUP,        KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   ST_MACRO_0,     ST_MACRO_1,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MS_WH_DOWN,  RGUI(RSFT(KC_LBRACKET)),KC_UP,          RGUI(RSFT(KC_RBRACKET)),KC_HOME,        KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT,                                                                 KC_MS_WH_UP,    KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_END,         KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_PGDOWN,      RGUI(KC_LBRACKET),KC_TRANSPARENT, RGUI(KC_RBRACKET),KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [2] = LAYOUT_ergodox_pretty(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_BRIGHTNESS_UP,KC_AUDIO_VOL_UP,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_REWIND,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_FAST_FORWARD,KC_MEDIA_NEXT_TRACK,                                                                KC_TRANSPARENT, KC_BRIGHTNESS_DOWN,KC_AUDIO_VOL_DOWN,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, WEBUSB_PAIR,                                    WEBUSB_PAIR,    KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
    [3] = LAYOUT_ergodox_pretty(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_MEH,         KC_HYPR,        KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_MEH,         KC_HYPR,        KC_TRANSPARENT,
                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                                                    KC_TRANSPARENT, KC_TRANSPARENT,
                                                                                    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),
};


bool is_oneshot_cancel_key(uint16_t keycode) {
    return KC_ESCAPE == keycode;
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
        // these keys wont cancel the oneshot, so should have mods here
        case OS_SHFT:
        case OS_CTRL:
        case OS_ALT:
        case OS_CMD:
            return true;

        default:
            // all other keys (like normal keys, A _ 4 etc) will be used and then cancel the oneshot
            return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
//    #ifdef CONSOLE_ENABLE
//        uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
//    #endif


    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );


      switch (keycode) {
            case ST_MACRO_0:
                if (record->event.pressed) {
                  //SEND_STRING("---------------------");
                  SEND_STRING("a");  // tmp less annoying until fixed
                    // everything works fine if nothing is sent, right? it must. so that means something is already active?
                    // maybe layer switching causes a problem?

                   printf("what does the state of various things look like? oneshot is active at this point but it shouldn't be, right?");
                }
            break;

            case ST_MACRO_1:
                if (record->event.pressed) {
                  SEND_STRING("- [ ] ");
                }
            break;

            // clear native oneshot for use when callum not working
//            case KC_ESC:
//                if (!record->event.pressed) { // keyup
//                    //clear_mods();
//                    clear_oneshot_mods(); // maybe more specefic, but only works in layer state func?
//                }
//            break;

    }

    return true; // Continue processing the key event.
}

uint32_t layer_state_set_user(uint32_t state) {
    uint8_t layer = biton32(state);
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (layer) {
        case 1:
            ergodox_right_led_1_on();
        break;

        case 2:
            ergodox_right_led_2_on();
        break;

        case 3:
            ergodox_right_led_3_on();
        break;

        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
        break;

        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
        break;

        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
        break;

        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
        break;
    }

    return state;
};
