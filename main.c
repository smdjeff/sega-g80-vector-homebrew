
////////////////////////////////////
// dependencies:
// https://github.com/z88dk/z88dk/releases
// export PATH=${PATH}:/Users/jmathews/Desktop/z88dk/bin
// export ZCCCFG=/Users/jmathews/Desktop/z88dk/lib/config

////////////////////////////////////
#include "sega.h"



static uint8_t nmi_counter = 0;
static uint16_t system_tick = 0;


// NMI int (the cpu board button was pushed)
void z80_nmi(void) __critical __interrupt {
   nmi_counter++;
}


static void timer_interrupt_4Hz(void);

// IRQ signal comes from multiple sources:
//    * XINT signal, which is a combination of:
//        - COINA impulse, clocks an LS74, cleared by INTCL signal
//        - COINB impulse, clocks an LS74, cleared by INTCL signal
//        - SERVICE impulse
//    * /EDGINT signal from vector board, clocks an LS74, cleared by INTCL signal
//        - signal comes from 15468480 crystal, divided by 3, and then by 0x1f788
void z80_rst_38h (void) __critical __interrupt(0) {

   // this is a 40Hz, 25ms timer
   system_tick++;

   static uint8_t div = 0;
   if ( div >= 10 ) {
      div = 0;
      // this is a 4Hz, 250ms timer
      timer_interrupt_4Hz();
   }
   div++;
   volatile uint8_t intcl = PORT_370; // force INTCL
}




static void delay(uint16_t ms) {
   while ( ms-- ) {
      for (uint16_t i=0; i<27; i++) {   // 1ms at 3.86712 MHz (when XY board is clocking)
      //for (uint16_t i=0; i<28; i++) {   // 1ms at 4.0 MHz (when CPU board is self clocking)
         __asm__( "nop" );
      }
   }
}



