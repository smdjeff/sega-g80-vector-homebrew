////////////////////////////////////
#include "sega.h"



const uint8_t font_data_alpha[] = {

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x1c, 0x00, 0x03,
     0x55, 0x18, 0x01, 0x02,  0x54, 0x0c, 0x01, 0x00,  0xd5, 0x1c, 0x00, 0x01, // 'a'

     0x54, 0x1b, 0x4c, 0x01,  0x55, 0x0c, 0xff, 0x03,  0x55, 0x18, 0x02, 0x03,
     0x55, 0x18, 0x00, 0x02,  0x55, 0x1c, 0x01, 0x01,  0x55, 0x0c, 0x00, 0x00,
     0xd5, 0x1c, 0x01, 0x03,                                                   // 'b'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x1c, 0x00, 0x03,  0x55, 0x18, 0x00, 0x00, 
     0xd5, 0x1c, 0x00, 0x01,                                                   // 'c'

     0x54, 0x1f, 0x8f, 0x01,  0x55, 0x14, 0xff, 0x02,  0x55, 0x18, 0x02, 0x00, 
     0x55, 0x14, 0x00, 0x01,  0x55, 0x0b, 0x81, 0x01,  0xd5, 0x12, 0x49, 0x02, // 'd'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x1c, 0x00, 0x03,  0x55, 0x18, 0x00, 0x00,
     0x55, 0x1c, 0x00, 0x01,  0x54, 0x0c, 0x02, 0x02,  0xd5, 0x1c, 0x00, 0x03, // 'e'

     0x54, 0x18, 0x00, 0x02,  0x55, 0x18, 0x01, 0x00,  0x55, 0x1c, 0x00, 0x01,
     0x54, 0x0c, 0x02, 0x02,  0xd5, 0x1c, 0x00, 0x03,                          // 'f'

     0x54, 0x11, 0x80, 0x01,  0x55, 0x10, 0x00, 0x01,  0x55, 0x0c, 0x00, 0x02,
     0x55, 0x1c, 0x01, 0x03,  0x55, 0x18, 0x01, 0x00,  0xd5, 0x1c, 0x01, 0x01, // 'g'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x18, 0x00, 0x02,  0x54, 0x0c, 0x01, 0x00,
     0x55, 0x1c, 0x01, 0x03,  0x54, 0x0c, 0x01, 0x02,  0xd5, 0x18, 0x01, 0x00, // 'h'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x1c, 0x00, 0x03,  0x54, 0x0e, 0x00, 0x01,
     0x55, 0x18, 0x00, 0x00,  0x54, 0x0e, 0x00, 0x01,  0xd5, 0x1c, 0x00, 0x03, // 'i'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x18, 0x00, 0x02,  0x55, 0x1c, 0x01, 0x03,
     0xd5, 0x08, 0x01, 0x00,                                                   // 'j'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x1e, 0xbe, 0x02,  0x54, 0x0c, 0xfb, 0x03,
     0x55, 0x18, 0x00, 0x02,  0x54, 0x1c, 0x01, 0x01,  0xd5, 0x18, 0x81, 0x03, // 'k'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x1c, 0x00, 0x03,  0xd5, 0x18, 0x00, 0x00, // 'l'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x14, 0x98, 0x02,
     0x55, 0x11, 0x80, 0x03,  0xd5, 0x18, 0x01, 0x02,                          // 'm'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x18, 0x00, 0x02,  0x55, 0x25, 0x74, 0x03,
     0xd5, 0x18, 0x00, 0x02,                                                   // 'n'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x1c, 0x00, 0x03,
     0x55, 0x18, 0x01, 0x02,  0xd5, 0x1c, 0x00, 0x01,                          // 'o'

     0x54, 0x18, 0x00, 0x02,  0x55, 0x18, 0x01, 0x00,  0x55, 0x1c, 0x00, 0x01,
     0x55, 0x0c, 0x02, 0x02,  0xd5, 0x1c, 0x00, 0x03,                          // 'p'
  
     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x1c, 0x00, 0x03,
     0x55, 0x18, 0x01, 0x02,  0x55, 0x1c, 0x00, 0x01,  0x54, 0x04, 0x01, 0x02,
     0xd5, 0x0b, 0x81, 0x03,                                                   // 'q'

     0x54, 0x18, 0x00, 0x02,  0x55, 0x18, 0x01, 0x00,  0x55, 0x1c, 0x00, 0x01,
     0x55, 0x0c, 0x02, 0x02,  0x55, 0x1c, 0x00, 0x03,  0x54, 0x0c, 0x00, 0x01,
     0xd5, 0x14, 0x69, 0x01,                                                   // 'r'

     0x54, 0x18, 0x00, 0x02,  0x55, 0x1c, 0x00, 0x01,  0x55, 0x0c, 0x01, 0x00,
     0x55, 0x1c, 0x01, 0x03,  0x55, 0x0c, 0x00, 0x00,  0xd5, 0x1c, 0x01, 0x01, // 's'

     0x54, 0x1c, 0xaa, 0x01,  0x55, 0x18, 0x00, 0x00,  0x54, 0x0e, 0xff, 0x00,
     0xd5, 0x1c, 0x02, 0x03,                                                   // 't'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x18, 0x00, 0x02,  0x55, 0x1c, 0x01, 0x03,
     0xd5, 0x18, 0x01, 0x00,                                                   // 'u' 

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x1d, 0x60, 0x02,  0xd5, 0x1b, 0xb6, 0x03, // 'v'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x18, 0x00, 0x02,  0x55, 0x11, 0x81, 0x03,
     0x55, 0x14, 0x97, 0x02,  0xd5, 0x18, 0x01, 0x00,                          // 'w'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x25, 0x8d, 0x02,  0x54, 0x1c, 0x00, 0x01,
     0xd5, 0x25, 0x75, 0x03,                                                   // 'x'

     0x54, 0x1c, 0x00, 0x01,  0x55, 0x0c, 0x00, 0x02,  0x55, 0x1c, 0x01, 0x03,
     0x55, 0x0c, 0x01, 0x00,  0x54, 0x12, 0x75, 0x01,  0xd5, 0x0c, 0xfb, 0x01, // 'y'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x1c, 0x00, 0x03,  0x55, 0x25, 0x8d, 0x00,
     0xd5, 0x1c, 0x01, 0x03,                                                   // 'z'

};


