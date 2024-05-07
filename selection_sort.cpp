void swap(int& a, int& b) {
   int c = a; a = b; b = c;
}

void selection_sort(int* vector, int length) {

   for (int i = 0; i < length - 1; i++) {

      int lmin = i;

      for (int j = i + 1; j < length; j++) {
         if (vector[lmin] > vector[j]) lmin = j;
      }

      swap(vector[lmin], vector[i]);
   }
}

// Para Luiz Felipe | Análise de Complexidade

#include <iostream>
#include <random>
#include <time.h>

enum RandomizationStyle {
   RANDOM,
   ORDERED,
   INVERSED,
   MOSTLY_ORDERED,
   MOSTLY_INVERSED,
};

void populate(int* vector, int length, int seed, int style = RandomizationStyle::RANDOM) {

   srand(seed);

   switch (style) {
      case RandomizationStyle::RANDOM:

         for (int i = 0; i < length; i++)
            vector[i] = i + 1;

         for (int i = 0; i < length; i++) {
            int index = (int)(((float)rand() / (RAND_MAX + 1)) * length);
            if (i != index) swap(vector[i], vector[index]);
         }

         break;

      case RandomizationStyle::ORDERED:
         for (int i = 0; i < length; i++)
            vector[i] = i + 1;
         break;

      case RandomizationStyle::INVERSED:
         for (int i = 0; i < length; i++)
            vector[i] = length - i;
         break;

      case RandomizationStyle::MOSTLY_ORDERED:

         for (int i = 0; i < length; i++)
            vector[i] = i + 1;

         for (int i = 0; i < length; i++) {
            int index = i - 0x7 + (rand() & 0xf);

            if (0 <= index && index < length && i != index)
               swap(vector[i], vector[index]);
         }

         break;

      case RandomizationStyle::MOSTLY_INVERSED:

         for (int i = 0; i < length; i++)
            vector[i] = length - i;

         for (int i = 0; i < length; i++) {
            int index = i - 0x7 + (rand() & 0xf);

            if (0 <= index && index < length && i != index)
               swap(vector[i], vector[index]);
         }

         break;

      default: throw;
   }
}

int main(int argc, char** argv) {

   int length;
   std::cout << "Tamanho do vetor: "; std::cin >> length;

   if (0 >= length || length > 8192) return 1;

   int* vector = new int[length];
   populate(vector, length, (int)time(0), RandomizationStyle::RANDOM);

   // Selection sort aqui

   for (int i = 0; i < length - 1; i++) {

      int lmin = i;

      for (int j = i + 1; j < length; j++) {
         if (vector[lmin] > vector[j]) lmin = j;
      }

      // para visualização apenas
      for (int i = 0; i < length; i++)
         std::cout << vector[i] << ' ';
      std::cout << '\n';
      std::cin.get();

      swap(vector[lmin], vector[i]);
   }

   // fim do selection sort

   for (int i = 0; i < length; i++)
      std::cout << vector[i] << ' ';

   delete[] vector;
   return 0;
}
