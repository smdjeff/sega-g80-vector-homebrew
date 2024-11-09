
////////////////////////////////////
// dependencies:
// https://github.com/z88dk/z88dk/releases
// export PATH=${PATH}:/Users/jmathews/Desktop/z88dk/bin
// export ZCCCFG=/Users/jmathews/Desktop/z88dk/lib/config
////////////////////////////////////

////////////////////////////////////

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
#define SYMBOLS_SZ      (0x100)
////////////////////////////////////

// Test button on CPU board asserts NMI
// 40Hz interrupt from vector timing board

#pragma output CRT_ORG_DATA = 0xC800  // start of RAM

#pragma output CRT_MODEL = 1 // data section copied from ROM into RAM on program start
//#pragma output CRT_MODEL = 2 // data section zx7 compressed in ROM, decompressed into RAM on program start

#ifdef ENABLE_BOOTROM
   #pragma output CRT_ORG_CODE = 0x0800 // when using boot rom
//   #pragma output CRT_ORG_VECTOR_TABLE = 0x0000
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

static uint8_t score0 = 0;
static uint8_t score = 0;

#define BASE_DRUM    0x2E
#define SNARE_DRUM   0x1E
#define TANK_MOVE    0x00
#define TANK_FIRE    0x1A

// NMI int (the cpu board button was pushed)
void z80_nmi(void) __critical __interrupt {
   score0++;
}


// IRQ signal comes from multiple sources:
//    * XINT signal, which is a combination of:
//        - COINA impulse, clocks an LS74, cleared by INTCL signal
//        - COINB impulse, clocks an LS74, cleared by INTCL signal
//        - SERVICE impulse
//    * /EDGINT signal from vector board, clocks an LS74, cleared by INTCL signal
//        - signal comes from 15468480 crystal, divided by 3, and then by 0x1f788
void z80_rst_38h (void) __critical __interrupt(0) {
   score++;

   // this is a 25ms timer
   static uint8_t div = 0;
   static uint8_t ix = 0;
   if ( div >= 250/25 ) {
      div = 0;
      const uint8_t track0[] = { BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                 BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM, 
                                 BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                 BASE_DRUM, SNARE_DRUM,  SNARE_DRUM, BASE_DRUM };
      const uint8_t track[]  = { BASE_DRUM,          0,  SNARE_DRUM,         0,
                                 BASE_DRUM,  BASE_DRUM,  SNARE_DRUM,         0, 
                                 BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                         0,  BASE_DRUM,  SNARE_DRUM,         0 };
      SOUND_COMMAND = track[ ix ];
      ix++;
      if (ix>=sizeof(track)) ix = 0;
   }
   div++;
}


