#include QMK_KEYBOARD_H
#include <print.h> // Used when debugging.
#include "version.h"

// Use callum-oakley's one-shot implementation, to avoid OSM bug in stock firmware.
// See https://github.com/qmk/qmk_firmware/issues/3963
#include "../../../users/callum/oneshot.h"

// This has to come before `keycodes` and `process_record_user`.
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

// Uncomment to see output in QMK Toolkit.
// Mac's on-screen keyboard viewer is also useful, and works even when not active application.
void keyboard_post_init_user( void ) {
	//debug_enable=true;
	//debug_matrix=true;
	//debug_keyboard=true;
	//debug_mouse=true;
}

bool is_oneshot_cancel_key( uint16_t keycode ) {
	// @todo Add mouse inputs if possible. Real mouse, not mouse keys on keyboard.
	return KC_ESCAPE == keycode;
}

bool is_oneshot_ignored_key( uint16_t keycode ) {
	switch ( keycode ) {
		case KC_LSFT:
		case OS_SHFT:
		case OS_CTRL:
		case OS_ALT:
		case OS_CMD:
			return true;

		default:
			return false;
	}
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state  = os_up_unqueued;
oneshot_state os_cmd_state  = os_up_unqueued;

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_ergodox_pretty(
		KC_ESCAPE,	  KC_1,		   KC_2,		   KC_3,		   KC_4,		   KC_5,		   KC_6,										   KC_TRANSPARENT, KC_7,		   KC_8,		   KC_9,		   KC_0,		   KC_MINUS,	   KC_EQUAL,
		KC_GRAVE,	   KC_Q,		   KC_W,		   KC_F,		   KC_P,		   KC_G,		   KC_LCBR,										KC_RCBR,		KC_J,		   KC_L,		   KC_U,		   KC_Y,		   KC_SCOLON,	  KC_BSLASH,
		KC_TAB,		 KC_A,		   KC_R,		   KC_S,		   KC_T,		   KC_D,																		   KC_H,		   KC_N,		   KC_E,		   KC_I,		   KC_O,		   KC_QUOTE,
		OS_SHFT,  KC_Z,		   KC_X,		   KC_C,		   KC_V,		   KC_B,		   KC_LBRACKET,									KC_RBRACKET,	KC_K,		   KC_M,		   KC_COMMA,	   KC_DOT,		 KC_SLASH,	   OS_SHFT,
		OS_CTRL,  KC_TRANSPARENT, KC_TRANSPARENT, OS_ALT,  OS_CMD,																								  OS_CMD,  OS_ALT,  KC_TRANSPARENT, KC_TRANSPARENT, OS_CTRL,
																OSL(2),		 KC_PGUP,		KC_LEFT,		KC_RIGHT,
																				KC_PGDOWN,	  KC_UP,
												KC_BSPACE,	  OSL(1),		 KC_DELETE,	  KC_DOWN,		KC_ENTER,	   KC_SPACE
	),

	[1] = LAYOUT_ergodox_pretty(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN3,	 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_PGUP,		KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   ST_MACRO_0,	 ST_MACRO_1,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,	 KC_MS_UP,	   KC_MS_BTN2,	 KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_MS_WH_DOWN,  RGUI(RSFT(KC_LBRACKET)),KC_UP,		  RGUI(RSFT(KC_RBRACKET)),KC_HOME,		KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_LEFT,	 KC_MS_DOWN,	 KC_MS_RIGHT,	KC_TRANSPARENT,																 KC_MS_WH_UP,	KC_LEFT,		KC_DOWN,		KC_RIGHT,	   KC_END,		 KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_PGDOWN,	  RGUI(KC_LBRACKET),KC_TRANSPARENT, RGUI(KC_RBRACKET),KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,																								 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
																KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
																				KC_TRANSPARENT, KC_TRANSPARENT,
												KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
	),

	[2] = LAYOUT_ergodox_pretty(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_TRANSPARENT, KC_BRIGHTNESS_UP,KC_AUDIO_VOL_UP,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_REWIND,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_FAST_FORWARD,KC_MEDIA_NEXT_TRACK,																KC_TRANSPARENT, KC_BRIGHTNESS_DOWN,KC_AUDIO_VOL_DOWN,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, WEBUSB_PAIR,									WEBUSB_PAIR,	KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_MUTE,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,																								 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
																KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
																				KC_TRANSPARENT, KC_TRANSPARENT,
												KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
	),

	[3] = LAYOUT_ergodox_pretty(
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,																 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,								 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
		KC_TRANSPARENT, KC_MEH,		 KC_HYPR,		KC_TRANSPARENT, KC_TRANSPARENT,																								 KC_TRANSPARENT, KC_TRANSPARENT, KC_MEH,		 KC_HYPR,		KC_TRANSPARENT,
																KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
																				KC_TRANSPARENT, KC_TRANSPARENT,
												KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
	),
};

bool process_record_user( uint16_t keycode, keyrecord_t *record ) {
	// Turn one-shot mods on/off.
	update_oneshot( &os_shft_state, KC_LSFT, OS_SHFT, keycode, record );
	update_oneshot( &os_ctrl_state, KC_LCTL, OS_CTRL, keycode, record );
	update_oneshot(	&os_alt_state, KC_LALT, OS_ALT,	keycode, record	);
	update_oneshot( &os_cmd_state, KC_LCMD, OS_CMD,	keycode, record	);

	switch (keycode) {
		// @todo tmp disabled b/c confilct w/ callum oneshot implementation.
		case ST_MACRO_0:
			if (record->event.pressed) {
				//SEND_STRING("---------------------");
				//SEND_STRING("a");  // tmp less annoying when macro bug happens
			}
		break;

		case ST_MACRO_1:
			if (record->event.pressed) {
				//SEND_STRING("- [ ] ");
			}
		break;
	}

	return true; // Continue processing the key event
}

uint32_t layer_state_set_user( uint32_t state ) {
	uint8_t layer = biton32( state );
	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();

	switch ( layer ) {
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
