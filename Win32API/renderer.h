#pragma once

#include "base.h"
#include "font_map.cpp"

namespace Win32API {

   enum Alignment {
      HALIGN_START = 0x0,
      HALIGN_CENTER = 0x1,
      HALIGN_END = 0x2,

      VALIGN_START = 0x00,
      VALIGN_CENTER = 0x10,
      VALIGN_END = 0x20,

      ALIGN_START = 0x00,
      ALIGN_CENTER = 0x11,
      ALIGN_END = 0x22,
   };

   enum Color {
      BLACK = 0x000000,
      SILVER = 0xc0c0c0,
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

   class RenderState {

      friend LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
      friend class Window;

   private:

      FontMap::Font font;
      BitmapBuffer bitmap;

   public:

      RenderState() {
         bitmap.buffer = nullptr;
         bitmap.info.bmiHeader.biSize = sizeof(BITMAPINFO);
         bitmap.info.bmiHeader.biBitCount = sizeof(clr) << 3;
         bitmap.info.bmiHeader.biCompression = BI_RGB;
         bitmap.info.bmiHeader.biPlanes = 1;
      }

      RenderState(const RenderState&) = delete;
      RenderState operator=(const RenderState&) = delete;

      ~RenderState() { if (bitmap.buffer) free(bitmap.buffer); };

      inline void setFont(const char* font_path) { font.ftmpAssembler(font_path); }

   public:

      inline int height() { return bitmap.height; }
      inline int width() { return bitmap.width; }

   public:

      inline clr getPixel(int x, int y) const;
      clr getPixel_s(int x, int y) const;

      inline void fillPixel(int x, int y, clr color);
      bool fillPixel_s(int x, int y, clr color);

      void fillBackground(clr color);
      void fillRect(int startX, int startY, int sizeX, int sizeY, clr color);

      void drawLine(int startX, int startY, int endX, int endY, clr color);

      inline void drawTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, clr color);
      void fillTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, clr color);

      void fillText(int, int, int, clr, uchar, const char*);
      void fillTextF(int, int, int, clr, uchar, const char*, ...);

   public:

      void resizeWindowBuffer(RECT&, unsigned pixel_ratio = 1);
      void copyBufferToWindow(HDC hdc);

   };
}