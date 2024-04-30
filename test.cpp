#include <iostream>
#include <random>
#include <time.h>

#include "selection_sorts.cpp"

static Vector vector;

int main(int argc, char** argv) {

   if (argc < 2) return 1;

   ulong vector_size = atoi(argv[1]);
   if (0 >= vector_size || vector_size > 4096) return 1;

   ulong test_size = atoi(argv[2]);
   if (0 > test_size || test_size > 4096) return 1;

   size_t test_duration = 0;

   for (ulong i = test_size; i > 0; i--) {

      ulong seed = (ulong)time(0);
      vector.populate(vector_size, seed, ListingStyle::RANDOM);

      long start = clock();

      selection_sort(vector);

      long end = clock();
      test_duration += end - start;

      for (ulong j = 1; j < vector_size; j++) {
         if (vector[j - 1] >= vector[j]) {
            std::cout << "Error on the seed " << seed << " at the " << i << " / " << j << " step\n";
            return 0;
         }
      }
   }

   std::cout << "No error was found\n";
   std::cout << "Average execution time: " << (double)test_duration / test_size << "ms";

   return 0;
}