static void vectorPosition( uint16_t sega_angle, uint16_t length, int16_t *x, int16_t *y ) {
  bool sin_neg, cos_neg;
  
  uint8_t sin_value = sinlut( sega_angle, &sin_neg );
  uint8_t cos_value = coslut( sega_angle, &cos_neg );

  *x = 0; *y = 0;
  do {
    uint16_t l = MIN(length,254);
    *x += xy_multiply( 1 + l, sin_value ) >> 8;
    *y += xy_multiply( 1 + l, cos_value ) >> 8;
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
   memcpy( (uint8_t*)USB_RAM, (uint8_t*)USB_ROM_A, USB_ROM_SZ_A );
   SOUND_COMMAND = 0x7F; 

#if 0 // observed, but unnecessary, factory initalization 
   SPEECH_CONTROL = 0x28;
   SPEECH_CONTROL = 0x28;

   // bounce 8035
   SOUND_COMMAND = 0xFF; 
   SOUND_COMMAND = 0x7F; 

   // overwrite last 2k  - is this ONLY for the MUSIC sounds
   SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   memcpy( USB_RAM+USB_ROM_SZ_B, USB_ROM_B, USB_ROM_SZ_B );
   SOUND_COMMAND = 0x7F; 

   sound_wait();
   SOUND_COMMAND = 0x2B; // COIN_DROP_MUSIC
   delay(5000);

   SPEECH_CONTROL = 0x28;
   // bounce 8035
   SOUND_COMMAND = 0xFF; 
   SOUND_COMMAND = 0x7F; 

   const uint8_t speech_init[] = { 0x3f, 0xbf, 0x0a, 0x8a, 0x08, 0x88, 0x03, 0x83 };
   for (uint8_t i=0; i<sizeof(speech_init); i++) {
      SPEECH_COMMAND = speech_init[i];
   }

   SPEECH_CONTROL = 0x28;
   // load 4k again
   SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   memcpy( USB_RAM, USB_ROM_A, USB_ROM_SZ_A );
   SOUND_COMMAND = 0x7F; 

   sound_wait();
   SOUND_COMMAND = 0x27;
   delay(1000);

   sound_wait();
   SOUND_COMMAND = 0x27;
   delay(1000);

   sound_wait();
   SOUND_COMMAND = 0x26;
   delay(1000);

   sound_wait();
   SOUND_COMMAND = 0x28;
   delay(1000);

   sound_wait();
   SOUND_COMMAND = 0x2e;
   delay(1000);
#endif

#endif
}




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
         memcpy( (uint8_t*)USB_RAM+USB_ROM_SZ_B, (uint8_t*)USB_ROM_B, USB_ROM_SZ_B );
         SOUND_COMMAND = 0x7F; 
      }
      // reload normal effects into the back half of the 8035
      if (s==IMPULSE) {
         SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
         memcpy( (uint8_t*)USB_RAM+USB_ROM_SZ_B, (uint8_t*)USB_ROM_A+USB_ROM_SZ_B, USB_ROM_SZ_B );
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
         case WARP_SUCK_END: //SAUCER_EXIT_END
         case NOMAD_MOTION_END: //NOMAD_STOPPED_END
            delay(500);
            break;
         default:
            delay(1000);
            break;
      }
   }
}



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



   const uint8_t vector[] = {
       #define V_LINE  (0)
       SEGA_CLEAR,                   0x25, LE(SEGA_ANGLE(130)),
       SEGA_COLOR_YELLOW|SEGA_LAST,  0x1C, LE(SEGA_ANGLE(270)),

       #define V_TANK (V_LINE+2)
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
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),   // animation sequence: 1,2,3
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(90)), 
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)), 
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN2,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)), 
       SEGA_COLOR_GREEN2|SEGA_LAST,    SIZE(4),   LE(SEGA_ANGLE(270)), 


     #define V_TURRET (V_TREAD+25)
     SEGA_CLEAR,                       SIZE(7.5), LE(SEGA_ANGLE(45)),  // 0
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(180)), // 1
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(270)), // 2
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(0)),   // 3
     SEGA_COLOR_GREEN,                 SIZE(11),  LE(SEGA_ANGLE(90)),  // 4
     SEGA_COLOR_GREEN1,                SIZE(2),   LE(SEGA_ANGLE(225)), // 5
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(180)), // 6
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(135)), // 7
     SEGA_COLOR_GREEN1,                SIZE(2),   LE(SEGA_ANGLE(315)), // 8
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(270)), // 9
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(225)), // 10
     SEGA_COLOR_GREEN1,                SIZE(2),   LE(SEGA_ANGLE(45)),  // 11
     SEGA_COLOR_GREEN,                 SIZE(8),   LE(SEGA_ANGLE(0)),   // 12
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(315)), // 13
     SEGA_COLOR_GREEN1,                SIZE(2),   LE(SEGA_ANGLE(135)), // 14
     SEGA_COLOR_GREEN|SEGA_LAST,       SIZE(8),   LE(SEGA_ANGLE(90)),  // 15

     #define V_BARREL (V_TURRET+16)
     SEGA_CLEAR,                       SIZE(5),   LE(SEGA_ANGLE(0)),
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN1,                SIZE(8),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(0)),
     SEGA_COLOR_GREEN,                 SIZE(4),   LE(SEGA_ANGLE(90)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(180)),
     SEGA_COLOR_GREEN,                 SIZE(1),   LE(SEGA_ANGLE(270)),
     SEGA_COLOR_GREEN1|SEGA_LAST,      SIZE(8),   LE(SEGA_ANGLE(180)),

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
     SEGA_CLEAR,                       SIZE(2.8), LE(SEGA_ANGLE(315)), // 0  beam wait
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 1  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 3  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 4  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 5  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 6  front
     SEGA_COLOR_RED,                   SIZE(5.6), LE(SEGA_ANGLE(135)), // 7  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 8  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 9  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 10  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 11 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 12 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 13 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 14 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 15 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 16 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 17 rear

     #define V_CUBE1 (V_CUBE0+18)
     SEGA_CLEAR,                       SIZE(2.8), LE(SEGA_ANGLE(315)), // 0  beam wait
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 1  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 3  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 4  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 5  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 6  front
     SEGA_COLOR_GREEN,                 SIZE(5.6), LE(SEGA_ANGLE(135)), // 7  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 8  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 9  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 10  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 11 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 12 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 13 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 14 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 15 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 16 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 17 rear

     #define V_CUBE2 (V_CUBE1+18)
     SEGA_CLEAR,                       SIZE(2.8), LE(SEGA_ANGLE(315)), // 0  beam wait
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 1  angle 
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 3  rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 4  angle 180
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(270)), // 5  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 6  front
     SEGA_COLOR_BLUE,                  SIZE(5.6), LE(SEGA_ANGLE(135)), // 7  front
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(0)),   // 8  front
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(45)),  // 9  angle
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(270)), // 10  retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(180)), // 11 rear
     SEGA_COLOR_CYAN,                  SIZE(1),   LE(SEGA_ANGLE(225)), // 12 angle 180
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(0)),   // 13 retrace
     SEGA_COLOR_CYAN,                  SIZE(4),   LE(SEGA_ANGLE(90)),  // 14 front
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(45)),  // 15 angle retrace
     SEGA_CLEAR,                       SIZE(4),   LE(SEGA_ANGLE(180)), // 16 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(4),   LE(SEGA_ANGLE(270)), // 17 rear

     #define V_STREET0 (V_CUBE2+18)
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 0
     SEGA_COLOR_WHITE,                 0,         LE(SEGA_ANGLE(180)),  // 1
     SEGA_COLOR_WHITE,                 0,         LE(SEGA_ANGLE(180)),  // 2
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 3
     SEGA_CLEAR,                       255,       LE(SEGA_ANGLE(180)),  // 4
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),   // 5
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 6
     SEGA_COLOR_WHITE,                 0,         LE(SEGA_ANGLE(180)),  // 7
     SEGA_COLOR_WHITE|SEGA_LAST,       0,         LE(SEGA_ANGLE(180)),  // 8

     #define V_STREET1 (V_STREET0+9)
     SEGA_COLOR_WHITE,                 0,         LE(SEGA_ANGLE(180)),  // 0
     SEGA_COLOR_WHITE,                 0,         LE(SEGA_ANGLE(180)),  // 1
     SEGA_COLOR_WHITE,                 0,         LE(SEGA_ANGLE(180)),  // 2
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),   // 3
     SEGA_CLEAR,                       255,       LE(SEGA_ANGLE(180)),  // 4
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 5
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 6
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 7
     SEGA_COLOR_WHITE|SEGA_LAST,       0,         LE(SEGA_ANGLE(180)),  // 8

     #define HITBOX_SZ 80
     #define V_BOX (V_STREET1+9)
     SEGA_CLEAR,                       (HITBOX_SZ/1.4),  LE(SEGA_ANGLE(225)),  // 0
     SEGA_COLOR_MAGENTA,               HITBOX_SZ,        LE(SEGA_ANGLE(0)),    // 1
     SEGA_COLOR_MAGENTA,               HITBOX_SZ,        LE(SEGA_ANGLE(90)),   // 2
     SEGA_COLOR_MAGENTA,               HITBOX_SZ,        LE(SEGA_ANGLE(180)),  // 3
     SEGA_COLOR_MAGENTA|SEGA_LAST,     HITBOX_SZ,        LE(SEGA_ANGLE(270)),  // 4

     #define V_EXPLODE0 (V_BOX+5)
     SEGA_CLEAR,                       SIZE(3.1), LE(SEGA_ANGLE(248)),   // 0
     SEGA_COLOR_RED,                   SIZE(3),   LE(SEGA_ANGLE(293)),   // 1
     SEGA_COLOR_RED,                   SIZE(3),   LE(SEGA_ANGLE(68)),    // 2
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(0)),     // 3
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(135)),   // 4
     SEGA_COLOR_RED,                   SIZE(4),   LE(SEGA_ANGLE(22)),    // 5
     SEGA_COLOR_RED,                   SIZE(4),   LE(SEGA_ANGLE(158)),   // 6
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(45)),    // 7
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(180)),   // 8
     SEGA_COLOR_RED,                   SIZE(3),   LE(SEGA_ANGLE(113)),   // 9
     SEGA_COLOR_RED,                   SIZE(3),   LE(SEGA_ANGLE(248)),   // 10
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(180)),   // 11
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(315)),   // 12
     SEGA_COLOR_RED,                   SIZE(4),   LE(SEGA_ANGLE(203)),   // 13
     SEGA_COLOR_RED,                   SIZE(4),   LE(SEGA_ANGLE(338)),   // 14
     SEGA_COLOR_YELLOW,                SIZE(2),   LE(SEGA_ANGLE(225)),   // 15
     SEGA_COLOR_YELLOW|SEGA_LAST,      SIZE(2),   LE(SEGA_ANGLE(0)),     // 16

     #define V_EXPLODE1 (V_EXPLODE0+17)
     SEGA_CLEAR,                       SIZE(1),   LE(SEGA_ANGLE(180)),   // 0
     SEGA_COLOR_WHITE,                 SIZE(2),   LE(SEGA_ANGLE(0)),     // 1
     SEGA_CLEAR,                       SIZE(1.5), LE(SEGA_ANGLE(135)),   // 2
     SEGA_COLOR_YELLOW|SEGA_LAST,      SIZE(2),   LE(SEGA_ANGLE(270)),   // 3
     
     #define V_LAST (V_EXPLODE1+4)

    };

   const uint8_t symbol[] = {
      // 10 bytes each entry
      // flags      x             y             address     rotation             scale

      #define S_DIG0  0
      SEGA_LAST,    LE(1024-40), LE(MIN_Y+30), LE(V_ADDR(V_LINE)),     LE(0),               0x40,
      #define S_DIG1  1
      SEGA_VISIBLE, LE(1024),    LE(MIN_Y+30), LE(V_ADDR(V_LINE)),     LE(0),               0x40,
      #define S_DIG2  2
      SEGA_VISIBLE, LE(1024+40), LE(MIN_Y+30), LE(V_ADDR(V_LINE)),     LE(0),               0x40,

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

      #define S_BOX 9
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BOX)), LE(SEGA_ANGLE(0)),   0x80,

      #define S_CHOPPER 10
      0, LE(1024), LE(MAX_Y-35), LE(V_ADDR(V_CHOPPER)), LE(0),     0x40,
      #define S_BLADE 11
      0, LE(1024), LE(MAX_Y-35), LE(V_ADDR(V_BLADE)), LE(0),     0x40,

      #define S_CUBE0 12
      SEGA_VISIBLE, LE(MIN_X), LE(1024-250), LE(V_ADDR(V_CUBE0)), LE(0),     0xf0,
      #define S_CUBE1 13
      SEGA_VISIBLE, LE(MAX_X-70), LE(1024), LE(V_ADDR(V_CUBE1)), LE(0),     0xf0,
      #define S_CUBE2 14
      SEGA_VISIBLE, LE(MIN_X), LE(1024+250), LE(V_ADDR(V_CUBE2)), LE(0),    0xf0,

      #define S_STREET0 15
      SEGA_VISIBLE, LE(1024-200), LE(MAX_Y), LE(V_ADDR(V_STREET0)), LE(0),    0x88,
      #define S_STREET1 16
      SEGA_VISIBLE, LE(1024+200), LE(MAX_Y), LE(V_ADDR(V_STREET1)), LE(0),    0x88,

      #define S_EXPLODE0 17
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE0)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_EXPLODE1 18
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE0)), LE(SEGA_ANGLE(45)),   0x20,

      #define S_EXPLODE2 19
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_EXPLODE3 20
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(11)),   0x40,
      #define S_EXPLODE4 21
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(22)),   0x40,
      #define S_EXPLODE5 22
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(33)),   0x40,
      #define S_EXPLODE6 23
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(44)),   0x40,
      #define S_EXPLODE7 24
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(55)),   0x40,

      #define S_LAST  24
      SEGA_LAST
   };
   


