/* dumped in big endian order.
   use `mrbc -e` option for better performance on little endian CPU. */
#include <stdint.h>
extern const uint8_t ary[];
const uint8_t
#if defined __GNUC__
__attribute__((aligned(4)))
#elif defined _MSC_VER
__declspec(align(4))
#endif
ary[] = {
0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x34,0xa3,0x10,0x00,0x00,0x01,0x0f,0x4d,0x41,
0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0xf1,0x30,0x30,
0x30,0x30,0x00,0x00,0x00,0xe9,0x00,0x01,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x23,
0x00,0x80,0x00,0x11,0x01,0x40,0x01,0x83,0x01,0x80,0x01,0x04,0x00,0x80,0x41,0x20,
0x00,0x80,0x00,0x11,0x01,0x40,0x02,0x03,0x01,0x80,0x01,0x04,0x00,0x80,0x41,0x20,
0x00,0x40,0x0b,0x17,0x00,0x80,0x00,0x11,0x01,0x40,0x01,0x83,0x01,0x80,0x02,0x04,
0x00,0x80,0xc1,0x20,0x00,0x80,0x00,0x11,0x01,0x40,0x02,0x03,0x01,0x80,0x02,0x04,
0x00,0x80,0xc1,0x20,0x00,0x80,0x00,0x11,0x01,0x41,0xf3,0x83,0x00,0x81,0x40,0xa0,
0x00,0x80,0x00,0x11,0x01,0x40,0x01,0x83,0x01,0x80,0x03,0x04,0x00,0x80,0xc1,0x20,
0x00,0x80,0x00,0x11,0x01,0x40,0x02,0x03,0x01,0x80,0x03,0x04,0x00,0x80,0xc1,0x20,
0x00,0x80,0x00,0x11,0x01,0x41,0xf3,0x83,0x00,0x81,0x40,0xa0,0x00,0x80,0x00,0x07,
0x00,0xbf,0xf4,0x18,0x00,0x80,0x00,0x05,0x00,0x00,0x00,0x4a,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x07,0x00,0x07,0x41,0x72,0x64,0x75,0x69,0x6e,0x6f,0x00,0x00,0x08,
0x70,0x69,0x6e,0x5f,0x6d,0x6f,0x64,0x65,0x00,0x00,0x06,0x4f,0x55,0x54,0x50,0x55,
0x54,0x00,0x00,0x0d,0x64,0x69,0x67,0x69,0x74,0x61,0x6c,0x5f,0x77,0x72,0x69,0x74,
0x65,0x00,0x00,0x04,0x48,0x49,0x47,0x48,0x00,0x00,0x05,0x64,0x65,0x6c,0x61,0x79,
0x00,0x00,0x03,0x4c,0x4f,0x57,0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
};