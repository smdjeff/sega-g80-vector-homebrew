
////////////////////////////////////
// dependencies:
// https://github.com/z88dk/z88dk/releases
// export PATH=${PATH}:/Users/jmathews/Desktop/z88dk/bin
// export ZCCCFG=/Users/jmathews/Desktop/z88dk/lib/config

////////////////////////////////////
#include "sega.h"



static volatile uint8_t nmi_counter = 0;
static volatile uint16_t system_tick = 0;
static volatile uint8_t _coin_counter = 0;
static uint8_t score = 0;
static uint8_t high_score = 0;
static game_state_t game_state = game_state_boot;
static uint8_t sound_track = 0;


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
   if ( div >= 5 ) {
      div = 0;
      // this is a 8Hz, 125ms timer
      timer_interrupt_4Hz();
   }
   div++;

   static uint8_t debounce = 0;
   if ( debounce == 0 ) {
      if ( !(PORT_370 & IO_COIN_N) ) {
         debounce = 20; // half second
         _coin_counter++;
         SOUND_COMMAND = COIN_DROP;
      }
   } else {
      debounce--;
   }

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


static void sound_init(void) {
   // copy main board ROMs into sound board's RAM 
   // so the 8035 can execute it
#ifdef EMBEDDED_USB
   // load 4k
   SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   memcpy( (uint8_t*)USB_RAM, (uint8_t*)USB_ROM_A, USB_ROM_SZ_A );
   SOUND_COMMAND = 0x7F; 
#endif
}


