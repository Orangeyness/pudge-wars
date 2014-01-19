#ifndef H_GAME_CONSTANTS_
#define H_GAME_CONSTANTS_

#include <cstddef>
#include <cstdint>

/***************** EXCEPTIONS ********************/

// Allegro
#define EXCEP_ALLEG_ENGINE_FAILED		0x01000010
#define EXCEP_ALLEG_DISPLAY_FAILED 		0x01000020
#define EXCEP_ALLEG_TIMER_FAILED 		0x01000030
#define EXCEP_ALLEG_EQUEUE_FAILED 		0x01000040
#define EXCEP_ALLEG_KEYBOARD_FAILED 	0x01000050
#define EXCEP_ALLEG_MOUSE_FAILED 		0x01000060
#define EXCEP_ALLEG_FONT_FAILED			0x01000070

// Engine Problems
#define EXCEP_STATE_UNEXPECTED_EMPTY	0x02000010
#define EXCEP_MULTIPLE_MESSAGE_ROUTERS  0x02000020
#define EXCEP_MISSING_MESSAGE_ROUTER  	0x02000021
#define EXCEP_DEBUG_WINDOW_EXISTS		0x02000030
#define EXCEP_DEBUG_WINDOW_MISSING		0x02000031

// Entity Problems
#define EXCEP_UNEXPECTED_ENTITY_TYPE	0x03000010

// State Problems
#define EXCEP_STATE_ALREADY_CHANGED		0x04000010
#define EXCEP_STATE_UNEXPECTED			0x04000020

// Event Problems
#define EXCEP_EVENT_WRONG_TYPE			0x05000030
#define EXCEP_EVENT_WRONG_ARGTYPE		0x05000031

// Service Problems
#define EXCEP_SERVICE_EXISTS			0x06000010
#define EXCEP_SERVICE_NONEXISTANT		0x06000011
#define EXCEP_SERVICE_NOT_IN_USE		0x06000012

/******************* EVENTS **********************/

#define EVENT_TYPE_ALL					0xFFFFFFFF
#define EVENT_TYPE_COLLISION			0x1000FFFF	/* Direct Messages EntityEventArgs, the other entity in the collision. */
#define EVENT_TYPE_SPAWN				0x2000FFFF
#define EVENT_TYPE_SPAWN_HOOK			0x20000001
#define EVENT_TYPE_ENTITY				0x4000FFFF
#define EVENT_TYPE_ENTITY_MOVE			0x40000001	/* Broadcasts (at least) EntityPositionEventArgs, the entity that moved and its new position. */
#define EVENT_TYPE_HOOK_ATTACH			0x40001000 	/* Broadcasts DoubleEntityPositionEventArgs, first entity the hooked, second entity the hook. */
#define EVENT_TYPE_HOOK_DETACH			0x40001001  /* Broadcasts EntityEventArgs, the entity is the now dettached hook. */

/********* COLLISION IDENTIFIER TYPES ************/

#define COLLISION_CHECK_BBOX			0x00000001
#define COLLISION_CHECK_RADIAL			0x00000002

/************** COLLISION GROUPS *****************/
#define COLLISION_GROUP_ALL				0xFFFFFFFF
#define COLLISION_GROUP_BASIC			0xFFFF0000
#define COLLISION_GROUP_PUDGES			0x00000001
#define COLLISION_GROUP_HOOKABLE		0x00000002
#define COLLISION_GROUP_HOOKED			0x00000004

#include <string>

std::string int_to_hex_string(int number);

#endif
