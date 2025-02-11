////////////////////////////////////
#include "sega.h"

 
uint8_t rand(void) {
   static uint8_t x = 0xC5;
   x |= (x == 0);   // if x == 0, set x = 1 instead
   x ^= (x & 0x07) << 5;
   x ^= x >> 3;
   x ^= (x & 0x03) << 6;
   return x & 0xff;
}

inline uint16_t xy_multiply( uint8_t x, uint8_t y ) {
   XY_MULTIPLICAND = x;
   XY_MULTIPLIER = y;
   uint16_t product = XY_MULTIPLIER;
   product += (uint16_t)XY_MULTIPLIER << 8;
   return product;
}


static inline uint8_t clz8(uint8_t x) {
    const uint8_t lookup[16] = { 4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 };
    uint8_t upper = x >> 4;
    uint8_t lower = x & 0x0F;
    return upper ? lookup[upper] : 4 + lookup[lower];
}


static inline uint8_t clz(uint16_t x) {
    uint8_t upper = MSB(x);
    uint8_t lower = LSB(x);
    return upper ? clz8(upper) : 8 + clz8(lower);
}

uint16_t div_16(uint16_t u, uint16_t v) {
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



uint8_t divideBy10(uint8_t *value) {
    uint8_t count = 0;
    while (*value >= 10) {
        *value -= 10;
        count++;
    }
    return count;
}

uint8_t divideBy100(uint8_t *value) {
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
