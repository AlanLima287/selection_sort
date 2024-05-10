#include <iostream>
#include <random>
#include <time.h>
#include <fstream>

#include "algorithms.cpp"

enum ListingStyle {
   RANDOM,
   ORDERED,
   INVERSED,
   MOSTLY_ORDERED,
   MOSTLY_INVERSED,
};

void populate(int* vector, ulong length, ulong seed, ulong style = ListingStyle::RANDOM) {

   srand(seed);

   switch (style) {
      case ListingStyle::RANDOM:

         for (ulong i = 0; i < length; i++)
            vector[i] = i + 1;

         for (ulong i = 0; i < length; i++) {
            ulong index = (ulong)(((float)rand() / (RAND_MAX + 1)) * length);
            if (i != index) swap(vector[i], vector[index]);
         }

         break;

      case ListingStyle::ORDERED:
         for (ulong i = 0; i < length; i++)
            vector[i] = i + 1;
         break;

      case ListingStyle::INVERSED:
         for (ulong i = 0; i < length; i++)
            vector[i] = length - i;
         break;

      case ListingStyle::MOSTLY_ORDERED:

         for (ulong i = 0; i < length; i++)
            vector[i] = i + 1;

         for (ulong i = 0; i < length; i++) {
            ulong index = i - 0x7 + (rand() & 0xf);

            if (0 <= index && index < length && i != index)
               swap(vector[i], vector[index]);
         }

         break;

      case ListingStyle::MOSTLY_INVERSED:

         for (ulong i = 0; i < length; i++)
            vector[i] = length - i;

         for (ulong i = 0; i < length; i++) {
            ulong index = i - 0x7 + (rand() & 0xf);

            if (0 <= index && index < length && i != index)
               swap(vector[i], vector[index]);
         }

         break;

      default: throw;
   }
}

int main(int argc, char** argv) {

   const ulong max_test_size = 10000;
   const ulong test_rigor = 10;

   const ulong step_size = 100;
   const ulong seed = (ulong)time(0);

   int* vector = new int[max_test_size];

   for (ulong i = step_size; i <= max_test_size; i += step_size) {

      size_t test_duration = 0;

      for (ulong j = 0; j < test_rigor; j++) {

         populate(vector, i, seed, ListingStyle::RANDOM);

         long start = clock();

         selection_sort(vector, i);

         test_duration += clock() - start;

         // for (ulong k = 1; k < i; k++) {
         //    if (vector[k - 1] >= vector[k]) {
         //       std::cout << "Error on the seed " << seed << " at the " << i << " / " << k << " step\n";
         //       return 0;
         //    }
         // }
      }

      std::cout << i << ';' << (double)test_duration / 10 << '\n';
   }

   delete[] vector;
   return 0;
}