static void delay(uint16_t ms) {
   while ( ms-- ) {
      for (uint16_t i=0; i<27; i++) {   // 1ms at 3.86712 MHz (when XY board is clocking)
      //for (uint16_t i=0; i<28; i++) {   // 1ms at 4.0 MHz (when CPU board is self clocking)
         __asm__( "nop" );
      }
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

static uint16_t wrap(uint16_t v, uint16_t max, uint16_t min) {
   if ( v > max ) {
      v -= min;
   }
   return v;
}

static uint16_t xy_multiply( uint8_t x, uint8_t y ) {
   XY_MULTIPLICAND = x;
   XY_MULTIPLIER = y;
   uint16_t product = XY_MULTIPLIER;
   product |= (uint16_t)XY_MULTIPLIER << 8;
   return product;
}

#define LSB(x) (uint8_t)((uint16_t)(x) & 0xFF)
#define MSB(x) (uint8_t)(((uint16_t)(x) >> 8) & 0xFF)


static uint8_t clz8(uint8_t x) {
    const uint8_t lookup[16] = { 4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t upper = x >> 4;
    uint8_t lower = x & 0x0F;
    return upper ? lookup[upper] : 4 + lookup[lower];
}


static uint8_t clz(uint16_t x) {
    uint8_t upper = MSB(x);
    uint8_t lower = LSB(x);
    return upper ? clz8(upper) : 8 + clz8(lower);
}

static uint16_t div_16(uint16_t u, uint16_t v) {
   uint16_t q = 0;
   int k = clz(v) - clz(u);
   switch (k) {
      case 15: if (v <= (u >> 15)) { u -= v << 15; q += 1 << 15; }
      case 14: if (v <= (u >> 14)) { u -= v << 14; q += 1 << 14; }
      case 13: if (v <= (u >> 13)) { u -= v << 13; q += 1 << 13; }
      case 12: if (v <= (u >> 12)) { u -= v << 12; q += 1 << 12; }
      case 11: if (v <= (u >> 11)) { u -= v << 11; q += 1 << 11; }
      case 10: if (v <= (u >> 10)) { u -= v << 10; q += 1 << 10; }
      case  9: if (v <= (u >>  9)) { u -= v <<  9; q += 1 <<  9; }
      case  8: if (v <= (u >>  8)) { u -= v <<  8; q += 1 <<  8; }
      case  7: if (v <= (u >>  7)) { u -= v <<  7; q += 1 <<  7; }
      case  6: if (v <= (u >>  6)) { u -= v <<  6; q += 1 <<  6; }
      case  5: if (v <= (u >>  5)) { u -= v <<  5; q += 1 <<  5; }
      case  4: if (v <= (u >>  4)) { u -= v <<  4; q += 1 <<  4; }
      case  3: if (v <= (u >>  3)) { u -= v <<  3; q += 1 <<  3; }
      case  2: if (v <= (u >>  2)) { u -= v <<  2; q += 1 <<  2; }
      case  1: if (v <= (u >>  1)) { u -= v <<  1; q += 1 <<  1; }
      case  0: if (v <= (u >>  0)) { u -= v <<  0; q += 1 <<  0; }
      default: break;
   }
   return q;
}

#define divideBy3(x) (((x)>>2)+((x)>>4))

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


const uint8_t sin_table[] = {
   0,2,3,5,6,8,9,11,13,14,16,17,19,20,22,23,25,27,28,30,31,33,34,36,38,39,41,42,44,45,47,48,50,51,53,54,56,58,59,61,62,64,65,
   67,68,70,71,73,74,76,77,79,80,82,83,85,86,88,89,91,92,93,95,96,98,99,101,102,104,105,106,108,109,111,112,114,115,116,118,
   119,120,122,123,125,126,127,129,130,131,133,134,135,137,138,139,141,142,143,145,146,147,148,150,151,152,153,155,156,157,
   158,160,161,162,163,165,166,167,168,169,170,172,173,174,175,176,177,178,180,181,182,183,184,185,186,187,188,189,190,191,
   192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,211,212,213,214,215,216,217,217,218,219,
   220,221,221,222,223,224,224,225,226,227,227,228,229,229,230,231,231,232,233,233,234,235,235,236,236,237,238,238,239,239,
   240,240,241,241,242,242,243,243,244,244,245,245,246,246,246,247,247,248,248,248,249,249,249,250,250,250,251,251,251,251,
   252,252,252,252,253,253,253,253,253,254,254,254,254,254,254,254,254,255,255,255,255,255,255,255,255,255,255,255
};

// Ed Logg notes in his Asteroids code: SIN(PI+A) = -SIN(A) and COS(A) = SIN(A+PI/2)
// the table then is just 0-90 degrees.
// 90-180 is simply a reflection of 0-90
// 180-360 is a negative sign reflection of 0-180
// and cos is just sin rotated 90
// the table is large because it's using sega's 10bit angle datatype units unscaled for speed

int8_t sinlut(uint16_t sega_angle, bool *negsign) {
    if ( sega_angle < SEGA_ANGLE(90) ) {
        *negsign = false;
        return sin_table[ sega_angle ];
    }
    if ( sega_angle < SEGA_ANGLE(180) ) {
        sega_angle -= SEGA_ANGLE(90);
        *negsign = false;
        return sin_table[ SEGA_ANGLE(90) - sega_angle ];
    }
    if ( sega_angle < SEGA_ANGLE(270) ) {
        sega_angle -= SEGA_ANGLE(180);
        *negsign = true;
        return sin_table[ sega_angle ];
    }
    sega_angle -= SEGA_ANGLE(270);
    *negsign = true;
    return sin_table[ SEGA_ANGLE(90) - sega_angle ];
}

uint8_t coslut(uint16_t sega_angle, bool *negsign) {
    sega_angle += SEGA_ANGLE(90);
    if (sega_angle>=SEGA_ANGLE(360)) {
        sega_angle -= SEGA_ANGLE(360);
    }
    return sinlut( sega_angle, negsign );
}


static void vectorPosition( uint16_t sega_angle, uint16_t length, int16_t *x, int16_t *y ) {
  bool sin_neg, cos_neg;
  uint8_t sin_value = sinlut( sega_angle, &sin_neg );
  uint8_t cos_value = coslut( sega_angle, &cos_neg );
  *x = 0; *y = 0;
  do {
    uint8_t l = MIN(length,254);

#if 0
    *x += xy_multiply( 1 + l, sin_value ) >> 8;
    *y += xy_multiply( 1 + l, cos_value ) >> 8;
#else
    XY_MULTIPLICAND = 1+l;
    XY_MULTIPLIER = sin_value;
    (volatile uint8_t *)XY_MULTIPLIER;
    *x += XY_MULTIPLIER;
    XY_MULTIPLIER = cos_value;
    (volatile uint8_t *)XY_MULTIPLIER;
    *y += XY_MULTIPLIER;
#endif
    length -= l;
  } while (length);
  if (sin_neg) {
      *x = - *x;
  }
  if (cos_neg) {
      *y = - *y;
  }
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


static uint8_t sound_wait(void) {
   uint16_t timeout = 3000/50;
   while ( timeout-- ) {
      if ( (SOUND_COMMAND & 0xFE) == 0x80 ) {
         // 8035 ready for next command
         //delay( 250 ); // wait for sound to finish
         return 0;
      }
      delay( 50 );
   }
   return 1;
}


static void sound_init(void) {
   // copy main board ROMs into sound board's RAM 
   // so the 8035 can execute it
#ifdef EMBEDDED_USB
   // load 4k
   SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   memcpy( USB_RAM, USB_ROM_A, USB_ROM_SZ_A );
   SOUND_COMMAND = 0x7F; 

   // SPEECH_CONTROL = 0x28;
   // SPEECH_CONTROL = 0x28;

   // // bounce 8035
   // SOUND_COMMAND = 0xFF; 
   // SOUND_COMMAND = 0x7F; 

   // // overwrite last 2k  - is this ONLY for the MUSIC?
   // SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   // memcpy( USB_RAM+USB_ROM_SZ_B, USB_ROM_B, USB_ROM_SZ_B );
   // SOUND_COMMAND = 0x7F; 

   // sound_wait();
   // SOUND_COMMAND = 0x2B; // COIN_DROP_MUSIC
   // delay(5000);

   // // SPEECH_CONTROL = 0x28;
   // // bounce 8035
   // SOUND_COMMAND = 0xFF; 
   // SOUND_COMMAND = 0x7F; 

   // const uint8_t speech_init[] = { 0x3f, 0xbf, 0x0a, 0x8a, 0x08, 0x88, 0x03, 0x83 };
   // for (uint8_t i=0; i<sizeof(speech_init); i++) {
   //    SPEECH_COMMAND = speech_init[i];
   // }

   // // SPEECH_CONTROL = 0x28;
   // // load 4k again
   // SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   // memcpy( USB_RAM, USB_ROM_A, USB_ROM_SZ_A );
   // SOUND_COMMAND = 0x7F; 

   // sound_wait();
   // SOUND_COMMAND = 0x27;
   // delay(1000);

   // sound_wait();
   // SOUND_COMMAND = 0x27;
   // delay(1000);

   // sound_wait();
   // SOUND_COMMAND = 0x26;
   // delay(1000);

   // sound_wait();
   // SOUND_COMMAND = 0x28;
   // delay(1000);

   // sound_wait();
   // SOUND_COMMAND = 0x2e;
   // delay(1000);

#endif
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


void sound_test(void) {
   const uint8_t a[] = {
      COIN_DROP_MUSIC,
      HIGH_SCORE_MUSIC,
      IMPULSE,
      IMPULSE_END,
      WARP,
      WARP_END,
      RED_ALERT,
      RED_ALERT_END,
      PHASER,
      PHOTON,
      TARGETING,
      DENY,
      SHIELD_HIT,
      ENTERPRISE_HIT,
      ENTERPRISE_EXPLOSION,
      KLINGON_EXPLOSION,
      DOCK,
      STARBASE_HIT,
      STARBASE_RED,
      WARP_SUCK,
      WARP_SUCK_END,
      SAUCER_EXIT,
      SAUCER_EXIT_END,
      STARBASE_EXPLOSION,
      SMALL_BONUS,
      LARGE_BONUS,
      STARBASE_INTRO,
      KLINGON_INTRO,
      ENTERPRISE_INTRO,
      PLAYER_CHANGE,
      KLINGON_FIRE,
      NOMAD_MOTION,
      NOMAD_MOTION_END,
      NOMAD_STOPPED,
      NOMAD_STOPPED_END,
   };
   for (uint8_t i=0; i<sizeof(a); i++) {
      uint8_t s = a[i];

      // for MUSIC we a different 2k loaded into the back half of the 8035
      if (s==COIN_DROP_MUSIC) {
         SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
         memcpy( USB_RAM+USB_ROM_SZ_B, USB_ROM_B, USB_ROM_SZ_B );
         SOUND_COMMAND = 0x7F; 
      }
      // reload normal effects into the back half of the 8035
      if (s==IMPULSE) {
         SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
         memcpy( USB_RAM+USB_ROM_SZ_B, USB_ROM_A+USB_ROM_SZ_B, USB_ROM_SZ_B );
         SOUND_COMMAND = 0x7F; 
      }

      sound_wait();
      SOUND_COMMAND = s;
      switch (s) {
         case ENTERPRISE_INTRO:
         case PLAYER_CHANGE:
            delay(3000);
            break;
         case COIN_DROP_MUSIC: 
            delay(5000);
            break;
         case HIGH_SCORE_MUSIC:
            delay(13000);
            break;
         case IMPULSE_END:
         case WARP_END:
         case RED_ALERT_END:
         case WARP_SUCK_END:
         case SAUCER_EXIT_END:
         case NOMAD_MOTION_END:
         case NOMAD_STOPPED_END:
            delay(500);
            break;
         default:
            delay(1000);
            break;
      }
   }
}

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


#define MAX_X (1024+450)
#define MIN_X (1024-450)
#define MAX_Y (1024+400)
#define MIN_Y (1024-400)

typedef struct {
   uint8_t last   : 1;
   uint8_t group  : 6;
   uint8_t visible : 1;
   uint16_t x;
   uint16_t y;
   uint16_t vector_addr; // E000 - EFFF 4k Vector RAM
   uint16_t rotation; // 10 bit angle of whole symbol
   uint8_t scale; // 0x40 = 1/2, 0x80 = 1x, 0xff = 2x
} symbol_t; // 10 bytes

#define SFIELD_COLOR(row)   (((row)*10)+0)
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
   uint8_t last   : 1;
   uint8_t red    : 2;
   uint8_t green  : 2;
   uint8_t blue    : 2;
   uint8_t visible : 1;
   uint8_t length;   // unscaled size
   uint8_t angle;   // degrees
   uint8_t quadrant; // msb of 10 bit angle
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
#define SEGA_COLOR_BLUE    (0x06|SEGA_VISIBLE)
#define SEGA_COLOR_YELLOW  (SEGA_COLOR_RED|SEGA_COLOR_GREEN)
#define SEGA_COLOR_CYAN    (SEGA_COLOR_GREEN|SEGA_COLOR_BLUE)
#define SEGA_COLOR_MAGENTA (SEGA_COLOR_RED|SEGA_COLOR_BLUE)
#define SEGA_COLOR_WHITE   (SEGA_COLOR_RED|SEGA_COLOR_GREEN|SEGA_COLOR_BLUE)
#define SEGA_COLOR_GRAY    (0x2A|SEGA_VISIBLE)
#define SEGA_ANGLE(deg)    ((uint16_t)(((float)(deg))*2.845))
#define SIZE(x)            (x*10)
#define LE(x)              LSB(x), MSB(x)


#define V_ADDR(x) (VECTOR_RAM+SYMBOLS_SZ+(x*4))
#define S_ADDR(x) (VECTOR_RAM+(x*10))


   const uint8_t vector[] = {
       #define V_LINE  0
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(180)),
       SEGA_COLOR_YELLOW|SEGA_LAST,  0x80, LE(SEGA_ANGLE(0)),

       #define V_0 (V_LINE+2)
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)),
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0xC0, LE(SEGA_ANGLE(17)),

       #define V_1 (V_0+4)
       SEGA_COLOR_MAGENTA,           0x40, LE(SEGA_ANGLE(90)),
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)),
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(270)),
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(90)),

       #define V_2 (V_1+4)
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)),
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(90)),

       #define V_3 (V_2+5)
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE43C
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE440
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE444
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE448
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE44C
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE450

       #define V_4 (V_3+6)
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(90)),  // 0xE454
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE458
       SEGA_CLEAR,                   0x60, LE(SEGA_ANGLE(17)),  // 0xE45C
       SEGA_CLEAR,                   0x40, LE(SEGA_ANGLE(90)),  // 0xE460
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE464
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x60, LE(SEGA_ANGLE(17)),  // 0xE468

       #define V_5 (V_4+6)
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE46C
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE470
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE474
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE478
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(197)), // 0xE47C
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE480

       #define V_6 (V_5+6)
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE484
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE488
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE48C
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE490
       SEGA_COLOR_MAGENTA,           0x60, LE(SEGA_ANGLE(17)),  // 0xE494
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE498

       #define V_7 (V_6+6)
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE49C
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0xC0, LE(SEGA_ANGLE(197)), // 0xE4A0

       #define V_8 (V_7+2)
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE4A4
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE4A8
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE4AC
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(17)),  // 0xE4B0
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),  // 0xE4B4
       SEGA_CLEAR,                   0x60, LE(SEGA_ANGLE(197)), // 0xE4B8
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE4BC

       #define V_9 (V_8+7)
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                   0x80, LE(SEGA_ANGLE(197)),
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(270)), // 0xE4C8
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(17)),  // 0xE4CC
       SEGA_COLOR_MAGENTA,           0x80, LE(SEGA_ANGLE(90)),  // 0xE4D0
       SEGA_COLOR_MAGENTA,           0xC0, LE(SEGA_ANGLE(197)), // 0xE4D4
       SEGA_COLOR_MAGENTA|SEGA_LAST, 0x80, LE(SEGA_ANGLE(270)), // 0xE4D8

       #define V_TANK (V_9+7)
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

       #define V_TREAD  (V_TANK+13)
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


     #define V_TURRET (V_TREAD+25)
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

     #define V_BARREL (V_TURRET+16)
     SEGA_CLEAR,                       SIZE(5),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(4),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN|SEGA_LAST,       SIZE(8),   LE(SEGA_ANGLE(180)),

     #define V_FLAME (V_BARREL+9)
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

     #define V_MISSILE (V_FLAME+11)
     SEGA_CLEAR,                       SIZE(0),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(0),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(0),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(0),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(18),  LE(SEGA_ANGLE(0)),
     SEGA_COLOR_YELLOW,                SIZE(1.2), LE(SEGA_ANGLE(158)),
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_YELLOW,                SIZE(1),   LE(SEGA_ANGLE(135)),
     SEGA_COLOR_YELLOW,                SIZE(2.2), LE(SEGA_ANGLE(270)),
     SEGA_COLOR_YELLOW,                SIZE(1),   LE(SEGA_ANGLE(45)),
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_YELLOW|SEGA_LAST,      SIZE(1.2), LE(SEGA_ANGLE(22)),

     #define V_BLADE (V_MISSILE+12)
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

     #define V_CHOPPER (V_BLADE+18)
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

     #define V_CUBE0 (V_CHOPPER+29)
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 0  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 1  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 3  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 4  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 5  front
     SEGA_COLOR_CYAN,                  SIZE(5.6), LE(SEGA_ANGLE(135)), // 6  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 7  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 8  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 9  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 10 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 11 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 12 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 13 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 14 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 15 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 16 rear

     #define V_CUBE1 (V_CUBE0+17)
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 0  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 1  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 3  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 4  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 5  front
     SEGA_COLOR_CYAN,                  SIZE(5.6), LE(SEGA_ANGLE(135)), // 6  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 7  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 8  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 9  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 10 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 11 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 12 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 13 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 14 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 15 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 16 rear

     #define V_CUBE2 (V_CUBE1+17)
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 0  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 1  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 3  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 4  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 5  front
     SEGA_COLOR_CYAN,                  SIZE(5.6), LE(SEGA_ANGLE(135)), // 6  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 7  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 8  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 9  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 10 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 11 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 12 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 13 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 14 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 15 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 16 rear

     #define V_LAST (V_CUBE2+17)
    };

   const uint8_t symbol[] = {
      // 10 bytes each entry
      // flags      x             y             address     rotation             scale

      #define S_DIG0  0
      SEGA_VISIBLE, LE(1024-40), LE(MIN_Y+30), LE(V_ADDR(V_0)),     LE(0),               0x10,
      #define S_DIG1  1
      SEGA_VISIBLE, LE(1024),    LE(MIN_Y+30), LE(V_ADDR(V_0)),     LE(0),               0x10,
      #define S_DIG2  2
      SEGA_VISIBLE, LE(1024+40), LE(MIN_Y+30), LE(V_ADDR(V_0)),     LE(0),               0x10,

      #define S_TANK  3
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_TANK)),  LE(SEGA_ANGLE(0)),   0x40,
      #define S_TREAD 4
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_TREAD)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_TURRET 5
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_TURRET)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_BARREL 6
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_BARREL)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_FLAME 7
      0,            LE(1024), LE(1024), LE(V_ADDR(V_FLAME)), LE(SEGA_ANGLE(0)),   0x40,

      #define S_MISSLE 8
      0,            LE(1024), LE(1024), LE(V_ADDR(V_MISSILE)), LE(SEGA_ANGLE(0)),   0x40,

      #define S_CHOPPER 9
      SEGA_VISIBLE, LE(1024), LE(MAX_Y-35), LE(V_ADDR(V_CHOPPER)), LE(0),     0x40,
      #define S_BLADE 10
      SEGA_VISIBLE, LE(1024), LE(MAX_Y-35), LE(V_ADDR(V_BLADE)), LE(0),     0x40,

      #define S_CUBE0 11
      SEGA_VISIBLE, LE(MIN_X), LE(1024-250), LE(V_ADDR(V_CUBE0)), LE(0),     0xf0,
      #define S_CUBE1 12
      SEGA_VISIBLE, LE(MAX_X-70), LE(1024), LE(V_ADDR(V_CUBE1)), LE(0),     0xf0,
      #define S_CUBE2 13
      SEGA_VISIBLE, LE(MIN_X), LE(1024+250), LE(V_ADDR(V_CUBE2)), LE(0),    0xf0,
      #define S_LAST  14
      SEGA_LAST
   };
   


