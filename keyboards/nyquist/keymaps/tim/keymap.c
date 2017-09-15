#include "nyquist.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_X1 LOWER
#define KC_X2 RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TILD, 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,EQL ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     TAB , Q  , W  , E  , R  , T  ,      Y  , U  , I  , O  , P  ,MINS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     ESC , A  , S  , D  , F  , G  ,      H  , J  , K  , L  ,SCLN,QUOT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LSFT, Z  , X  , C  , V  , B  ,      N  , M  ,COMM,DOT ,SLSH,RSFT,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     LCTL,LALT, X1 , X2 ,SPC ,DEL ,     BSPC,ENT ,LEFT,DOWN, UP ,RGHT
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_LOWER] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         , 1  , 2  , 3  , 4  , 5  ,      6  , 7  , 8  , 9  , 0  ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     DEL ,    ,LEFT,RGHT, UP ,LBRC,     RBRC, P4 , P5 , P6 ,PLUS,PIPE,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,DOWN,LCBR,     RCBR, P1 , P2 , P3 ,MINS,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,     DEL ,    , P0 ,PDOT,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_RAISE] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     TILD,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,BSPC,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,EXLM, AT ,HASH,DLR ,PERC,     CIRC,AMPR,ASTR,LPRN,RPRN,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     DEL ,MPRV,MNXT,VOLU,PGUP,UNDS,     EQL ,HOME,    ,    ,    ,BSLS,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
     MUTE,MSTP,MPLY,VOLD,PGDN,MINS,     PLUS,END ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  ),

  [_ADJUST] = KC_KEYMAP(
  //,----+----+----+----+----+----.    ,----+----+----+----+----+----.
     F12 , F1 , F2 , F3 , F4 , F5 ,      F6 , F7 , F8 , F9 ,F10 ,F11 ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----|    |----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    ,
  //`----+----+----+----+----+----'    `----+----+----+----+----+----'
  )
};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
