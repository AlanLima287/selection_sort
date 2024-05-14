#pragma once

#include "base.h"

typedef unsigned long clr;

enum Color {
   BLACK = 0x000000,
   SILVER = 0xcccccc,
   GRAY = 0x808080,
   WHITE = 0xffffff,

   BROWN = 0x803000,

   YELLOW = 0xffff00,
   MAGENTA = 0xff00ff,
   CYAN = 0x00ffff,

   RED = 0xff0000,
   GREEN = 0x00ff00,
   BLUE = 0x0000ff,

   MAROON = 0x800000,
   FOREST = 0x008000,
   NAVY = 0x000080,

   PURPLE = 0x800080,
   OLIVE = 0x808000,
   TEAL = 0x008080,

   ROSE = 0xff0080,
   ORANGE = 0xff8000,
   LIME = 0x80ff00,
   AQUA = 0x00ff80,
   VIOLET = 0x8000ff,
   SKY = 0x0080ff,

   PINK = 0xffc0c0,
   ICE = 0xc0c0ff,
};

clr rgb(float red, float green, float blue) {
   return ((clr)(red * 255.f) << 16) | ((clr)(green * 255.f) << 8) | (clr)(blue * 255.f);
}

clr rgb(ulong red, ulong green, ulong blue) {
   return (clr)(red << 16 | green << 8 | blue);
}

clr hsl(float hue, float sat, float lum) {

   hue /= 60.f;
   float C = (1 - std::abs(2 * lum - 1)) * sat;
   float X = C * (1 - std::abs(mod_f(hue, 2.f) - 1));

   float m = lum - C / 2;

   C += m;
   X += m;

   switch ((long)hue % 6) {
      case 0: return (clr)(C * 255) << 16 | (clr)(X * 255) << 8 | (clr)(m * 255);
      case 1: return (clr)(X * 255) << 16 | (clr)(C * 255) << 8 | (clr)(m * 255);
      case 2: return (clr)(m * 255) << 16 | (clr)(C * 255) << 8 | (clr)(X * 255);
      case 3: return (clr)(m * 255) << 16 | (clr)(X * 255) << 8 | (clr)(C * 255);
      case 4: return (clr)(X * 255) << 16 | (clr)(m * 255) << 8 | (clr)(C * 255);
      case 5: return (clr)(C * 255) << 16 | (clr)(m * 255) << 8 | (clr)(X * 255);
   }

   return 0;
}

clr color_lerp(clr color0, clr color1, float t) {

   return ((clr)((float)(color1 & 0xff0000) * t + (float)(color0 & 0xff0000) * (1 - t)) & 0xff0000)
      | ((clr)((float)(color1 & 0xff00) * t + (float)(color0 & 0xff00) * (1 - t)) & 0xff00)
      | ((clr)((float)(color1 & 0xff) * t + (float)(color0 & 0xff) * (1 - t)) & 0xff);
}