// the xy ram is not dual port. and the xy board is running asynchonously 
// from the cpu, so you can't read from it without collissions and corrupting graphics.
uint8_t *symbols = (uint8_t*)(VECTOR_RAM); // must be at the top of vector ram   

// the vector table is useful to describe vectors, but since scale, position and rotation
// are all set in the symbol drawing list that vector table might as well be in rom
uint8_t *vectors = (uint8_t*)(VECTOR_RAM+SYMBOLS_SZ); // arbitrary location in vector ram


static void vector_init(void) {
   #if S_ADDR(S_LAST) > (VECTOR_RAM+SYMBOLS_SZ)
       #error 'symbols do not fit in memory'
   #endif
   #if V_ADDR(V_LAST) > (VECTOR_RAM+VECTOR_RAM_SZ)
       #error 'vectors do not fit in memory'
   #endif
   memcpy( symbols, symbol, sizeof(symbol) );
   memcpy( vectors, vector, sizeof(vector) );
}


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
// seems to work great on real hardeware, but not in mame
//      delta <<= 4;  // x 16
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

/*
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 0  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 1  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 3  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 4  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 5  front
     SEGA_COLOR_CYAN,                  SIZE(5.6), LE(SEGA_ANGLE(135)), // 6  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 7  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 8  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 9  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 10 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 11 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 12 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 13 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 14 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 15 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 16 rear
*/

