
////////////////////////////////////
// dependencies:
// https://github.com/z88dk/z88dk/releases
// export PATH=${PATH}:/Users/jmathews/Desktop/z88dk/bin
// export ZCCCFG=/Users/jmathews/Desktop/z88dk/lib/config
////////////////////////////////////

////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>


// #define ENABLE_UART

////////////////////////////////////
// sega g80 memory map
#define MEM_PTR(x)      ((volatile uint8_t*)(x))

#define CPU_ROM         (0x0000) // 2k power on and diagnostics rom (cpu board)
#define CPU_ROM_SZ      (2*1024)

#define ROM_BOARD       (0x0800) // 46k rom board
#define ROM_BOARD_SZ    (46*1024)

#ifdef EMBEDDED_USB
   // 4k image for the usb's 8035 (allocated at end of our image)
   #define USB_ROM_SZ   (4*1024)
   #define USB_ROM      (0x7000)  // from 28k-32k address
#else
   // 4k image for the usb's 8035 (hidden inside rom board U10,11,12)
   #define USB_ROM_SZ   (4*1024)
   #define USB_ROM      (0x5400)
#endif

#define CPU_RAM         (0xC800) // 2k ram (cpu board)
#define CPU_RAM_SZ      (2*1024)

#define USB_RAM         (0xD000) // 4k ram for the 8035 (universal serial board)
#define USB_RAM_SZ      (4*1024)

#define VECTOR_RAM      (0xE000) // 4k ram (xy board)
#define VECTOR_RAM_SZ   (4*1024)
////////////////////////////////////

// Test button on CPU board asserts NMI
// 40Hz interrupt from vector timing board

#pragma output CRT_ORG_DATA = 0xC800  // start of RAM

#pragma output CRT_MODEL = 1 // data section copied from ROM into RAM on program start
//#pragma output CRT_MODEL = 2 // data section zx7 compressed in ROM, decompressed into RAM on program start

#ifdef ENABLE_BOOTROM
   #pragma output CRT_ORG_CODE = 0x0800 // when using boot rom
#else
   #pragma output CRT_ORG_CODE = 0x0000
#endif
// #pragma output CRT_ORG_VECTOR_TABLE = 0x0800 

#pragma output REGISTER_SP = 0xCFFF

// used to calculate heap size (default is just unused ram)
// #pragma output CRT_STACK_SIZE = 0xf // 128

// #pragma output CRT_ENABLE_STDIO = 0
// #pragma output CRT_ENABLE_RST = 0x80 // User implements rst38h (IM1). user must preserve register values and exit with "ei; reti"
// #pragma output CRT_ENABLE_RST = 0x00 // User implements no isrs (default)
// #pragma output CRT_ENABLE_NMI = 1 // program supplies nmi isr
#pragma output CRT_ENABLE_EIDI = 0x01 // disable interrupts di on start
// #pragma output CRT_ENABLE_EIDI = 0x02 // enable interrupts ei on start
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
__sfr __at 0x3b SPEECH_TIMER;
__sfr __at 0x39 VOTRAX_COMMAND;
__sfr __at 0x3f SOUND_COMMAND;

/*
   ds 0h-$  ; RESET VECTOR
   ds 8h-$  ; SWRST 1
   ds 10h-$ ; SWRST 2
   ds 18h-$ ; SWRST 3
   ds 20h-$ ; SWRST 4
   ds 28h-$ ; SWRST 5
   ds 30h-$ ; SWRST 6
   ds 38h-$ ; IM 1
   ds 66h-$ ; NMI
*/

// these interrupt declarations don't work with current settings...

// nmi int (the cpu board button was pushed)
// void z80_nmi(void) __critical __interrupt {
//    // __asm__("rst 00h");
//     // PORT_370 = 0x80 | 0x40;
//    // __asm
//    // di
//    // halt
//    // __endasm;
// }

// // // halt int (the halt instruction was called)
// void z80_rst_38h (void) __critical __interrupt(0) {
//    __asm__("rst 00h");
//    // // diagnostic led comes on
//    // // continue very quickly to the next instruction
//    // __asm
//    // POP   DE
//    // INC   DE
//    // PUSH   DE
//    // __endasm;
// }


