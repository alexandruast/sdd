#include "utils.cpp"

void adaugaArticol(Articol* heap, Articol articol, int i) {
  // nu avem radacina
  if (heap[i].id == NULL) {
    heap[i] = deepCopy(articol);
    return;
  }
  if (articol.id <= heap[i].id) {
  adaugaArticol(heap, articol, 2*i+1);
}
  if (articol.id > heap[i].id) {
    adaugaArticol(heap, articol, 2*i+2);
  }
}

Articol* citesteArticole(Articol* heap, char* f_name, int items) {
  // citire din fisier
  FILE* f = fopen(f_name,"r");
  Articol articol;
  for (int i=0; i<items; i++) {
    articol = citesteArticol(f);
    adaugaArticol(heap, articol,i);
    afiseazaArticol(articol);
  }
  fclose(f);
  return heap;
}

void swap(Articol* heap, int x, int y) {
  Articol temp = heap[x];
  heap[x] = heap[y];
  heap[y] = temp;
}

void maxHeapify(Articol* heap, int heapSize, int root) {
  int st = 2*root + 1;
  int dr = 2*root + 2;
  int max = root;
  if (st <= heapSize - 1 && heap[st].id  > heap[root].id) {
    max = st;
  } else {
    max = root;
  }
  if (dr <= heapSize - 1 && heap[dr].id  > heap[max].id) {
    max = dr;
  }

  if (max != root) {
    swap(heap, root, max);
    maxHeapify(heap, heapSize, max);
  }
}

void minHeapify(Articol* heap, int heapSize, int root) {
  int st = 2*root + 1;
  int dr = 2*root + 2;
  int min = root;
  if (st <= heapSize - 1 && heap[st].id !=0 && heap[st].id  < heap[root].id) {
    min = st;
  } else {
    min = root;
  }
  if (dr <= heapSize - 1 && heap[dr].id !=0 && heap[dr].id  < heap[min].id) {
    min = dr;
  }

  if (min != root) {
    swap(heap, root, min);
    minHeapify(heap, heapSize, min);
  }
}

int main() {
  // arbore articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  int items = fileRecords(f_name);
  int heapSize = 1;
  while(heapSize < items) heapSize*=2;

  printf("heapSize:%d\n",heapSize);
  // citire articole din arbore
  Articol* heap = (Articol*)malloc(sizeof(Articol)*heapSize);
  for (int i=0; i<heapSize; i++) {
    heap[i].id = NULL;
    heap[i].marime = NULL;
  }
  printf("Citire valori in heap:\n");
  heap = citesteArticole(heap, f_name, items);

  // afisare arbore
  printf("Afisare structura arbore:\n");
  afisareArbore(NULL, heap, heapSize);

  // afisare MaxHeap
  printf("Afisare arbore dupa MaxHeap:\n");
  for (int i = heapSize/2 - 1; i>=0; i--) {
      maxHeapify(heap, heapSize, i);
  }
  afisareArbore(NULL, heap, heapSize);

  // afisare MinHeap
  printf("Afisare arbore dupa MinHeap:\n");
  for (int i = heapSize/2 - 1; i>=0; i--) {
      minHeapify(heap, heapSize, i);
  }
  afisareArbore(NULL, heap, heapSize);

  // cleanup
  for (int i=0; i<heapSize;i++){
    if (heap[i].id != NULL) {
      free(heap[i].nume);
    }
  }
  free(heap);

  printf("Sfarsit demonstratie.\n");
  return 0;
}