const uint8_t font_data_numeric[] = {

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x1c, 0x00, 0x03,
     0x55, 0x18, 0x01, 0x02,  0xd5, 0x1c, 0x00, 0x01,                          // '0'

     0x54, 0x1c, 0xaa, 0x01,  0xd5, 0x18, 0x00, 0x00,                          // '1'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x1c, 0x00, 0x03,  0x55, 0x0c, 0xff, 0x03,
     0x55, 0x1c, 0x00, 0x01,  0x55, 0x0c, 0x00, 0x00,  0xd5, 0x1c, 0x00, 0x03, // '2'

     0x54, 0x18, 0x00, 0x02,  0x55, 0x1c, 0x00, 0x01,  0x55, 0x18, 0x01, 0x00,
     0x55, 0x1c, 0x01, 0x03,  0x54, 0x0c, 0x02, 0x02,  0xd5, 0x1c, 0x01, 0x01, // '3'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x54, 0x0c, 0x02, 0x02,
     0x55, 0x1c, 0x00, 0x03,  0xd5, 0x0c, 0x01, 0x00,                          // '4'

     0x54, 0x18, 0x00, 0x02,  0x55, 0x1c, 0x00, 0x01,  0x55, 0x0c, 0x01, 0x00,
     0x55, 0x1c, 0x01, 0x03,  0x55, 0x0c, 0x00, 0x00,  0xd5, 0x1c, 0x01, 0x01, // '5' 

     0x54, 0x0c, 0x00, 0x02,  0x55, 0x1c, 0x00, 0x01,  0x55, 0x0c, 0x00, 0x02, 
     0x55, 0x1c, 0x01, 0x03,  0xd5, 0x18, 0x01, 0x00,                          // '6'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0xd5, 0x1c, 0x00, 0x03, // '7'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x1c, 0x00, 0x03, 
     0x55, 0x18, 0x01, 0x02,  0x55, 0x1c, 0x00, 0x01,  0x54, 0x0c, 0x01, 0x00, 
     0xd5, 0x1c, 0x00, 0x03,                                                   // '8'

     0x54, 0x25, 0x73, 0x01,  0x55, 0x18, 0x00, 0x00,  0x55, 0x1c, 0x00, 0x03,
     0x55, 0x0c, 0x02, 0x02,  0xd5, 0x1c, 0x00, 0x01,                          // '9'
};



static uint16_t font_addr_alpha = 0;
static uint16_t font_addr_numeric = 0;
static uint16_t font_addr_string = 0;

uint16_t installFonts( uint16_t addr ) {
     font_addr_alpha = addr;
     memcpy( (uint8_t*)addr, font_data_alpha, sizeof(font_data_alpha) ); 
     addr += sizeof(font_data_alpha);

     font_addr_numeric = addr;
     memcpy( (uint8_t*)addr, font_data_numeric, sizeof(font_data_numeric) );
     addr += sizeof(font_data_numeric);

     font_addr_string = addr;

     return addr;
}

