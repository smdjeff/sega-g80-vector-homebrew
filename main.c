
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
static uint8_t high_score[3] = { 1, 5, 10 };
static char* high_name[3] = { "amy", "sno", "jef" };
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
         debounce = 20; // half second
      if ( !(PORT_370 & IO_COIN0_N) ) {
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


static void sound_init(void) {
   extern const uint8_t usbrom_bin[];
   // copy main board ROMs into sound board's RAM 
   // so the 8035 can execute it
   SOUND_COMMAND = 0xFF; // assert RAM LOAD latch
   memcpy( (uint8_t*)USB_RAM, usbrom_bin, (1024*4) );
   SOUND_COMMAND = 0x7F; 
}


static void say(uint8_t i) {
   static uint16_t last_tick = 0;
   while ( system_tick - last_tick < 750/25 ) {
      // wait for speech to finish, sending too fast causes glitches
      // but unclear how to receive interrupt on complete of phrase
      // so just busy wait
      //SPEECH_COMMAND = NO_PHRASE;
      __asm__( "nop" );
   }
   SPEECH_COMMAND = i;
   SPEECH_COMMAND = i | 0x80;
   last_tick = system_tick;
}

static void digits3( uint8_t *d0, uint8_t *d1, uint8_t *d2, uint8_t r ) {
   *d0 = '0' + divideBy100( &r ); 
   *d1 = '0' + divideBy10( &r );
   *d2 = '0' + r;
}


#pragma disable_warning 110 // flow changed by optimizer
#pragma disable_warning 126 // unreachable code

static inline void stretch3(uint8_t *p, uint16_t i) {
   p[sizeof(vector_t)*0] = MIN(255,i); i-=MIN(255,i);
   p[sizeof(vector_t)*1] = MIN(255,i); i-=MIN(255,i);
   p[sizeof(vector_t)*2] = MIN(255,i);
}

static inline void stretch5(uint8_t *p, uint16_t i) {
   p[sizeof(vector_t)*0] = MIN(255,i); i-=MIN(255,i);
   p[sizeof(vector_t)*1] = MIN(255,i); i-=MIN(255,i);
   p[sizeof(vector_t)*2] = MIN(255,i); i-=MIN(255,i);
   p[sizeof(vector_t)*3] = MIN(255,i); i-=MIN(255,i);
   p[sizeof(vector_t)*4] = MIN(255,i);

}

static inline void stretch4_fast(uint8_t *p, uint8_t i) {
   p[sizeof(vector_t)*0] = i;
   p[sizeof(vector_t)*1] = i;
   p[sizeof(vector_t)*2] = i;
   p[sizeof(vector_t)*3] = i;
}


   const uint8_t vector[] = {
       #define V_BLANK (0)
       SEGA_CLEAR|SEGA_LAST,            0, LE(SEGA_ANGLE(0)),

       #define V_LINE  (V_BLANK+1)
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
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(90)), 
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)), 
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(90)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(90)),
       SEGA_CLEAR,                     SIZE(3),   LE(SEGA_ANGLE(180)),
       SEGA_COLOR_GREEN1,              SIZE(4),   LE(SEGA_ANGLE(270)),
       SEGA_CLEAR,                     SIZE(8),   LE(SEGA_ANGLE(270)), 
       SEGA_COLOR_GREEN1|SEGA_LAST,    SIZE(4),   LE(SEGA_ANGLE(270)), 


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
     SEGA_CLEAR,                       SIZE(5.6), LE(SEGA_ANGLE(315)), // 0  beam wait
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(45)),  // 1  angle 
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(90)),  // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(180)), // 3  rear
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(225)), // 4  angle 180
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(270)), // 5  front
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(0)),   // 6  front
     SEGA_COLOR_RED,                   SIZE(11.2), LE(SEGA_ANGLE(135)), // 7  front
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(0)),   // 8  front
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(45)),  // 9  angle
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(270)), // 10  retrace
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(180)), // 11 rear
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(225)), // 12 angle 180
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(0)),   // 13 retrace
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(90)),  // 14 front
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(45)),  // 15 angle retrace
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(180)), // 16 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(8),   LE(SEGA_ANGLE(270)), // 17 rear

     #define V_CUBE1 (V_CUBE0+18)
     SEGA_CLEAR,                       SIZE(5.6), LE(SEGA_ANGLE(315)), // 0  beam wait
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(45)),  // 1  angle 
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(90)),  // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(180)), // 3  rear
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(225)), // 4  angle 180
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(270)), // 5  front
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(0)),   // 6  front
     SEGA_COLOR_GREEN,                 SIZE(11.2), LE(SEGA_ANGLE(135)), // 7  front
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(0)),   // 8  front
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(45)),  // 9  angle
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(270)), // 10  retrace
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(180)), // 11 rear
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(225)), // 12 angle 180
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(0)),   // 13 retrace
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(90)),  // 14 front
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(45)),  // 15 angle retrace
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(180)), // 16 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(8),   LE(SEGA_ANGLE(270)), // 17 rear

     #define V_CUBE2 (V_CUBE1+18)
     SEGA_CLEAR,                       SIZE(5.6), LE(SEGA_ANGLE(315)), // 0  beam wait
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(45)),  // 1  angle 
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(90)),  // 2  rear
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(180)), // 3  rear
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(225)), // 4  angle 180
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(270)), // 5  front
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(0)),   // 6  front
     SEGA_COLOR_BLUE,                  SIZE(11.2), LE(SEGA_ANGLE(135)), // 7  front
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(0)),   // 8  front
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(45)),  // 9  angle
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(270)), // 10  retrace
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(180)), // 11 rear
     SEGA_COLOR_CYAN,                  SIZE(2),   LE(SEGA_ANGLE(225)), // 12 angle 180
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(0)),   // 13 retrace
     SEGA_COLOR_CYAN,                  SIZE(8),   LE(SEGA_ANGLE(90)),  // 14 front
     SEGA_CLEAR,                       SIZE(2),   LE(SEGA_ANGLE(45)),  // 15 angle retrace
     SEGA_CLEAR,                       SIZE(8),   LE(SEGA_ANGLE(180)), // 16 retrace
     SEGA_COLOR_CYAN|SEGA_LAST,        SIZE(8),   LE(SEGA_ANGLE(270)), // 17 rear


