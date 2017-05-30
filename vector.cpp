#include "utils.cpp"

// citire articole intr-un vector
Articol* citesteArticole(char* f_name, int items) {
  // alocare memorie vector articole
  Articol* articole = (Articol*)malloc(sizeof(Articol)*items);
  // citire din fisier
  FILE* f = fopen(f_name,"r");
  for (int i=0; i<items; i++) {
    articole[i] = citesteArticol(f);
  }
  fclose(f);
  return articole;
}

int main() {

  // vector int
  int items = 10;
  // alocare memorie vector
  int* v = (int*)malloc(sizeof(int)*items);
  // parcurgere si setare valori (0 - 255 random)
  for (int i=0; i<items; i++) {
    v[i] = rand() % 255;
  }
  // parcurgere si afisare valori
  for (int i=0; i<items; i++) {
    printf("%d\t",v[i]);
    if (i == items-1) printf("\n");
  }

  // vector articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  items = fileRecords(f_name);
  // citire articole in vector
  Articol* articole = citesteArticole(f_name, items);
  // afisare articole din vector
  printf("Vector articole, afisare:\n");
  for (int i=0; i<items; i++) afiseazaArticol(articole[i]);

  // cleanup
  free(v);
  for (int i=0; i<items; i++) free(articole[i].nume);
  free(articole);

  printf("Sfarsit demonstratie.\n");
  return 0;
}
