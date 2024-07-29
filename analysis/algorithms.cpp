typedef unsigned long ulong;

void swap(int& a, int& b) {
   int c = a; // c armazena a para que seu valor não seja perdido
   a = b; // a recebe b
   b = c; // b recebe o valor que pertencia a a
}

void selection_sort(int* vector, int length) {

   // para cada posição, itera-se uma vez, exceto a última, 
   // pois a ordenação de n - 1 elementos, implicará em ordenação total
   for (int i = 0; i < length - 1; i++) {

      int lmin = i; // o mínimo local é inicialmente dado por i

      // itera sobre a lista não ordenadada, de i + 1 até n
      for (int j = i + 1; j < length; j++) {

         // se o elemento no mínimo local é maior que elemento em j, 
         // então j será o novo mínimo local
         if (vector[lmin] > vector[j])
            lmin = j;
      }

      // após a iteração, lmin será um mínimo local verdadeiro
      // e este será posto no início da lista não ordenadada
      swap(vector[lmin], vector[i]);
   }
}

void insertion_sort(int* vector, ulong length) {

   for (ulong i = 1; i < length; i++) {

      for (ulong j = i; j > 0; j--) {
         if (vector[j - 1] > vector[j])
            swap(vector[j - 1], vector[j]);
         else break;
      }
   }
}

void bubble_sort(int* vector, ulong length) {

   bool swapped = true;

   for (ulong i = 0; i < length && swapped; i++) {

      swapped = false;

      for (ulong j = 0; j < length - i - 1; j++) {

         if (vector[j] > vector[j + 1]) {
            swap(vector[j], vector[j + 1]);
            swapped = true;
         }
      }
   }
}

void merge_sort(int* vector, ulong length) {

}

int partition(int* vector, ulong left, ulong right);
void quicksort(int* vector, ulong start, ulong end) {

   if (start >= end) return;

   ulong pivot = partition(vector, end, start);

   // ulong pivot = start;

   // for (ulong j = start; j < end; j++) {

   //    if (vector[j] <= vector[end]) {
   //       swap(vector[pivot], vector[j]);
   //       pivot++;
   //    }
   // }

   // swap(vector[pivot], vector[end]);

   quicksort(vector, start, pivot - 1);
   quicksort(vector, pivot + 1, end);
}

int partition(int* vector, ulong left, ulong right) {

   int pivot = vector[left];
   ulong i = left;

   for (int j = left + 1; j <= right; j++) {
      if (vector[j] <= pivot) {
         i += 1;
         swap(vector[i], vector[j]);
      }
   }

   swap(vector[left], vector[i]);

   return i;
}

void double_selection_sort(int* vector, ulong length) {

   for (ulong i = 0, j = length - 1; i < j; i++, j--) {

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

void heapsort(int* vector, ulong length) {

   for (ulong end = length, start = end >> 1; end > 1;) {

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

void cycle_sort(int* vector, ulong length) {

   for (ulong i = 0; i < length - 1; i++) {

      int item = vector[i];
      int pos = i;

      for (ulong j = i + 1; j < length; j++)
         if (vector[j] < item) pos++;

      if (pos == i) continue;

      while (item == vector[pos]) pos++;

      swap(item, vector[pos]);

      while (pos != i) {

         pos = i;

         for (ulong j = i + 1; j < length; j++)
            if (vector[j] < item) pos++;

         while (item == vector[pos]) pos++;

         swap(item, vector[pos]);
      }
   }
}