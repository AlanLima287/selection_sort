typedef unsigned long ulong;

void swap(int& a, int& b) {
   a ^= b; b ^= a; a ^= b;
}

void selection_sort(int* vector, ulong length) {

   for (ulong i = 0; i < length - 1; i++) {

      ulong lmin = i;

      for (ulong j = i + 1; j < length; j++) {
         if (vector[lmin] > vector[j]) lmin = j;
      }

      if (lmin != i)
         swap(vector[lmin], vector[i]);
   }
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