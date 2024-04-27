#include "./Win32API/Win32API.h"
#include "selection_sorts.cpp"

struct Helper {
   ulong i, j, k, lmin, lmax;

   ulong comparisons, swaps;
   char name[255], text[255];

   float aspect_height, bar_width;
   bool go;

   void (*sorter)(Vector&);
   void (*display)(Vector&);

} helper{
   (ulong)~0, (ulong)~0, (ulong)~0, (ulong)~0,
   (ulong)~0, (ulong)~0, (ulong)~0,
   "", "", .0f,.0f, false, 
   nullptr, nullptr
};

void update_selection_sort(Vector& vector) {

   for (; helper.i < vector.get_length() - 1; helper.i++) {

      helper.lmin = helper.i;

      for (; helper.j < vector.get_length(); helper.j++) {
         if (vector[helper.lmin] > vector[helper.j]) helper.lmin = helper.j;

         return;
      }

      helper.j = helper.i + 1;
      if (helper.lmin != helper.i)
         swap(vector[helper.lmin], vector[helper.i]);
   }
}

// void update_selection_sort(Vector& vector) {

//    helper.comparisons++;

//    if (helper.i < vector.get_length() - 1) {

//       if (vector[helper.lmin] > vector[helper.j]) {
//          helper.lmin = helper.j;
//       }

//       helper.j++;

//       if (helper.j >= vector.get_length()) {

//          helper.comparisons++;

//          if (helper.lmin != helper.i) {
//             swap(vector[helper.lmin], vector[helper.i]);
//             helper.swaps++;
//          }

//          helper.i++;
//          helper.j = helper.i + 1;
//          helper.lmin = helper.i;
//       }

//       helper.comparisons += 2;
//    }

//    else vector.set_sorted(true);
// } 

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

   helper.comparisons++;

   if (helper.i < helper.j) {

      if (vector[helper.lmin] > vector[helper.k])
         helper.lmin = helper.k;

      else if (vector[helper.lmax] < vector[helper.k])
         helper.lmax = helper.k;

      helper.k++;

      if (helper.k > helper.j) {

         if (helper.lmin != helper.i) {
            swap(vector[helper.lmin], vector[helper.i]);
            helper.swaps++;
         }

         if (helper.lmax == helper.i) {

            if (helper.lmin != helper.j) {
               swap(vector[helper.lmin], vector[helper.j]);
               helper.swaps++;
            }

         }
         else if (helper.lmax != helper.j) {
            swap(vector[helper.lmax], vector[helper.j]);
            helper.swaps++;
         }

         helper.comparisons += 3;

         helper.i++;
         helper.j--;
         helper.k = helper.i + 1;

         helper.lmin = helper.i;
         helper.lmax = helper.i;
      }

      helper.comparisons += 3;
   }

   else vector.set_sorted(true);
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

   if (helper.i > 1) {

      if (helper.lmin < helper.i) {

         if (helper.lmin + 1 < helper.i && vector[helper.lmin] < vector[helper.lmin + 1])
            helper.lmin++;

         if (vector[helper.lmax] < vector[helper.lmin]) {
            if (helper.lmax != helper.lmin)
               swap(vector[helper.lmax], vector[helper.lmin]);
            helper.lmax = helper.lmin;
         }

         else {
            if (helper.j > 0) helper.j--;
            else {
               helper.i--;
               swap(vector[helper.i], vector[0]);
            }

            helper.lmax = helper.j;
            helper.lmin = (helper.lmax << 1) + 1;

            return;
         }

         helper.lmin = (helper.lmax << 1) + 1;
      }
      else {
         if (helper.j > 0) helper.j--;
         else {
            helper.i--;
            swap(vector[helper.i], vector[0]);
         }

         helper.lmax = helper.j;
         helper.lmin = (helper.lmax << 1) + 1;
      }

   }
   else vector.set_sorted(true);
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