static void delay(uint16_t ms) {
   while ( ms-- ) {
      for (uint16_t i=0; i<27; i++) {   // 1ms at 3.86712 MHz (when XY board is clocking)
      //for (uint16_t i=0; i<28; i++) {   // 1ms at 4.0 MHz (when CPU board is self clocking)
         __asm__( "nop" );
      }
   }
}

static void memcpy(uint8_t *dst, uint8_t *src, uint16_t len) {
   for (uint16_t i=0; i<len; i++) {
      *dst = *src;
      dst++;
      src++;
   }
}

static void memset(uint8_t *dst, uint8_t val, uint16_t len) {
   for (uint16_t i=0; i<len; i++) {
      *dst = val;
      dst++;
   }
}

static uint8_t rand(void) {
   static uint8_t x = 0xC5;
   x |= (x == 0);   // if x == 0, set x = 1 instead
   x ^= (x & 0x07) << 5;
   x ^= x >> 3;
   x ^= (x & 0x03) << 6;
   return x & 0xff;
}


#ifdef ENABLE_UART

static void send_uart_byte(uint8_t b) {
   // ~16us per bit at 8.0MHz, approx 57600
   uint8_t start_bit = 0x00;
   uint8_t d0 = (b & (1<<0)) ? 0x01 : 0x00;
   uint8_t d1 = (b & (1<<1)) ? 0x01 : 0x00;
   uint8_t d2 = (b & (1<<2)) ? 0x01 : 0x00;
   uint8_t d3 = (b & (1<<3)) ? 0x01 : 0x00;
   uint8_t d4 = (b & (1<<4)) ? 0x01 : 0x00;
   uint8_t d5 = (b & (1<<5)) ? 0x01 : 0x00;
   uint8_t d6 = (b & (1<<6)) ? 0x01 : 0x00;
   uint8_t d7 = (b & (1<<7)) ? 0x01 : 0x00;
   uint8_t stop_bit = 0x01;

   PORT_370 = start_bit;
   PORT_370 = d0;
   PORT_370 = d1;
   PORT_370 = d2;
   PORT_370 = d3;
   PORT_370 = d4;
   PORT_370 = d5;
   PORT_370 = d6;
   PORT_370 = d7;
   PORT_370 = stop_bit;
}

static void send_uart_data(const char *data, uint8_t len) {
   for(uint8_t i=0; i<len; i++) {
      send_uart_byte( data[i] );
   }
}

static void sprint8(char *s, uint8_t v) {
    const char *hex = "0123456789abcdef";
    s[0] = hex[ (v >> 4) & 0xf ];
    s[1] = hex[ (v >> 0) & 0xf ];
}

static void sprint16(char *s, uint16_t v) {
   sprint8( &s[0], (uint8_t)(v>>8)&0xff );
   sprint8( &s[2], (uint8_t)(v>>0)&0xff );
}

static void sprint32(char *s, uint32_t v) {
    sprint16( &s[0], (uint16_t)(v>>16)&0xffff );
    sprint16( &s[4], (uint16_t)(v&0xffff) );
}

#endif // ENABLE_UART


static uint16_t xy_multiply( uint8_t x, uint8_t y ) {
   XY_MULTIPLICAND = x;
   XY_MULTIPLIER = y;
   uint16_t product = XY_MULTIPLIER;
   product |= (uint16_t)XY_MULTIPLIER << 8;
   return product;
}


static uint8_t sound_wait(void) {
   // uint16_t timeout = 2000/50;
   // while ( timeout-- ) {
      delay( 50 );
   //    if ( (SOUND_COMMAND & 0xFE) == 0x80 ) {
   //       // 8035 ready for next command
   //       delay( 250 ); // wait for sound to finish
   //       return 0;
   //    }
   // }
   return 1;
}

static void sound_init(void) {
   // copy main board ROMs into sound board's RAM 
   // so the 8035 can execute it
   SOUND_COMMAND = 0xFF; // 8035 in reset and assert RAM LOAD latch
   memcpy( USB_RAM, USB_ROM, USB_ROM_SZ );
   //memcpy( 0xD800, 0x5100, 0x0800 ); //?
   SOUND_COMMAND = 0x7F; // release 8035
   sound_wait();
}

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
   RED_ALERT = 0x19,                // "RED ALERT"
   LAST_PHRASE = 0x1A
} phrase_t;

