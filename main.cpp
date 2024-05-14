#include <stdio.h>
#include <iostream>
#include <random>
#include <time.h>

#include "./Win32API/Win32API.h"
#include "update.cpp"
#include "vector.h"

using Win32API::Window;

static Vector vector;

int main(int argc, char** argv) {

   if (argc < 3) return 1;

   ulong size = atoi(argv[1]);
   if (0 >= size || size > 1024) return 1;

   ulong list_style = 1;

   if (argv[3][0] == '-') switch (argv[3][1]) {

      case 'r': list_style = ListingStyle::RANDOM; break;
      case 'i': list_style = ListingStyle::INVERSED; break;
      case 'o': list_style = ListingStyle::ORDERED; break;

      case 'm':
         if (argv[3][2] == 'o') list_style = ListingStyle::MOSTLY_ORDERED;
         else list_style = ListingStyle::MOSTLY_INVERSED;
         break;

      default: return 1;
   }
   else return 1;

   vector.populate(size, (ulong)time(0), list_style);

   if (argv[2][0] == '-') switch (argv[2][1]) {

      case 's':
         strcpy(helper.name, "Selection Sort");
         helper.sorter = &update_selection_sort;
         helper.display = &show_selection_sort;
         break;

      case 'd':
         strcpy(helper.name, "Double Selection Sort");
         helper.sorter = &update_double_selection_sort;
         helper.display = &default_show;
         break;

      case 'h':
         strcpy(helper.name, "Heapsort");
         helper.sorter = &update_heapsort;
         helper.display = &default_show;
         break;

      case 'c':
         strcpy(helper.name, "Cycle Sort");
         helper.sorter = &update_cycle_sort;
         helper.display = &default_show;
         break;

      case 't':
         strcpy(helper.name, "Stable Selection Sort");
         helper.sorter = &update_stable_selection_sort;
         helper.display = &default_show;
         break;

      default: return 1;
   }
   else return 1;

   Window& window = Window::getInstance();
   window.setInstanceName("Sorting Algorithms");
   window.getContext().setFont("assets/Consola16.ftmp");
   window.launchWindow(SW_SHOWMAXIMIZED, false, true);

   helper.sorter(vector);
   vector.set_sorted(true);

   while (window.windowProcess());
   
   return 0;
}

void Win32API::Window::update(float deltaTime) {

   if (input.keyboard.pressed(VK_RETURN)) helper.go = !helper.go;

   ctx.fillBackground(Color::WHITE);
   ctx.fillText(0, ctx.height(), 50, Color::BLACK, Alignment::VALIGN_END, helper.name);

   if (input.keyboard.isDown(VK_CONTROL)) Sleep(30);

   helper.display(vector);
}

void Win32API::Window::resize() {
   helper.bar_width = (float)ctx.width() / vector.get_length();
   helper.aspect_height = (float)ctx.height() * 0.8f / vector.get_length();
}