// the xy ram is not dual port. and the xy board is running asynchonously 
// from the cpu, so you can't read from it without collissions and corrupting graphics.
uint8_t *symbols = (uint8_t*)(VECTOR_RAM); // must be at the top of vector ram   

// the vector table is useful to describe vectors, but since scale, position and rotation
// are all set in the symbol drawing list that vector table might as well be in rom
#define VECTOR_RAM_BASE (VECTOR_RAM+SYMBOLS_SZ)
#define FONT_RAM_BASE   (V_ADDR(V_LAST))
uint8_t *vectors = (uint8_t*)(VECTOR_RAM_BASE); // arbitrary location in vector ram


static void vector_init(void) {
   #if S_ADDR(S_LAST) > (VECTOR_RAM_BASE)
       #error 'symbols do not fit in memory'
   #endif
   #if V_ADDR(V_LAST) > (VECTOR_RAM+VECTOR_RAM_SZ)
       #error 'vectors do not fit in memory'
   #endif

   memcpy( symbols, symbol, sizeof(symbol) );
   memcpy( vectors, vector, sizeof(vector) );

   installFonts( (uint16_t)vectors+sizeof(vector) );
   // TODO: this should break the build if it doesn't fit.
   // #if FONT_RAM_BASE+FONT_RAM_SIZE > (VECTOR_RAM+VECTOR_RAM_SZ)
   //     #error 'fonts do not fit in memory'
   // #endif
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
      #if 1
         delta >>= 2;
      #else
         // seems to work great on real hardware, but not in mame
         delta <<= 4;  // x 16
      #endif
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


static uint16_t flipCubeX( uint16_t x ) {
   if ( x < 1024 ) {
      return MAX_X-70;
   }
   return MIN_X;
}

static void colorCube( uint16_t vid, uint8_t quad ) {
   switch ( quad ) {
      case 1: // top right
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+4) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+9) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+12) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+17) ] = SEGA_COLOR_CYAN|SEGA_LAST;
         break;
      case 2: // top left
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+4) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+9) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+12) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+17) ] = SEGA_COLOR_CYAN|SEGA_LAST;
         break;
      case 3: // bottom left
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+4) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+9) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+12) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+17) ] = SEGA_COLOR_GRAY|SEGA_LAST;
         break;
      case 4: // bottom right
         vectors[ VFIELD_COLOR(vid+1) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+2) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+3) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+4) ] = SEGA_COLOR_GRAY;
         vectors[ VFIELD_COLOR(vid+9) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+11) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+12) ] = SEGA_COLOR_CYAN;
         vectors[ VFIELD_COLOR(vid+17) ] = SEGA_COLOR_GRAY|SEGA_LAST;
         break;
   }
}


