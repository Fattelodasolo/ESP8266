#include <avr/pgmspace.h>
const unsigned char gImage_sun[800] = { /* 0X00,0X01,0X50,0X00,0X50,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X03,0X00,0X00,0X03,0XC0,0X00,0X00,
0XC0,0X00,0X00,0X07,0X80,0X00,0X03,0XC0,0X00,0X01,0XE0,0X00,0X00,0X0F,0XC0,0X00,
0X03,0XC0,0X00,0X03,0XF0,0X00,0X00,0X0F,0XE0,0X00,0X01,0X80,0X00,0X07,0XF0,0X00,
0X00,0X07,0XF0,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,0X00,0X03,0XF8,0X00,0X00,0X00,
0X00,0X1F,0XC0,0X00,0X00,0X01,0XFC,0X00,0X00,0X00,0X00,0X3F,0X80,0X00,0X00,0X00,
0XFE,0X00,0X00,0X00,0X00,0X7F,0X00,0X00,0X00,0X00,0X7E,0X00,0X00,0X00,0X00,0X7E,
0X00,0X00,0X00,0X00,0X3F,0X00,0X1F,0XF8,0X00,0XFC,0X00,0X00,0X00,0X00,0X1E,0X00,
0XFF,0XFF,0X00,0X78,0X00,0X00,0X00,0X00,0X04,0X03,0XFF,0XFF,0XC0,0X20,0X00,0X00,
0X00,0X00,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0XFE,0X3F,
0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0XE0,0X07,0XFC,0X00,0X00,0X00,0X00,0X00,
0X00,0X3F,0X80,0X01,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X7E,0X00,0X00,0X7E,0X00,
0X00,0X00,0X00,0X00,0X00,0XFC,0X00,0X00,0X3F,0X00,0X00,0X00,0X00,0X00,0X01,0XF8,
0X00,0X00,0X1F,0X80,0X00,0X00,0X00,0X00,0X01,0XF0,0X00,0X00,0X0F,0X80,0X00,0X00,
0X00,0X00,0X03,0XF0,0X00,0X00,0X0F,0XC0,0X00,0X00,0X00,0X00,0X03,0XE0,0X00,0X00,
0X07,0XC0,0X00,0X00,0X00,0X00,0X03,0XE0,0X00,0X00,0X07,0XC0,0X00,0X00,0X00,0X00,
0X07,0XC0,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X07,0XC0,0X00,0X00,0X03,0XE0,
0X00,0X00,0X00,0X00,0X07,0XC0,0X00,0X00,0X03,0XE0,0X00,0X00,0X3F,0XFE,0X07,0X80,
0X00,0X00,0X01,0XE0,0X7F,0XFC,0X3F,0XFF,0X07,0X80,0X00,0X00,0X01,0XE0,0XFF,0XFC,
0X3F,0XFF,0X07,0X80,0X00,0X00,0X01,0XE0,0XFF,0XFC,0X3F,0XFE,0X07,0X80,0X00,0X00,
0X01,0XE0,0X7F,0XFC,0X00,0X00,0X07,0XC0,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,
0X07,0XC0,0X00,0X00,0X03,0XE0,0X00,0X00,0X00,0X00,0X07,0XC0,0X00,0X00,0X03,0XE0,
0X00,0X00,0X00,0X00,0X03,0XE0,0X00,0X00,0X07,0XC0,0X00,0X00,0X00,0X00,0X03,0XE0,
0X00,0X00,0X07,0XC0,0X00,0X00,0X00,0X00,0X03,0XF0,0X00,0X00,0X0F,0XC0,0X00,0X00,
0X00,0X00,0X01,0XF0,0X00,0X00,0X0F,0X80,0X00,0X00,0X00,0X00,0X01,0XF8,0X00,0X00,
0X1F,0X80,0X00,0X00,0X00,0X00,0X00,0XFC,0X00,0X00,0X3F,0X00,0X00,0X00,0X00,0X00,
0X00,0X7E,0X00,0X00,0X7E,0X00,0X00,0X00,0X00,0X00,0X00,0X3F,0X80,0X01,0XFC,0X00,
0X00,0X00,0X00,0X00,0X00,0X3F,0XE0,0X07,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,
0XFE,0X3F,0XF0,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XFF,0XFF,0XE0,0X00,0X00,0X00,
0X00,0X00,0X04,0X03,0XFF,0XFF,0XC0,0X20,0X00,0X00,0X00,0X00,0X1E,0X00,0XFF,0XFF,
0X00,0X78,0X00,0X00,0X00,0X00,0X3F,0X00,0X1F,0XF8,0X00,0XFC,0X00,0X00,0X00,0X00,
0X7E,0X00,0X00,0X00,0X00,0X7E,0X00,0X00,0X00,0X00,0XFE,0X00,0X00,0X00,0X00,0X7F,
0X00,0X00,0X00,0X01,0XFC,0X00,0X00,0X00,0X00,0X3F,0X80,0X00,0X00,0X03,0XF8,0X00,
0X00,0X00,0X00,0X1F,0XC0,0X00,0X00,0X07,0XF0,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,
0X00,0X0F,0XE0,0X00,0X01,0X80,0X00,0X07,0XF0,0X00,0X00,0X0F,0XC0,0X00,0X03,0XC0,
0X00,0X03,0XF0,0X00,0X00,0X07,0X80,0X00,0X03,0XC0,0X00,0X01,0XE0,0X00,0X00,0X03,
0X00,0X00,0X03,0XC0,0X00,0X00,0XC0,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};