static void say(uint8_t i) {
   SPEECH_COMMAND = i;
   SPEECH_COMMAND = i | 0x80;
   // wait for speech to finish, sending too fast causes glitches
   // but unclear how to receive interrupt on complete of phrase
   delay( 750 );
   SPEECH_COMMAND = NO_PHRASE;
}

static uint8_t divideBy10(uint8_t *value) {
    uint8_t count = 0;
    while (*value >= 10) {
        *value -= 10;
        count++;
    }
    return count;
}

static uint8_t divideBy100(uint8_t *value) {
    uint8_t count = 0;
    while (*value >= 100) {
        *value -= 100;
        count++;
    }
    return count;
}
static void speech_0to9(uint8_t v) {
   if ( v <= 9 ) {
      say( ZERO + v);
   }
}

static void say8(uint8_t v) {
   uint8_t r = v; // remainder
   uint8_t d0 = divideBy100( &r ); 
   uint8_t d1 = divideBy10( &r );
   uint8_t d2 = r;
   if ( d0 ) {
      speech_0to9( d0 );
   }
   if ( d1 || d0 ) {
      speech_0to9( d1 );
   }
   speech_0to9( d2 );
}


typedef struct {
   uint8_t last   : 1;
   uint8_t group  : 6;
   uint8_t visible : 1;
   uint16_t x;
   uint16_t y;
   uint16_t vector_addr; // E000 - EFFF 4k Vector RAM
   uint16_t rotation; // 10 bit angle of whole symbol
   uint8_t scale; // 0x40 = 1/2, 0x80 = 1x, 0xff = 2x
} symbol_t;

typedef struct {
   uint8_t last   : 1;
   uint8_t red    : 2;
   uint8_t green  : 2;
   uint8_t blue    : 2;
   uint8_t visible : 1;
   uint8_t length;   // unscaled size
   uint8_t angle;   // degrees
   uint8_t quadrant; // msb of 10 bit angle
} vector_t;


// L R R G G B B D
#define SEGA_VISIBLE       (0x01)
#define SEGA_LAST          (0x80)
#define SEGA_CLEAR         (0)
#define SEGA_COLOR_RED     (0x60|SEGA_VISIBLE)
#define SEGA_COLOR_GREEN   (0x18|SEGA_VISIBLE)
#define SEGA_COLOR_BLUE    (0x06|SEGA_VISIBLE)
#define SEGA_COLOR_YELLOW  (SEGA_COLOR_RED|SEGA_COLOR_GREEN)
#define SEGA_COLOR_CYAN    (SEGA_COLOR_GREEN|SEGA_COLOR_BLUE)
#define SEGA_COLOR_MAGENTA (SEGA_COLOR_RED|SEGA_COLOR_BLUE)
#define SEGA_COLOR_WHITE   (SEGA_COLOR_RED|SEGA_COLOR_GREEN|SEGA_COLOR_BLUE)
#define SEGA_ANGLE(deg)    ((uint16_t)(((float)(deg))*2.845))
#define SIZE(x)            (x*10)

#define LSB(x)             ((x)&0xFF)
#define MSB(x)             (((x)>>8)&0xFF)
#define LE(x)              LSB(x), MSB(x)



static uint16_t spinner_vector_angle(void) {
   PORT_370 = 0xFE; // switch io expander to spinner
   delay(1);
   uint8_t value = PORT_374;
   bool dir = value & 0x01;
   value = value >> 1;
   PORT_370 = 0xFF; // switch io expander to buttons
   delay(1);

   static uint16_t angle = 0;
   static uint16_t lastvalue = 0xffff;
   if (lastvalue != 0xffff) {
      if ( value > lastvalue ) {
         lastvalue += 127; // 2^7 max angle in spinner space
      }
      uint8_t delta = lastvalue - value;
      // spinner angle in degrees is about 5.6 * value
      // vector is SEGA_ANGLE( angle ), so 2.845 * 5.6 = ~16
      delta <<= 4;  // x 16
      if (dir) {
         // only ever counts down so we have to account for direction bit
         angle += delta;
      } else {
         angle -= delta;
      }
      angle &= 0x03FF; // 2^10 max angle in vector space
    }
    lastvalue = value;
    return angle;
}


