#include "base.h"

namespace Win32API {

   typedef unsigned long clr;

   clr hsl(float hue, float sat, float lum) {

      hue /= 60.f;
      float C = (1 - std::abs(2 * lum - 1)) * sat;
      float X = C * (1 - std::abs(mod_f(hue, 2) - 1));

      float m = lum - C / 2;

      C += m;
      X += m;

      float rgb[3] = {};

      switch ((long)hue) {
         case 0: { rgb[0] = C; rgb[1] = X; rgb[2] = m; } break;
         case 1: { rgb[0] = X; rgb[1] = C; rgb[2] = m; } break;
         case 2: { rgb[0] = m; rgb[1] = C; rgb[2] = X; } break;
         case 3: { rgb[0] = m; rgb[1] = X; rgb[2] = C; } break;
         case 4: { rgb[0] = X; rgb[1] = m; rgb[2] = C; } break;
         case 5: { rgb[0] = C; rgb[1] = m; rgb[2] = X; } break;
      }

      return ((clr)(rgb[0] * 255) << 16) | ((clr)(rgb[1] * 255) << 8) | (clr)(rgb[2] * 255);
   }

   clr color_lerp(clr color0, clr color1, float t) {

      return ((clr)((float)(color0 & 0xff0000) * t + (float)(color1 & 0xff0000) * (1 - t)) & 0xff0000)
         | ((clr)((float)(color0 & 0xff00) * t + (float)(color1 & 0xff00) * (1 - t)) & 0xff00)
         | ((clr)((float)(color0 & 0xff) * t + (float)(color1 & 0xff) * (1 - t)) & 0xff);
   }
}