//        ^
//        0
//        |
// < 270 -+- 90 >
//        |
//       180
//        v

     #define V_STREET (V_CUBE2+18)
     SEGA_CLEAR,                       255,       LE(SEGA_ANGLE(0)),   // 0 up adjustable
     SEGA_CLEAR,                       255,       LE(SEGA_ANGLE(0)),   // 1 up adjustable
     SEGA_CLEAR,                       200,       LE(SEGA_ANGLE(0)),   // 2 up adjustable
     SEGA_CLEAR,                       128,       LE(SEGA_ANGLE(0)),   // 3 up fixed offset - middle of road

     SEGA_CLEAR,                       0,         LE(SEGA_ANGLE(270)), // 4 left adjustable
     SEGA_CLEAR,                       0,         LE(SEGA_ANGLE(270)), // 5 left adjustable
     SEGA_CLEAR,                       0,         LE(SEGA_ANGLE(270)), // 6 left adjustable
     SEGA_CLEAR,                       0,         LE(SEGA_ANGLE(270)), // 7 left adjustable
     SEGA_CLEAR,                       0,         LE(SEGA_ANGLE(270)), // 8 left adjustable
     SEGA_CLEAR,                       128,       LE(SEGA_ANGLE(270)), // 9 left fixed offset for middle of road

     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),  // 10
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),  // 11
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),  // 12
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),  // 13
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(90)),  // 14

     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),   // 15
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),   // 16
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),   // 17
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),   // 18

     SEGA_CLEAR,                       255,       LE(SEGA_ANGLE(90)),  // 19

     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 20
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 21
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 22
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 23
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 24

     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 25
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 26
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 27
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 28
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(270)),  // 29

     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 30
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 31
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 32
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(180)),  // 33

     SEGA_CLEAR,                       255,       LE(SEGA_ANGLE(270)),  // 34

     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),  // 35
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),  // 36
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),  // 37
     SEGA_COLOR_WHITE,                 255,       LE(SEGA_ANGLE(0)),  // 38
     SEGA_COLOR_WHITE|SEGA_LAST,       255,       LE(SEGA_ANGLE(0)),  // 39


     #define HITBOX_SZ 80
     #define V_BOX (V_STREET+40)
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
      0x2A, 0x42, 0x22, 0x03,
      0x2B, 0x0a, 0xcf, 0x03,
      0x2B, 0x0a, 0x33, 0x00,
      0x2B, 0x08, 0x8b, 0x00,
      0x2B, 0x05, 0xd5, 0x00,
      0x2A, 0x09, 0x49, 0x01,
      0x2B, 0x0e, 0x3e, 0x00,
      0x2B, 0x10, 0x77, 0x00,
      0x2B, 0x0f, 0xb6, 0x00,
      0x2B, 0x11, 0xf7, 0x00,
      0x2B, 0x10, 0x33, 0x01,
      0x2B, 0x0e, 0x82, 0x01,
      0x2B, 0x0c, 0xdd, 0x01,
      0x2A, 0x0a, 0x77, 0x00,
      0x2B, 0x0b, 0x27, 0x01,
      0x2B, 0x0b, 0x80, 0x01,
      0x2B, 0x0e, 0xf1, 0x01,
      0x2B, 0x0b, 0x44, 0x02,
      0x2A, 0x08, 0xcf, 0x02,
      0x2B, 0x12, 0x58, 0x01,
      0x2B, 0x16, 0xb3, 0x01,
      0x2B, 0x12, 0x30, 0x02,
      0x2B, 0x11, 0x8e, 0x02,
      0x2B, 0x14, 0xd2, 0x02,
      0x2B, 0x11, 0x44, 0x03,
      0x2A, 0x0d, 0xc1, 0x01,
      0x2B, 0x0a, 0x47, 0x02,
      0x2B, 0x0c, 0x93, 0x02,
      0x2B, 0x0c, 0xf1, 0x02,
      0x2B, 0x0b, 0x4c, 0x03,
      0x2B, 0x0c, 0xa7, 0x03,
      0x2A, 0x0c, 0x4f, 0x00,
      0x2B, 0x14, 0xdd, 0x02,
      0x2B, 0x12, 0x22, 0x03,
      0x2B, 0x15, 0x9c, 0x03,
      0x2B, 0x16, 0xee, 0x03,
      0x2B, 0x0d, 0x3b, 0x00,
      0x2B, 0x0d, 0x77, 0x00,
      0x80, 0x00, 0x00, 0x00
     #define V_LAST (V_SMOKE+39)

    };




   const uint8_t symbol[] = {
      // 10 bytes each entry
      // flags      x             y             address     rotation             scale

      #define S_SCORE0    0
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x80,
      #define S_SCORE1    1
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x80,
      #define S_SCORE2    2
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x80,
      #define S_NAME0     3
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x40,
      #define S_NAME1     4
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x40,
      #define S_NAME2     5
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x40,
      #define S_STRING    6
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BLANK)),     LE(0),               0x40,

      #define S_TANK      7
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_TANK)),  LE(SEGA_ANGLE(0)),   0x40,
      #define S_TREAD     8
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_TREAD)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_TURRET    9
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_TURRET)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_BARREL   10
      SEGA_VISIBLE, LE(1024), LE(1024), LE(V_ADDR(V_BARREL)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_FLAME    11
      0,            LE(1024), LE(1024), LE(V_ADDR(V_FLAME)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_MISSLE   12
      0,            LE(1024), LE(1024), LE(V_ADDR(V_MISSILE)), LE(SEGA_ANGLE(0)),   0x40,

      #define S_BOX      13
      0,            LE(1024), LE(1024), LE(V_ADDR(V_BOX)), LE(SEGA_ANGLE(0)),   0x80,

      #define S_CHOPPER  14
      0,            LE(1024), LE(MAX_Y-35), LE(V_ADDR(V_CHOPPER)), LE(0),     0x50,
      #define S_BLADE    15
      0,            LE(1024), LE(MAX_Y-35), LE(V_ADDR(V_BLADE)), LE(0),     0x50,

      #define S_CUBE0    16
      SEGA_VISIBLE, LE(MIN_X+10), LE(1024-300), LE(V_ADDR(V_CUBE0)), LE(0),     0xe0,
      #define S_CUBE1    17
      SEGA_VISIBLE, LE(MAX_X-70), LE(1024), LE(V_ADDR(V_CUBE1)), LE(0),     0xe0,
      #define S_CUBE2    18
      SEGA_VISIBLE, LE(MIN_X+10), LE(1024+300), LE(V_ADDR(V_CUBE2)), LE(0),    0xe0,

      #define S_STREET   19
      SEGA_VISIBLE,  LE(1024), LE(1024), LE(V_ADDR(V_STREET)), LE(0),    0x80,

      #define S_EXPLODE0 20
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE0)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_EXPLODE1 21
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE0)), LE(SEGA_ANGLE(45)),   0x20,

      #define S_EXPLODE2 22
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_EXPLODE3 23
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(11)),   0x40,
      #define S_EXPLODE4 24
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(22)),   0x40,
      #define S_EXPLODE5 25
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(33)),   0x40,
      #define S_EXPLODE6 26
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(44)),   0x40,
      #define S_EXPLODE7 27
      0,             LE(1024), LE(1024), LE(V_ADDR(V_EXPLODE1)), LE(SEGA_ANGLE(55)),   0x40,

      #define S_SMOKE0   28
      0,             LE(1024), LE(1024), LE(V_ADDR(V_SMOKE)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_SMOKE1   29
      0,             LE(1024), LE(1024), LE(V_ADDR(V_SMOKE)), LE(SEGA_ANGLE(0)),   0x40,
      #define S_SMOKE2   30
      0,             LE(1024), LE(1024), LE(V_ADDR(V_SMOKE)), LE(SEGA_ANGLE(0)),   0x40,

      #define S_LAST  30
      SEGA_VISIBLE|SEGA_LAST, LE(1024), LE(1024), LE(V_ADDR(V_BLANK)), LE(0), 0x80,
   };
   