static inline uint8_t quadrant( uint16_t x, uint16_t y ) {
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

static void enableSymbol( uint8_t sid, uint16_t x, uint16_t y, uint16_t sega_angle, uint8_t scale ) {
   uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
   if ( x != 0xFFFF ) p[0] = x;
   if ( y != 0xFFFF ) p[1] = y;
//   p[2] = addr;
   if ( sega_angle != 0xFFFF) p[3] = sega_angle;
   if ( scale != 0xFF ) symbols[ SFIELD_SCALE(sid) ] = scale;
   symbols[ SFIELD_VISIBLE(sid) ] = SEGA_VISIBLE;
}

static bool moveSymbol( uint8_t sid, int8_t x0, int8_t y0 ) {
#if 0
   uint16_t x = symbols[ SFIELD_X_L(sid) ] + (symbols[ SFIELD_X_H(sid) ] << 8);
   uint16_t y = symbols[ SFIELD_Y_L(sid) ] + (symbols[ SFIELD_Y_H(sid) ] << 8);
   x += x0;
   y += y0;
   symbols[ SFIELD_X_L(sid) ] = LSB(x);
   symbols[ SFIELD_X_H(sid) ] = MSB(x);
   symbols[ SFIELD_Y_L(sid) ] = LSB(y);
   symbols[ SFIELD_Y_H(sid) ] = MSB(y);
   return false;
#else
   // 16bit pointer math is faster
   uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
   p[0] += x0;
   p[1] += y0;
   if ( x0 > 0 && p[0] > MAX_X ) return true;
   if ( x0 < 0 && p[0] < MIN_X ) return true;
   if ( y0 > 0 && p[1] > MAX_Y ) return true;
   if ( y0 < 0 && p[1] < MIN_Y ) return true;
   return false;
#endif   
}

static inline bool sizeSymbol( uint8_t sid, int8_t s ) {
   uint8_t scale = symbols[ SFIELD_SCALE(sid) ];
   if ( (uint8_t)(scale + s) < scale ) {
      return true;
   }
   symbols[ SFIELD_SCALE(sid) ] += s;
   return false;
}

static inline void rotateSymbol( uint8_t sid, int8_t sega_angle ) {
#if 0
   uint16_t a = symbols[ SFIELD_ANGLE_L(sid) ] + (symbols[ SFIELD_ANGLE_H(sid) ] << 8);
   a += deg;
   symbols[ SFIELD_ANGLE_L(sid) ] = LSB(a);
   symbols[ SFIELD_ANGLE_H(sid) ] = MSB(a);
#else
   // 16bit pointer math is faster
   uint16_t *p = &symbols[ SFIELD_ANGLE_L(sid) ];
   *p += sega_angle;
#endif   
}

static void moveStreet( uint8_t sid, int8_t movey ) {

   uint16_t y = symbols[ SFIELD_Y_L(sid) ] + (symbols[ SFIELD_Y_H(sid) ] << 8);

   y += movey;
   if ( y > MAX_Y ) {
      y = MIN_Y;
   } else if ( y < MIN_Y ) {
      y = MAX_Y;
   }

   symbols[ SFIELD_Y_L(sid) ] = LSB(y);
   symbols[ SFIELD_Y_H(sid) ] = MSB(y);
}

static void moveCube( uint8_t sid, uint16_t vid, int8_t movex, int8_t movey ) {

   uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
   uint16_t x = p[0];
   uint16_t y = p[1];

   uint8_t quad_a = quadrant( x, y );

   y += movey;
   if ( y < MIN_Y ) {
      y = MAX_Y;
      x = flipCubeX( x );

      // uint16_t a;
      // if ( x < 1024 ) {
      //    static uint8_t ct = 0;
      //    if ( ct & 0x01 ) {
      //       a = SEGA_ANGLE(180);
      //    } else {
      //       a = SEGA_ANGLE(270);
      //    }
      //    ct++;
      // } else {
      //    static uint8_t ct = 0;
      //    if ( ct & 0x01 ) {
      //       a = SEGA_ANGLE(0);
      //    } else {
      //       a = SEGA_ANGLE(90);
      //    }
      //    ct++;
      // }
      // // uint8_t sid2 = sid - S_CUBE0 + S_STREET0;
      // uint16_t *street_xy = &symbols[ SFIELD_X_L(sid2) ];
      // street_xy[0] = x;
      // street_xy[1] = y + 0;
      // street_xy[4] = a;
   }

   if ( y > MAX_Y ) {
      y = MIN_Y;
      x = flipCubeX( x );
   }

   p[0] = x;
   p[1] = y;

   uint8_t quad_b = quadrant( x, y );
   if ( quad_a != quad_b ) {
      colorCube( vid, quad_b );
   }

   static uint8_t ct = 0;
   ct++;
   if ( ct > 3 ) {
      // only need to update angle every 3 moves
      ct = 0;

      uint16_t a = 0;
      if ( x < 1024 ) {
         a = divideBy3(y - MIN_Y) + SEGA_ANGLE(45);
      } else {
         a = SEGA_ANGLE(315) - divideBy3(y - MIN_Y);
      }

#if 0
      vectors[ VFIELD_ANGLE_L(vid+1) ] = LSB(a);
      vectors[ VFIELD_ANGLE_H(vid+1) ] = MSB(a);
      vectors[ VFIELD_ANGLE_L(vid+4) ] = LSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_H(vid+4) ] = MSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_L(vid+9) ] = LSB(a);
      vectors[ VFIELD_ANGLE_H(vid+9) ] = MSB(a);
      vectors[ VFIELD_ANGLE_L(vid+12) ] = LSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_H(vid+12) ] = MSB(a+SEGA_ANGLE(180));
      vectors[ VFIELD_ANGLE_L(vid+15) ] = LSB(a);
      vectors[ VFIELD_ANGLE_H(vid+15) ] = MSB(a);
