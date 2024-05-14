typedef unsigned long ulong;

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

   bool has_swapped;

   do {

      has_swapped = false;

      for (ulong i = 1; i < length; i++) {

         if (vector[i - 1] > vector[i]) {
            swap(vector[i - 1], vector[i]);
            has_swapped = true;
         }
      }

   } while (has_swapped);
}

void merge_sort(int* vector, ulong length) {

   bool has_swapped;

   do {

      has_swapped = false;

      for (ulong i = 1; i < length; i++) {

         if (vector[i - 1] > vector[i]) {
            swap(vector[i - 1], vector[i]);
            has_swapped = true;
         }
      }

   } while (has_swapped);
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