// the xy ram is not dual port. and the xy board is running asynchonously 
// from the cpu, so you can't read from it without collissions and corrupting graphics.
uint8_t *symbols = (uint8_t*)(VECTOR_RAM); // must be at the top of vector ram   

// the vector table is useful to describe vectors, but since scale, position and rotation
// are all set in the symbol drawing list that vector table might as well be in rom
#define VECTOR_RAM_BASE (VECTOR_RAM+SYMBOLS_SZ)
#define FONT_RAM_BASE   (V_ADDR(V_LAST))
uint8_t *vectors = (uint8_t*)(VECTOR_RAM_BASE); // arbitrary location in vector ram

typedef struct {
   int8_t x_speed;
   int8_t y_speed;
   int8_t rotation_speed;
   int8_t resize_speed;
   bool slow; // floating point speeds are tempting
} motion_t;

static motion_t motion[S_LAST+1] = { {0,}, };


static void animate(void) {
   static uint16_t last_tick = 0;
   uint8_t frame = system_tick - last_tick;

   if ( frame == 0 ) return;
   last_tick = system_tick;

   symbol_t *sym = (symbol_t*)symbols;
   for (uint8_t i=0; i<sizeof(symbol)/sizeof(symbol_t); i++) {
      if ( sym->visible ) {
         motion_t *m = &motion[ i ];
         if ( m->slow && ((system_tick & 0x0003) != 0) ) continue;
         sym->y += m->y_speed;
         sym->rotation = (sym->rotation + m->rotation_speed) & 0x03FF;
         uint8_t last_scale = sym->scale;
         if ( m->resize_speed ) {
            sym->scale += m->resize_speed;
            if ( sym->scale < last_scale ) {
               sym->visible = 0;
            }
         }
         if ( m->x_speed ) {
            sym->x += m->x_speed;
            if ((m->x_speed > 0 && sym->x > MAX_X) || (m->x_speed < 0 && sym->x < MIN_X)) {
               sym->visible = 0;
            }
         }
         if ( m->y_speed ) {
            sym->y += m->y_speed;
            if ((m->y_speed > 0 && sym->y > MAX_Y) || (m->y_speed < 0 && sym->y < MIN_Y)) {
               sym->visible = 0;
            }
         }
      }
      sym += 1;
   }
}

static inline void setTrajectory( uint8_t sid, uint8_t velocity, uint16_t sega_angle ) {
   // compound literals require ISO C99 or later and are not implemented
   // motion[sid] = (motion_t){ .y = 5 };
   motion_t *m = &motion[ sid ];
   int16_t x, y;
   vectorToXY( sega_angle, velocity, &x, &y );
   m->x_speed = x;
   m->y_speed = y;
}

