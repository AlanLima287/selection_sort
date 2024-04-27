#include <stdio.h>
#include <iostream>
#include <random>
#include <time.h>

#include "./Win32API/Win32API.h"
#include "selection_sorts.cpp"
#include "update.cpp"

using Win32API::Window;

static Vector vector;

int main(int argc, char** argv) {

   if (argc < 3) return 1;

   ulong size = atoi(argv[1]);
   if (0 >= size || size >= 1024) return 1;

   if (argv[3][0] == '-') switch (argv[3][1]) {

      case 'r':
         vector.populate(size, (ulong)time(0), ListingStyle::RANDOM);
         break;

      case 'm':
         if (argv[3][2] == 'o') vector.populate(size, (ulong)time(0), ListingStyle::MOSTLY_ORDERED);
         else vector.populate(size, (ulong)time(0), ListingStyle::MOSTLY_INVERSED);
         break;

      case 'i':
         vector.populate(size, 0, ListingStyle::INVERSED);
         break;

      case 'o':
         vector.populate(size, 0, ListingStyle::ORDERED);
         break;

      default: return 1;
   }

   if (argv[2][0] == '-') switch (argv[2][1]) {

      case 's':
         strcpy(helper.name, "Selection Sort");
         helper.sorter = &update_selection_sort;
         helper.display = &show_selection_sort;
         break;

      case 'd':
         strcpy(helper.name, "Double Selection Sort");
         helper.sorter = &update_double_selection_sort;
         helper.display = &show_double_selection_sort;
         break;

      case 'h':
         strcpy(helper.name, "Heapsort");
         helper.sorter = &update_heapsort;
         helper.display = &show_heapsort;
         break;

      default: return 1;
   }

   Window& window = Window::getInstance();
   window.setInstanceName("Selection Sort");
   window.getContext().setFont("assets/Consola8.ftmp");
   window.launchWindow(SW_SHOWMAXIMIZED, false, true);

   Win32API::Input& input = window.getInput();

   for (helper.i = 0; helper.i < vector.get_length() - 1; helper.i++) {

      helper.lmin = helper.i;

      for (helper.j = helper.i + 1; helper.j < vector.get_length(); helper.j++) {
         if (vector[helper.lmin] > vector[helper.j]) helper.lmin = helper.j;

         while (vector.is_sorted() || (!input.keyboard.pressed(VK_RIGHT) && !helper.go)) {
            if (!window.windowProcess(1.f)) return 0;
         }
      }

      if (helper.lmin != helper.i)
         swap(vector[helper.lmin], vector[helper.i]);
   }

   return 0;
}

void Win32API::Window::update(float deltaTime) {

   if (input.keyboard.pressed(VK_RETURN)) helper.go ^= true;

   ctx.fillBackground(Color::BLACK);
   ctx.fillText(0, ctx.height() - 0x2, 27, Color::WHITE, Alignment::VALIGN_END, helper.name);

   sprintf(helper.text, "Comparasions: %lu", helper.comparisons);
   ctx.fillText(0, ctx.height() - 0x25, 25, Color::WHITE, Alignment::VALIGN_END, helper.text);

   sprintf(helper.text, "Swaps: %lu", helper.swaps);
   ctx.fillText(0, ctx.height() - 0x45, 25, Color::WHITE, Alignment::VALIGN_END, helper.text);

   helper.display(vector);
}

void Win32API::Window::resize() {
   helper.bar_width = (float)ctx.width() / vector.get_length();
   helper.aspect_height = (float)ctx.height() * 0.8f / vector.get_length();
}
