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