static uint16_t flipCubeX( uint16_t x ) {
   if ( x < 1024 ) {
      return MAX_X-70;
   }
   return MIN_X;
}

static void colorCube( uint16_t vid, uint8_t quad ) {
   switch ( quad ) {
      case 1: // top right
         vectors[ VFIELD_COLOR(vid+0) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+8) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+10) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+16) ] = SEGA_COLOR_CYAN|SEGA_LAST;
         break;
      case 2: // top left
         vectors[ VFIELD_COLOR(vid+0) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+8) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+10) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+16) ] = SEGA_COLOR_CYAN|SEGA_LAST;
         break;
      case 3: // bottom left
         vectors[ VFIELD_COLOR(vid+0) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+8) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+10) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+16) ] = SEGA_COLOR_GRAY|SEGA_LAST;
         break;
      case 4: // bottom right
         vectors[ VFIELD_COLOR(vid+0) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+8) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+10) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+16) ] = SEGA_COLOR_GRAY|SEGA_LAST;
         break;
   }
}


static uint8_t quadrant( uint16_t x, uint16_t y ) {
   if ( x < 1024 ) {
      if ( y < 1024 ) {
         return 3; // bottom left
      } else {
         return 2; // top left
      }
   } else {
      if ( y < 1024 ) {
         return 4; // bottom right
      } else {
         return 1; // top right
      }
   }
}