static void vector_test(void) {

   // the vector table is useful to describe vectors, but since scale, position and rotation
   // are all set in the symbol drawing list that vector table might as well be in rom
   uint8_t *vectors = (uint8_t*)0xE400; // arbitrary location in vector ram
   #define VEC_BASE 0xE400

   // the xy ram is not dual port. and the xy board is running asynchonously 
   // from the cpu, so you can't read from it without collissions and corrupting graphics.
   uint8_t *symbols = (uint8_t*)0xE000; // must be at the top of vector ram

   const uint8_t vector[] = {
       #define ADDR_LINE  0
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(180)),
       SEGA_COLOR_YELLOW|SEGA_LAST,  0x80, LE(SEGA_ANGLE(0)),

       #define ADDR_0 (ADDR_LINE+(2*4))
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)),
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0xC0, LE(SEGA_ANGLE(17)),

       #define ADDR_1 (ADDR_0+(4*4))
       SEGA_COLOR_MAGENTA,           0x40, LE(SEGA_ANGLE(90)),
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)),
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(270)),
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(90)),

       #define ADDR_2 (ADDR_1+(4*4))
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)),
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(90)),

       #define ADDR_3 (ADDR_2+(5*4))
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE43C
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE440
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE444
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE448
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE44C
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE450

       #define ADDR_4 (ADDR_3+(6*4))
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(90)),  // 0xE454
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE458
       SEGA_CLEAR,                   0x60, LE(SEGA_ANGLE(17)),  // 0xE45C
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(90)),  // 0xE460
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE464
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x60, LE(SEGA_ANGLE(17)),  // 0xE468

       #define ADDR_5 (ADDR_4+(6*4))
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE46C
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE470
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE474
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE478
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE47C
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE480

       #define ADDR_6 (ADDR_5+(6*4))
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE484
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE488
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE48C
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE490
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(17)),  // 0xE494
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE498

       #define ADDR_7 (ADDR_6+(6*4))
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE49C
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0xC0, LE(SEGA_ANGLE(197)), // 0xE4A0

       #define ADDR_8 (ADDR_7+(2*4))
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE4A4
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE4A8
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE4AC
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(17)),  // 0xE4B0
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE4B4
       SEGA_CLEAR,                   0x60, LE(SEGA_ANGLE(197)), // 0xE4B8
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE4BC

       #define ADDR_9 (ADDR_8+(7*4))
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE4C8
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(17)),  // 0xE4CC
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE4D0
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE4D4
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE4D8

       #define ADDR_TANK (ADDR_9+(7*4))
       SEGA_CLEAR,                  SIZE(13),  LE(SEGA_ANGLE(320)),
       SEGA_COLOR_GREEN,            SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN,            SIZE(1),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN,            SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN,            SIZE(1),   LE(SEGA_ANGLE(0)),
       SEGA_COLOR_GREEN,            SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN,            SIZE(20),  LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN,            SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN,            SIZE(1),   LE(SEGA_ANGLE(0)),
       SEGA_COLOR_GREEN,            SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN,            SIZE(1),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN,            SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN|SEGA_LAST,  SIZE(20),  LE(SEGA_ANGLE(0)),

       #define ADDR_TREAD  (ADDR_TANK+(13*4))
       SEGA_CLEAR,                     SIZE(13),  LE(SEGA_ANGLE(320)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),   // animation sequence size:1,2,3
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(90)), 
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)), 
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_BLUE,                SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)), 
       SEGA_COLOR_BLUE|SEGA_LAST,      SIZE(4),   LE(SEGA_ANGLE(270)), 


     #define ADDR_TURRET (ADDR_TREAD+(25*4))
     SEGA_CLEAR,                       SIZE(7.5), LE(SEGA_ANGLE(45)),
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(180)),
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(90)),
     SEGA_COLOR_GREEN,                 SIZE(2),   LE(SEGA_ANGLE(225)),
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(180)),
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(135)),
     SEGA_COLOR_GREEN,                 SIZE(2),   LE(SEGA_ANGLE(315)),
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(270)),
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(225)),
     SEGA_COLOR_GREEN,                 SIZE(2),   LE(SEGA_ANGLE(45)),
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(315)),
     SEGA_COLOR_GREEN,                 SIZE(2),   LE(SEGA_ANGLE(135)),
     SEGA_COLOR_GREEN|SEGA_LAST,       SIZE(8),   LE(SEGA_ANGLE(90)),

     #define ADDR_BARREL (ADDR_TURRET+(16*4))
     SEGA_CLEAR,                       SIZE(5),   LE(SEGA_ANGLE(345)),
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(4),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN|SEGA_LAST,       SIZE(8),   LE(SEGA_ANGLE(180)),

     #define ADDR_FLAME (ADDR_BARREL+(8*4))
     SEGA_CLEAR,                       SIZE(14),  LE(SEGA_ANGLE(347)),
     SEGA_COLOR_RED,                   SIZE(3),   LE(SEGA_ANGLE(315)),
     SEGA_COLOR_RED,                   SIZE(2),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_RED,                   SIZE(2),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_RED,                   SIZE(2),   LE(SEGA_ANGLE(135)),
     SEGA_COLOR_RED,                   SIZE(4),   LE(SEGA_ANGLE(22)),
     SEGA_COLOR_RED,                   SIZE(4),   LE(SEGA_ANGLE(158)),
     SEGA_COLOR_RED,                   SIZE(2),   LE(SEGA_ANGLE(45)),
     SEGA_COLOR_RED,                   SIZE(2),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_RED,                   SIZE(2),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_RED|SEGA_LAST,         SIZE(3),   LE(SEGA_ANGLE(225)),

     #define ADDR_MISSILE (ADDR_FLAME+(11*4))
     SEGA_COLOR_YELLOW,                SIZE(3.4), LE(SEGA_ANGLE(158)),
     SEGA_COLOR_YELLOW,                SIZE(4),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_YELLOW,                SIZE(1),   LE(SEGA_ANGLE(135)),
     SEGA_COLOR_YELLOW,                SIZE(4),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_YELLOW,                SIZE(1),   LE(SEGA_ANGLE(45)),
     SEGA_COLOR_YELLOW,                SIZE(4),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_YELLOW|SEGA_LAST,      SIZE(3.4), LE(SEGA_ANGLE(22)),

     #define ADDR_BLADE (ADDR_MISSILE+(7*4))
     SEGA_COLOR_CYAN,                  SIZE(1.3), LE(SEGA_ANGLE(55)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(293)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(68)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(158)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(22)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(9),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(1),   LE(SEGA_ANGLE(158)),

     #define ADDR_CHOPPER (ADDR_BLADE+(18*4))
     SEGA_CLEAR,                       SIZE(2.6), LE(SEGA_ANGLE(330)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(158)),
     SEGA_COLOR_CYAN,                  SIZE(5),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(3),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(6),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(7),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(6),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(3),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(5),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(203)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(6.7), LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(3),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_CYAN,                  SIZE(3),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(2),   LE(SEGA_ANGLE(90)),

     #define CUBE_IX (ADDR_CHOPPER+(29*4))
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 0  adjust angle  invisible below horizon
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 1  invisible below horizon
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 2
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 3  adjust angle (45...135)
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 4
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 5
     SEGA_COLOR_CYAN,                  SIZE(5.6), LE(SEGA_ANGLE(135)), // 6
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 7
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 8  adjust angle 
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 9
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 10 invisible above horizon
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 11 adjust angle invisible above horizon
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 12
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(90)),  // 13

    };
   memcpy( vectors, vector, sizeof(vector) );

