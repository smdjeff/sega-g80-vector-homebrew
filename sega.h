#ifndef _SEGA_H_
#define _SEGA_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>



#define BIT(n)             (1<<(n))
#define MIN(a,b)           (((a)<(b))?(a):(b))
#define MAX(a,b)           (((a)>(b))?(a):(b))
#define LSB(x)             (uint8_t)((uint16_t)(x) & 0xFF)
#define MSB(x)             (uint8_t)(((uint16_t)(x) >> 8) & 0xFF)
#define LE(x)              LSB(x), MSB(x)
#define SECONDS(s)         ((s)*1000/25)



////////////////////////////////////
// sega g80 memory map
#define CPU_ROM         (0x0000) // 2k power on and diagnostics rom (cpu board)
#define CPU_ROM_SZ      (2*1024)

#define ROM_BOARD       (0x0800) // 46k rom board
#define ROM_BOARD_SZ    (46*1024)

#define CPU_RAM         (0xC800) // 2k ram (cpu board)
#define CPU_RAM_SZ      (2*1024)

#define USB_RAM         (0xD000) // 4k ram for the 8035 (universal serial board)
#define USB_RAM_SZ      (4*1024)

#define VECTOR_RAM      (0xE000) // 4k ram (xy board)
#define VECTOR_RAM_SZ   (4*1024)
#define VECTOR_RAM_END  (VECTOR_RAM+VECTOR_RAM_SZ)
#define SYMBOLS_SZ      (0x160)
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
#define BUTTON_PLAYER_1    BIT(0)
#define BUTTON_PLAYER_2    BIT(1)
#define BUTTON_THRUST      BIT(2)
#define BUTTON_FIRE        BIT(3)
#define BUTTON_PHOTON      BIT(4)
#define BUTTON_WARP        BIT(5)

__sfr __at 0xf8 PORT_370;
#define SELECT_SPINNER     0xFE
#define SELECT_BUTTONS     0xFF
#define IO_COIN_N          BIT(5)

__sfr __at 0xf9 PORT_371;

__sfr __at 0xbe XY_MULTIPLIER;
__sfr __at 0xbd XY_MULTIPLICAND;
__sfr __at 0xbf XY_INIT;

__sfr __at 0x38 SPEECH_COMMAND;
__sfr __at 0x3b SPEECH_CONTROL;
__sfr __at 0x39 VOTRAX_COMMAND;
__sfr __at 0x3f SOUND_COMMAND;


//   2048-   -------------------
//          |                   |
//          |                   |
//   1536-  |     ---------     |
//          |    |         |    |
//   1024-  |    |    +    |    |
//          |    |         |    |
//    512-  |     ---------     |
//          |                   |
//          |                   |
//      0-   -------------------
//          |    |    |    |    |
//          0   512 1024  1536 2048

//   315  0  45
//      \ | /
//   270 -+- 90
//      / | \
//   225 180  135

// 0 = 0 deg, 2^10 (1024) = 360 deg
#define SEGA_ANGLE(deg)    ((int16_t)(((float)(deg))*2.845))

#define V_ADDR(x) (VECTOR_RAM+SYMBOLS_SZ+((x)*4))
#define S_ADDR(x) (VECTOR_RAM + ((x)*10))
#define SYM_ADDR(x) ((symbol_t*)(VECTOR_RAM+((x)*10)))

typedef struct {
   uint8_t visible : 1;  // lsb
   uint8_t group   : 6;  // user
   uint8_t last    : 1;  // msb
   uint16_t x;           // 0x000-0x7FF 10bit wrap, viewport is 0x200-0x600 with 0x400 center 
   uint16_t y;
   uint16_t vector_addr; // E000 - EFFF 4k Vector RAM
   uint16_t rotation;    // 0x7FF 10 bit angle of whole symbol
   uint8_t scale;        // 0x40 = 1/2, 0x80 = 1x, 0xff = 2x
} symbol_t; // 10 bytes

#define SFIELD_VISIBLE(row) (((row)*10)+0)
#define SFIELD_X_L(row)     (((row)*10)+1)
#define SFIELD_X_H(row)     (((row)*10)+2)
#define SFIELD_Y_L(row)     (((row)*10)+3)
#define SFIELD_Y_H(row)     (((row)*10)+4)
#define SFIELD_ADDR_L(row)  (((row)*10)+5)
#define SFIELD_ADDR_H(row)  (((row)*10)+6)
#define SFIELD_ANGLE_L(row) (((row)*10)+7)
#define SFIELD_ANGLE_H(row) (((row)*10)+8)
#define SFIELD_SCALE(row)   (((row)*10)+9)