static void moveCube( uint8_t sid, uint16_t vid, int8_t movex, int8_t movey ) {

   uint16_t x = symbols[ SFIELD_X_L(sid) ] | (symbols[ SFIELD_X_H(sid) ] << 8);
   uint16_t y = symbols[ SFIELD_Y_L(sid) ] | (symbols[ SFIELD_Y_H(sid) ] << 8);

   uint8_t quad_a = quadrant( x, y );

   x += movex;
   if ( x > MAX_X ) {
      x = MIN_X;
   } else if ( x < MIN_X ) {
      x = MAX_X;
   }

   y += movey;
   if ( y > MAX_Y ) {
      y = MIN_Y;
      x = flipCubeX( x );
   } else if ( y < MIN_Y ) {
      y = MAX_Y;
      x = flipCubeX( x );
   }

   symbols[ SFIELD_X_L(sid) ] = LSB(x);
   symbols[ SFIELD_X_H(sid) ] = MSB(x);
   symbols[ SFIELD_Y_L(sid) ] = LSB(y);
   symbols[ SFIELD_Y_H(sid) ] = MSB(y);


   uint8_t quad_b = quadrant( x, y );
   if ( quad_a != quad_b ) {
      colorCube( vid, quad_b );
   }

   static uint8_t ct = 0;
   ct++;
   if ( ct > 3 ) {
      // only need to update angle every 3 moves
      ct = 0;

      uint16_t a;
      if ( x < 1024 ) {
         a = divideBy3(y - MIN_Y) + SEGA_ANGLE(45);
      } else {
         a = SEGA_ANGLE(315) - divideBy3(y - MIN_Y);
      }

      vectors[ VFIELD_ANGLE_L(vid+0) ] = LSB(a);
      vectors[ VFIELD_ANGLE_H(vid+0) ] = MSB(a);
      vectors[ VFIELD_ANGLE_L(vid+3) ] = LSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_H(vid+3) ] = MSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_L(vid+8) ] = LSB(a);
      vectors[ VFIELD_ANGLE_H(vid+8) ] = MSB(a);
      vectors[ VFIELD_ANGLE_L(vid+11) ] = LSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_H(vid+11) ] = MSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_L(vid+14) ] = LSB(a);
      vectors[ VFIELD_ANGLE_H(vid+14) ] = MSB(a);
   }

}

