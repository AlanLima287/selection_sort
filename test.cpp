#include <iostream>
#include <random>
#include <time.h>

#include "selection_sorts.cpp"

static Vector vector;

int main(int argc, char** argv) {

   if (argc < 2) return 1;

   ulong size = atoi(argv[1]);
   if (0 >= size || size >= 1024) return 1;

   for (int i = atoi(argv[2]); i > 0; i--) {
      ulong seed = (ulong)time(0);
      vector.populate(size, seed, ListingStyle::RANDOM);
      heapsort(vector);

      for (int j = 1; j < size; j++) {
         if (vector[j - 1] >= vector[j]) {
            std::cout << "Error on the seed " << seed << " at the " << i << " / " << j << " step\n";
            return 0;
         }
      }
   }

   std::cout << "No error was found";
 
   return 0;
}