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

void selection_sort(Vector& vector) {

   for (ulong i = 0; i < vector.get_length() - 1; i++) {

      ulong lmin = i;

      for (ulong j = i + 1; j < vector.get_length(); j++) {
         if (vector[lmin] > vector[j]) lmin = j;
      }

      if (lmin != i)
         swap(vector[lmin], vector[i]);
   }
}

void double_selection_sort(Vector& vector) {

   for (ulong i = 0, j = vector.get_length() - 1; i < j; i++, j--) {

      ulong lmin = i;
      ulong lmax = i;

      for (ulong k = i + 1; k <= j; k++) {
         if (vector[lmin] > vector[k]) lmin = k;
         else if (vector[lmax] < vector[k]) lmax = k;
      }

      if (lmin != i) swap(vector[lmin], vector[i]);
      if (lmax == i) { if (lmin != j) swap(vector[lmin], vector[j]); }
      else if (lmax != j) swap(vector[lmax], vector[j]);
   }
}

void heapsort(Vector& vector) {

   for (ulong end = vector.get_length(), start = end >> 1; end > 1;) {

      if (start > 0)
         start--;
      else { 
         end--;
         swap(vector[end], vector[0]);
      }

      ulong root = start;

      for (ulong child = (root << 1) + 1; child < end; child = (root << 1) + 1) {

         if (child + 1 < end && vector[child] < vector[child + 1])
            child++;

         if (vector[root] < vector[child]) {
            if (root != child)
               swap(vector[root], vector[child]);
            root = child;
         }

         else break;
      }
   }
}