#include "utils.cpp"

int stackLevel = 0;
int stackSize = 5;

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

bool isEmpty(Articol* stack) {
  if (stackLevel == 0) return true;
  return false;
}

bool isFull(Articol* stack) {
  if (stackLevel == stackSize) return true;
  return false;
}

bool push(Articol articol, Articol* stack) {
  if (! isFull(stack)) {
    stack[stackLevel] = deepCopy(articol);
    stackLevel++;
    return true;
  }
  return false;
}

bool pop(Articol* stack) {
  if (! isEmpty(stack)) {
    stackLevel--;
    free(stack[stackLevel].nume);
    stack[stackLevel].id = NULL;
    stack[stackLevel].marime = NULL;
    return true;
  }
  return false;
}

Articol* peek(Articol* stack) {
  if (! isEmpty(stack)) {
    return &stack[stackLevel-1];
  }
  return NULL;
}

int main() {

  // citire articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  int items = fileRecords(f_name);
  // citire articole in vector
  Articol* articole = citesteArticole(f_name, items);
  // afisare articole din vector
  printf("Vector articole, afisare:\n");
  for (int i=0; i<items; i++) afiseazaArticol(articole[i]);

  // initializare stack
  Articol* stack = (Articol*)malloc(sizeof(Articol)*stackSize+1);

  // adaugare articole in stack
  printf("Se adauga articole in stack.\n");
  for (int i=0; i<items; i++) {
    if (!push(articole[i], stack))
      printf("Articolul %d %s %0.2f nu a putut fi introdus in stack!\n", articole[i].id,  articole[i].nume, articole[i].marime);
  }
  printf("Marimea stackului este de %d articole.\n", stackLevel);

  // ne uitam la articolul de la capatul stack-ului
  printf("Articol la capatul stack-ului:\n");
  afiseazaArticol(*peek(stack));

  // stergere articol
  printf("S-a sters un articol din stack.\n");
  pop(stack);

  // afisare stack
  printf("Marimea stackului este de %d articole:\n", stackLevel);
  for (int i=0; i<stackLevel; i++) {
      afiseazaArticol(stack[i]);
  }

  // cleanup
  for (int i=0; i<items; i++) free(articole[i].nume);
  free(articole);
  for (int i=0; i<stackLevel; i++) free(stack[i].nume);
  free(stack);
  printf("Sfarsit demonstratie.\n");
  return 0;
}
