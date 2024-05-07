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