#include "./Win32API/Win32API.h"
#include "vector.h"

struct Helper {
   ulong i, j, lmin;

   char name[255], text[255];
   float aspect_height, bar_width;
   bool go;

   void (*sorter)(Vector&);
   void (*display)(Vector&);

} helper{
   (ulong)~0, (ulong)~0, (ulong)~0,
   "", "", .0f, .0f, false,
   nullptr, nullptr
};

void update_selection_sort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (helper.i = 0; helper.i < vector.get_length() - 1; helper.i++) {

      helper.lmin = helper.i;

      for (helper.j = helper.i + 1; helper.j < vector.get_length(); helper.j++) {
         do if (!window.windowProcess()) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);

         if (vector[helper.lmin] > vector[helper.j])
            helper.lmin = helper.j;
      }

      swap_s(vector[helper.lmin], vector[helper.i]);
   }
}

void show_selection_sort(Vector& vector) {

   using namespace Win32API;
   RenderState& ctx = Window::getInstance().getContext();
   Input& input = Window::getInstance().getInput();

   if (!vector.is_sorted() && input.keyboard.isDown(VK_SHIFT)) {
      sprintf(helper.text, "%d < %d", vector[helper.j], vector[helper.lmin]);
      ctx.fillText(ctx.width() >> 1, (int)(ctx.height() * .9f), 50,
         (vector[helper.lmin] > vector[helper.j]) ? Color::FOREST : Color::RED, Alignment::HALIGN_CENTER, helper.text);
   }

   float start = 0;
   int half_bar_width = (int)helper.bar_width >> 1;
   for (ulong b = 0; b < vector.get_length(); b++) {

      clr color = (!vector.is_sorted() && (b == helper.lmin || b == helper.j)) ? Color::GRAY :
         color_lerp(Color::FOREST, Color::BLUE, (float)(vector[b] - 1) / vector.get_length());

      ctx.fillRect((int)ceil(start), 0, (int)ceil(helper.bar_width), (int)(helper.aspect_height * (1 + vector[b])), color);

      sprintf(helper.text, "%u", vector[b]);
      ctx.fillText((int)start + half_bar_width, 0, half_bar_width, Color::WHITE, Alignment::HALIGN_CENTER, helper.text);

      start += helper.bar_width;
   }
}

void update_double_selection_sort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (ulong i = 0, j = vector.get_length() - 1; i < j; i++, j--) {

      ulong lmin = i;
      ulong lmax = i;

      for (ulong k = i + 1; k <= j; k++) {
         if (vector[lmin] > vector[k]) lmin = k;
         else if (vector[lmax] < vector[k]) lmax = k;

         do if (!window.windowProcess(1.f)) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);
      }

      swap_s(vector[lmin], vector[i]);
      if (lmax == i) swap_s(vector[lmin], vector[j]);
      else swap_s(vector[lmax], vector[j]);
   }
}

void update_heapsort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (ulong i = vector.get_length(), j = i >> 1; i > 1;) {

      if (j > 0) j--;
      else {
         i--;
         swap_s(vector[i], vector[0]);
      }

      ulong root = j;

      for (ulong child = (root << 1) + 1; child < i; child = (root << 1) + 1) {

         if (child + 1 < i && vector[child] < vector[child + 1])
            child++;

         if (vector[root] < vector[child]) {

            do if (!window.windowProcess(1.f)) exit(0);
            while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);

            swap_s(vector[root], vector[child]);
            root = child;
         }

         else break;
      }
   }
}

void update_stable_selection_sort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (ulong i = 0; i < vector.get_length() - 1; i++) {

      ulong min = i;

      for (ulong j = i + 1; j < vector.get_length(); j++) {

         do if (!window.windowProcess(1.f)) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);

         if (vector[min] > vector[j]) min = j;
      }

      int key = vector[min];
      for (ulong k = min; k > i; k--) {
         vector[k] = vector[k - 1];
      }

      vector[i] = key;
   }
}

void update_cycle_sort(Vector& vector) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   for (ulong i = 0; i < vector.get_length() - 1; i++) {

      int item = vector[i];
      ulong pos = i;

      for (ulong j = i + 1; j < vector.get_length(); j++)
         if (vector[j] < item) pos++;

      if (pos == i) continue;

      while (item == vector[pos]) pos++;

      swap_s(item, vector[pos]);

      while (pos != i) {

         pos = i;

         for (ulong j = i + 1; j < vector.get_length(); j++)
            if (vector[j] < item) pos++;

         while (item == vector[pos]) pos++;

         do if (!window.windowProcess()) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);

         swap_s(item, vector[pos]);
      }
   }
}

void update_quicksort_ex(Vector& vector, ulong left, ulong right) {

   Win32API::Window& window = Win32API::Window::getInstance();
   Win32API::Input& input = window.getInput();

   if (left >= right) return;

   int p;
   {
      int pivot = vector[(left + right) >> 1];

      ulong i = left - 1;
      ulong j = right + 1;

      while (true) {

         // Move the left index to the right at least once and while the element at
         // the left index is less than the pivot
         do i++; while (vector[i] < pivot);

         // Move the right index to the left at least once and while the element at
         // the right index is greater than the pivot
         do j--; while (vector[j] > pivot);

         do if (!window.windowProcess()) exit(0);
         while (!input.keyboard.pressed(VK_RIGHT) && !helper.go);

         // If the indices crossed, return
         if (i >= j) {
            p = j;
            break;
         }

         swap_s(vector[i], vector[j]);
      }
   }

   update_quicksort_ex(vector, left, p);
   update_quicksort_ex(vector, p + 1, right);
}

void update_quicksort(Vector& vector) {
   update_quicksort_ex(vector, 0, vector.get_length() - 1);
}

void default_show(Vector& vector) {

   using namespace Win32API;
   RenderState& ctx = Window::getInstance().getContext();

   float start = 0;
   for (ulong b = 0; b < vector.get_length(); b++) {

      ctx.fillRect((int)ceil(start), 0, (int)ceil(helper.bar_width), (int)(helper.aspect_height * vector[b]),
         color_lerp(Color::FOREST, Color::PURPLE, (float)(vector[b] - 1) / vector.get_length()));

      start += helper.bar_width;
   }
}