#ifndef _SEGA_H_
#define _SEGA_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// #define ENABLE_UART

////////////////////////////////////
// sega g80 memory map
#define CPU_ROM         (0x0000) // 2k power on and diagnostics rom (cpu board)
#define CPU_ROM_SZ      (2*1024)

#define ROM_BOARD       (0x0800) // 46k rom board
#define ROM_BOARD_SZ    (46*1024)

// 6k image for the usb's 8035 (allocated at end of our image)
#define USB_ROM_SZ_A   (4*1024)
#define USB_ROM_SZ_B   (2*1024)
#define USB_ROM_A      (0x6800)  // from 26k-32k address
#define USB_ROM_B      (USB_ROM_A+USB_ROM_SZ_A)

#define CPU_RAM         (0xC800) // 2k ram (cpu board)
#define CPU_RAM_SZ      (2*1024)

#define USB_RAM         (0xD000) // 4k ram for the 8035 (universal serial board)
#define USB_RAM_SZ      (4*1024)

#define VECTOR_RAM      (0xE000) // 4k ram (xy board)
#define VECTOR_RAM_SZ   (4*1024)
#define SYMBOLS_SZ      (0x180)
////////////////////////////////////

// Test button on CPU board asserts NMI
// 40Hz interrupt from vector timing board

#pragma output CRT_ORG_DATA = 0xC800  // start of RAM

#pragma output CRT_MODEL = 1 // data section copied from ROM into RAM on program start
//#pragma output CRT_MODEL = 2 // data section zx7 compressed in ROM, decompressed into RAM on program start

#ifdef ENABLE_BOOTROM
/*
   Simply setting CRT_ORG_VECTOR_TABLE will not work, since it's  ignored when CRT_ORG_CODE is non zero.
   Workaround is to patch z88dk/libsrc/_DEVELOPMENT/target/z80/startup/z80_crt_0.asm.m4 as follows:
   ;IF (ASMPC = 0) && (__crt_org_code = 0)
     include "../crt_page_zero_z80.inc"
   ;ENDIF
*/
   #pragma output CRT_ORG_CODE = 0x0800 // when using boot rom
//   #pragma output CRT_ORG_VECTOR_TABLE = -0x0800
#else
   #pragma output CRT_ORG_CODE = 0x0000
#endif


#pragma output REGISTER_SP = 0xCFFF

// used to calculate heap size (default is just unused ram)
// #pragma output CRT_STACK_SIZE = 0xf // 128

#pragma output CRT_ENABLE_RST = 0x80 // User implements rst38h (IM1). user must preserve register values and exit with "ei; reti"
// #pragma output CRT_ENABLE_RST = 0x00 // User implements no isrs (default)
#pragma output CRT_ENABLE_NMI = 1 // program supplies nmi isr
#pragma output CRT_ENABLE_EIDI = 0x01 // disable interrupts di on start
//#pragma output CRT_ENABLE_EIDI = 0x02 // enable interrupts ei on start
#pragma output CRT_INTERRUPT_MODE = 1
#pragma output CLIB_MALLOC_HEAP_SIZE = 0
#pragma output CLIB_STDIO_HEAP_SIZE = 0


__sfr __at 0xfc PORT_374;
// |   D7    |   D6    |   D5    |   D4    |   D3    |   D2    |   D1    |   D0   |
// +=========+=========+=========+=========+=========+=========+=========+========+
// |  P1-30  |  P1-29  |  P1-28  |  P1-27  |  P1-26  |  P1-25  |  P1-24  |  P1-23 |
// +---------+---------+---------+---------+---------+---------+---------+--------+
// |RotL P2  |RotR P2  | FIRE P2 |THRUST P2|   <--- SPACE FURY (cocktail)         |
// +---------+---------+---------+---------+---------+---------+---------+--------+
// ELIMINATOR --->                                   |RotR Red |ThrustRed|Fire Red|
// +---------+---------+---------+---------+---------+---------+---------+--------+
// STAR TREK  --->     | WARP    | PHOTON  | PHASER  | IMPULSE | 2Player |1Player 
#define BUTTON_PLAYER_1 (1<<0)
#define BUTTON_PLAYER_2 (1<<1)
#define BUTTON_THRUST   (1<<2)
#define BUTTON_FIRE     (1<<3)
#define BUTTON_PHOTON   (1<<4)
#define BUTTON_WARP     (1<<5)

__sfr __at 0xf8 PORT_370;
   #define PORT_370_D7      0x80
   #define PORT_370_D6      0x40
   #define PORT_370_D5      0x20
   #define PORT_370_D4      0x10
   #define PORT_370_D3      0x08
   #define PORT_370_D2      0x04
   #define PORT_370_D1      0x02
   #define PORT_370_D0      0x01
   #define PORT_SEL         PORT_370_D0

__sfr __at 0xf9 PORT_371;
   #define PORT_371_D7      0x80
   #define PORT_371_D6      0x40
   #define PORT_371_D5      0x20
   #define PORT_371_D4      0x10
   #define PORT_371_D3      0x08
   #define PORT_371_D2      0x04
   #define PORT_371_D1      0x02
   #define PORT_371_D0      0x01
   #define COIN_COUNTER_A   PORT_371_D7
   #define COIN_COUNTER_B   PORT_371_D6

#define PORT_LED            PORT_370
#define LED_1               PORT_370_D7
#define LED_2               PORT_370_D6


__sfr __at 0xbe XY_MULTIPLIER;
__sfr __at 0xbd XY_MULTIPLICAND;
__sfr __at 0xbf XY_INIT;

