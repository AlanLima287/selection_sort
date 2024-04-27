#pragma once

#include "renderer.h"

namespace Win32API {

   inline clr RenderState::getPixel(int x, int y) const {
      return *((clr*)bitmap.buffer + bitmap.width * y + x);
   }

   clr RenderState::getPixel_s(int x, int y) const {
      if ((0 > x && x >= bitmap.width) || (0 > y && y >= bitmap.height)) return 0;
      return *((clr*)bitmap.buffer + bitmap.width * y + x);
   }

   inline void RenderState::fillPixel(int x, int y, clr color) {
      *((clr*)bitmap.buffer + bitmap.width * y + x) = color;
   }

   bool RenderState::fillPixel_s(int x, int y, clr color) {
      if (0 <= x && x < bitmap.width && 0 <= y && y < bitmap.height)
         return (*((clr*)bitmap.buffer + bitmap.width * y + x) = color);
      return false;
   }

   void RenderState::fillBackground(clr color) {
      clr* pixel = (clr*)bitmap.buffer;
      for (int x = 0; x < bitmap.width; x++)
         for (int y = 0; y < bitmap.height; y++) *pixel++ = color;
   }

   void RenderState::fillRect(int startX, int startY, int sizeX, int sizeY, clr color) {

      sizeX = startX + sizeX;
      sizeY = startY + sizeY;

      startX = clamp(0, startX, bitmap.width);
      startY = clamp(0, startY, bitmap.height);
      sizeX = clamp(0, sizeX, bitmap.width);
      sizeY = clamp(0, sizeY, bitmap.height);

      for (int y = startY; y < sizeY; y++) {
         clr* pixel = (clr*)bitmap.buffer + startX + y * bitmap.width;
         for (int x = startX; x < sizeX; x++) *pixel++ = color;
      }
   }

   void RenderState::drawLine(int startX, int startY, int endX, int endY, clr color) {

      int dx = abs(endX - startX);
      int dy = -abs(endY - startY);
      int signX = startX < endX ? 1 : -1;
      int signY = startY < endY ? 1 : -1;
      int error = dx + dy;

      if (std::hypot(dx, dy) > 1600) return;

      while (true) {

         fillPixel_s(startX, startY, color);
         if (startX == endX && startY == endY) break;

         int e2 = error << 1;

         if (e2 >= dy) { startX += signX; error += dy; }
         if (e2 <= dx) { startY += signY; error += dx; }

      }
   }

   inline void RenderState::drawTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, clr color) {
      drawLine(p0_x, p0_y, p1_x, p1_y, color);
      drawLine(p1_x, p1_y, p2_x, p2_y, color);
      drawLine(p2_x, p2_y, p0_x, p0_y, color);
   }

   void RenderState::fillTriangle(int p0_x, int p0_y, int p1_x, int p1_y, int p2_x, int p2_y, clr color) {

      if (p0_y > p1_y) { swap(p0_x, p1_x); swap(p0_y, p1_y); }
      if (p0_y > p2_y) { swap(p0_x, p2_x); swap(p0_y, p2_y); }
      if (p1_y > p2_y) { swap(p1_x, p2_x); swap(p1_y, p2_y); }

      int total_height = p2_y - p0_y;

      for (int y = p0_y; y <= p1_y; y++) {

         int segment_height = p1_y - p0_y + 1;

         float alpha = (float)(y - p0_y) / total_height;
         float beta = (float)(y - p0_y) / segment_height;

         int A = (int)(p0_x + (p2_x - p0_x) * alpha);
         int B = (int)(p0_x + (p1_x - p0_x) * beta);

         if (A > B) swap(A, B);
         A = clamp(0, A, bitmap.width);
         B = clamp(0, B, bitmap.width);

         for (int x = A; x <= B; x++) fillPixel_s(x, y, color);
      }

      for (int y = p1_y; y <= p2_y; y++) {

         int segment_height = p2_y - p1_y + 1;

         float alpha = (float)(y - p0_y) / total_height;
         float beta = (float)(y - p1_y) / segment_height;

         int A = (int)(p0_x + (p2_x - p0_x) * alpha);
         int B = (int)(p1_x + (p2_x - p1_x) * beta);

         if (A > B) std::swap(A, B);
         A = clamp(0, A, bitmap.width);
         B = clamp(0, B, bitmap.width);

         for (int x = A; x <= B; x++) fillPixel_s(x, y, color);
      }

   }
   void RenderState::fillText(int x, int y, int fontSize, clr color, uchar align, const char* text) {

      if (!font.isLoaded()) return;

      float blockSize = (float)fontSize / font.height;
      float glyphWidth = blockSize * (float)font.width;

      float pivotX = x - (float)strlen(text) * blockSize * font.width * (float)(align & 0xf) * .5f;
      float pivotY = y + fontSize * (2 - (align >> 4)) * .5f;
      float posX, posY;

      int boxSize = (int)std::ceil(blockSize);

      while (*text) {

         const uchar* charSheet = font.getCharacterSheet(*text);

         posX = pivotX;
         posY = pivotY;

         long index = -1;
         ulong cursor = 0x80u;

         for (ulong i = 0, j = 0; i < font.sheet_length; i++, j++) {
            if (!(i & 0b111)) { index++; }

            if (j >= font.width) { j = 0; posY -= blockSize; posX = pivotX; }
            if ((charSheet[index] & cursor) != 0) fillRect((int)posX, (int)posY, boxSize, boxSize, color);

            cursor = cursor == 1 ? 0x80u : cursor >> 1;
            posX += blockSize;
         }

         pivotX += glyphWidth;
         text++;
      }
   }

   void RenderState::fillTextF(int x, int y, int fontSize, clr color, uchar align, const char* text, ...) {

   }

   void RenderState::resizeWindowBuffer(RECT& rect, unsigned pixel_ratio) {

      bitmap.originX = rect.left;
      bitmap.originY = rect.top;

      bitmap.height = rect.bottom;
      bitmap.width = rect.right;

      size_t length = (size_t)bitmap.width * bitmap.height;

      if (bitmap.buffer) free(bitmap.buffer);
      bitmap.buffer = malloc(length * sizeof(clr));

      bitmap.info.bmiHeader.biHeight = bitmap.height;
      bitmap.info.bmiHeader.biWidth = bitmap.width;

      bitmap.screenHeight = bitmap.height;
      bitmap.screenHeight = bitmap.width;
   }

   void RenderState::copyBufferToWindow(HDC hdc) {

      StretchDIBits(
         hdc,
         0, 0, bitmap.info.bmiHeader.biWidth, bitmap.info.bmiHeader.biHeight,
         0, 0, bitmap.info.bmiHeader.biWidth, bitmap.info.bmiHeader.biHeight,
         bitmap.buffer, &bitmap.info, DIB_RGB_COLORS, SRCCOPY
      );
   }
}