typedef struct {
   union {
      struct {
         uint8_t visible : 1;
         uint8_t blue    : 2;
         uint8_t green   : 2;
         uint8_t red     : 2;
         uint8_t last    : 1;
      };
      uint8_t color;
   };
   uint8_t size;  // unscaled size
   uint16_t angle;  // 0x7FF 10 bit angle
} vector_t; // 4 bytes

#define VFIELD_COLOR(row)   (((row)*4)+0)
#define VFIELD_SIZE(row)    (((row)*4)+1)
#define VFIELD_ANGLE_L(row) (((row)*4)+2)
#define VFIELD_ANGLE_H(row) (((row)*4)+3)

// L R R G G B B D
#define SEGA_VISIBLE       (0x01)
#define SEGA_LAST          (0x80)
#define SEGA_CLEAR         (0)
#define SEGA_COLOR_RED     (0x60|SEGA_VISIBLE)
#define SEGA_COLOR_GREEN   (0x18|SEGA_VISIBLE)
#define SEGA_COLOR_GREEN1  (0x10|SEGA_VISIBLE)
#define SEGA_COLOR_GREEN2  (0x08|SEGA_VISIBLE)
#define SEGA_COLOR_BLUE    (0x06|SEGA_VISIBLE)
#define SEGA_COLOR_YELLOW  (SEGA_COLOR_RED|SEGA_COLOR_GREEN)
#define SEGA_COLOR_CYAN    (SEGA_COLOR_GREEN|SEGA_COLOR_BLUE)
#define SEGA_COLOR_MAGENTA (SEGA_COLOR_RED|SEGA_COLOR_BLUE)
#define SEGA_COLOR_ORANGE  (SEGA_COLOR_RED|SEGA_COLOR_GREEN1)
#define SEGA_COLOR_BRWHITE (0x7E|SEGA_VISIBLE)
#define SEGA_COLOR_WHITE   (0x54|SEGA_VISIBLE)
#define SEGA_COLOR_GRAY    (0x2A|SEGA_VISIBLE)
#define SIZE(x)            (x*10)

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
#define CHOPPER_EXPLODE 0x1C
#define TANK_MOVE    0x00
#define TANK_FIRE    0x1A
#define TANK_EXPLODE 0x16
#define COIN_DROP    0x24


typedef enum {
   game_state_boot,
   game_state_attract,
   game_state_play,
   game_state_game_over,
   game_state_game_over_pause,
   game_state_highscore,
} game_state_t;


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
#define FONT_STRING 0x01
uint16_t installFonts( uint16_t addr );
uint16_t fontAddress( char c );
void drawString( symbol_t *sym, uint16_t x, uint16_t y, uint8_t scale, uint8_t color, const char *str, uint8_t len );
void colorize( uint8_t *vector, uint16_t len, uint8_t color );
bool drawScore( uint8_t score, bool reset );

////////////////////////////////////
// math.h
uint8_t rand(void);
inline uint16_t xy_multiply( uint8_t x, uint8_t y );
uint16_t div_16(uint16_t u, uint16_t v);
uint8_t divideBy10(uint8_t *value);
uint8_t divideBy100(uint8_t *value);
void vectorToXY( uint16_t sega_angle, uint16_t length, int16_t *x, int16_t *y );
uint16_t xyToVector(uint16_t x, uint16_t y);

#define randSegaAngle()    (rand() << 2)
#define divide3(x)         (((x)>>2)+((x)>>4))
#define divide5(x)         (((x)>>3)+((x)>>4)+((x)>>6))
#define divide40(x)        ((((x)*26214U)+(1U<<19))>>20)

#define writeDebug( c,v ) \
   do { \
     uint8_t *mame = (uint8_t*)(0xF666); \
     *mame = 0xBE; \
     *mame = 0xEF; \
     *mame = c; \
     *mame = MSB(v); \
     *mame = LSB(v); \
   } while(0)

#define kill(x) \
   do { \
     uint8_t *halt = (uint8_t*)(0x0000); \
     *halt = x; \
   } while(0)



#endif //_SEGA_H_