__sfr __at 0x38 SPEECH_COMMAND;
__sfr __at 0x3b SPEECH_CONTROL;
__sfr __at 0x39 VOTRAX_COMMAND;
__sfr __at 0x3f SOUND_COMMAND;


#define SEGA_ANGLE(deg)    ((uint16_t)(((float)(deg))*2.845))
#define divideBy3(x)       (((x)>>2)+((x)>>4))

#define MIN(a,b)           (((a)<(b))?(a):(b))
#define MAX(a,b)           (((a)>(b))?(a):(b))
#define LSB(x)             (uint8_t)((uint16_t)(x) & 0xFF)
#define MSB(x)             (uint8_t)(((uint16_t)(x) >> 8) & 0xFF)
#define LE(x)              LSB(x), MSB(x)

#define CENTER_X (1024)
#define CENTER_Y (1024)
#define MAX_X (1024+450)
#define MIN_X (1024-450)
#define MAX_Y (1024+400)
#define MIN_Y (1024-400)

// sounds
#define BASE_DRUM    0x2E
#define SNARE_DRUM   0x1E
#define HAT_DRUM     0x0E
#define TANK_MOVE    0x00
#define TANK_FIRE    0x1A


typedef enum {
   IMPULSE = 0x04,
   IMPULSE_END = 0x05,
   WARP = 0x06,
   WARP_END = 0x07,
   RED_ALERT = 0x0C,
   RED_ALERT_END = 0x0D,
   PHASER = 0x08,
   PHOTON = 0x0A,
   TARGETING = 0x0E,
   DENY = 0x10,
   SHIELD_HIT = 0x12,
   ENTERPRISE_HIT = 0x14,
   ENTERPRISE_EXPLOSION = 0x16,
   KLINGON_EXPLOSION = 0x1A,
   DOCK = 0x1C,
   STARBASE_HIT = 0x1E,
   STARBASE_RED = 0x11,
   WARP_SUCK = 0x18,
   WARP_SUCK_END = 0x2F,
   SAUCER_EXIT = 0x19,
   SAUCER_EXIT_END = 0x2F,
   STARBASE_EXPLOSION = 0x22,
   SMALL_BONUS = 0x24,
   LARGE_BONUS = 0x25,
   STARBASE_INTRO = 0x26,
   KLINGON_INTRO = 0x27,
   ENTERPRISE_INTRO = 0x28,
   PLAYER_CHANGE = 0x29,
   KLINGON_FIRE = 0x2E,
   HIGH_SCORE_MUSIC = 0x2A,
   COIN_DROP_MUSIC = 0x2B,
   NOMAD_MOTION = 0x2C,
   NOMAD_MOTION_END = 0x21,
   NOMAD_STOPPED = 0x2D,
   NOMAD_STOPPED_END = 0x21,
} sound_t;

typedef enum {
   NO_PHRASE = 0x00,                // no phrase
   COMMAND_THE_ENTERPRISE = 0x01,   // "COMMAND THE ENTERPRISE"
   PLAY_STAR_TREK = 0x02,           // "PLAY STAR TREK"
   WELCOME_ABOARD_CAPTAIN = 0x03,   // "WELCOME ABOARD, CAPTAIN" (SPOCK)
   CONGRATULATIONS = 0x04,          // "CONGRATULATIONS"
   HIGH_SCORE = 0x05,               // "HIGH SCORE"
   PRESS_PLAYER_ONE = 0x06,         // "PRESS PLAYER ONE"
   OR_PLAYER_TWO = 0x07,            // "OR PLAYER TWO"
   START = 0x08,                    // "START"
   BE_THE_CAPTAIN = 0x09,           // "BE THE CAPTAIN OF THE STARSHIP ENTERPRISE" (SCOTTY)
   DAMAGE_REPAIRED_SIR = 0x0A,      // "DAMAGE REPAIRED, SIR" (SCOTTY)
   SECTOR_SECURED = 0x0B,           // "SECTOR SECURED" (CHEKOV)
   ENTERING_SECTOR = 0x0C,          // "ENTERING SECTOR" (SPOCK)
   ZERO = 0x0D,                     // "ZERO"
   ONE = 0x0E,                      // "ONE"
   TWO = 0x0F,                      // "TWO"
   THREE = 0x10,                    // "THREE"
   FOUR = 0x11,                     // "FOUR"
   FIVE = 0x12,                     // "FIVE"
   SIX = 0x13,                      // "SIX"
   SEVEN = 0x14,                    // "SEVEN"
   EIGHT = 0x15,                    // "EIGHT"
   NINE = 0x16,                     // "NINE"
   POINT = 0x17,                    // "POINT"
   POINT_HIGHER_PITCH = 0x18,       // "POINT" (HIGHER PITCH)
   RED_ALERT_PHRASE = 0x19,         // "RED ALERT"
   LAST_PHRASE = 0x1A
} phrase_t;


////////////////////////////////////
// font.h
#define FONT_INSERT_COIN 0x01
#define FONT_PRESS_START 0x02
#define FONT_GAME_OVER   0x03
uint16_t installFonts( uint16_t addr );
uint16_t fontAddress( char c );

////////////////////////////////////
// math.h
uint8_t rand(void);
inline uint16_t xy_multiply( uint8_t x, uint8_t y );
uint16_t div_16(uint16_t u, uint16_t v);
uint8_t divideBy10(uint8_t *value);
uint8_t divideBy100(uint8_t *value);
int8_t sinlut(uint16_t sega_angle, bool *negsign);
uint8_t coslut(uint16_t sega_angle, bool *negsign);


#endif //_SEGA_H_
