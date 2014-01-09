#include "UserInputProxy.cpp"
#include "gtest/gtest.h"

#include <cmath>
#include <allegro5/allegro.h>

#define _AL_KEYBOARD_STATE_INI(STATE)									\
	memset(STATE, 0, sizeof(ALLEGRO_KEYBOARD_STATE))

#define _AL_KEYBOARD_STATE_KEY_DOWN(STATE, KEYCODE)                     \
   (((STATE).__key_down__internal__[(KEYCODE) / 32] & (1 << ((KEYCODE) % 32)))\
    ? true : false)

#define _AL_KEYBOARD_STATE_SET_KEY_DOWN(STATE, KEYCODE)                 \
   do {                                                                 \
      int kc = (KEYCODE);                                               \
      (STATE).__key_down__internal__[kc / 32] |= (1 << (kc % 32));      \
   } while (0)

#define _AL_KEYBOARD_STATE_CLEAR_KEY_DOWN(STATE, KEYCODE)               \
   do {                                                                 \
      int kc = (KEYCODE);                                               \
      (STATE).__key_down__internal__[kc / 32] &= ~(1 << (kc % 32));     \
   } while (0)


TEST(UserInputProxy, NoMoveDirection) {
	ALLEGRO_KEYBOARD_STATE kbState;
	ALLEGRO_MOUSE_STATE mState;

	_AL_KEYBOARD_STATE_INI(&kbState);

	UserInputProxy uip;

	uip.update(&kbState, &mState);

	ASSERT_FALSE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, 0);
	ASSERT_EQ(uip.moveDirection().y, 0);
}

TEST(UserInputProxy, ArrowKeyDirections) {
	ALLEGRO_KEYBOARD_STATE kbState;
	ALLEGRO_MOUSE_STATE mState;

	_AL_KEYBOARD_STATE_INI(&kbState);

	UserInputProxy uip;

	// Up
	_AL_KEYBOARD_STATE_SET_KEY_DOWN(kbState, ALLEGRO_KEY_UP);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, 0);
	ASSERT_EQ(uip.moveDirection().y, -1);

	// Up Left
	_AL_KEYBOARD_STATE_SET_KEY_DOWN(kbState, ALLEGRO_KEY_LEFT);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, -1.0/sqrt(2));
	ASSERT_EQ(uip.moveDirection().y, -1.0/sqrt(2));

	// Left
	_AL_KEYBOARD_STATE_CLEAR_KEY_DOWN(kbState, ALLEGRO_KEY_UP);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, -1.0);
	ASSERT_EQ(uip.moveDirection().y, 0);

	// Down Left
	_AL_KEYBOARD_STATE_SET_KEY_DOWN(kbState, ALLEGRO_KEY_DOWN);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, -1.0/sqrt(2));
	ASSERT_EQ(uip.moveDirection().y, 1.0/sqrt(2));

	// Down
	_AL_KEYBOARD_STATE_CLEAR_KEY_DOWN(kbState, ALLEGRO_KEY_LEFT);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, 0);
	ASSERT_EQ(uip.moveDirection().y, 1.0);

	// Down Right
	_AL_KEYBOARD_STATE_SET_KEY_DOWN(kbState, ALLEGRO_KEY_RIGHT);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, 1.0/sqrt(2));
	ASSERT_EQ(uip.moveDirection().y, 1.0/sqrt(2));

	// Right
	_AL_KEYBOARD_STATE_CLEAR_KEY_DOWN(kbState, ALLEGRO_KEY_DOWN);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, 1.0);
	ASSERT_EQ(uip.moveDirection().y, 0);

	// Up Right
	_AL_KEYBOARD_STATE_SET_KEY_DOWN(kbState, ALLEGRO_KEY_UP);
	uip.update(&kbState, &mState);

	ASSERT_TRUE(uip.hasMoveDirection());
	ASSERT_EQ(uip.moveDirection().x, 1.0/sqrt(2));
	ASSERT_EQ(uip.moveDirection().y, -1.0/sqrt(2));
}
