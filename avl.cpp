#include "utils.cpp"

int inaltime;

int factorEchilibru(nod* root) {
  return (inaltimeArbore(root->st) - inaltimeArbore(root->dr));
}

nod* rotatieStanga(nod* root) {
  nod* pivot = root->dr;
  root->dr = pivot->st;
  pivot->st = root;
  return pivot;
}

nod* rotatieDreapta(nod* root) {
  nod* pivot = root->st;
  root->st = pivot->dr;
  pivot->dr = root;
  return pivot;
}

nod* adaugaArticol(nod* root, Articol articol){
  nod* temp = (nod*)malloc(sizeof(nod));
  temp->info = deepCopy(articol);
  // nu avem radacina
  if (!root) {
    temp->st = NULL;
    temp->dr = NULL;
    return temp;
  }

  if (articol.id <= root->info.id) {
    root->st = adaugaArticol(root->st, articol);
  }

  if (articol.id > root->info.id) {
    root->dr = adaugaArticol(root->dr, articol);
  }

  if (factorEchilibru(root) == 2) {
    if (factorEchilibru(root->st) == -1) {
      root = rotatieStanga(root->st);
    } else {
      root = rotatieDreapta(root);
    }
  }

  if (factorEchilibru(root) == -2) {
    if (factorEchilibru(root->dr) == 1) {
      root = rotatieDreapta(root->dr);
    } else {
      root = rotatieStanga(root);
    }
  }

  return root;
}

nod* citesteArticole(nod* root, char* f_name, int items) {
  // citire din fisier
  FILE* f = fopen(f_name,"r");
  Articol articol;
  for (int i=0; i<items; i++) {
    articol = citesteArticol(f);
    root = adaugaArticol(root, articol);
    afiseazaArticol(articol);
  }
  fclose(f);
  return root;
}

int main() {
  // arbore articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  int items = fileRecords(f_name);

  // citire articole din arbore
  nod* root = NULL;
  printf("Citire valori in arbore:\n");
  root = citesteArticole(root, f_name, items);

  // afisare avl
  printf("Afisare structura arbore AVL:\n");
  afisareArbore(root);

  // cleanup
  freeTree(root);

  printf("Sfarsit demonstratie.\n");
  return 0;
}
