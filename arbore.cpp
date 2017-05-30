#include "utils.cpp"

int recursions;

struct nod {
  Articol info;
  nod* st;
  nod* dr;
};

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
  return root;
}

Articol * cautaArticol(nod* root, int value) {
  recursions++;
  if (!root) return 0;
  if (value == root->info.id) return &root->info;
  if (value <= root->info.id) return cautaArticol(root->st, value);
  if (value > root->info.id) return cautaArticol(root->dr, value);
  return NULL;
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

  nod* root = NULL;

  // citire articole din arbore
  printf("Citire valori in arbore:\n");
  root = citesteArticole(root, f_name, items);
  while (true) {
    printf("Introduceti id-ul de cautat:");
    int id = NULL;
    recursions = 0;
    scanf("%d",&id);
    // iesire daca id = 0
    if (id == 0) break;
    Articol * p_articol = cautaArticol(root, id);
    printf("Parcurgeri recursive:%d\n",recursions);
    Articol articol;
    if (p_articol) {
      articol = * p_articol;
      afiseazaArticol(articol);
    } else {
      printf("Nodul nu a fost gasit!");
    }
  }
  // ToDo: desenare arbore ? :)

  printf("Sfarsit demonstratie.\n");
  return 0;
}
