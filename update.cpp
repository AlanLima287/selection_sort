#include "./Win32API/Win32API.h"
#include "vector.h"

struct Helper {
   ulong i, j, k, lmin, lmax;

   ulong comparisons, swaps;
   char name[255], text[255];

   float aspect_height, bar_width;
   bool go;

   void (*sorter)(Vector&);
   void (*display)(Vector&);

} helper{
   (ulong)~0, (ulong)~0, (ulong)~0,
   (ulong)~0, (ulong)~0, 0, 0,
   "", "", .0f, .0f, false,
   nullptr, nullptr
};

void update_selection_sort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (helper.i = 0; helper.i < vector.get_length() - 1; helper.i++) {

      helper.lmin = helper.i;

      for (helper.j = helper.i + 1; helper.j < vector.get_length(); helper.j++) {
         if (vector[helper.lmin] > vector[helper.j]) helper.lmin = helper.j;

         do if (!window.windowProcess(1.f)) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);

      }

      if (helper.lmin != helper.i)
         swap(vector[helper.lmin], vector[helper.i]);
   }
}

void show_selection_sort(Vector& vector) {

   using namespace Win32API;
   RenderState& ctx = Window::getInstance().getContext();

   if (!vector.is_sorted()) {
      sprintf(helper.text, "Current Comparasion: %d > %d", vector[helper.lmin], vector[helper.j]);
      ctx.fillText(0, ctx.height() - 0x6E, 25, Color::WHITE, Alignment::VALIGN_END, helper.text);
   }

   float start = 0;
   for (ulong b = 0; b < vector.get_length(); b++) {

      clr color = (!vector.is_sorted() && (b == helper.lmin || b == helper.j)) ?
         Color::WHITE : color_lerp(Color::FOREST, Color::PURPLE, (float)(vector[b] - 1) / vector.get_length());

      ctx.fillRect((int)ceil(start), 0, (int)ceil(helper.bar_width), (int)(helper.aspect_height * vector[b]), color);
      start += helper.bar_width;
   }
}

void update_double_selection_sort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (helper.i = 0, helper.j = vector.get_length() - 1; helper.i < helper.j; helper.i++, helper.j--) {

      helper.lmin = helper.i;
      helper.lmax = helper.i;

      for (helper.k = helper.i + 1; helper.k <= helper.j; helper.k++) {
         if (vector[helper.lmin] > vector[helper.k]) helper.lmin = helper.k;
         else if (vector[helper.lmax] < vector[helper.k]) helper.lmax = helper.k;

         do if (!window.windowProcess(1.f)) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);
      }

      if (helper.lmin != helper.i) swap(vector[helper.lmin], vector[helper.i]);
      if (helper.lmax == helper.i) { if (helper.lmin != helper.j) swap(vector[helper.lmin], vector[helper.j]); }
      else if (helper.lmax != helper.j) swap(vector[helper.lmax], vector[helper.j]);
   }
}

void show_double_selection_sort(Vector& vector) {

   using namespace Win32API;
   RenderState& ctx = Window::getInstance().getContext();

   if (!vector.is_sorted()) {
      sprintf(helper.text, "Current Comparasion: %d > %d | %d < %d",
         vector[helper.lmin], vector[helper.k], vector[helper.lmax], vector[helper.k]);
      ctx.fillText(0, ctx.height() - 0x6E, 25, Color::WHITE, Alignment::VALIGN_END, helper.text);
   }

   float start = 0;
   for (ulong b = 0; b < vector.get_length(); b++) {

      clr color = (!vector.is_sorted() && (b == helper.lmin || b == helper.lmax || b == helper.k)) ?
         Color::WHITE : color_lerp(Color::FOREST, Color::PURPLE, (float)(vector[b] - 1) / vector.get_length());

      ctx.fillRect((int)ceil(start), 0, (int)ceil(helper.bar_width), (int)(helper.aspect_height * vector[b]), color);
      start += helper.bar_width;
   }
}

void update_heapsort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (helper.i = vector.get_length(), helper.j = helper.i >> 1; helper.i > 1;) {

      if (helper.j > 0) helper.j--;
      else {
         helper.i--;
         swap(vector[helper.i], vector[0]);
      }

      ulong root = helper.j;

      for (ulong child = (root << 1) + 1; child < helper.i; child = (root << 1) + 1) {

         if (child + 1 < helper.i && vector[child] < vector[child + 1])
            child++;

         if (vector[root] < vector[child]) {
            if (root != child)
               swap(vector[root], vector[child]);
            
            helper.lmax = root;
            helper.lmin = child;
            
            do if (!window.windowProcess(1.f)) exit(0);
            while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);
            
            root = child;
         }

         else break;

      }
   }
}

void show_heapsort(Vector& vector) {

   using namespace Win32API;
   RenderState& ctx = Window::getInstance().getContext();

   if (!vector.is_sorted()) {
      sprintf(helper.text, "Current Comparasion: %lu %lu %lu %lu", helper.i, helper.j, helper.lmin, helper.lmax);
      ctx.fillText(0, ctx.height() - 0x6E, 25, Color::WHITE, Alignment::VALIGN_END, helper.text);
   }

   float start = 0;
   for (ulong b = 0; b < vector.get_length(); b++) {

      clr color = (!vector.is_sorted() && (b == helper.i || b == helper.j || b == helper.lmin || b == helper.lmax)) ?
         Color::WHITE : color_lerp(Color::FOREST, Color::PURPLE, (float)(vector[b] - 1) / vector.get_length());

      ctx.fillRect((int)ceil(start), 0, (int)ceil(helper.bar_width), (int)(helper.aspect_height * vector[b]), color);
      start += helper.bar_width;
   }
}