#else
      // 16bit pointer math is faster
      uint16_t _a = a + SEGA_ANGLE(180);
      uint16_t *p = &vectors[ VFIELD_ANGLE_L(vid) ];
      p[1 *4/2] = a;
      p[4 *4/2] = _a;
      p[9 *4/2] = a;
      p[12 *4/2] = _a;
      p[15 *4/2] = a;
#endif
   }

}

static int8_t flight_ex = 0;
static int8_t flight_ey = 0;
const int8_t flight_ea = SEGA_ANGLE(18);

static void startChopper(void) {
   uint8_t q = rand()&3;
   switch ( q ) {
      case 0:
         enableSymbol( S_CHOPPER, MIN_X, 1024, SEGA_ANGLE(180), 0xFF );
         enableSymbol( S_BLADE, MIN_X, 1024, SEGA_ANGLE(0), 0xFF );
         flight_ex = 5;
         flight_ey = 0;
         break;
      case 1:
         enableSymbol( S_CHOPPER, MAX_X, 1024, SEGA_ANGLE(0), 0xFF );
         enableSymbol( S_BLADE, MAX_X, 1024, SEGA_ANGLE(0), 0xFF );
         flight_ex = -5;
         flight_ey = 0;
         break;
      case 2:
         enableSymbol( S_CHOPPER, 1024, MIN_Y, SEGA_ANGLE(90), 0xFF );
         enableSymbol( S_BLADE, 1024, MIN_Y, SEGA_ANGLE(0), 0xFF );
         flight_ex = 0;
         flight_ey = 5;
         break;
      case 3:
         enableSymbol( S_CHOPPER, 1024, MAX_Y, SEGA_ANGLE(270), 0xFF );
         enableSymbol( S_BLADE, 1024, MAX_Y, SEGA_ANGLE(0), 0xFF );
         flight_ex = 0;
         flight_ey = -5;
         break;
   }
}

static void stopChopper(void) {
   symbols[ SFIELD_VISIBLE(S_EXPLODE0) ] = 0;
   symbols[ SFIELD_VISIBLE(S_EXPLODE1) ] = 0;
   symbols[ SFIELD_VISIBLE(S_CHOPPER) ] = 0;
   symbols[ SFIELD_VISIBLE(S_BLADE) ] = 0;
}

static void drawChopper(void) {
   static uint16_t *chopper_xy = &symbols[ SFIELD_X_L(S_CHOPPER) ];
   static uint16_t *blade_xy = &symbols[ SFIELD_X_L(S_BLADE) ];
   static uint16_t *blade_angle = &symbols[ SFIELD_ANGLE_L(S_BLADE) ];

   if ( moveSymbol( S_CHOPPER, flight_ex, flight_ey ) ) {
      stopChopper();
   } else {
      blade_xy[0] = chopper_xy[0];
      blade_xy[1] = chopper_xy[1];
      *blade_angle = (*blade_angle + flight_ea) & 0x03FF;
   }
}

