#include "utils.cpp"

struct nod {
  Articol info;
  nod* next;
  nod* prev;
};

// adaugare articol in dublu inlantuita circulara
nod* adaugaArticol(nod* cap, int pos, Articol articol) {
  nod* temp = (nod*)malloc(sizeof(nod));
  temp->info = deepCopy(articol);
  // nu avem cap
  if (!cap) {
    temp->next = temp;
    temp->prev = temp;
    return temp;
  }
  // inseram pe pozitia 0 (inceput)
  if (pos == 0) {
    temp->prev = cap;
    temp->next = cap;
    cap->prev = temp;
    return temp;
  }
  // mergem prin lista pana cand ajungem la capat sau la pozitie
  nod* curent = cap;
  int i = 0;
  while (curent->next != cap && pos != i) {
    curent=curent->next; i++;
  }
  // verificam daca suntem la sfarsit
  if (curent->next == cap) {
    // inserare la sfarsit
    temp->next   = cap;
    temp->prev   = curent;
    curent->next = temp;
    cap->prev    = temp;
  } else {
    // inserare pe pozitie
    temp->next   = curent;
    temp->prev   = curent->prev;
    curent->prev = temp;
  }
  return cap;
}

nod* citesteArticole(nod* cap, char* f_name, int items) {
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

  nod* cap = NULL;

  // citire articole in lista
  cap = citesteArticole(cap, f_name, items);

  // lista circulara, parcurgere si afisare in ambele sensuri
  nod* curent = cap;

  // parcurgem pana la mijloc
  for (int i=0; i<items/2; i++) curent=curent->next;
  nod* pos = curent;

  printf("Lista circulara, parcurgere pe next:\n");
  do {
    afiseazaArticol(curent->info);
    curent = curent->next;
    if (curent == pos) break;
  } while(true);

  printf("Lista circulara, parcurgere pe prev:\n");
  do {
    afiseazaArticol(curent->info);
    curent = curent->prev;
    if (curent == pos) break;
  } while(true);

  // cleanup
  curent = cap;
  do {
    free(curent->info.nume);
    if (curent->next != cap) {
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