static void say(uint8_t i) {
   SPEECH_COMMAND = i;
   SPEECH_COMMAND = i | 0x80;
   // wait for speech to finish, sending too fast causes glitches
   // but unclear how to receive interrupt on complete of phrase
   delay( 750 );
   SPEECH_COMMAND = NO_PHRASE;
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
     
     #define V_SMOKE (V_EXPLODE1+4)
   0x60, 0x42, 0x22, 0x03,
   0x61, 0x0a, 0xcf, 0x03,
   0x61, 0x0a, 0x33, 0x00,
   0x61, 0x08, 0x8b, 0x00,
   0x61, 0x05, 0xd5, 0x00,
   0x60, 0x09, 0x49, 0x01,
   0x61, 0x0e, 0x3e, 0x00,
   0x61, 0x10, 0x77, 0x00,
   0x61, 0x0f, 0xb6, 0x00,
   0x61, 0x11, 0xf7, 0x00,
   0x61, 0x10, 0x33, 0x01,
   0x61, 0x0e, 0x82, 0x01,
   0x61, 0x0c, 0xdd, 0x01,
   0x60, 0x0a, 0x77, 0x00,
   0x61, 0x0b, 0x27, 0x01,
   0x61, 0x0b, 0x80, 0x01,
   0x61, 0x0e, 0xf1, 0x01,
   0x61, 0x0b, 0x44, 0x02,
   0x60, 0x08, 0xcf, 0x02,
   0x61, 0x12, 0x58, 0x01,
   0x61, 0x16, 0xb3, 0x01,
   0x61, 0x12, 0x30, 0x02,
   0x61, 0x11, 0x8e, 0x02,
   0x61, 0x14, 0xd2, 0x02,
   0x61, 0x11, 0x44, 0x03,
   0x60, 0x0d, 0xc1, 0x01,
   0x61, 0x0a, 0x47, 0x02,
   0x61, 0x0c, 0x93, 0x02,
   0x61, 0x0c, 0xf1, 0x02,
   0x61, 0x0b, 0x4c, 0x03,
   0x61, 0x0c, 0xa7, 0x03,
   0x60, 0x0c, 0x4f, 0x00,
   0x61, 0x14, 0xdd, 0x02,
   0x61, 0x12, 0x22, 0x03,
   0x61, 0x15, 0x9c, 0x03,
   0x61, 0x16, 0xee, 0x03,
   0x61, 0x0d, 0x3b, 0x00,
   0x61, 0x0d, 0x77, 0x00,
      0x80, 0x00, 0x00, 0x00
     #define V_LAST (V_SMOKE+38)

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
      #define S_SMOKE0 25
      0,             LE(1024), LE(1024), LE(V_ADDR(V_SMOKE)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_SMOKE1 26
      0,             LE(1024), LE(1024), LE(V_ADDR(V_SMOKE)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_SMOKE2 27
      0,             LE(1024), LE(1024), LE(V_ADDR(V_SMOKE)), LE(SEGA_ANGLE(0)),   0x40,

      #define S_LAST  27
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
   PORT_370 = SELECT_SPINNER;
   delay(1);
   uint8_t value = PORT_374;
   bool dir = value & 0x01;
   value = value >> 1;
   PORT_370 = SELECT_BUTTONS;
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

static void timer_interrupt_4Hz(void) {

   switch( game_state ) {
      case game_state_boot:
         break;

      case game_state_attract:
         break;

      case game_state_play: {
         if ( system_tick & BIT(0) ) {
            return;
         }
         // simple break beat
         const uint8_t track0[] = { BASE_DRUM,          0,  SNARE_DRUM,         0,
                                    BASE_DRUM,  BASE_DRUM,  SNARE_DRUM,         0, 
                                    BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                            0,  BASE_DRUM,  SNARE_DRUM,         0 };

         // // more complex break beat
         const uint8_t track1[] = { BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                    BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM, 
                                    BASE_DRUM,          0,  SNARE_DRUM, BASE_DRUM,
                                    BASE_DRUM, SNARE_DRUM,  SNARE_DRUM, BASE_DRUM };
         static uint8_t ix = 0;
         if ( sound_track == 0 ) {
            SOUND_COMMAND = track0[ ix ];
         } else {
            SOUND_COMMAND = SNARE_DRUM;
            if (ix==0 || ix==4 || ix==8 || ix==12) {
               if (sound_track) {
                  sound_track--;
               }
            }
         }
         ix++;
         if (ix>=sizeof(track0)) {
            ix = 0;
         }
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

// sets position, and size of symbol on screen and makes it visible
void enableSymbol( uint8_t sid, uint16_t x, uint16_t y, uint16_t sega_angle, uint8_t scale ) {
   uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
   if ( x != 0xFFFF ) p[0] = x;
   if ( y != 0xFFFF ) p[1] = y;
//   p[2] = addr;
   if ( sega_angle != 0xFFFF) p[3] = sega_angle;
   if ( scale != 0xFF ) symbols[ SFIELD_SCALE(sid) ] = scale;
   symbols[ SFIELD_VISIBLE(sid) ] = SEGA_VISIBLE;
}


// if symbol is currently visible, moves the symbol by delta
// until it is moved off screen at which point it's made invisble
static bool moveSymbol( uint8_t sid, int8_t x0, int8_t y0 ) {
   if ( symbols[ SFIELD_VISIBLE(sid) ] ) {
      uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
      p[0] += x0;
      p[1] += y0;
       if ((x0 > 0 && p[0] > MAX_X) || (x0 < 0 && p[0] < MIN_X) || 
           (y0 > 0 && p[1] > MAX_Y) || (y0 < 0 && p[1] < MIN_Y)) {
           symbols[ SFIELD_VISIBLE(sid) ] = 0;
           return false;
       }
    }
    return true;
}

// if symbol is currently visible, symbol is enlarged by delta
// until it's max size and then made invisible
static bool sizeSymbol( uint8_t sid, int8_t delta, uint8_t max ) {
   if ( symbols[ SFIELD_VISIBLE(sid) ] ) {
      symbols[ SFIELD_SCALE(sid) ] += delta;
      if ( symbols[ SFIELD_SCALE(sid) ] > max ) {
         symbols[ SFIELD_VISIBLE(sid) ] = 0;
         return false;
      }
   }
   return true;
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
   *p += sega_angle & 0x03FF;
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
      blade_xy[0] = chopper_xy[0];
      blade_xy[1] = chopper_xy[1];
      *blade_angle = (*blade_angle + flight_ea) & 0x03FF;
   } else {
      stopChopper();
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


static void beginAttract( void ) {
   // set font 'a' thru 'z' to brightest white for phosphor afterglow
   colorize( (uint8_t*)fontAddress('a'), fontAddress('z')-fontAddress('a'), SEGA_COLOR_BRWHITE );
   enableSymbol( S_DIG0, MIN_X-70, CENTER_Y, SEGA_ANGLE(0), 0xFE );

   const char *s = "insert coin";
   drawString( (uint8_t*)S_ADDR(S_DIG1), CENTER_X-165, MIN_Y+40, 0x80, SEGA_COLOR_BLUE, s );

   // disable all other symbols on screen
   symbols[ SFIELD_VISIBLE(S_DIG2) ] = SEGA_LAST;
}


static void endAttract( void ) {

   // set font 'a' thru 'z' to regular white
   colorize( (uint8_t*)fontAddress('a'), fontAddress('z')-fontAddress('a'), SEGA_COLOR_WHITE );

   // set numbers '0' thru '9' to pink
   colorize( (uint8_t*)fontAddress('0'), fontAddress('9')-fontAddress('0'), SEGA_COLOR_MAGENTA );

   // TODO: should restore positions and scales only (not make visible)
   enableSymbol( S_DIG0, CENTER_X-40, MIN_Y+30, SEGA_ANGLE(0), 0x40 );
   enableSymbol( S_DIG1, CENTER_X,    MIN_Y+30, SEGA_ANGLE(0), 0x40 );
   enableSymbol( S_DIG2, CENTER_X+40, MIN_Y+30, SEGA_ANGLE(0), 0x40 );

   say( START );
}

static bool drawAttract( void ) {
   static uint16_t last_tick = 0;
   static uint8_t ix = 0;
   const char *str = "attack vektor";
   const char *s = "press start";


   uint16_t coin_counter = _coin_counter;
   if ( coin_counter ) {
      static uint8_t last_coin_counter = 0xff;
      if ( coin_counter != last_coin_counter ) {
         last_coin_counter = coin_counter;
         if ( coin_counter ) {
            drawString( (uint8_t*)S_ADDR(S_DIG1), CENTER_X-165, MIN_Y+40, 0x80, SEGA_COLOR_GREEN, s);
         }
      }
      if ( (PORT_374 & BUTTON_PLAYER_1) ) {
         _coin_counter--;
         return true;
      }
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
      if (ix > strlen(str)) {
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

      static uint16_t *chopper_xy = &symbols[ SFIELD_X_L(S_CHOPPER) ];
      int16_t x,y = 0;
      if ( symbols[ SFIELD_VISIBLE(S_MISSLE) ] && drawMissle( &missle, &x, &y ) ) {
         uint16_t x0 = x-(HITBOX_SZ/2);
         uint16_t x1 = x+(HITBOX_SZ/2);
         uint16_t y0 = y-(HITBOX_SZ/2);
         uint16_t y1 = y+(HITBOX_SZ/2);
         if ( chopper_xy[0] > x0 && chopper_xy[0] < x1 && chopper_xy[1] > y0 && chopper_xy[1] < y1 ) {

            score++;
            symbols[ SFIELD_VISIBLE(S_MISSLE) ] = 0;
            symbols[ SFIELD_VISIBLE(S_CHOPPER) ] = 0;
            symbols[ SFIELD_VISIBLE(S_BLADE) ] = 0;

            sound_track = 2;

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
      }

      // if ( symbols[ SFIELD_VISIBLE(S_EXPLODE0) ] == SEGA_VISIBLE ) {
      //    rotateSymbol( S_EXPLODE0, 10 );
      //    rotateSymbol( S_EXPLODE1, -20 );
      //    sizeSymbol( uint8_t sid, uint8_t min, uint8_t max, int8_t delta );
      //    sizeSymbol( S_EXPLODE0, 2 );
      //    if ( ! sizeSymbol( S_EXPLODE1, 1 ) ) {
      //       stopChopper();
      //    }
      // }

      for (uint8_t i=0; i<sizeof(ex); i++) {
         uint8_t sid = S_EXPLODE2 + i;
         if ( symbols[ SFIELD_VISIBLE(sid) ] == SEGA_VISIBLE ) {
            if ( moveSymbol( sid, ex[i], ey[i] ) ) {
               rotateSymbol( sid, 2+i+i );
            }
         }
      }

      if ( symbols[ SFIELD_VISIBLE(S_CHOPPER) ] == SEGA_VISIBLE ) {

         uint16_t x0 = CENTER_X-(HITBOX_SZ/2);
         uint16_t x1 = CENTER_X+(HITBOX_SZ/2);
         uint16_t y0 = CENTER_Y-(HITBOX_SZ/2);
         uint16_t y1 = CENTER_Y+(HITBOX_SZ/2);
         if ( chopper_xy[0] > x0 && chopper_xy[0] < x1 && chopper_xy[1] > y0 && chopper_xy[1] < y1 ) {
            symbols[ SFIELD_VISIBLE(S_FLAME) ] = 0;
            symbols[ SFIELD_VISIBLE(S_MISSLE) ] = 0;
            enableSymbol( S_EXPLODE0, CENTER_X, CENTER_Y, SEGA_ANGLE(0), 0x60 );
            enableSymbol( S_EXPLODE1, CENTER_X, CENTER_Y, SEGA_ANGLE(0), 0x30 );
            SOUND_COMMAND = TANK_EXPLODE;
            return true; // game over
         }
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

static bool drawGameOver(void) {

   delay(10);

   static int16_t x0,y0;
   static int16_t x1,y1;
   static bool init = true;
   if ( init ) {
      init = false;
      if ( score <= high_score ) {
         const char *s = "game over";
         drawString( (uint8_t*)S_ADDR(S_DIG1), CENTER_X-280, MIN_Y, 0xFE, SEGA_COLOR_RED, s );
      }  else {
         const char *s = "high score";
         drawString( (uint8_t*)S_ADDR(S_DIG1), CENTER_X-280, MIN_Y, 0xFE, SEGA_COLOR_RED, s );
      }
      colorize( (uint8_t*)V_ADDR(V_LINE), V_ADDR(V_LAST)-V_ADDR(V_LINE), SEGA_COLOR_GRAY );
      colorize( (uint8_t*)V_ADDR(V_EXPLODE0), 0, SEGA_COLOR_YELLOW );
      colorize( (uint8_t*)V_ADDR(V_SMOKE), 0, SEGA_COLOR_GRAY );

      // calculate x and y deltas from vector velocity
      vectorPosition( randSegaAngle(), 5, &x0, &y0 );
      vectorPosition( randSegaAngle(), 6, &x1, &y1 );
   }

   rotateSymbol( S_TURRET, 7 );
   rotateSymbol( S_BARREL, -5 );

   moveSymbol( S_TURRET, x0, y0 );
   moveSymbol( S_BARREL, x1, y1 );

   {
      uint8_t sid = S_DIG1;
      uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
      if ( p[1] < CENTER_Y ) {
         p[1] += 1;
      }
   }


   {
      static uint16_t last_tick = 0;
      uint8_t frame = system_tick - last_tick;
      if ( frame >= 1 ) {
         last_tick = system_tick;

         drawChopper();

         {
            static uint8_t ix = 0;
            uint8_t sid = S_SMOKE0 + ix;
            sizeSymbol( sid, 1, 128 );
            rotateSymbol( sid, 1 );
            if ( last_tick & 0x0001 ) {
               moveSymbol( sid, 1, 1 );
            }
            if ( ++ix > 2 ) {
               ix = 0;
            }
         }
      }
   }


   {
      static uint16_t last_tick = 0;
      uint8_t frame = system_tick - last_tick;
      if ( frame >= 120 ) {
         last_tick = system_tick;

         for (uint8_t i=0; i<3; i++) {
            uint8_t sid = S_SMOKE0 + i;
            if ( !symbols[ SFIELD_VISIBLE(sid) ] ) { 
               symbols[ SFIELD_VISIBLE(sid) ] = SEGA_VISIBLE;
               uint16_t *p = &symbols[ SFIELD_X_L(sid) ];
               p[0] = CENTER_X;
               p[1] = CENTER_Y;
               symbols[ SFIELD_SCALE(sid) ] = 16;
               break;
            }
         }
      }
   }


   // if ( sizeSymbol( S_EXPLODE0, 20, 128, 2 ) ) {
   //    rotateSymbol( S_EXPLODE0, 10 );
   // }

   // if ( symbols[ SFIELD_VISIBLE(S_CHOPPER) ] == 0 ) {
   //    colorize( (uint8_t*)V_ADDR(V_EXPLODE0), 0, SEGA_COLOR_GRAY );
   //    colorize( (uint8_t*)V_ADDR(V_EXPLODE1), 0, SEGA_COLOR_GRAY );
   //    init = true;
   //    return true;
   // }
   return false;
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
            drawScore( score );
            if ( drawPlay() ) {
               game_state = game_state_game_over;
            }
            break;

         case game_state_game_over:
            if ( drawGameOver() ) {
               if ( score <= high_score ) {
                  game_state = game_state_attract;
               } else {
                  game_state = game_state_highscore;
               }
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
   PORT_370 = SELECT_BUTTONS;
}




void main(void) {

   init();

   sound_init();

   vector_init();

   __asm__("ei");
   __asm__("halt");

   for (;;) {
      super_loop();
   }

}