#define MAX_X (1024+450)
#define MIN_X (1024-450)
#define MAX_Y (1024+450)
#define MIN_Y (1024-450)

   const uint8_t symbol[] = {
      // 10 bytes each entry
      // flags      x             y             address     rotation             scale

      #define SYM_DIG0  0
      SEGA_VISIBLE, LE(1024-50), LE(1024-250), LE(VEC_BASE+ADDR_0),     LE(0),               0x40,
      #define SYM_DIG1  1
      SEGA_VISIBLE, LE(1024+50), LE(1024-250), LE(VEC_BASE+ADDR_0),     LE(0),               0x40,

      #define SYM_TANK  2
      SEGA_VISIBLE, LE(1024),     LE(1024),     LE(VEC_BASE+ADDR_TANK),  LE(SEGA_ANGLE(0)),   0x80,
      #define SYM_TREAD0 3
      SEGA_VISIBLE, LE(1024-70), LE(1024+80), LE(VEC_BASE+ADDR_TREAD), LE(SEGA_ANGLE(0)),   0x80,
      #define SYM_TREAD1 4
      SEGA_VISIBLE, LE(1024+70-32), LE(1024+80), LE(VEC_BASE+ADDR_TREAD), LE(SEGA_ANGLE(0)),   0x80,
      #define SYM_TURRET 5
      SEGA_VISIBLE, LE(1024),     LE(1024),     LE(VEC_BASE+ADDR_TURRET), LE(SEGA_ANGLE(0)),   0x80,
      #define SYM_BARREL 6
      SEGA_VISIBLE, LE(1024),     LE(1024),     LE(VEC_BASE+ADDR_BARREL), LE(SEGA_ANGLE(0)),   0x80,
      #define SYM_FLAME 7
      0, LE(1024),     LE(1024),     LE(VEC_BASE+ADDR_FLAME), LE(SEGA_ANGLE(0)),   0x80,

      #define SYM_CHOPPER 8
      SEGA_VISIBLE, LE(1024+200), LE(1024+350), LE(VEC_BASE+ADDR_CHOPPER), LE(0),     0x80,
      #define SYM_BLADE 9
      SEGA_VISIBLE, LE(1024+200), LE(1024+350), LE(VEC_BASE+ADDR_BLADE), LE(0),     0x80,

      #define SYM_CUBE0 10
      SEGA_VISIBLE,           LE(MIN_X), LE(MIN_Y), LE(VEC_BASE+CUBE_IX), LE(0),     0x80,
      #define SYM_CUBE1 11
      SEGA_VISIBLE,           LE(MIN_X), LE(1024), LE(VEC_BASE+CUBE_IX), LE(0),     0x80,
      #define SYM_CUBE2 12
      SEGA_VISIBLE,           LE(MAX_X), LE(MIN_Y), LE(VEC_BASE+CUBE_IX), LE(0),     0x80,
      #define SYM_CUBE3 13
      SEGA_VISIBLE|SEGA_LAST, LE(MAX_X), LE(1024), LE(VEC_BASE+CUBE_IX), LE(0),     0x80,
   };
   memcpy( symbols, symbol, sizeof(symbol) );

   for (;;) {

            static uint8_t ct=0;
            if ( ct == 0 ) {
               uint8_t button = PORT_374;
               if ( button == BUTTON_FIRE ) {
                  ct = 30;
                  SOUND_COMMAND = 0x1a;
                  symbols[(SYM_FLAME*10)+0] = SEGA_VISIBLE;
               }
            }
            if (ct>=30) {
               ct++; 
               vectors[ADDR_BARREL+1] = ct;
            }
            if (ct==45) {
               symbols[(SYM_FLAME*10)+0] = 0;
            }
            if (ct==60) {
               vectors[ADDR_BARREL+1] = SIZE(6);
               ct = 0;
            }

            static uint16_t flight_x = 1024;
            if (flight_x<MIN_X) {
               flight_x=MAX_X;
            }
            flight_x -= 4;
            symbols[(SYM_CHOPPER*10)+1] = LSB(flight_x);
            symbols[(SYM_CHOPPER*10)+2] = MSB(flight_x);
            symbols[(SYM_BLADE*10)+1] = LSB(flight_x);
            symbols[(SYM_BLADE*10)+2] = MSB(flight_x);

            uint8_t ix = SYM_BLADE*10;
            static uint16_t blade_angle = 0;
            blade_angle = (blade_angle - 10) & 0x03FF;
            symbols[ix+7] = LSB( blade_angle ); 
            symbols[ix+8] = MSB( blade_angle );

            uint16_t vec_angle = spinner_vector_angle();
            uint8_t r[] = {SYM_BARREL*10,SYM_FLAME*10,SYM_TURRET*10};
            for (uint8_t i=0; i<sizeof(r)/sizeof(r[0]); i++) {
               uint8_t ix = r[i];
               symbols[ix+7] = LSB(vec_angle); 
               symbols[ix+8] = MSB(vec_angle);
            }

            #define FIELD_COLOR(row) (((row)*4)+0)
            #define FIELD_SIZE(row)  (((row)*4)+1)
            #define FIELD_ANGLE(row) (((row)*4)+2)

               static uint16_t ground_y = MIN_Y;
               static uint16_t ground_a = SEGA_ANGLE(45);
               static uint8_t ground_c = 0;
               ground_y++;
               ground_c++;
               if ( ground_c >= 7 ) {
                  ground_c = 0;
                  ground_a += SEGA_ANGLE(1);
               }
               if ( ground_y >= MAX_Y ) {
                  ground_y = MIN_Y;
                  ground_a = SEGA_ANGLE(45); // should be at 135 by now
               }
               symbols[(SYM_CUBE0*10)+1] = LSB(ground_y);
               symbols[(SYM_CUBE0*10)+2] = MSB(ground_y);

               // adjust cube angle depending on y position.
               // y = 575 then a = 45, y = 1474 then a = 135
               // SEGA_ANGLE( (y - 125) / 10 );
               vectors[CUBE_IX+FIELD_ANGLE(0)+0] = LSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(0)+1] = MSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(3)+0] = LSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(3)+1] = MSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(8)+0] = LSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(8)+1] = MSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(11)+0] = LSB(ground_a);
               vectors[CUBE_IX+FIELD_ANGLE(11)+1] = MSB(ground_a);

               if ( ground_y < 1024 ) {
                  // vectors 1,2 invisible below horizon
                  vectors[CUBE_IX+FIELD_COLOR(0)+0] = SEGA_CLEAR;
                  vectors[CUBE_IX+FIELD_COLOR(1)+0] = SEGA_CLEAR;
                  vectors[CUBE_IX+FIELD_COLOR(10)+0] = SEGA_COLOR_CYAN;
                  vectors[CUBE_IX+FIELD_COLOR(11)+0] = SEGA_COLOR_CYAN;
               } else {
                  // vectors 10,11 invisible below horizon
                  vectors[CUBE_IX+FIELD_COLOR(0)+0] = SEGA_COLOR_CYAN;
                  vectors[CUBE_IX+FIELD_COLOR(1)+0] = SEGA_COLOR_CYAN;
                  vectors[CUBE_IX+FIELD_COLOR(10)+0] = SEGA_CLEAR;
                  vectors[CUBE_IX+FIELD_COLOR(11)+0] = SEGA_CLEAR;
               }
            }



            // uint16_t d[] = {VEC_BASE+ADDR_0,VEC_BASE+ADDR_1,VEC_BASE+ADDR_2,VEC_BASE+ADDR_3,VEC_BASE+ADDR_4,VEC_BASE+ADDR_5,VEC_BASE+ADDR_6,VEC_BASE+ADDR_7,VEC_BASE+ADDR_8,VEC_BASE+ADDR_9};
            // symbols[(SYM_DIG0*10)+5] = LSB(d[k]);
            // symbols[(SYM_DIG1*10)+5] = LSB(d[j]);
   }
}


static void init(void) {

   SPEECH_TIMER = 0x24;
   SPEECH_COMMAND = 0x00;

   // SPEECH_COMMAND = 0x80;
   // SOUND_COMMAND = 0xFF; // 8035 in reset and assert RAM LOAD latch

   // // blank the screen and clear vector ram
   memset( VECTOR_RAM, 0x00, VECTOR_RAM_SZ );

   const uint8_t s[] = { SEGA_LAST, LE(1024), LE(1024), LE(0xE40A), LE(0), 0x80,
                         SEGA_CLEAR|SEGA_LAST, 0x80, LE(0) };
   memcpy( VECTOR_RAM, s, sizeof(s) );

   XY_INIT = 0x04;

   PORT_371 = 0x00;
   PORT_370 = 0xFF; // switch io expander from spinner to buttons
}




void main(void) {

   init();

   sound_init();

#ifdef ENABLE_UART
   send_uart_data("boot\r\n",6);
#endif

   say( START );

   for (;;) {

      vector_test();

   }

}