static void drawChopper(void) {
   static uint16_t flight_x = 1024;
   static uint16_t flight_y = 1024;
   if (flight_x<MIN_X) {
      flight_x=MAX_X;
      flight_y = 1024-128 + (rand() << 1);
      symbols[ SFIELD_Y_L(S_CHOPPER) ] = LSB(flight_y);
      symbols[ SFIELD_Y_H(S_CHOPPER) ] = MSB(flight_y);
      symbols[ SFIELD_Y_L(S_BLADE) ] = LSB(flight_y);
      symbols[ SFIELD_Y_H(S_BLADE) ] = MSB(flight_y);
   }
   flight_x -= 4;
   symbols[ SFIELD_X_L(S_CHOPPER) ] = LSB(flight_x);
   symbols[ SFIELD_X_H(S_CHOPPER) ] = MSB(flight_x);
   symbols[ SFIELD_X_L(S_BLADE) ] = LSB(flight_x);
   symbols[ SFIELD_X_H(S_BLADE) ] = MSB(flight_x);

   static uint16_t blade_angle = 0;
   blade_angle = (blade_angle - 10) & 0x03FF;
   symbols[ SFIELD_ANGLE_L(S_BLADE) ] = LSB( blade_angle ); 
   symbols[ SFIELD_ANGLE_H(S_BLADE) ] = MSB( blade_angle );
}

