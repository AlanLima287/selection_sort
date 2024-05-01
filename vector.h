#pragma once

#include <random>

typedef unsigned long ulong;

#ifndef __XOR_SWAP__
#define __XOR_SWAP__

/* Warning! If the values have the same address, it will end up setting both to 0 */
inline void swap(int& a, int& b) {
   a ^= b; b ^= a; a ^= b;
}

#endif

enum ListingStyle {
   RANDOM,
   ORDERED,
   INVERSED,
   MOSTLY_ORDERED,
   MOSTLY_INVERSED,
};

class Vector {

   int* vector;
   ulong length;
   bool sorted;

public:

   Vector() : vector(nullptr), length(0), sorted(false) {}

   Vector(ulong size, ulong seed) : sorted(false) {
      populate(size, seed);
   }

   Vector(const Vector&) = delete;
   Vector operator=(const Vector&) = delete;

   ~Vector() {
      if (vector) delete[] vector;
   }

   void populate(ulong size, ulong seed, ulong style = ListingStyle::RANDOM) {

      srand(seed);

      vector = new int[size];
      length = size;

      switch (style) {
         case ListingStyle::RANDOM:

            for (ulong i = 0; i < size; i++)
               vector[i] = i + 1;

            for (ulong i = 0; i < size; i++) {
               ulong index = (ulong)(((float)rand() / (RAND_MAX + 1)) * size);
               if (i != index) swap(vector[i], vector[index]);
            }

            break;

         case ListingStyle::ORDERED:
            for (ulong i = 0; i < size; i++)
               vector[i] = i + 1;
            break;

         case ListingStyle::INVERSED:
            for (ulong i = 0; i < size; i++)
               vector[i] = size - i;
            break;

         case ListingStyle::MOSTLY_ORDERED:

            for (ulong i = 0; i < size; i++)
               vector[i] = i + 1;

            for (ulong i = 0; i < size; i++) {
               ulong index = i - 0x7 + (rand() & 0xf);

               if (0 <= index && index < length && i != index)
                  swap(vector[i], vector[index]);
            }

            break;

         case ListingStyle::MOSTLY_INVERSED:

            for (ulong i = 0; i < size; i++)
               vector[i] = size - i;

            for (ulong i = 0; i < size; i++) {
               ulong index = i - 0x7 + (rand() & 0xf);

               if (0 <= index && index < length && i != index)
                  swap(vector[i], vector[index]);
            }

            break;

         default: throw;
      }
   }

   inline int& operator[](ulong index) {
      return vector[index];
   }

   inline bool is_sorted() const {
      return sorted;
   }

   inline void set_sorted(bool sorted) {
      this->sorted = sorted;
   }

   bool check_sorted() {
      for (ulong i = 1; i < length; i++)
         if (vector[i - 1] > vector[i]) {
            sorted = false;
            return false;
         }

      sorted = true;
      return true;
   }

   inline ulong get_length() const {
      return length;
   }

};