static void drawTank(uint16_t angle) {
   static uint16_t last_angle = 0;
   if ( angle != last_angle ) {
      last_angle = angle;
      uint8_t syms[] = {S_BARREL*10,S_FLAME*10,S_TURRET*10};
      for (uint8_t i=0; i<sizeof(syms)/sizeof(syms[0]); i++) {
         uint8_t ix = syms[i];
         symbols[ix+7] = LSB(angle); 
         symbols[ix+8] = MSB(angle);
      }
   }
}

static bool drawMissle(uint8_t *dist, int16_t *x, int16_t *y) {
   if ( symbols[ SFIELD_VISIBLE(S_MISSLE) ] == SEGA_VISIBLE ) {
      if (*dist < 250 ) {
         *dist += 2;
         vectors[ VFIELD_SIZE(V_MISSILE+0) ] = *dist;
         vectors[ VFIELD_SIZE(V_MISSILE+1) ] = *dist;
         vectors[ VFIELD_SIZE(V_MISSILE+2) ] = *dist;
         vectors[ VFIELD_SIZE(V_MISSILE+3) ] = *dist;

         uint16_t sega_angle = symbols[ SFIELD_ANGLE_L(S_MISSLE) ] + (symbols[ SFIELD_ANGLE_H(S_MISSLE) ]<<8); 
         uint16_t length = (*dist << 1) + 70;
         int16_t x0,y0;
         vectorPosition( sega_angle, length, &x0, &y0 );

         uint16_t x1 = symbols[ SFIELD_X_L(S_MISSLE) ] + (symbols[ SFIELD_X_H(S_MISSLE) ]<<8); 
         uint16_t y1 = symbols[ SFIELD_Y_L(S_MISSLE) ] + (symbols[ SFIELD_Y_H(S_MISSLE) ]<<8); 
         *x = x1 + x0;
         *y = y1 + y0;

         return true;
      } else {
         symbols[ SFIELD_VISIBLE(S_MISSLE)] = 0;
      }
   }
   return false;
}



typedef enum {
   game_state_boot,
   game_state_attract,
   game_state_play,
   game_state_highscore,
   game_state_test
} game_state_t;


static void beginAttract( void ) {
   // set font 'a' thru 'z' to brightest white for phosphor afterglow
   colorize( fontAddress('a'), fontAddress('z')-fontAddress('a'), SEGA_COLOR_BRWHITE );
   enableSymbol( S_DIG0, MIN_X-70, CENTER_Y, SEGA_ANGLE(0), 0xFE );

   drawString( (uint8_t*)S_ADDR(S_DIG1), CENTER_X-165, MIN_Y+40, 0x80, SEGA_COLOR_BLUE, "insert coin" );

   // disable all other symbols on screen
   symbols[ SFIELD_VISIBLE(S_DIG2) ] = SEGA_LAST;
}


static void endAttract( void ) {

   // set font 'a' thru 'z' to regular white
   colorize( fontAddress('a'), fontAddress('z')-fontAddress('a'), SEGA_COLOR_WHITE );

   // set numbers '0' thru '9' to pink
   colorize( fontAddress('0'), fontAddress('9')-fontAddress('0'), SEGA_COLOR_MAGENTA );

   // TODO: should restore positions and scales only (not make visible)
   enableSymbol( S_DIG0, CENTER_X-40, MIN_Y+30, SEGA_ANGLE(0), 0x40 );
   enableSymbol( S_DIG1, CENTER_X,    MIN_Y+30, SEGA_ANGLE(0), 0x40 );
   enableSymbol( S_DIG2, CENTER_X+40, MIN_Y+30, SEGA_ANGLE(0), 0x40 );

   say( START );
}

static bool drawAttract( void ) {
   static uint16_t last_tick = 0;
   static uint8_t ix = 0;
   const char str[] = "attack vector";

   uint8_t buttons = PORT_374;
   if ( (buttons & BUTTON_PLAYER_1) ) {
      return true;
   }

#if 1
   // wait for XY redraw
   last_tick = system_tick;
   while ( system_tick == last_tick ) {
      __asm__( "nop" );
   }
#else   
   if ( (system_tick - last_tick) > 0 ) 
#endif
   {
      last_tick = system_tick;
      uint16_t *p = &symbols[ SFIELD_X_L(S_DIG0) ];
      p[0] += 70;
      if ( str[ix] == ' ' ) {
         symbols[ SFIELD_VISIBLE(S_DIG0) ] = 0;
      } else {
         p[2] = fontAddress( str[ix] );
         symbols[ SFIELD_VISIBLE(S_DIG0) ] = SEGA_VISIBLE;
      }
      ix++;
      if (ix == sizeof(str)) {
         symbols[ SFIELD_VISIBLE(S_DIG0) ] = 0;
         p[0] = MIN_X - 70;
         ix = 0;
      }
   }
   return false;
}

static bool drawInitials( void ) {
   static uint16_t last_tick = 0;
   static uint8_t ix = 0;
   static char initial[3] = {'a','a','a'};

   uint16_t vec_angle = spinner_vector_angle();
   initial[ix] = 'a' + vec_angle * 26 / SEGA_ANGLE(360);


   uint8_t buttons = PORT_374;
   static bool button_update = false;
   if ( !button_update && (buttons & BUTTON_FIRE) ) {
      button_update = true;
   }

   if ( (system_tick - last_tick) > 10 ) {
      last_tick = system_tick;

      static uint16_t *addr[] = {  &symbols[ SFIELD_ADDR_L(S_DIG0) ],
                                   &symbols[ SFIELD_ADDR_L(S_DIG1) ],
                                   &symbols[ SFIELD_ADDR_L(S_DIG2) ] };

      if ( *addr[ix] == V_ADDR(V_LINE) || button_update ) {
         *addr[ix] = fontAddress( initial[ix] );
      } else {
         *addr[ix] = V_ADDR(V_LINE);
      }
      if ( button_update ) {
         button_update = false;
         ix++;
         if (ix == 3) {
            say( CONGRATULATIONS );
            return true;
         }
      }
   }
   return false;
}

