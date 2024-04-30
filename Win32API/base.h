#pragma once

#include <iostream>
#include <math.h>

#include <Windows.h>
#include <Windowsx.h>

#define clamp(minv, val, maxv) (((val) < (minv)) ? (minv) : (((val) > (maxv)) ? (maxv) : (val)))

typedef unsigned char uchar;
typedef unsigned long ulong;
typedef unsigned int uint;

#ifndef M_PI

#define M_E        2.71828182845904523536   // e
#define M_LOG2E    1.44269504088896340736   // log2(e)
#define M_LOG10E   0.434294481903251827651  // log10(e)
#define M_LN2      0.693147180559945309417  // ln(2)
#define M_LN10     2.30258509299404568402   // ln(10)
#define M_PI       3.14159265358979323846   // pi
#define M_PI_2     1.57079632679489661923   // pi/2
#define M_PI_4     0.785398163397448309616  // pi/4
#define M_1_PI     0.318309886183790671538  // 1/pi
#define M_2_PI     0.636619772367581343076  // 2/pi
#define M_2_SQRTPI 1.12837916709551257390   // 2/sqrt(pi)
#define M_SQRT2    1.41421356237309504880   // sqrt(2)
#define M_SQRT1_2  0.707106781186547524401  // 1/sqrt(2)

#endif

inline float mod_f(float num, float mod) {
   float result = num - std::floor(num / mod) * mod;
   return result >= 0 ? result : result + mod;
}

float invsqrtf(float num) {

   long i;
   float x2, y;
   const float threehalfs = 1.5f;

   x2 = num * 0.5f;
   y = num;
   i = *(long*)&y;									   // evil floating point bit level hacking
   i = 0x5f3759df - (i >> 1);						   // what the fuck?
   y = *(float*)&i;
   y = y * (threehalfs - (x2 * y * y));			// 1st iteration
   // y  = y * ( threehalfs - ( x2 * y * y ) );	// 2nd iteration, this can be removed

   return y;
}

#ifndef __XOR_SWAP__
#define __XOR_SWAP__

/* Warning! If the values have the same address, it will end up setting both to 0 */
inline void swap(int& a, int& b) {
   a ^= b; b ^= a; a ^= b;
}

#endif

namespace Win32API {

   LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

   typedef struct {
      int width, height;
      int originX, originY;
      int screenWidth, screenHeight;
      BITMAPINFO info;
      void* buffer;
   } BitmapBuffer;

   int str_length_until_newline_end(char* str) {
      int i = 0;
      while (*str != '\0' && *str != '\n') { i++; str++; }
      return i;
   }

   class Window;
   class RenderState;
   class Input;
}