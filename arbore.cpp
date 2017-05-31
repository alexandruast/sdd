#include "utils.cpp"
#include <math.h>

int inaltime;

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
  inaltime++;
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

int countNodes(nod* root, bool left=true) {
  int count = 0;
  if(root && left) {
    if (root->st) count ++;
    count += countNodes(root->st) + countNodes(root->dr);
  }
  if(root && !left) {
    if (root->dr) count ++;
    count += countNodes(root->dr, false) + countNodes(root->st, false);
  }
  return count;
}

void breadthFirst(nod* root, int* arbore, int index=0) {
  if(root) {
    arbore[index]=root->info.id;
    if(root->st) {
      breadthFirst(root->st, arbore, 2 * index + 1);
    }
    if(root->dr) {
      breadthFirst(root->dr, arbore, 2 * index + 2);
    }
  }
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

  int left = countNodes(root,true);
  int right = countNodes(root,false);
  int depth = (left > right) ? left : right;
  int elemente = pow(2,depth);
  int* arbore = (int*)malloc(sizeof(int)*elemente);
  for (int i=0; i<elemente; i++) {
      arbore[i] = 0;
  }

  // cautare articol in arbore
  while (true) {
    printf("Introduceti id-ul de cautat:");
    int id = NULL;
    inaltime = 0;
    scanf("%d",&id);
    // iesire daca id = 0
    if (id == 0) break;
    Articol * p_articol = cautaArticol(root, id);
    printf("Inaltime nod cautat:%d\n",inaltime);
    Articol articol;
    if (p_articol) {
      articol = * p_articol;
      afiseazaArticol(articol);
    } else {
      printf("Nodul nu a fost gasit!");
    }
  }

  // conversie in vector breadth first pentru afisare
  printf("Afisare structura arbore:\n");
  char spacer[]=" ";
  breadthFirst(root, arbore);
  for (int i=0; i<depth;i++) {
    for (int k=1;k<pow(2,depth-i)/2;k++) printf("%s",spacer);
    for (int j=pow(2,i)-1; j<pow(2,i+1)-1; j++) {
      if (arbore[j] != 0) {
        printf("%d",arbore[j]);
      } else {
        printf("%s",spacer);
      }
      for (int k=1;k<pow(2,depth-i);k++) printf("%s",spacer);
    }
    printf("\n");
  }

  printf("Sfarsit demonstratie.\n");
  return 0;
}