static inline void setRotationSpeed( uint8_t sid, int8_t rotation_speed ) {
   motion_t *m = &motion[ sid ];
   m->rotation_speed = rotation_speed;
}

static inline void setResizeSpeed( uint8_t sid, int8_t resize_speed ) {
   motion_t *m = &motion[ sid ];
   m->resize_speed = resize_speed;
}

static inline void setStop( uint8_t sid ) {
   motion_t *m = &motion[ sid ];
   memset( m, 0x00, sizeof(motion_t) );
}


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


static uint16_t spinner_vector_angle( bool reset ) {
   PORT_370 = SELECT_SPINNER;
   delay(1);
   uint8_t value = PORT_374;
   bool dir = value & 0x01;
   value = value >> 1;
   PORT_370 = SELECT_BUTTONS;
   delay(1);

   static uint16_t angle = 0;
   static uint16_t lastvalue = 0;
   if ( reset ) {
      angle = 0;
   } else {
      if ( value > lastvalue ) {
         lastvalue += 127; // 2^7 max angle in spinner space
      }
      uint8_t delta = lastvalue - value;
      // spinner angle in degrees is about 5.6 * value
      // vector is SEGA_ANGLE( angle ), so 2.845 * 5.6 = ~16
      #ifdef MAME_BUILD
         delta >>= 2; // mame seems to increment the spinner inaccurately
      #else
         // seems to work great on real hardware
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

   }
}


