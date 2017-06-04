#include "utils.cpp"

struct nodLista {
  Articol info;
  nodLista* next;
  nodLista* prev;
};

// adaugare articol in lista
nodLista* adaugaArticol(nodLista* cap, int pos, Articol articol) {
  nodLista* temp = (nodLista*)malloc(sizeof(nodLista));
  temp->info = deepCopy(articol);
  // nu avem cap
  if (!cap) {
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
  }
  // inseram pe pozitia 0 (inceput)
  if (pos == 0) {
    temp->prev = NULL;
    temp->next = cap;
    cap->prev = temp;
    return temp;
  }
  // mergem prin lista pana cand ajungem la capat sau la pozitie
  nodLista* curent = cap;
  int i = 0;
  while (curent->next != NULL && pos != i) {
    curent=curent->next; i++;
  }
  // verificam daca suntem la sfarsit
  if (curent->next == NULL) {
    // inserare la sfarsit
    temp->next   = NULL;
    temp->prev   = curent;
    curent->next = temp;
  } else {
    // inserare pe pozitie
    temp->next = curent;
    temp->prev = curent->prev;
    curent->prev = temp;
  }
  return cap;
}

nodLista* citesteArticole(nodLista* cap, char* f_name, int items) {
  // citire din fisier
  FILE* f = fopen(f_name,"r");
  Articol articol;
  int pos = INT_MAX; // inserare la sfarsit
  for (int i=0; i<items; i++) {
    articol = citesteArticol(f);
    cap = adaugaArticol(cap, pos, articol);
  }
  fclose(f);
  return cap;
}

int main() {

  // lista articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  int items = fileRecords(f_name);

  nodLista* cap = NULL;

  // citire articole in lista
  cap = citesteArticole(cap, f_name, items);

  // lista dubla inlantuita, parcurgere si afisare in ambele sensuri
  nodLista* curent = cap;

  printf("Lista dublu inlantuita, parcurgere pe next:\n");
  do {
    afiseazaArticol(curent->info);
    if (curent->next) curent = curent->next; else break;
  } while(true);

  printf("Lista dublu inlantuita, parcurgere pe prev:\n");
  do {
    afiseazaArticol(curent->info);
    if (curent->prev) curent = curent->prev; else break;
  } while(true);

  // cleanup
  curent = cap;
  do {
    free(curent->info.nume);
    if (curent->next) {
      curent = curent->next;
      free(curent->prev);
    } else {
      free(curent);
      break;
    }
  } while(true);

  printf("Sfarsit demonstratie.\n");
  return 0;
}
