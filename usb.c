#include "sega.h"

const uint8_t usbrom_bin[] = {
  0xe5, 0x04, 0x0e, 0x15, 0x00, 0x00, 0x93, 0x35, 0x00, 0x00, 0x93, 0x02,
  0x05, 0x61, 0x27, 0x3a, 0x15, 0x35, 0x65, 0x55, 0x75, 0xe5, 0x23, 0x10,
  0xd7, 0xa5, 0xb5, 0x23, 0x7f, 0x39, 0xb8, 0x00, 0xba, 0x04, 0xfa, 0x07,
  0x3a, 0x27, 0x90, 0xe8, 0x26, 0xea, 0x22, 0x23, 0x03, 0x3a, 0x23, 0x01,
  0xb9, 0x03, 0xbc, 0x40, 0x91, 0x19, 0x19, 0x19, 0x19, 0xec, 0x34, 0x27,
  0x3a, 0xb8, 0x03, 0xb9, 0x03, 0x23, 0x36, 0x90, 0x23, 0x76, 0x90, 0x23,
  0x92, 0x90, 0xf8, 0x03, 0x08, 0xa8, 0xe9, 0x41, 0x23, 0x83, 0x3a, 0x23,
  0x43, 0x3a, 0x56, 0x5c, 0x14, 0x7d, 0x04, 0x56, 0x23, 0xc3, 0x3a, 0x23,
  0x43, 0x3a, 0xb9, 0x02, 0x09, 0x53, 0x7f, 0xc6, 0x6b, 0x14, 0x83, 0x81,
  0xc6, 0x56, 0xa9, 0xb8, 0x16, 0x81, 0xa0, 0x19, 0x18, 0x81, 0xa0, 0x19,
  0x23, 0x40, 0x3a, 0x27, 0x93, 0x09, 0x53, 0x7f, 0x96, 0x83, 0x83, 0xaa,
  0x09, 0x53, 0x7f, 0xab, 0xda, 0xc6, 0x8e, 0xfb, 0x04, 0x83, 0x23, 0x03,
  0x3a, 0x23, 0x43, 0x3a, 0xfa, 0x6a, 0xab, 0x1b, 0x54, 0x00, 0xf2, 0xcd,
  0xac, 0xfa, 0x53, 0x7e, 0xc6, 0xcc, 0xe7, 0x03, 0x03, 0xa8, 0x80, 0x07,
  0x96, 0xc8, 0x90, 0xf9, 0xaa, 0xc8, 0xb9, 0x02, 0x81, 0x90, 0xf8, 0x07,
  0x07, 0x91, 0x80, 0x03, 0x03, 0xa9, 0xc8, 0xf8, 0x07, 0x91, 0xfa, 0xa9,
  0xfc, 0x90, 0xfb, 0x54, 0x00, 0xc8, 0x90, 0x83, 0xc8, 0xc8, 0x04, 0xc0,
  0xfc, 0x14, 0xcf, 0xb8, 0x0b, 0x53, 0x7f, 0xa0, 0xfb, 0x54, 0x00, 0xc8,
  0xa0, 0x23, 0x40, 0x3a, 0x27, 0x93, 0xf8, 0xd5, 0xa8, 0x14, 0xf6, 0x23,
  0x40, 0x3a, 0x93, 0xd5, 0xc7, 0x07, 0x53, 0x07, 0xe7, 0x03, 0x08, 0xa8,
  0x14, 0xf6, 0x23, 0x40, 0x3a, 0x93, 0x23, 0x43, 0x3a, 0xf0, 0xc9, 0xc9,
  0x91, 0x19, 0x18, 0xf0, 0x53, 0x0f, 0x91, 0x19, 0x83, 0x23, 0x10, 0xd7,
  0x23, 0x43, 0x3a, 0x04, 0x64, 0x23, 0x10, 0xd7, 0x23, 0x43, 0x3a, 0x19,
  0x81, 0xa8, 0x18, 0x18, 0xc9, 0x81, 0x90, 0x03, 0x03, 0xa8, 0x19, 0x81,
  0x90, 0x23, 0x01, 0x91, 0xc9, 0x04, 0x64, 0x23, 0x43, 0x3a, 0x93, 0xd5,
  0xc7, 0x07, 0x53, 0x07, 0xe7, 0x03, 0x08, 0xa8, 0x14, 0xf6, 0x23, 0x10,
  0xd7, 0x04, 0x64, 0xd5, 0x42, 0x6f, 0xaa, 0xa8, 0x6a, 0xaa, 0x6a, 0xaa,
  0x6a, 0x6a, 0x68, 0x17, 0xaf, 0xc5, 0xaa, 0xfb, 0xc6, 0x56, 0x37, 0x17,
  0xa8, 0xfa, 0xaa, 0x68, 0xf6, 0x52, 0x93, 0x41, 0x0d, 0x09, 0x53, 0xb8,
  0x1f, 0xba, 0x00, 0xf4, 0x99, 0x34, 0xfc, 0xb8, 0x20, 0xbd, 0x04, 0xbe,
  0x01, 0x76, 0x79, 0xb8, 0x23, 0xba, 0x02, 0xf4, 0x99, 0x34, 0xfc, 0xb8,
  0x24, 0xbd, 0x03, 0xbe, 0x3a, 0x27, 0xab, 0xac, 0xaf, 0xb9, 0x1c, 0xf4,
  0xac, 0xe6, 0x8a, 0x1b, 0xc6, 0x8a, 0xfd, 0x91, 0xf4, 0x00, 0xb9, 0x1d,
  0xf4, 0xac, 0xe6, 0x97, 0x1c, 0xc6, 0x97, 0xfd, 0x91, 0xf4, 0x0c, 0xb9,
  0x1e, 0xf4, 0xac, 0xe6, 0xa4, 0x1f, 0xc6, 0xa4, 0xfd, 0x91, 0xf4, 0x18,
  0xf4, 0x25, 0xf6, 0xc3, 0xb6, 0xc1, 0xfe, 0xb4, 0x12, 0xae, 0xb9, 0x14,
  0xfb, 0xc6, 0xb5, 0xfe, 0x91, 0x19, 0xfc, 0xc6, 0xbb, 0xfe, 0x91, 0x19,
  0xff, 0xc6, 0xc1, 0xfe, 0x91, 0x24, 0xf4, 0xb9, 0x1c, 0xb8, 0x14, 0xfb,
  0xc6, 0xcd, 0x27, 0x91, 0x90, 0x18, 0x19, 0xfc, 0xc6, 0xd5, 0x27, 0x91,
  0x90, 0x18, 0x19, 0xff, 0xc6, 0xdd, 0x27, 0x91, 0x90, 0x24, 0xf8, 0x43,
  0x4f, 0x44, 0x45, 0x3a, 0x0d, 0x0d, 0x3b, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a,
  0x2a, 0x2a, 0x2a, 0x2a, 0x04, 0xde, 0x04, 0x00, 0x24, 0x05, 0x24, 0x2b,
  0x24, 0x0d, 0x24, 0x27, 0x04, 0xe7, 0x4e, 0x54, 0xa3, 0x83, 0x81, 0xfa,
  0x81, 0xfa, 0x81, 0xfa, 0x0b, 0x00, 0x0b, 0x14, 0x0c, 0x19, 0x0c, 0x00,
  0x06, 0x12, 0x81, 0xfa, 0x08, 0x00, 0x81, 0xfa, 0x09, 0x00, 0x09, 0x34,
  0x09, 0x3d, 0x81, 0xfa, 0x02, 0x6c, 0x02, 0x60, 0x02, 0xa9, 0x81, 0xfa,
  0x01, 0x5b, 0x81, 0xfa, 0x0a, 0x10, 0x81, 0xfa, 0x0d, 0x70, 0x0d, 0x76,
  0x0a, 0x08, 0x81, 0xfa, 0x0d, 0x00, 0x81, 0xfa, 0x01, 0x6b, 0x81, 0xfa,
  0x0e, 0x4a, 0x8e, 0x08, 0x0a, 0x00, 0x81, 0xfa, 0x02, 0x64, 0x02, 0x68,
  0x09, 0x86, 0x09, 0x8c, 0x09, 0x92, 0x08, 0xa1, 0x09, 0x00, 0x09, 0x02,
  0x0e, 0x14, 0x0e, 0x1a, 0x0e, 0x63, 0x8d, 0x64, 0xba, 0x46, 0x76, 0x6e,
  0xba, 0x3e, 0x76, 0x6e, 0xba, 0x42, 0x76, 0x6e, 0xba, 0x3a, 0xb9, 0x19,
  0x23, 0x06, 0x91, 0xb8, 0x27, 0xf4, 0x99, 0xf4, 0x99, 0x34, 0xfc, 0xb8,
  0x28, 0xf4, 0x5d, 0xf6, 0xa0, 0xb6, 0x8b, 0xfe, 0xf2, 0xa0, 0xb4, 0x12,
  0xb9, 0x0c, 0x91, 0xb8, 0x2c, 0xf4, 0x5d, 0xb6, 0x9e, 0xb8, 0x08, 0xfe,
  0x6e, 0xae, 0x17, 0xb4, 0x10, 0x90, 0xfe, 0xb4, 0x10, 0x90, 0x24, 0xf4,
  0x27, 0xb9, 0x19, 0x91, 0xb9, 0x0c, 0x91, 0x24, 0xf8, 0xb9, 0x1d, 0x23,
  0x0a, 0x91, 0xb8, 0x20, 0xb0, 0xff, 0x18, 0xb0, 0xff, 0xb8, 0x2f, 0xba,
  0x4a, 0xf4, 0x99, 0xf4, 0x99, 0x34, 0xfc, 0xb8, 0x30, 0xf4, 0x25, 0xf6,
  0xee, 0xb8, 0x20, 0xb6, 0xd3, 0xfe, 0xb4, 0x12, 0xb9, 0x15, 0x91, 0xf0,
  0x03, 0xfa, 0xa0, 0xf0, 0x18, 0x60, 0xa0, 0xe6, 0xec, 0xb8, 0x34, 0xf4,
  0x25, 0xb6, 0xec, 0xb8, 0x11, 0xfe, 0x6e, 0xae, 0x17, 0xb4, 0x10, 0x90,
  0xfe, 0xb4, 0x10, 0x90, 0x24, 0xf4, 0x27, 0xb9, 0x15, 0x91, 0xb9, 0x1d,
  0x91, 0x24, 0xf8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0x8f, 0x80,
  0x00, 0x01, 0xa0, 0x00, 0x0f, 0x12, 0xff, 0x00, 0x00, 0x0b, 0x01, 0x01,
  0x03, 0x0a, 0xff, 0x08, 0x1e, 0xff, 0x00, 0x00, 0x00, 0x02, 0x0a, 0x01,
  0x01, 0x0a, 0x00, 0x02, 0x0a, 0xff, 0x01, 0x64, 0x00, 0x0d, 0x08, 0xff,
  0x00, 0x00, 0x1b, 0x01, 0xfd, 0x01, 0x01, 0x51, 0x00, 0x26, 0x00, 0x0c,
  0x02, 0x01, 0x09, 0x0f, 0xff, 0x00, 0x00, 0x00, 0x01, 0x78, 0x00, 0x0b,
  0x05, 0xff, 0x01, 0x39, 0x00, 0x0c, 0x02, 0x01, 0x01, 0x98, 0x00, 0x07,
  0x0a, 0xff, 0x00, 0x00, 0x01, 0xe8, 0x7f, 0x01, 0x50, 0x00, 0x3c, 0x03,
  0x01, 0xff, 0xff, 0x00, 0x01, 0x70, 0x00, 0x0b, 0x0a, 0xff, 0x02, 0x64,
  0xff, 0x00, 0x55, 0x00, 0x01, 0x14, 0x00, 0x04, 0x03, 0xff, 0x04, 0x06,
  0x01, 0x0f, 0x1e, 0xff, 0x00, 0x00, 0x01, 0x06, 0x38, 0x00, 0x86, 0x00,
  0x01, 0x64, 0x00, 0x0f, 0x3c, 0xff, 0x00, 0x00, 0x05, 0x05, 0x01, 0x08,
  0x1e, 0xff, 0xff, 0xff, 0x00, 0x08, 0x04, 0xff, 0x01, 0x01, 0x08, 0x00,
  0x89, 0x00, 0x09, 0x02, 0x01, 0x09, 0x02, 0xff, 0x00, 0x92, 0x00, 0x08,
  0x2f, 0x01, 0x00, 0xb4, 0x00, 0x2f, 0x08, 0x01, 0x00, 0xb4, 0x00, 0xdc,
  0x02, 0x01, 0x00, 0x00, 0xff, 0x02, 0xff, 0x00, 0x00, 0x2d, 0x08, 0xff,
  0xff, 0xff, 0x00, 0x08, 0x2d, 0xff, 0x00, 0xb4, 0x00, 0x0f, 0x0f, 0xff,
  0x00, 0x00, 0x06, 0x15, 0x01, 0x01, 0xa3, 0x05, 0x01, 0x64, 0xfe, 0x01,
  0xc8, 0xff, 0x00, 0x00, 0x02, 0x91, 0x00, 0x01, 0x01, 0x38, 0x21, 0x03,
  0xff, 0x30, 0x01, 0x01, 0x49, 0x02, 0xff, 0x00, 0xf1, 0x00, 0x0d, 0x0a,
  0x01, 0x01, 0x6a, 0xfd, 0x04, 0x51, 0xff, 0x00, 0xf1, 0x00, 0x04, 0x21,
  0x01, 0xff, 0xff, 0x00, 0x48, 0x04, 0xff, 0x01, 0x01, 0x48, 0x00, 0xf1,
  0xc8, 0x8c, 0xc8, 0x8c, 0xff, 0x0f, 0x07, 0x00, 0x00, 0x0d, 0x01, 0x01,
  0x03, 0x01, 0xff, 0x01, 0x78, 0x00, 0x0a, 0x05, 0xff, 0x00, 0x00, 0x24,
  0x05, 0x01, 0xff, 0xff, 0x00, 0x0b, 0x32, 0xff, 0x00, 0x00, 0x14, 0x03,
  0x01, 0x01, 0x01, 0xec, 0x00, 0x1e, 0x00, 0x0a, 0x01, 0x01, 0x0a, 0x65,
  0xff, 0x00, 0x00, 0x32, 0x02, 0x01, 0x32, 0x02, 0xff, 0x01, 0x01, 0x32,
  0x00, 0x32, 0x03, 0x00, 0x11, 0x30, 0x17, 0x09, 0x1c, 0x3c, 0x17, 0x0b,
  0x1c, 0x52, 0x25, 0x00, 0x2d, 0x34, 0x13, 0x0d, 0x24, 0x77, 0xa3, 0x83,
  0x2d, 0x00, 0x36, 0x0b, 0x4a, 0x81, 0x56, 0x0d, 0x00, 0x0a, 0x02, 0x01,
  0x02, 0x96, 0x00, 0x05, 0x02, 0xff, 0x07, 0x02, 0x01, 0x05, 0xa6, 0x00,
  0x0d, 0x05, 0xff, 0x00, 0x00, 0x14, 0x01, 0x06, 0x02, 0x96, 0x00, 0x32,
  0x01, 0xfc, 0x07, 0x64, 0x00, 0x32, 0x01, 0x04, 0xff, 0xff, 0x00, 0x57,
  0x00, 0x6b, 0x50, 0x00, 0x02, 0xc8, 0x00, 0x0a, 0x1e, 0xff, 0x00, 0x00,
  0x02, 0xc8, 0x00, 0x0a, 0x0a, 0xff, 0x00, 0x00, 0x03, 0xe1, 0x00, 0x0a,
  0x2d, 0xff, 0x00, 0x00, 0x82, 0x0a, 0x8a, 0x0a, 0x92, 0x0a, 0x62, 0x0f,
  0x70, 0x01, 0x76, 0x0f, 0x7e, 0x37, 0x6b, 0x0f, 0x87, 0x3f, 0x90, 0x00,
  0x99, 0x00, 0x9f, 0x02, 0xa5, 0x1e, 0xb5, 0x00, 0xaf, 0x02, 0xaa, 0x1e,
  0xc0, 0x01, 0xce, 0x16, 0xe0, 0x01, 0xf2, 0x50, 0xec, 0x01, 0xef, 0x12,
  0x00, 0x0a, 0x01, 0x01, 0x0f, 0x0a, 0xff, 0x00, 0x00, 0x02, 0x01, 0x0b,
  0x02, 0x01, 0xf6, 0x00, 0xd1, 0x00, 0x01, 0x02, 0x01, 0x02, 0x01, 0x02,
  0x01, 0x02, 0x01, 0x02, 0x02, 0xff, 0x04, 0x01, 0xff, 0x00, 0xda, 0x00,
  0x0c, 0x01, 0x01, 0x01, 0x02, 0xf4, 0x00, 0xec, 0xc7, 0x05, 0xcf, 0x14,
  0xc7, 0x00, 0xcf, 0x10, 0xc8, 0x8c, 0xc8, 0x8c, 0x00, 0x07, 0x0b, 0x10,
  0x16, 0x1d, 0x26, 0x30, 0x3b, 0x48, 0x58, 0x6b, 0x81, 0xa0, 0xc5, 0xff,
  0x03, 0x10, 0xa3, 0x83, 0xfd, 0x18, 0xee, 0xe3, 0xe1, 0x7b, 0xd4, 0xd4,
  0xc8, 0xe3, 0xbd, 0x9b, 0xb2, 0xf7, 0xa8, 0xeb, 0x9f, 0x70, 0x96, 0x7d,
  0x8e, 0x0c, 0x86, 0x13, 0x7e, 0x8c, 0x77, 0x72, 0x70, 0xbe, 0x6a, 0x6a,
  0x64, 0x71, 0x5e, 0xce, 0x59, 0x7b, 0x54, 0x76, 0x4f, 0xb9, 0x4b, 0x3f,
  0x47, 0x06, 0x43, 0x09, 0x3f, 0x46, 0x3b, 0xb9, 0x38, 0x5f, 0x35, 0x35,
  0x32, 0x38, 0x2f, 0x67, 0x2c, 0xbe, 0x2a, 0x3b, 0x27, 0xdc, 0x25, 0x9f,
  0x23, 0x83, 0x21, 0x85, 0x1f, 0xa3, 0x1d, 0xdd, 0x1c, 0x2f, 0x1a, 0x9b,
  0x19, 0x1c, 0x17, 0xb3, 0x16, 0x5f, 0x15, 0x1d, 0x13, 0xee, 0x12, 0xd0,
  0x11, 0xc1, 0x10, 0xc2, 0x0f, 0xd2, 0x0e, 0xee, 0x0e, 0x18, 0x0d, 0x4d,
  0x0c, 0x8e, 0x0b, 0xda, 0x0b, 0x2f, 0x0a, 0x8f, 0x09, 0xf7, 0x09, 0x68,
  0x08, 0xe1, 0x08, 0x61, 0x07, 0xe9, 0x07, 0x77, 0x07, 0x0c, 0x06, 0xa7,
  0x06, 0x47, 0x05, 0xed, 0x05, 0x98, 0x05, 0x47, 0x04, 0xfc, 0x04, 0xb4,
  0x04, 0x70, 0x04, 0x31, 0x03, 0xf4, 0x03, 0xbc, 0x03, 0x86, 0x03, 0x53,
  0x03, 0x24, 0x02, 0xf6, 0x02, 0xcc, 0x02, 0xa4, 0x02, 0x7e, 0x02, 0x5a,
  0x02, 0x38, 0x02, 0x18, 0x01, 0xfa, 0x01, 0xde, 0x01, 0xc3, 0x01, 0xaa,
  0x01, 0x92, 0x01, 0x7b, 0x01, 0x66, 0x01, 0x52, 0x01, 0x3f, 0x01, 0x2d,
  0x01, 0x1c, 0x01, 0x0c, 0x00, 0xfd, 0x00, 0xef, 0x00, 0xe1, 0x00, 0xd5,
  0x00, 0xc9, 0x00, 0xbe, 0x00, 0xb3, 0x00, 0xa9, 0x00, 0x9f, 0x00, 0x96,
  0x00, 0x8e, 0x00, 0x86, 0x00, 0x7f, 0x00, 0x77, 0x00, 0x71, 0x00, 0x6a,
  0x00, 0x64, 0x00, 0x5f, 0x00, 0x59, 0x00, 0x54, 0x00, 0x50, 0x00, 0x4b,
  0x03, 0x43, 0x01, 0x00, 0x03, 0x3d, 0x01, 0x00, 0x80, 0x01, 0x77, 0x01,
  0x00, 0x01, 0x73, 0x01, 0x00, 0x89, 0xb8, 0x3d, 0xba, 0x50, 0xf4, 0x99,
  0xb8, 0x37, 0x23, 0x08, 0x90, 0x27, 0x18, 0x90, 0xb8, 0x39, 0x27, 0x90,
  0x18, 0x23, 0xff, 0x90, 0x18, 0x27, 0x90, 0x18, 0x23, 0x08, 0x90, 0x34,
  0xfc, 0xb8, 0x3e, 0xf4, 0x25, 0xf6, 0xeb, 0xb8, 0x37, 0x80, 0x07, 0x90,
  0x96, 0x47, 0x23, 0x08, 0x90, 0x18, 0x80, 0x07, 0x90, 0xaf, 0xa7, 0xb8,
  0x39, 0xba, 0x08, 0xb9, 0x19, 0xd4, 0x7c, 0xb8, 0x3b, 0xba, 0x09, 0xb9,
  0x1a, 0xd4, 0x7c, 0xbd, 0x04, 0xb9, 0x1b, 0xf4, 0xac, 0xe6, 0x7a, 0xc6,
  0x6d, 0xfd, 0x91, 0xb8, 0x0a, 0x23, 0x01, 0x90, 0xb8, 0x40, 0x80, 0x76,
  0x70, 0xb6, 0x7a, 0xfe, 0x03, 0xfc, 0xf6, 0x75, 0x27, 0xb4, 0x12, 0xb8,
  0x0e, 0x90, 0x24, 0xf4, 0xbb, 0x00, 0xe6, 0x81, 0x1b, 0xbd, 0x04, 0xf4,
  0xac, 0xf6, 0x8b, 0xbd, 0x00, 0x76, 0x97, 0x97, 0xc6, 0x97, 0xfd, 0x91,
  0xa7, 0xb9, 0x38, 0x81, 0xaf, 0x76, 0x9b, 0xfb, 0xc6, 0x9b, 0xa7, 0xfa,
  0xa9, 0x80, 0x96, 0xbe, 0x18, 0x80, 0x17, 0xaa, 0xa3, 0xf2, 0xba, 0xc8,
  0x90, 0x18, 0x1a, 0xfa, 0x90, 0xc8, 0xf8, 0xac, 0xb8, 0x38, 0x80, 0xaf,
  0xfc, 0xa8, 0x97, 0xa7, 0x76, 0x9d, 0x53, 0x7f, 0x76, 0xa3, 0x07, 0x90,
  0xe6, 0xdc, 0xfd, 0xc6, 0xd6, 0x18, 0x80, 0x18, 0xa3, 0xc6, 0xe1, 0x6f,
  0xe7, 0xab, 0x17, 0xb4, 0x10, 0x91, 0xfb, 0xb4, 0x10, 0x91, 0xb8, 0x40,
  0x80, 0xae, 0x76, 0xde, 0xb6, 0xea, 0xfe, 0xb4, 0x12, 0x19, 0x19, 0x19,
  0x19, 0x2d, 0xc6, 0xea, 0x2d, 0x91, 0x93, 0xbb, 0x03, 0xbd, 0x04, 0xb9,
  0x19, 0xb8, 0x0c, 0xf4, 0xac, 0xe6, 0xfa, 0x27, 0x90, 0x91, 0x18, 0x19,
  0xeb, 0xf3, 0x24, 0xf8, 0xb9, 0x10, 0x23, 0xcd, 0x91, 0x23, 0x37, 0x91,
  0xb9, 0x14, 0x76, 0x1e, 0xb9, 0x11, 0x23, 0x06, 0x91, 0x23, 0x47, 0x91,
  0xb9, 0x15, 0x76, 0x1e, 0xb9, 0x12, 0xfe, 0x91, 0xb9, 0x16, 0x18, 0x18,
  0x80, 0xc8, 0xc8, 0x91, 0x83, 0x85, 0x95, 0x80, 0x07, 0x90, 0x96, 0x5b,
  0x95, 0x18, 0x80, 0xa9, 0x17, 0xe3, 0xae, 0x18, 0x80, 0x6e, 0x90, 0xae,
  0xc8, 0xc8, 0xc8, 0x80, 0x07, 0x90, 0x18, 0x96, 0x58, 0x19, 0x19, 0xf9,
  0xe3, 0x96, 0x50, 0xf9, 0x17, 0xe3, 0xa9, 0x96, 0x44, 0x97, 0xa7, 0x83,
  0x19, 0xc8, 0x90, 0x18, 0x18, 0xf9, 0x90, 0xc8, 0xf9, 0xe3, 0x90, 0x97,
  0x83, 0x85, 0x95, 0x80, 0x07, 0x90, 0x96, 0x97, 0x95, 0x18, 0x80, 0xa9,
  0x17, 0x94, 0x4e, 0xae, 0x18, 0x80, 0x6e, 0x90, 0xae, 0xc8, 0xc8, 0xc8,
  0x80, 0x07, 0x90, 0x18, 0x96, 0x93, 0x19, 0x19, 0xf9, 0x94, 0x4e, 0x96,
  0x8b, 0xf9, 0x17, 0x94, 0x4e, 0xa9, 0x96, 0x7d, 0x97, 0xa7, 0x83, 0x19,
  0xc8, 0x90, 0x18, 0x18, 0xf9, 0x90, 0xc8, 0xf9, 0x94, 0x4e, 0x90, 0x97,
  0x83, 0x23, 0x01, 0x90, 0x18, 0x90, 0x18, 0xfa, 0x1a, 0x94, 0x4e, 0x90,
  0x18, 0xfa, 0x1a, 0x94, 0x4e, 0x90, 0x18, 0x83, 0x81, 0xc6, 0xb3, 0x37,
  0x17, 0x6d, 0x83, 0x97, 0xa7, 0x17, 0x83, 0xa3, 0x83, 0x96, 0x2f, 0x67,
  0x2f, 0xc9, 0x17, 0xb3, 0x17, 0xda, 0x0b, 0xe0, 0x0b, 0x06, 0x47, 0xb0,
  0x46, 0x94, 0x23, 0x83, 0x23, 0xc1, 0x11, 0xcb, 0x11, 0x83, 0x23, 0xa2,
  0x23, 0xc1, 0x11, 0xdb, 0x11, 0xe1, 0x08, 0xe6, 0x08, 0x23, 0x01, 0x91,
  0x19, 0x91, 0x19, 0xfa, 0x1a, 0x94, 0x4e, 0x91, 0x19, 0x80, 0x96, 0xf0,
  0xfa, 0x94, 0x4e, 0x91, 0x1a, 0x19, 0x83, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xb8, 0x41, 0xba, 0x52,
  0xf4, 0x99, 0xf4, 0x99, 0xf4, 0x99, 0x23, 0x01, 0xb8, 0x07, 0x90, 0x34,
  0xfc, 0xb9, 0x18, 0xbd, 0x06, 0xf4, 0xac, 0xf6, 0x1d, 0xbd, 0x00, 0x76,
  0x28, 0xc6, 0x28, 0xfd, 0x91, 0xbd, 0xff, 0xb8, 0x02, 0x23, 0x31, 0x90,
  0xb8, 0x42, 0xf4, 0x25, 0xf6, 0x91, 0xfd, 0xf2, 0x87, 0xc6, 0x74, 0xb6,
  0x3d, 0xfe, 0xb4, 0x12, 0xb9, 0x04, 0x91, 0x19, 0x91, 0xb8, 0x46, 0xf4,
  0x25, 0xba, 0x03, 0x42, 0x53, 0x1f, 0x32, 0x4f, 0x03, 0x24, 0xe6, 0x55,
  0x1a, 0x76, 0x55, 0x37, 0x03, 0x25, 0xf6, 0x55, 0xca, 0xab, 0xb9, 0x48,
  0x81, 0xf2, 0x61, 0x6b, 0xe6, 0x65, 0x1a, 0x76, 0x65, 0x6b, 0xf6, 0x65,
  0xca, 0xab, 0xb8, 0x00, 0x90, 0xfa, 0x90, 0x18, 0xfb, 0x03, 0x6e, 0x90,
  0xfa, 0x13, 0xfe, 0x90, 0xb8, 0x4a, 0xf4, 0x25, 0xfd, 0xf2, 0x8c, 0xc6,
  0x85, 0xb6, 0x85, 0xfe, 0xb4, 0x12, 0xb8, 0x06, 0x90, 0x24, 0xf4, 0xb8,
  0x44, 0x80, 0x76, 0x36, 0xb8, 0x4c, 0x80, 0x76, 0x80, 0xfd, 0xc6, 0x9f,
  0xb8, 0x04, 0x27, 0x90, 0x18, 0x90, 0x18, 0x90, 0xb9, 0x18, 0x91, 0x24,
  0xf8, 0xb8, 0x4d, 0xba, 0x7f, 0xf4, 0x99, 0xf4, 0x99, 0xb9, 0x02, 0x23,
  0x3b, 0x91, 0xb9, 0x07, 0x23, 0x01, 0x91, 0x34, 0xfc, 0xb8, 0x4e, 0xf4,
  0x5d, 0xf6, 0xde, 0xb6, 0xc6, 0x42, 0x53, 0x01, 0x6e, 0xb4, 0x12, 0xb9,
  0x05, 0x91, 0xb8, 0x52, 0xf4, 0x5d, 0xb6, 0xdc, 0xb9, 0x01, 0xfe, 0xe7,
  0x53, 0xfe, 0x03, 0x90, 0x91, 0xfe, 0xe7, 0x53, 0x01, 0x13, 0x01, 0x91,
  0x24, 0xf4, 0x27, 0xb9, 0x05, 0x91, 0x24, 0xf8, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xb9, 0x1a, 0x23, 0x06, 0x91, 0xb8, 0x0d, 0x23, 0x48, 0x90, 0xb9, 0x22,
  0xb1, 0x9a, 0x19, 0xb1, 0x08, 0x34, 0xfc, 0xb8, 0x09, 0xb9, 0x22, 0xf1,
  0x03, 0xfd, 0xa1, 0x19, 0x90, 0xf1, 0xf6, 0x22, 0x07, 0xa1, 0x90, 0xd3,
  0x04, 0x96, 0x32, 0xc9, 0xf1, 0xd3, 0xb0, 0x96, 0x32, 0xb1, 0x9a, 0x19,
  0xb1, 0x08, 0x24, 0xf4, 0x27, 0xb8, 0x1a, 0x90, 0xb8, 0x0d, 0x90, 0x24,
  0xf8, 0xb9, 0x1c, 0xbd, 0x05, 0xfd, 0x91, 0xb8, 0x14, 0x23, 0x6b, 0x90,
  0xb8, 0x10, 0x23, 0xc9, 0x90, 0x23, 0x01, 0x90, 0x19, 0xf4, 0xac, 0xe6,
  0x64, 0xfd, 0x91, 0xb8, 0x15, 0x23, 0x11, 0x90, 0xb8, 0x11, 0x23, 0x41,
  0x90, 0x23, 0x03, 0x90, 0xb8, 0x24, 0xb0, 0xdd, 0x34, 0xfc, 0xb8, 0x24,
  0x10, 0xf0, 0xc6, 0x72, 0x24, 0xf4, 0xb9, 0x1c, 0x91, 0xb8, 0x14, 0x90,
  0x19, 0xbd, 0x05, 0xf4, 0xac, 0xe6, 0x84, 0x96, 0x84, 0x91, 0x18, 0x90,
  0x24, 0xf8, 0xba, 0x9c, 0xbb, 0xb9, 0x76, 0x96, 0xba, 0x9e, 0xbb, 0xc5,
  0x76, 0x96, 0xba, 0xa0, 0xbb, 0xd1, 0xb9, 0x25, 0xb1, 0xff, 0xb8, 0x55,
  0xf4, 0x99, 0xb8, 0x00, 0xbc, 0x03, 0xbd, 0x02, 0xfb, 0x1b, 0xf4, 0xb7,
  0x90, 0xfb, 0x1b, 0xf4, 0xb7, 0x90, 0x18, 0xed, 0xa4, 0x23, 0x01, 0x90,
  0xf8, 0x03, 0x05, 0xa8, 0x23, 0x01, 0x90, 0x18, 0xec, 0xa2, 0x34, 0xf6,
  0xb9, 0x25, 0xb1, 0x00, 0x34, 0xfc, 0xb9, 0x25, 0xf1, 0x96, 0xf8, 0xb8,
  0x56, 0xf4, 0x5d, 0xf6, 0xe7, 0xb6, 0xe5, 0xfe, 0xb4, 0x12, 0xae, 0xbb,
  0x03, 0xb8, 0x04, 0xfe, 0x90, 0x18, 0x90, 0xf8, 0x03, 0x07, 0xa8, 0xeb,
  0xdb, 0x24, 0xf4, 0xb8, 0x04, 0xbd, 0x03, 0x27, 0x90, 0x18, 0x90, 0x18,
  0x18, 0x90, 0xf8, 0x03, 0x05, 0xa8, 0xed, 0xeb, 0x24, 0xf8, 0x01, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xb8, 0x6a, 0xba, 0xaa, 0xbf, 0x23, 0x76, 0x16,
  0xb8, 0x5a, 0xba, 0xa2, 0xbf, 0x21, 0x76, 0x16, 0xb8, 0x62, 0xba, 0xa6,
  0xbf, 0x22, 0xb9, 0x1b, 0x23, 0x06, 0x91, 0xf4, 0x99, 0xf4, 0x99, 0xff,
  0xb3, 0x36, 0x2c, 0x24, 0x34, 0xfc, 0xb8, 0x6b, 0xbf, 0x30, 0x76, 0x3c,
  0x34, 0xfc, 0xb8, 0x63, 0xbf, 0x20, 0xbd, 0x01, 0x76, 0x3c, 0x34, 0xfc,
  0xb8, 0x5b, 0xbf, 0x10, 0xb9, 0x59, 0x81, 0x53, 0xf0, 0xdf, 0xbd, 0x00,
  0x96, 0x47, 0x1d, 0xf4, 0x25, 0xf6, 0xb6, 0x18, 0x18, 0x80, 0xae, 0x18,
  0x18, 0xb9, 0x59, 0xfd, 0xc6, 0x5a, 0xb6, 0x9f, 0x76, 0x65, 0x81, 0x53,
  0x0f, 0xc6, 0x64, 0x37, 0x17, 0x6e, 0xe6, 0x9f, 0xcd, 0xfe, 0x4f, 0x91,
  0xfe, 0xb4, 0x12, 0xb9, 0x0e, 0x91, 0xab, 0xb9, 0x1e, 0x81, 0x96, 0x7d,
  0xb9, 0x16, 0xfb, 0x91, 0xb9, 0x12, 0x23, 0x3f, 0x91, 0xb9, 0x19, 0x81,
  0x96, 0x8e, 0xb9, 0x0c, 0xfb, 0x91, 0xb9, 0x08, 0x23, 0xc7, 0x91, 0x23,
  0x58, 0x91, 0xb9, 0x1a, 0x81, 0x96, 0x9f, 0xb9, 0x0d, 0xfb, 0x91, 0xb9,
  0x09, 0x23, 0xad, 0x91, 0x23, 0x90, 0x91, 0xf4, 0x25, 0xf6, 0xb6, 0xfd,
  0xc6, 0xb4, 0xf2, 0xac, 0xb6, 0xb4, 0x76, 0xb0, 0x18, 0x18, 0x80, 0xae,
  0xb9, 0x0a, 0xfe, 0x91, 0x24, 0xf4, 0xfd, 0xc6, 0xd8, 0x27, 0xb9, 0x59,
  0x91, 0xb9, 0x0e, 0x91, 0xb9, 0x1e, 0x81, 0x96, 0xc8, 0xb9, 0x16, 0x91,
  0xb9, 0x19, 0x81, 0x96, 0xd0, 0xb9, 0x0c, 0x91, 0xb9, 0x1a, 0x81, 0x96,
  0xd8, 0xb9, 0x0d, 0x91, 0xb9, 0x1b, 0x91, 0x24, 0xf8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x06, 0x01, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xb8, 0x72, 0x80, 0x96,
  0x10, 0xb9, 0x07, 0x23, 0x01, 0x91, 0xb9, 0x73, 0xba, 0xae, 0xf4, 0xdd,
  0xba, 0xb0, 0x76, 0x1b, 0xb8, 0x72, 0x80, 0xc6, 0xcd, 0xba, 0xb6, 0xb9,
  0x77, 0xf4, 0xdd, 0xf4, 0xdd, 0xf4, 0xdd, 0x80, 0x96, 0x32, 0xb8, 0x26,
  0xb0, 0xff, 0xb8, 0x27, 0xba, 0x06, 0xb0, 0x00, 0xea, 0x2e, 0xb8, 0x72,
  0x23, 0x80, 0x90, 0x34, 0xfc, 0xf5, 0x74, 0xdd, 0xe5, 0xb8, 0x78, 0xf4,
  0x25, 0xb6, 0x59, 0xfe, 0xf2, 0x8b, 0x03, 0xf7, 0xe6, 0x50, 0xbe, 0x08,
  0xb8, 0x7a, 0xfe, 0x90, 0xfd, 0xc6, 0x59, 0xfe, 0xb4, 0x12, 0xb8, 0x04,
  0x90, 0xb8, 0x7c, 0xf4, 0x25, 0xb6, 0x73, 0xfe, 0xf2, 0x8f, 0x03, 0xd0,
  0xe6, 0x6c, 0xbe, 0x2f, 0xb8, 0x7e, 0xfe, 0x90, 0xb8, 0x27, 0x10, 0x18,
  0x18, 0xfe, 0xa0, 0xb8, 0x80, 0xf4, 0x25, 0xf6, 0x93, 0xb6, 0x9b, 0xfe,
  0x03, 0x05, 0xe6, 0x86, 0xbe, 0xfa, 0xb8, 0x82, 0xfe, 0x90, 0xfe, 0xc6,
  0xcd, 0x76, 0x9e, 0xbe, 0x00, 0x76, 0x4c, 0xbe, 0x00, 0x76, 0x68, 0x34,
  0xfc, 0xf5, 0x74, 0xdd, 0xe5, 0xb8, 0x80, 0x18, 0x18, 0x80, 0xb8, 0x26,
  0x60, 0xa0, 0xe6, 0xcb, 0xb8, 0x74, 0xf4, 0x25, 0xb6, 0xb0, 0xb8, 0x27,
  0x10, 0x18, 0xfe, 0xa0, 0xb8, 0x27, 0xf0, 0xc6, 0xcb, 0xfd, 0xc6, 0xcb,
  0xb0, 0x00, 0x18, 0xf0, 0x18, 0x60, 0xaa, 0x6a, 0xaa, 0xb8, 0x00, 0x17,
  0xb4, 0x10, 0x90, 0xfa, 0xb4, 0x10, 0x90, 0x24, 0xf4, 0x27, 0xb9, 0x72,
  0x91, 0xfd, 0xc6, 0xdb, 0x27, 0xb9, 0x18, 0x91, 0xb9, 0x04, 0x91, 0x24,
  0xf8, 0xe5, 0xb9, 0x18, 0xbd, 0x02, 0xf4, 0xac, 0xf6, 0xe9, 0xbd, 0x00,
  0x83, 0xc6, 0xfd, 0xfd, 0x91, 0xb9, 0x27, 0x11, 0xb9, 0x7a, 0x81, 0xb4,
  0x12, 0xb9, 0x04, 0x91, 0x23, 0x37, 0xb9, 0x02, 0x91, 0xf5, 0x83, 0x8c,
  0xb8, 0x83, 0x80, 0xc6, 0xda, 0xb8, 0x84, 0xba, 0xbb, 0xbb, 0x06, 0x23,
  0x01, 0x90, 0x18, 0x90, 0x18, 0xfa, 0x90, 0x18, 0x18, 0xeb, 0x0b, 0x76,
  0x32, 0xb8, 0x83, 0x80, 0x96, 0x93, 0x17, 0x90, 0xb8, 0x07, 0x90, 0x23,
  0x08, 0xb8, 0x18, 0x90, 0xba, 0xbc, 0xb8, 0x84, 0xbb, 0x06, 0xf4, 0x99,
  0xeb, 0x2e, 0x34, 0xfc, 0xb8, 0x85, 0xba, 0xff, 0xbc, 0x00, 0xbf, 0x06,
  0xf4, 0x25, 0xe6, 0x41, 0x1c, 0xff, 0x12, 0x5f, 0x1a, 0x1a, 0x1a, 0x1a,
  0x1a, 0xb6, 0x88, 0xfa, 0xa9, 0xff, 0xd3, 0x06, 0x96, 0x55, 0xfe, 0xc6,
  0xcc, 0xfe, 0xf2, 0x5c, 0xb4, 0x12, 0x76, 0x87, 0x27, 0x76, 0x87, 0xca,
  0xca, 0xca, 0xca, 0xfa, 0xa9, 0xff, 0x52, 0x6e, 0xb6, 0x88, 0x32, 0x84,
  0x76, 0x86, 0x18, 0x18, 0x80, 0xc8, 0xc8, 0xae, 0x42, 0x53, 0x07, 0x6e,
  0xae, 0x6e, 0xae, 0x17, 0xb4, 0x10, 0x91, 0xfe, 0xb4, 0x10, 0x76, 0x87,
  0x27, 0x91, 0xfe, 0x91, 0x18, 0x18, 0x18, 0x18, 0xef, 0x3c, 0xfc, 0x96,
  0x93, 0x24, 0xf4, 0xb8, 0x01, 0x23, 0x00, 0x90, 0x23, 0x50, 0x90, 0x18,
  0x23, 0x12, 0x90, 0x18, 0x18, 0x23, 0x09, 0xb4, 0x12, 0x90, 0x18, 0x23,
  0x07, 0xb4, 0x12, 0x90, 0x18, 0x23, 0x05, 0xb4, 0x12, 0x90, 0x34, 0xfc,
  0xb8, 0x00, 0x42, 0xa9, 0xf1, 0xd9, 0x62, 0x53, 0x07, 0x03, 0x14, 0xae,
  0x6e, 0xae, 0x17, 0xb4, 0x10, 0x90, 0xfe, 0xb4, 0x10, 0x90, 0x24, 0xf4,
  0xb8, 0x04, 0x27, 0x90, 0x18, 0x90, 0x18, 0x90, 0xb8, 0x18, 0x90, 0xb8,
  0x83, 0x90, 0x24, 0xf8, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xb8, 0x2d, 0xb0, 0x01, 0x18, 0xb0, 0x0f, 0xb8,
  0x07, 0x23, 0x01, 0x90, 0x34, 0xfc, 0xb9, 0x18, 0xbd, 0x04, 0xf4, 0xac,
  0xf6, 0x1a, 0xbd, 0x00, 0x76, 0x1e, 0xc6, 0x1e, 0xfd, 0x91, 0xb8, 0x2d,
  0xf0, 0x07, 0x96, 0x2d, 0x18, 0xf0, 0x07, 0xc6, 0x56, 0xa0, 0xc8, 0x23,
  0x2f, 0xa0, 0x18, 0xfd, 0xc6, 0x54, 0xb9, 0x02, 0x23, 0x32, 0x91, 0xf0,
  0xb4, 0x12, 0xb8, 0x04, 0x90, 0x18, 0x90, 0xb8, 0x00, 0x23, 0x5f, 0x90,
  0x42, 0x53, 0x01, 0x03, 0x3b, 0x90, 0x18, 0x23, 0x9f, 0x90, 0x42, 0x53,
  0x01, 0x03, 0x28, 0x90, 0x24, 0xf4, 0xfd, 0xc6, 0x62, 0x27, 0xb8, 0x04,
  0x90, 0x18, 0x90, 0xb8, 0x18, 0x90, 0x24, 0xf8, 0xb8, 0x9c, 0x80, 0x12,
  0x6b, 0x24, 0xfa, 0x43, 0x80, 0x90, 0x24, 0xfa, 0x23, 0x54, 0xbb, 0xff,
  0x76, 0x7a, 0x23, 0xe6, 0xbb, 0xfb, 0xb8, 0x2f, 0xa0, 0x18, 0xb0, 0xff,
  0x18, 0xfb, 0xa0, 0x18, 0xb0, 0xe8, 0x18, 0xb0, 0x03, 0xb8, 0x9c, 0x80,
  0x43, 0x01, 0x90, 0x34, 0xfc, 0xb8, 0x9c, 0x80, 0xf2, 0xd7, 0xb9, 0x1d,
  0xbd, 0x07, 0xf4, 0xac, 0x85, 0xb8, 0x11, 0xf6, 0xa4, 0x95, 0x76, 0xb4,
  0xc6, 0xb4, 0xfd, 0x91, 0xb9, 0x32, 0xf1, 0x90, 0x19, 0xf1, 0x90, 0xb9,
  0x15, 0x23, 0x81, 0x91, 0xb9, 0x2f, 0xf1, 0x19, 0x61, 0xa1, 0xe6, 0xd5,
  0x19, 0xf1, 0x19, 0x61, 0xa1, 0xaa, 0x19, 0xf1, 0xf6, 0xc8, 0x07, 0xa1,
  0x96, 0xcf, 0xfa, 0xd3, 0x14, 0xc6, 0xd7, 0xb6, 0xd5, 0xfa, 0x90, 0xf1,
  0x90, 0x24, 0xf4, 0xb9, 0x1d, 0xbd, 0x07, 0xf4, 0xac, 0xe6, 0xe5, 0x96,
  0xe5, 0x91, 0xb8, 0x15, 0x90, 0xb8, 0x9c, 0x27, 0x90, 0x24, 0xf8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xd8, 0x00, 0xea, 0x3c,
  0xd8, 0x02, 0xea, 0x2c, 0xb8, 0xad, 0x80, 0x12, 0x0f, 0x24, 0xfa, 0x43,
  0x80, 0x90, 0x24, 0xfa, 0x23, 0x90, 0xba, 0x00, 0x76, 0x1e, 0x23, 0x50,
  0xba, 0x04, 0xb9, 0x38, 0xa1, 0x19, 0xb1, 0xff, 0xb8, 0xae, 0xf5, 0xd4,
  0xe7, 0xb8, 0xad, 0x80, 0x43, 0x01, 0x90, 0x34, 0xfc, 0xb8, 0xad, 0x80,
  0xbf, 0x38, 0xbd, 0x08, 0xf2, 0x3e, 0xb8, 0xaf, 0x76, 0x7a, 0x27, 0x90,
  0xb9, 0x1d, 0xf4, 0xac, 0xe6, 0xe5, 0x96, 0xe5, 0x76, 0xdb, 0xb8, 0x9d,
  0xba, 0xf4, 0xf4, 0x99, 0xf4, 0x99, 0xb9, 0x34, 0xb1, 0x19, 0x19, 0xb1,
  0xff, 0x34, 0xfc, 0xb8, 0x9e, 0xbf, 0x34, 0xbd, 0x09, 0x76, 0x7a, 0xb8,
  0xa5, 0xba, 0xf8, 0xf4, 0x99, 0xf4, 0x99, 0xb9, 0x36, 0xb1, 0xdc, 0x19,
  0xb1, 0xff, 0x34, 0xfc, 0xb8, 0xa6, 0xbf, 0x36, 0xbd, 0x06, 0xb9, 0x1d,
  0xf4, 0xac, 0xf6, 0x84, 0xbd, 0x00, 0x76, 0xa8, 0xc6, 0xa8, 0xfd, 0x91,
  0xb9, 0x15, 0x18, 0x18, 0x80, 0xf2, 0xdb, 0xb4, 0x12, 0x91, 0x18, 0x18,
  0x18, 0x18, 0xb9, 0x11, 0x80, 0xae, 0x6e, 0xae, 0x17, 0xb4, 0x10, 0x91,
  0xfe, 0xb4, 0x10, 0x91, 0xf8, 0x03, 0xfa, 0xa8, 0xff, 0xa9, 0xf1, 0x19,
  0x61, 0xa1, 0xe6, 0xd9, 0xf4, 0x5d, 0xf6, 0xdb, 0xb6, 0xc1, 0xfd, 0xc6,
  0xc1, 0xfe, 0xf2, 0xdb, 0xb4, 0x12, 0xb9, 0x15, 0x91, 0x18, 0x18, 0x18,
  0x18, 0xf4, 0x5d, 0xb6, 0xd9, 0xfd, 0xc6, 0xd9, 0xb9, 0x11, 0xfe, 0x6e,
  0xae, 0x17, 0xb4, 0x10, 0x91, 0xfe, 0xb4, 0x10, 0x91, 0x24, 0xf4, 0xfd,
  0xc6, 0xe5, 0x27, 0xb8, 0x15, 0x90, 0xb8, 0x1d, 0x90, 0x24, 0xf8, 0xbb,
  0x02, 0x23, 0x01, 0x90, 0x18, 0x90, 0x18, 0xfa, 0x1a, 0xa3, 0x90, 0x18,
  0xfa, 0x1a, 0xa3, 0x90, 0x18, 0xeb, 0xe9, 0xe5, 0x83, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x06, 0x01, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c, 0xf5, 0xf4, 0xe3, 0xd2,
  0x88, 0xe5, 0x24, 0xfa, 0xaf, 0x53, 0x03, 0xae, 0xf4, 0xd4, 0xa8, 0xf4,
  0xd4, 0xad, 0x85, 0xff, 0x52, 0x9c, 0x95, 0xfe, 0x43, 0x40, 0x3a, 0xff,
  0xb2, 0xb2, 0xb6, 0xa3, 0xf0, 0xe4, 0xa4, 0x80, 0x18, 0xf4, 0xc1, 0xed,
  0x9e, 0xf4, 0xbb, 0x27, 0x3a, 0x43, 0x40, 0x3a, 0xe4, 0x81, 0xfd, 0xb6,
  0xb8, 0xa0, 0xe4, 0xb9, 0x90, 0xe4, 0x81, 0x09, 0x53, 0x7f, 0xc6, 0xbb,
  0x83, 0xb9, 0x08, 0xac, 0xf4, 0xbb, 0xfc, 0x77, 0xac, 0x43, 0x7f, 0x39,
  0xfe, 0x3a, 0x43, 0x40, 0x3a, 0xe9, 0xc4, 0x83, 0xf4, 0xe3, 0x53, 0x0f,
  0xad, 0xf4, 0xe3, 0x53, 0x0f, 0xe7, 0xe7, 0xe7, 0xe7, 0x4d, 0x83, 0xf4,
  0xbb, 0xaa, 0x09, 0x53, 0x7f, 0xab, 0xda, 0xc6, 0xf0, 0xfb, 0xe4, 0xe5,
  0x3a, 0x23, 0x40, 0x3a, 0xfa, 0x83, 0xc8, 0x8c, 0xc8, 0x8c, 0xc8, 0x8c,
  0xc8, 0x8c, 0xc8, 0x8c
};
const uint16_t usbrom_bin_len = 4096;