static void drawTank(uint16_t angle) {
   uint8_t syms[] = {S_BARREL*10,S_FLAME*10,S_TURRET*10};
   for (uint8_t i=0; i<sizeof(syms)/sizeof(syms[0]); i++) {
      uint8_t ix = syms[i];
      symbols[ix+7] = LSB(angle); 
      symbols[ix+8] = MSB(angle);
   }
}

static uint8_t drawMissle(uint8_t dist) {
   if ( symbols[ SFIELD_COLOR(S_MISSLE) ] == SEGA_VISIBLE ) {
      if (dist < 250 ) {
         dist += 5;
         vectors[ VFIELD_SIZE(V_MISSILE+0) ] = dist;
         vectors[ VFIELD_SIZE(V_MISSILE+1) ] = dist;
         vectors[ VFIELD_SIZE(V_MISSILE+2) ] = dist;
         vectors[ VFIELD_SIZE(V_MISSILE+3) ] = dist;
      } else {
         symbols[ SFIELD_COLOR(S_MISSLE)] = 0;
      }
   }
   return dist;
}


static void vector_test(void) {

   vector_init();

   for (;;) {

            // draw score
            uint16_t lut[] = { V_ADDR(V_0),V_ADDR(V_1),V_ADDR(V_2),V_ADDR(V_3),V_ADDR(V_4),V_ADDR(V_5),V_ADDR(V_6),V_ADDR(V_7),V_ADDR(V_8),V_ADDR(V_9) };
            uint8_t r = score; // remainder
            uint8_t d0 = divideBy100( &r ); 
            uint8_t d1 = divideBy10( &r );
            uint8_t d2 = r;
            symbols[ SFIELD_ADDR_L(S_DIG0) ] = LSB(lut[d0]);
            symbols[ SFIELD_ADDR_H(S_DIG0) ] = MSB(lut[d0]);
            symbols[ SFIELD_ADDR_L(S_DIG1) ] = LSB(lut[d1]);
            symbols[ SFIELD_ADDR_H(S_DIG1) ] = MSB(lut[d1]);
            symbols[ SFIELD_ADDR_L(S_DIG2) ] = LSB(lut[d2]);
            symbols[ SFIELD_ADDR_H(S_DIG2) ] = MSB(lut[d2]);

            uint16_t vec_angle = spinner_vector_angle();
            static uint8_t missle = 0;

            static uint8_t ct=0;
            if ( ct == 0 ) {
               uint8_t button = PORT_374;
               if ( button == BUTTON_FIRE ) {
                  ct = 30;
                  SOUND_COMMAND = TANK_FIRE;
                  symbols[ SFIELD_COLOR(S_FLAME) ] = SEGA_VISIBLE;
                  symbols[ SFIELD_ANGLE_L(S_MISSLE) ] = LSB( vec_angle ); 
                  symbols[ SFIELD_ANGLE_H(S_MISSLE) ] = MSB( vec_angle );
                  symbols[ SFIELD_COLOR(S_MISSLE)] = SEGA_VISIBLE;
                  missle = 0;
               }
            }
            if (ct>=30) {
               ct++; 
               vectors[ VFIELD_SIZE(V_BARREL) ] = ct;
            }
            if (ct==45) {
               symbols[ SFIELD_COLOR(S_FLAME) ] = 0;
            }
            if (ct==60) {
               vectors[ VFIELD_SIZE(V_BARREL) ] = SIZE(5);
               ct = 0;
            }

            drawTank( vec_angle );

            missle = drawMissle( missle );

            drawChopper();

            if ( PORT_374 == BUTTON_THRUST ) {

               SOUND_COMMAND = TANK_MOVE;
               static uint8_t l = 10;
               vectors[ VFIELD_SIZE(V_TREAD+1) ] = l;
               if ( l < 40 ) {
                  l++;
               } else {
                  l = 10;
               }

               moveCube( S_CUBE0, V_CUBE0, 0, -1 );
               moveCube( S_CUBE1, V_CUBE1, 0, -1 );
               moveCube( S_CUBE2, V_CUBE2, 0, -1 );
            }
   }
}


static void init(void) {

   SPEECH_CONTROL = 0x28;
   // SPEECH_COMMAND = 0x00;

   // SPEECH_COMMAND = 0x80;
   // SOUND_COMMAND = 0xFF; // 8035 in reset and assert RAM LOAD latch

   // // blank the screen and clear vector ram
   const uint8_t s[] = { SEGA_LAST, LE(1024), LE(1024), LE(VECTOR_RAM+10), LE(0), 0x80,
                         SEGA_CLEAR|SEGA_LAST, 0x80, LE(0) };
   memcpy( VECTOR_RAM, s, sizeof(s) );
   memset( VECTOR_RAM+14, 0x00, VECTOR_RAM_SZ-14 );

   XY_INIT = 0x04;

   PORT_371 = 0x00;
   PORT_370 = 0xFF; // switch io expander from spinner to buttons
}




void main(void) {

   init();

   sound_init();
   __asm__("ei");

#ifdef ENABLE_UART
   send_uart_data("boot\r\n",6);
#endif

   //say( START );

   for (;;) {

      vector_test();

   }

}

