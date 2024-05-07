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

void selection_sort_ex(int* vector, int length) {

   int i = 0;
   while (i < length - 1) {
      
      int lmin = i;
      
      int j = i + 1;
      while (j < length) {
         if (vector[lmin] > vector[j]) 
            lmin = j;

         j++;
      }

      //swap(vector[lmin], vector[i]); 
      {
         int c = vector[lmin]; 
         vector[lmin] = vector[i]; 
         vector[i] = c;
      }

      i++;
   }
}