uint16_t fontAddress( char c ) {

   const uint16_t font_alpha[] = {
      0x0000,0x0018,0x0034,0x0044,0x005c,0x0074,0x0088,0x00a0,0x00b8,0x00d0,
      0x00e0,0x00f8,0x0104,0x0118,0x0128,0x013c,0x0150,0x016c,0x0188,0x01a0,
      0x01b0,0x01c0,0x01cc,0x01e0,0x01f0,0x0208,0x0208+(4*sizeof(vector_t))};

   const uint16_t font_numeric[] = {
      0x0000,0x0014,0x001C,0x0034,0x004C,0x0060,0x0078,0x008C,0x0098,0x00B4,0x00B4+(5*sizeof(vector_t))};

   if ( c>='0' && c<='9' ) return font_addr_numeric + font_numeric[ c-'0' ];

   if ( c>='a' && c<='z' ) return font_addr_alpha + font_alpha[ c-'a' ];

   return 0;
}

static inline uint16_t fontSize( char c ) {
   return fontAddress( c + 1 ) - fontAddress( c );
}

// SEGA_ANGLE(90)
static uint8_t offset_x( char ch ) {
     switch ( ch ) {
          case 'a': return 0x04;
          case 'c': return 0x08;
          case 'd': return 0x0c;
          case 'f': return 0x24;
          case 'g': return 0x04;
          case 'k': return 0x18;
          case 'o': return 0x04;
          case 'q': return 0x0c;
          case 'r': return 0x06;
          case 's': return 0x04;
          case 'u': return 0x24;
          case 'y': return 0x18;
          case '0': return 0x04;
          case '1': return 0x08;
          case '3': return 0x08;
          case '5': return 0x08;
          case '9': return 0x08;
     }
     return 0x21;
}

// SEGA_ANGLE(0)
static uint8_t offset_y( char ch ) {
     switch ( ch ) {
          case 'a': return 0x0c;
          case 'b': return 0x0c;
          case 'e': return 0x0c;
          case 'd': return 0x18;
          case 'f': return 0x0c;
          case 'j': return 0x10;
          case 'k': return 0x08;
          case 'm': return 0x18;
          case 'n': return 0x18;
          case 'o': return 0x18;
          case 'p': return 0x0c;
          case 'q': return 0x14;
          case 'r': return 0x18;
          case 'y': return 0x18;
          case '0': return 0x18;
          case '3': return 0x0c;
          case '8': return 0x0c;
          case '9': return 0x0c;

     }
     return 0x00;
}


void drawString( uint8_t *sym, uint16_t x, uint16_t y, uint8_t scale, uint8_t color, const char *str, uint8_t len ) {

   uint8_t *vec = (uint8_t*)font_addr_string;
   uint16_t v_sz = 0;

  for (uint8_t j=0; j<len; j++) {
      if ( (uint16_t)&vec[v_sz] + len + (sizeof(vector_t)*2) >= VECTOR_RAM_END ) kill( 1 );

      char ch = str[ j ];

      uint16_t sz = fontSize( ch );
      uint8_t *in = (uint8_t*)fontAddress( ch );
      if ( in ) {
           memcpy( &vec[v_sz], in, sz );
           v_sz += sz;
           vec[v_sz - 4] &= ~ SEGA_LAST;
      }

     uint8_t oy = offset_y( ch );
     if ( oy ) {
          vec[v_sz++] = 0x00;
          vec[v_sz++] = oy;
          vec[v_sz++] = LSB(SEGA_ANGLE(0));
          vec[v_sz++] = MSB(SEGA_ANGLE(0));
     }

     uint8_t ox = offset_x( ch );
     if ( ox ) {
          vec[v_sz++] = 0x00;
          vec[v_sz++] = ox;
          vec[v_sz++] = LSB(SEGA_ANGLE(90));
          vec[v_sz++] = MSB(SEGA_ANGLE(90));
     }
   }

   if ( (uint16_t)&vec[v_sz-sizeof(vector_t)] < VECTOR_RAM + SYMBOLS_SZ ) kill( 2 );

   vec[v_sz - sizeof(vector_t)] |= SEGA_LAST;

   colorize( vec, v_sz, color );

   sym[ SFIELD_VISIBLE(0) ] = SEGA_VISIBLE;
   sym[ SFIELD_X_L(0) ] = LSB(x);
   sym[ SFIELD_X_H(0) ] = MSB(x);
   sym[ SFIELD_Y_L(0) ] = LSB(y);
   sym[ SFIELD_Y_H(0) ] = MSB(y);
   sym[ SFIELD_ADDR_L(0) ] = LSB( vec );
   sym[ SFIELD_ADDR_H(0) ] = MSB( vec );
   // sym[ SFIELD_ANGLE_L(0) = LSB( angle );
   // sym[ SFIELD_ANGLE_H(0) = MSB( angle );
   sym[ SFIELD_SCALE(0) ] = scale;
}


void colorize( uint8_t *vec, uint16_t len, uint8_t color ) {
   for (uint16_t i=0; i<len; i+=sizeof(vector_t)) {
      if ( (uint16_t)&vec[i] < VECTOR_RAM + SYMBOLS_SZ  ) kill(3);
      if ( (uint16_t)&vec[i] + len >= VECTOR_RAM_END ) kill(4);
      vec[i] &= ~0x7E;
      vec[i] |= (color & 0x7E);
   }
}


