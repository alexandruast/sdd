#include "utils.cpp"

int queueLevel = 0;
int queueSize = 5;

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

bool isEmpty(Articol* queue) {
  if (queueLevel == 0) return true;
  return false;
}

bool isFull(Articol* queue) {
  if (queueLevel == queueSize) return true;
  return false;
}

bool push(Articol articol, Articol* queue) {
  if (! isFull(queue)) {
    queue[queueLevel] = deepCopy(articol);
    queueLevel++;
    return true;
  }
  return false;
}

bool pop(Articol* queue) {
  if (! isEmpty(queue)) {
    queueLevel--;
    free(queue[0].nume);
    queue[0].id = NULL;
    queue[0].marime = NULL;
    for (int i=0; i<queueLevel; i++) {
      queue[i] = queue[i+1];
    }
    return true;
  }
  return false;
}

Articol* peek(Articol* queue) {
  if (! isEmpty(queue)) {
    return &queue[0];
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

  // initializare queue
  Articol* queue = (Articol*)malloc(sizeof(Articol)*queueSize+1);

  // adaugare articole in queue
  printf("Se adauga articole in queue.\n");
  for (int i=0; i<items; i++) {
    if (!push(articole[i], queue))
      printf("Articolul %d %s %0.2f nu a putut fi introdus in queue!\n", articole[i].id,  articole[i].nume, articole[i].marime);
  }
  printf("Dimensiunea queue este de %d articole.\n", queueLevel);

  // ne uitam la articolul de la capatul queue-ului
  printf("Articol la capatul queue-ului:\n");
  afiseazaArticol(*peek(queue));

  // stergere articol
  printf("S-a sters un articol din queue.\n");
  pop(queue);

  // afisare queue
  printf("Dimensiunea queueului este de %d articole:\n", queueLevel);
  for (int i=0; i<queueLevel; i++) {
      afiseazaArticol(queue[i]);
  }

  // cleanup
  for (int i=0; i<items; i++) free(articole[i].nume);
  free(articole);
  for (int i=0; i<queueLevel; i++) free(queue[i].nume);
  free(queue);
  printf("Sfarsit demonstratie.\n");
  return 0;
}