static bool drawScore( uint8_t score ) {
   static uint8_t last_score = 0;
   if ( score != last_score ) {
      last_score = score;
      uint8_t r = score; // remainder
      uint8_t d0 = divideBy100( &r ); 
      uint8_t d1 = divideBy10( &r );
      uint8_t d2 = r;
      static uint16_t *dig0_addr = &symbols[ SFIELD_ADDR_L(S_DIG0) ];
      static uint16_t *dig1_addr = &symbols[ SFIELD_ADDR_L(S_DIG1) ];
      static uint16_t *dig2_addr = &symbols[ SFIELD_ADDR_L(S_DIG2) ];
      *dig0_addr =  fontAddress( d0 + '0' );
      *dig1_addr =  fontAddress( d1 + '0' );
      *dig2_addr =  fontAddress( d2 + '0' );
   }
   return false;
}


static bool drawPlay(void) {

      static uint16_t last_tick = 0;
      uint8_t frame = system_tick - last_tick;
      last_tick = system_tick;


      uint16_t vec_angle = spinner_vector_angle();
      static uint8_t missle = 0;

      uint8_t buttons = PORT_374;

      static uint8_t ct=0;
      if ( ct == 0 && symbols[ SFIELD_VISIBLE(S_MISSLE)] == 0 ) {
         if ( buttons & BUTTON_FIRE ) {
            ct = 30;
            SOUND_COMMAND = TANK_FIRE;
            symbols[ SFIELD_VISIBLE(S_FLAME) ] = SEGA_VISIBLE;
            symbols[ SFIELD_ANGLE_L(S_MISSLE) ] = LSB( vec_angle ); 
            symbols[ SFIELD_ANGLE_H(S_MISSLE) ] = MSB( vec_angle );
            symbols[ SFIELD_VISIBLE(S_MISSLE)] = SEGA_VISIBLE;
            missle = 0;
         }
      }
      if (ct>=30) {
         ct++; 
         vectors[ VFIELD_SIZE(V_BARREL) ] = ct;
      }
      if (ct==45) {
         symbols[ SFIELD_VISIBLE(S_FLAME) ] = 0;
      }
      if (ct==60) {
         vectors[ VFIELD_SIZE(V_BARREL) ] = SIZE(5);
         ct = 0;
      }

      drawTank( vec_angle );

      static int8_t ex[3] = {0,};
      static int8_t ey[3] = {0,};

      int16_t x,y = 0;
      if ( symbols[ SFIELD_VISIBLE(S_MISSLE) ] && drawMissle( &missle, &x, &y ) ) {
         uint16_t x0 = x-(HITBOX_SZ/2);
         uint16_t x1 = x+(HITBOX_SZ/2);
         uint16_t y0 = y-(HITBOX_SZ/2);
         uint16_t y1 = y+(HITBOX_SZ/2);
         static uint16_t *chopper_xy = &symbols[ SFIELD_X_L(S_CHOPPER) ];
         if ( chopper_xy[0] > x0 && chopper_xy[0] < x1 && chopper_xy[1] > y0 && chopper_xy[1] < y1 ) {

            symbols[ SFIELD_VISIBLE(S_MISSLE) ] = 0;
            symbols[ SFIELD_VISIBLE(S_CHOPPER) ] = 0;
            symbols[ SFIELD_VISIBLE(S_BLADE) ] = 0;

            enableSymbol( S_EXPLODE0, x, y, SEGA_ANGLE(0), 0x60 );
            enableSymbol( S_EXPLODE1, x, y, SEGA_ANGLE(0), 0x30 );

            for (uint8_t i=0; i<sizeof(ex); i++) {
               uint8_t sid = S_EXPLODE2 + i;
               enableSymbol( sid, x, y, SEGA_ANGLE(0), 0xFF );
               int16_t sx, sy;
               vectorPosition( vec_angle - (1<<5) + (i<<5), 5, &sx, &sy );
               ex[i] = sx - flight_ex; // explosion vector is combo of missle and chopper of equal mass?
               ey[i] = sy - flight_ey;
            }
         }

         enableSymbol( S_BOX, x, y, SEGA_ANGLE(0), 0xFF );
      }

      if ( symbols[ SFIELD_VISIBLE(S_EXPLODE0) ] == SEGA_VISIBLE ) {
         rotateSymbol( S_EXPLODE0, 10 );
         rotateSymbol( S_EXPLODE1, -20 );
         sizeSymbol( S_EXPLODE0, 2 );
         if ( sizeSymbol( S_EXPLODE1, 1 ) ) {
            stopChopper();
         }
      }

      for (uint8_t i=0; i<sizeof(ex); i++) {
         uint8_t sid = S_EXPLODE2 + i;
         if ( symbols[ SFIELD_VISIBLE(sid) ] == SEGA_VISIBLE ) {
            if ( moveSymbol( sid, ex[i], ey[i] ) ) {
               symbols[ SFIELD_VISIBLE(sid) ] = 0;
            } else {
               rotateSymbol( sid, 2+i+i );
            }
         }
      }

      if ( symbols[ SFIELD_VISIBLE(S_CHOPPER) ] == SEGA_VISIBLE ) {
         if ( frame ) {
            drawChopper();
         }
      } else {
         static uint8_t frame_count = 0;
         frame_count += frame;
         if ( frame_count >= 40 /*1sec*/ ) {
            frame_count = 0;
            startChopper();
         }
      }


      int8_t tank_ey = 0;
      if ( buttons & BUTTON_THRUST ) {
         tank_ey = 1;
      }
      if ( buttons & BUTTON_PHOTON ) {
         tank_ey = -1;
      }
      if ( tank_ey ) {

         SOUND_COMMAND = TANK_MOVE;
         static uint8_t l = 10;
         vectors[ VFIELD_SIZE(V_TREAD+1) ] = l;
         l += tank_ey;
         if ( l >40 ) l = 10;
         if ( l <10 ) l = 40;

         moveCube( S_CUBE0, V_CUBE0, 0, -tank_ey );
         moveCube( S_CUBE1, V_CUBE1, 0, -tank_ey );
         moveCube( S_CUBE2, V_CUBE2, 0, -tank_ey );

         {
         uint8_t *p = &vectors[ VFIELD_SIZE(V_STREET0) ];
         uint16_t l0 = p[0*4] + p[1*4] + p[2*4];
         l0 += tank_ey;

         p[0*4] = MIN( l0, 255 );
         l0 -= MIN( l0, 255 );
         p[1*4] = MIN( l0, 255 );
         l0 -= MIN( l0, 255 );
         p[2*4] = MIN( l0, 255 );
         }

         {
         uint8_t *p = &vectors[ VFIELD_SIZE(V_STREET1) ];
         uint16_t l0 = p[0*4] + p[1*4] + p[2*4];
         l0 += tank_ey;

         p[0*4] = MIN( l0, 255 );
         l0 -= MIN( l0, 255 );
         p[1*4] = MIN( l0, 255 );
         l0 -= MIN( l0, 255 );
         p[2*4] = MIN( l0, 255 );
         }

         moveSymbol( S_CHOPPER, 0, -tank_ey );
         moveSymbol( S_BLADE, 0, -tank_ey );
      }

      return false;
}