static void colorizeCube( vector_t *vec, uint8_t quad ) {
   switch ( quad ) {
      case 1: // top right
         vec[1].color = SEGA_COLOR_CYAN;
         vec[2].color = SEGA_COLOR_GRAY;
         vec[3].color = SEGA_COLOR_GRAY;
         vec[4].color = SEGA_COLOR_CYAN;
         vec[9].color = SEGA_COLOR_GRAY;
         vec[11].color = SEGA_COLOR_CYAN;
         vec[12].color = SEGA_COLOR_CYAN;
         vec[17].color = SEGA_COLOR_CYAN|SEGA_LAST;
         break;
      case 2: // top left
         vec[1].color = SEGA_COLOR_GRAY;
         vec[2].color = SEGA_COLOR_GRAY;
         vec[3].color = SEGA_COLOR_CYAN;
         vec[4].color = SEGA_COLOR_CYAN;
         vec[9].color = SEGA_COLOR_CYAN;
         vec[11].color = SEGA_COLOR_GRAY;
         vec[12].color = SEGA_COLOR_CYAN;
         vec[17].color = SEGA_COLOR_CYAN|SEGA_LAST;
         break;
      case 3: // bottom left
         vec[1].color = SEGA_COLOR_CYAN;
         vec[2].color = SEGA_COLOR_CYAN;
         vec[3].color = SEGA_COLOR_CYAN;
         vec[4].color = SEGA_COLOR_CYAN;
         vec[9].color = SEGA_COLOR_CYAN;
         vec[11].color = SEGA_COLOR_GRAY;
         vec[12].color = SEGA_COLOR_GRAY;
         vec[17].color = SEGA_COLOR_GRAY|SEGA_LAST;
         break;
      case 4: // bottom right
         vec[1].color = SEGA_COLOR_CYAN;
         vec[2].color = SEGA_COLOR_CYAN;
         vec[3].color = SEGA_COLOR_GRAY;
         vec[4].color = SEGA_COLOR_GRAY;
         vec[9].color = SEGA_COLOR_CYAN;
         vec[11].color = SEGA_COLOR_CYAN;
         vec[12].color = SEGA_COLOR_CYAN;
         vec[17].color = SEGA_COLOR_GRAY|SEGA_LAST;
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

static inline void resetSymbol( symbol_t *sym, uint16_t x, uint16_t y, uint16_t sega_angle, uint8_t scale ) {
   sym->x = x;
   sym->y = y;
   sym->rotation = sega_angle;
   if ( scale != 0 ) sym->scale = scale;
}

static void enableSymbol( uint8_t sid, uint16_t x, uint16_t y, uint16_t sega_angle, uint8_t scale ) {
   symbol_t *sym = &((symbol_t *)symbols)[ sid ];
   resetSymbol( sym, x, y, sega_angle, scale );
   sym->visible = 1;
}

static void moveCubesX( void ) {
   for (uint8_t i=0; i<3; i++) {
      symbol_t *sym = &((symbol_t *)symbols)[S_CUBE0 + i];
      sym->x -= 1;
      if ( sym->x < 250 ) {
         sym->x = 1024+500;
      }
      sym++;
   }
}

static void moveCubesY( void ) {
   ((symbol_t*)symbols)[S_CHOPPER].y -= 1;
   ((symbol_t*)symbols)[S_BLADE].y -= 1;
   for (uint8_t i=0; i<3; i++) {
      symbol_t *sym = &((symbol_t *)symbols)[S_CUBE0 + i];
      sym->y -= 1;
      if ( sym->y < 250 ) {
         sym->y = 1024+500;
      }
      sym++;
   }
}


static void skewCubes( void ) {
   static uint8_t last_quad[3] = {0xFF,0xFF,0xFF};
   static uint8_t ct = 0;
   if (++ct<9) return;
   ct = 0;

   static uint8_t ix = 0;
   ix++;
   if (ix>2) ix = 0;

   const uint16_t vid[] = { V_CUBE0, V_CUBE1, V_CUBE2 };
   vector_t *vec = &((vector_t *)vectors)[ vid[ix] ];
   symbol_t *sym = &((symbol_t *)symbols)[ S_CUBE0 + ix ];

   uint8_t quad = quadrant( sym->x, sym->y );
   if ( quad != last_quad[ ix ] ) {
      colorizeCube( vec, quad );
      last_quad[ ix ] = quad;
   }

   uint16_t _a = xyToVector( sym->x, sym->y );
   uint16_t a = _a + SEGA_ANGLE(180) & 0x3FF;
   vec[1].angle = a;
   vec[4].angle = _a;
   vec[9].angle = a;
   vec[12].angle = _a;
   vec[15].angle = a;
}

static void startChopper(void) {
   uint8_t q = rand()&3;
   switch ( q ) {
      case 0:
         enableSymbol( S_CHOPPER, MIN_X, 1024, SEGA_ANGLE(180), 0 );
         enableSymbol( S_BLADE, MIN_X, 1024, SEGA_ANGLE(0), 0 );
         setTrajectory( S_CHOPPER, 5, SEGA_ANGLE(90) );
         setTrajectory( S_BLADE, 5, SEGA_ANGLE(90) );
         break;
      case 1:
         enableSymbol( S_CHOPPER, MAX_X, 1024, SEGA_ANGLE(0), 0 );
         enableSymbol( S_BLADE, MAX_X, 1024, SEGA_ANGLE(0), 0 );
         setTrajectory( S_CHOPPER, 5, SEGA_ANGLE(270) );
         setTrajectory( S_BLADE, 5, SEGA_ANGLE(270) );
         break;
      case 2:
         enableSymbol( S_CHOPPER, 1024, MIN_Y, SEGA_ANGLE(90), 0 );
         enableSymbol( S_BLADE, 1024, MIN_Y, SEGA_ANGLE(0), 0 );
         setTrajectory( S_CHOPPER, 5, SEGA_ANGLE(0) );
         setTrajectory( S_BLADE, 5, SEGA_ANGLE(0) );
         break;
      case 3:
         enableSymbol( S_CHOPPER, 1024, MAX_Y, SEGA_ANGLE(270), 0 );
         enableSymbol( S_BLADE, 1024, MAX_Y, SEGA_ANGLE(0), 0 );
         setTrajectory( S_CHOPPER, 5, SEGA_ANGLE(180) );
         setTrajectory( S_BLADE, 5, SEGA_ANGLE(180) );
         break;
   }
   setRotationSpeed( S_BLADE, SEGA_ANGLE(18) );
}


static void drawTank(uint16_t angle) {
   static uint16_t last_angle = 0;
   if ( angle != last_angle ) {
      last_angle = angle;
      symbol_t *sym = (symbol_t*)symbols;
      sym[ S_BARREL ].rotation = angle;
      sym[ S_TURRET ].rotation = angle;
      sym[ S_FLAME ].rotation = angle;
   }
}

static bool drawMissle(uint8_t *dist, int16_t *x, int16_t *y) {
   symbol_t *sym = (symbol_t*)symbols;

   if ( sym[ S_MISSLE ].visible ) {
      if (*dist < 250 ) {
         *dist += 2;
         // easiest way to move this is to fix the origin at the center of the screen
         // and stretch the invisible vectors at the beginning of the symbol
         stretch4_fast( &vectors[ VFIELD_SIZE(V_MISSILE+0) ], *dist );

         // although the hardware can quickly draw things at angles, we still have a lot 
         // of math to find its x,y position to deal with collision detection
         uint16_t length = (*dist << 1) + 70;
         int16_t x0,y0;
         vectorToXY( sym[S_MISSLE].rotation, length, &x0, &y0 );
         *x = x0 + sym[S_MISSLE].x;
         *y = y0 + sym[S_MISSLE].y;
         return true;
      } else {
         symbols[ SFIELD_VISIBLE(S_MISSLE)] = 0;
      }
   }
   return false;
}


static void resetVectors( void ) {
   memset( motion, 0x00, sizeof(motion) );
   memcpy( vectors, vector, sizeof(vector) ); // reset colorized vectors
   memcpy( symbols, symbol, sizeof(symbol) ); // reset symbols
}

static void beginAttract( void ) {
   resetVectors();

   // set font 'a' thru 'z' to brightest white for phosphor afterglow
   colorize( (uint8_t*)fontAddress('a'), fontAddress('z'+1)-fontAddress('a'), SEGA_COLOR_BRWHITE );

   // disable all other symbols on screen
   // interestingly, hardware ignores last flag if it's not also visible
   symbols[ SFIELD_VISIBLE(S_STRING) ] = SEGA_VISIBLE|SEGA_LAST;
}


static void endAttract( void ) {
   resetVectors();

   // set font 'a' thru 'z' to regular white
   colorize( (uint8_t*)fontAddress('a'), fontAddress('z'+1)-fontAddress('a'), SEGA_COLOR_WHITE );

   // set numbers '0' thru '9' to pink
   colorize( (uint8_t*)fontAddress('0'), fontAddress('9'+1)-fontAddress('0'), SEGA_COLOR_MAGENTA );

   // enable all other symbols on screen
   symbols[ SFIELD_VISIBLE(S_STRING) ] = 0;
}


static bool drawAttract( void ) {
   symbol_t *sym = (symbol_t*)symbols;

   if ( _coin_counter ) {
      if ( (PORT_374 & BUTTON_PLAYER_1) ) {
         _coin_counter--;
         return true;
      }
   }

   static uint8_t state = 0;
   static uint16_t last_tick = 0;
   if ( system_tick - last_tick > SECONDS(3) ) {
      last_tick = system_tick;
      state++;
   }

   static uint8_t last_coin_counter = 0;
   uint16_t coin_counter = _coin_counter;
   if ( coin_counter != last_coin_counter ) {
      last_coin_counter = coin_counter;
      last_tick = system_tick;
      state = 2;
   }

   switch ( state ) {

      case 0: {
         const char s[] = "game over";
         drawString( SYM_ADDR(S_STRING), CENTER_X-155, MIN_Y+40, 0x80, SEGA_COLOR_YELLOW, s, sizeof(s)-1 );
         enableSymbol( S_SCORE0, MIN_X-70, CENTER_Y, SEGA_ANGLE(0), 0xFF );
         state++;
         break; }

      case 2:
         if ( _coin_counter > 0 ) {
            const char s[] = "press start";
            drawString( SYM_ADDR(S_STRING), CENTER_X-165, MIN_Y+40, 0x80, SEGA_COLOR_BLUE, s, sizeof(s)-1 );
         } else {
            const char s[] = "insert coin";
            drawString( SYM_ADDR(S_STRING), CENTER_X-165, MIN_Y+40, 0x80, SEGA_COLOR_GREEN, s, sizeof(s)-1 );
         }
         state++;
         break;

      case 1: 
      case 3: {
         const char str[] = "attack vektor";
         symbol_t *sym = &((symbol_t *)symbols)[ S_SCORE0 ];
         sym->x = MIN_X-70;
         for ( uint8_t i=0; i<sizeof(str); i++ ) {
            // draw as fast as possible 
            // but in step with vector XY redraw which we're sensing indirectly though system_tick IRQ
            static uint16_t last_tick = 0;
            while ( system_tick == last_tick ) {
               __asm__( "nop" );
            }
            last_tick = system_tick;

            sym->x += 70;
            if ( str[i] == ' ' ) {
               sym->visible = false;
            } else {
               sym->vector_addr = fontAddress( str[i] );
               sym->visible = true;
            }
         }
         break; }

      case 4:
         sym[ S_SCORE0 ].visible = false;
         state++;
         break;

      case 5:
      case 7:
      case 9: {
         char s[7];
         const uint8_t i = ((state - 5) / 2);
         memcpy( &s[0], high_name[i], 3 );
         digits3( &s[4], &s[5], &s[6], high_score[i] );
         drawString( SYM_ADDR(S_STRING), 0, CENTER_Y+40, 0xA0, SEGA_COLOR_CYAN, s, sizeof(s) );
         setTrajectory( S_STRING, 20, SEGA_ANGLE(90) );
         state++;
         break; }

      case 6:
      case 8:
      case 10:
         if ( ((symbol_t*)symbols)[S_STRING].x > CENTER_X-150 ) {
            setStop( S_STRING );
         }
         break;

      default:
         state = 0;
         break;
    }

   return false;
}


static void beginDrawInitials( void ) {
   say( HIGH_SCORE );
   enableSymbol( S_NAME0, CENTER_X-70, CENTER_Y-220, SEGA_ANGLE(0), 0xA0 );
   enableSymbol( S_NAME1, CENTER_X-10, CENTER_Y-220, SEGA_ANGLE(0), 0xA0 );
   enableSymbol( S_NAME2, CENTER_X+50, CENTER_Y-220, SEGA_ANGLE(0), 0xA0 );
   spinner_vector_angle( true );
}


static bool drawInitials( void ) {
   static uint8_t ix = 0;
   static uint16_t *addr[] = {  &symbols[ SFIELD_ADDR_L(S_NAME0) ],
                                &symbols[ SFIELD_ADDR_L(S_NAME1) ],
                                &symbols[ SFIELD_ADDR_L(S_NAME2) ] };

   uint16_t vec_angle = spinner_vector_angle( false );
   char ch = 'a' + div_16( vec_angle, 39 ); // 2^10 / 26
   ch = MIN( MAX(ch, 'a'), 'z');
   static char last_ch = 0;
   if ( ch != last_ch ) {
      last_ch = ch;
      *addr[ix] = fontAddress( ch );
   } else {
      // blink cursor
      static uint16_t last_tick = 0;
      if ( (system_tick - last_tick) > 10 ) {
         last_tick = system_tick;
         if ( *addr[ix] == V_ADDR(V_LINE) ) {
            *addr[ix] = fontAddress( ch );
         } else {
            *addr[ix] = V_ADDR(V_LINE);
         }
      }
   }

   // debounce and advance next letter
   static uint16_t last_button_tick = 0; 
   uint8_t buttons = PORT_374;
   if ((buttons & BUTTON_FIRE) && ((system_tick - last_button_tick) > 50)) {
      last_button_tick = system_tick;
      *addr[ix] = fontAddress( ch );
      ix++;
      if (ix == 3) {
         say( CONGRATULATIONS );
         uint16_t last_tick = system_tick;
         // rainbow effect
         for (uint8_t color=0; color<0x3F; color++) {
            // synchronize color to the vector XY redraw
            static uint16_t last_tick = 0;
            while ( system_tick == last_tick ) {
               __asm__( "nop" );
            }
            last_tick = system_tick;
            colorize( (uint8_t*)fontAddress('a'), fontAddress('z'+1)-fontAddress('a'), (color&0x3F) << 1 );
         }
         return true;
      }
   }
   return false;
}

bool drawScore( uint8_t score, bool reset ) {
   static uint8_t last_score = 0;
   if ( score != last_score || reset ) {
      last_score = score;
      uint8_t d0,d1,d2;
      digits3( &d0, &d1, &d2, score );
      uint8_t r = score; // remainder
      symbol_t *sym = (symbol_t*)symbols;
      sym[ S_SCORE0 ].vector_addr = fontAddress( d0 );
      sym[ S_SCORE1 ].vector_addr = fontAddress( d1 );
      sym[ S_SCORE2 ].vector_addr = fontAddress( d2 );
   }
   return false;
}

static void shrapnel( uint16_t x, uint16_t y ) {
   for (uint8_t sid=S_EXPLODE2, q=0; sid<=S_EXPLODE7; sid++,q++) {
      uint8_t scale = 0x30 + (q<<4);
      uint8_t velocity = 1 + 30-(q<<1);
      setTrajectory( sid, velocity, randSegaAngle() );
      setRotationSpeed( sid, SEGA_ANGLE(18) );
      enableSymbol( sid, x, y, SEGA_ANGLE(0), scale );
   }
}

static void explode( uint16_t x, uint16_t y ) {
   setRotationSpeed( S_EXPLODE0, SEGA_ANGLE(12) );
   setResizeSpeed( S_EXPLODE0, 25 );
   enableSymbol( S_EXPLODE0, x, y, SEGA_ANGLE(0), 0x30 );

   setRotationSpeed( S_EXPLODE1, SEGA_ANGLE(-12) );
   setResizeSpeed( S_EXPLODE1, 35 );
   enableSymbol( S_EXPLODE1, x, y, SEGA_ANGLE(0), 0x10 );
}

static uint8_t street_state;
static int16_t street_y;
static int16_t street_x;
static uint16_t chopper_timer;

static void beginPlay(void) {
   street_state = 0;
   street_y = (200+(255*2));
   street_x = 0;
   chopper_timer = system_tick;
   score = 0;
   enableSymbol( S_SCORE0, CENTER_X-40, MIN_Y+10, SEGA_ANGLE(0), 0x80 );
   enableSymbol( S_SCORE1, CENTER_X,    MIN_Y+10, SEGA_ANGLE(0), 0x80 );
   enableSymbol( S_SCORE2, CENTER_X+40, MIN_Y+10, SEGA_ANGLE(0), 0x80 );
   drawScore(score, true);
   spinner_vector_angle( true );
}


static bool drawPlay(void) {
   symbol_t *sym = (symbol_t*)symbols;

   uint16_t vec_angle = spinner_vector_angle( false );
   static uint8_t missle_dist = 0;

   uint8_t buttons = PORT_374;

   static uint8_t ct=0;
   if ( ct == 0 && !sym[ S_MISSLE ].visible ) {
      if ( buttons & BUTTON_FIRE ) {
         ct = 30;
         SOUND_COMMAND = TANK_FIRE;
         sym[ S_FLAME ].visible = true;
         sym[ S_MISSLE ].rotation = vec_angle;
         sym[ S_MISSLE ].visible = true;
         missle_dist = 0;
      }
   }
   if (ct>=30) {
      ct++; 
      vectors[ VFIELD_SIZE(V_BARREL) ] = ct;
   }
   if (ct==45) {
      sym[ S_FLAME ].visible = false;
   }
   if (ct==60) {
      vectors[ VFIELD_SIZE(V_BARREL) ] = SIZE(5);
      ct = 0;
   }

   drawTank( vec_angle );

   symbol_t *chopper = &((symbol_t*)symbols)[S_CHOPPER];
   int16_t x,y = 0;
   if ( sym[S_MISSLE].visible && drawMissle( &missle_dist, &x, &y ) ) {
      uint16_t x0 = x-(HITBOX_SZ/2);
      uint16_t x1 = x+(HITBOX_SZ/2);
      uint16_t y0 = y-(HITBOX_SZ/2);
      uint16_t y1 = y+(HITBOX_SZ/2);
      if (  chopper->visible  ) {
         if ( chopper->x > x0 && chopper->x < x1 && chopper->y > y0 && chopper->y < y1 ) {

            score++;
            sym[ S_MISSLE ].visible = false;
            sym[ S_CHOPPER ].visible = false;
            sym[ S_BLADE ].visible = false;

            sound_track = 2;

            explode( x, y );
            shrapnel( x, y );
         }
      }
   }

   if ( chopper->visible ) {

      uint16_t x0 = CENTER_X-(HITBOX_SZ/2);
      uint16_t x1 = CENTER_X+(HITBOX_SZ/2);
      uint16_t y0 = CENTER_Y-(HITBOX_SZ/2);
      uint16_t y1 = CENTER_Y+(HITBOX_SZ/2);
      if ( chopper->x > x0 && chopper->x < x1 && chopper->y > y0 && chopper->y < y1 ) {
         sym[ S_FLAME ].visible = false;
         sym[ S_MISSLE ].visible = false;

         explode( CENTER_X, CENTER_Y );

         SOUND_COMMAND = TANK_EXPLODE;
         return true; // game over
      }

   } else {

      if ( system_tick - chopper_timer >= 50 - MIN(50,score) ) {
         chopper_timer = system_tick;
         startChopper();
      }

   }


   // symbols aren't drawn if their origin point is off screen
   // but the hardware will clip big symbol vectors outside the view.
   // so move the street by changing the invisible offset vector at the
   // begining of the symbol and just leave origin at CENTER screen

   vector_t *vec = (vector_t*)&vectors[ V_STREET * sizeof(vector_t) ];
   motion_t *m = &motion[ S_TANK ];
   uint16_t angle = sym[ S_TANK ].rotation;

   if ( buttons & BUTTON_THRUST ) {
      SOUND_COMMAND = TANK_MOVE;
      static uint8_t l = 10;
      vectors[ VFIELD_SIZE(V_TREAD+1) ] = l;
      l += 1;
      if ( l >40 ) l = 10;
   }

   switch ( street_state ) {
      case 0:
         // moving up screen
         if ( buttons & BUTTON_THRUST ) {
            if ( street_y > 0 ) {
               stretch3( &vec[0].size, street_y );
               street_y -= 1;
               moveCubesY();
               skewCubes();
            } else {
               setRotationSpeed( S_TANK, SEGA_ANGLE(12) );
               setRotationSpeed( S_TREAD, SEGA_ANGLE(12) );
               street_state++;
            }
         }
         break;
      case 1:
         // turning to right
         if ( angle >= SEGA_ANGLE(90) ) {
            setRotationSpeed( S_TANK, 0 );
            setRotationSpeed( S_TREAD, 0 );
            sym[ S_TANK ].rotation = SEGA_ANGLE(90);
            sym[ S_TREAD ].rotation = SEGA_ANGLE(90);
            street_state++;
         }
         break;
      case 2:
         // moving right
         if ( buttons & BUTTON_THRUST ) {
            if ( street_x < (255*5) ) {
               stretch5( &vec[4].size, street_x );
               street_x += 1;
               moveCubesX();
               skewCubes();
            } else {
               setRotationSpeed( S_TANK, SEGA_ANGLE(-12) );
               setRotationSpeed( S_TREAD, SEGA_ANGLE(-12) );
               street_state++;
            }
         }
         break;
      case 3:
         // turning to left
         if ( angle > SEGA_ANGLE(360-45) ) {
            setRotationSpeed( S_TANK, 0 );
            setRotationSpeed( S_TREAD, 0 );
            sym[ S_TANK ].rotation = SEGA_ANGLE(0);
            sym[ S_TREAD ].rotation = SEGA_ANGLE(0);
            vec[0].angle = SEGA_ANGLE(180);
            vec[1].angle = SEGA_ANGLE(180);
            vec[2].angle = SEGA_ANGLE(180);
            street_state++;
         }
         break;
      case 4:
         // moving up
         if ( buttons & BUTTON_THRUST ) {
            if ( street_y < (255*3) ) {
               stretch3( &vec[0].size, street_y );
               street_y += 1;
               moveCubesY();
               skewCubes();
            } else {
               // reset
               resetSymbol( SYM_ADDR(S_CUBE0), MIN_X+10,    1024-300, 0, 0xe0 );
               resetSymbol( SYM_ADDR(S_CUBE1), MAX_X-70, 1024,     0, 0xe0 );
               resetSymbol( SYM_ADDR(S_CUBE2), MIN_X+10,    1024+300, 0, 0xe0 );
               vec[0].angle = SEGA_ANGLE(0);
               vec[1].angle = SEGA_ANGLE(0);
               vec[2].angle = SEGA_ANGLE(0);
               street_x = 0;
               street_y = 200+(255*2);
               stretch3( &vec[0].size, street_y );
               stretch5( &vec[4].size, street_x );
               street_state = 0;
            }
         }
         break;
   }

   return false;
}

static void keepPuffing(void) {
   static uint16_t last_tick = 0;
   uint16_t frame = system_tick - last_tick;
   if ( frame >= SECONDS(1.5) ) {
      last_tick = system_tick;
      static uint8_t sid = S_SMOKE0;
      if ( ++sid > S_SMOKE2 ) sid = S_SMOKE0;
      enableSymbol( sid, CENTER_X, CENTER_Y, SEGA_ANGLE(0), 16 );
   }
}

static void beginGameOver(void) {
   if ( score <= high_score[2] ) {
      const char s[] = "game over";
      drawString( SYM_ADDR(S_STRING), CENTER_X-280, MIN_Y, 0xFE, SEGA_COLOR_RED, s, sizeof(s)-1 );
   }  else {
      const char s[] = "high score";
      drawString( SYM_ADDR(S_STRING), CENTER_X-280, MIN_Y, 0xFE, SEGA_COLOR_YELLOW, s, sizeof(s)-1 );
   }

   colorize( (uint8_t*)V_ADDR(V_SMOKE), V_ADDR(V_LAST)-V_ADDR(V_SMOKE), SEGA_COLOR_WHITE );

   setTrajectory( S_STRING, 5, SEGA_ANGLE(0) );

   uint16_t a = randSegaAngle();
   setTrajectory( S_TURRET, 6, a );
   setRotationSpeed( S_TURRET, SEGA_ANGLE(7) );
   setTrajectory( S_BARREL, 7, a+SEGA_ANGLE(90) );
   setRotationSpeed( S_BARREL, -SEGA_ANGLE(5) );

   for (uint8_t i=0; i<3; i++) {
      uint8_t sid = S_SMOKE0 + i;
      setRotationSpeed( sid, 1 );
      setTrajectory( sid, 2, SEGA_ANGLE(22) );
      setResizeSpeed( sid, 1 );
      motion[ sid ].slow = true;
   }
}

static bool drawGameOver(void) {
   // wait for text to slide into place
   if ( ((symbol_t*)symbols)[S_STRING].y > MAX_Y - 120 ) {
      setStop( S_STRING );
      return true;
   }
   return false;
}




static void super_loop(void) {
      static uint16_t last_tick = 0;

      animate();

      switch( game_state ) {

         case game_state_boot:
            beginAttract();
            game_state++;
            break;

         case game_state_attract:
            if ( drawAttract() ) {
               endAttract();
               beginPlay();
               game_state++;
            }
            break;

         case game_state_play:
            drawScore( score, false );
            if ( drawPlay() ) {
               game_state = game_state_game_over;
               beginGameOver();
            }
            break;

         case game_state_game_over:
            if ( drawGameOver() ) {
               if ( score <= high_score[2] ) {
                  last_tick = system_tick;
                  game_state = game_state_game_over_pause;
               } else {
                  game_state = game_state_highscore;
                  beginDrawInitials();
               }
            } else {
               keepPuffing();
            }
            break;

         case game_state_game_over_pause:
            if ( system_tick - last_tick > SECONDS(4) ) {
               game_state = game_state_boot;
            } else {
               keepPuffing();
            }
            break;

         case game_state_highscore:
            if ( drawInitials() ) {
               game_state = game_state_boot;
            } else {
               keepPuffing();
            }
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