static game_state_t game_state = game_state_boot;



static void timer_interrupt_4Hz(void) {

   switch( game_state ) {
      case game_state_boot:
         break;

      case game_state_attract:
         break;

      case game_state_play: {
         // simple break beat
         const uint8_t track[]  = { BASE_DRUM,          0,  SNARE_DRUM,         0,
                                    BASE_DRUM,  BASE_DRUM,  SNARE_DRUM,         0, 
                                    BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                            0,  BASE_DRUM,  SNARE_DRUM,         0 };

         // // more complex break beat
         // const uint8_t track[]  = { BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
         //                            BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM, 
         //                            BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
         //                            BASE_DRUM, SNARE_DRUM,  SNARE_DRUM, BASE_DRUM };
         static uint8_t ix = 0;
         SOUND_COMMAND = track[ ix ];
         ix++;
         if (ix>=sizeof(track)) ix = 0;
         break; }

      case game_state_highscore: {
         // new order blue monday
         const uint8_t track[]  = { BASE_DRUM,         0,           0,         0,
                                    BASE_DRUM,         0,           0,         0,
                                    BASE_DRUM,         0,           0,         0,
                                    BASE_DRUM,         0,           0,         0,
                                    BASE_DRUM,         0,           0,         0,
                                    BASE_DRUM,         0,           0,         0,
                                    BASE_DRUM, BASE_DRUM, BASE_DRUM, BASE_DRUM,
                                    BASE_DRUM, BASE_DRUM, BASE_DRUM, BASE_DRUM };
         static uint8_t ix = 0;
         SOUND_COMMAND = track[ ix ];
         ix++;
         if (ix>=sizeof(track)) ix = 0;
         break; }

      case game_state_test:
         break;
   }
}


static void super_loop(void) {

      switch( game_state ) {

         case game_state_boot:
            beginAttract();
            game_state++;
            break;

         case game_state_attract:
            if ( drawAttract() ) {
               endAttract();
               drawScore( 255 );
               game_state++;
            }
            break;

         case game_state_play:
            if ( drawPlay() ) {
               game_state = game_state_attract;
            }
            break;

         case game_state_highscore:
            if ( drawInitials() ) {
               game_state = game_state_attract;
            }
            break;

         case game_state_test:
            drawScore( system_tick / 40 );
            break;
      }
}



static void init(void) {

   SPEECH_CONTROL = 0x28;
   SPEECH_COMMAND = 0x00;
   SPEECH_COMMAND = 0x80;
   SOUND_COMMAND = 0xFF; // 8035 in reset and assert RAM LOAD latch

   // // blank the screen and clear vector ram
   const uint8_t s[] = { SEGA_LAST, LE(1024), LE(1024), LE(VECTOR_RAM+10), LE(0), 0x80,
                         SEGA_CLEAR|SEGA_LAST, 0x80, LE(0) };
   memcpy( (uint8_t*)VECTOR_RAM, s, sizeof(s) );
   memset( (uint8_t*)VECTOR_RAM+14, 0x00, VECTOR_RAM_SZ-14 );

   XY_INIT = 0x04;

   PORT_371 = 0x00;
   PORT_370 = 0xFF; // switch io expander from spinner to buttons
}




void main(void) {

   init();

   sound_init();

   vector_init();

   __asm__("ei");
   __asm__("halt");

#ifdef ENABLE_UART
   send_uart_data("boot\r\n",6);
#endif

   for (;;) {
      super_loop();
   }

}

