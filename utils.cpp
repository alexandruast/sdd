#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>

/** ToDo
    MaxHeap, MinHeap
    tabele de dispersie
    algoritmi sortare
    algoritmi stergere
**/

struct Articol {
  int id;
  char* nume;
  float marime;
};

struct nod {
  Articol info;
  nod* st;
  nod* dr;
};

// deepCopy articol
Articol deepCopy(Articol articol);

// afisare articol
void afiseazaArticol(Articol articol);

// initializarea unui articol nou
Articol newArticol(int id, char* nume, float marime);

// citirea unui articol din fisierul de date
Articol citesteArticol(FILE* f);

// numarul inregistrarilor din fisierul de date
int fileRecords(char* f_name);

// inaltimea unui arbore
int inaltimeArbore(nod* root);

// afisare arbore grafic
void afisareArbore(nod* root, Articol* heap, int heapSize);

// arbore stocat intr-o matrice breadthFirst
void breadthFirst(nod* root, int* arbore, int index);

// dezalocare spatiu ocupat arbore
void freeTree(nod* root);

Articol deepCopy(Articol articol) {
  Articol temp;
  temp.id = articol.id;
  temp.nume = (char*)malloc(sizeof(char)*strlen(articol.nume) + 1);
  strcpy(temp.nume, articol.nume);
  temp.marime = articol.marime;
  return temp;
}

void afiseazaArticol(Articol articol) {
  printf("%03d %s %05.2f\n", articol.id, articol.nume, articol.marime);
}

Articol newArticol(int id, char* nume, float marime) {
  Articol articol;
  articol.id = id;
  articol.nume = (char*)malloc(sizeof(char)*strlen(nume) + 1);
  strcpy(articol.nume, nume);
  articol.marime = marime;
  return articol;
}

Articol citesteArticol(FILE* f) {
  Articol articol;
  if (!f) return articol;
  int id;
  char nume_buffer[32];
  float marime;
  fscanf(f,"%d\t%s\t%f",&id,nume_buffer,&marime);
  articol = newArticol(id, nume_buffer, marime);
  return articol;
}

int fileRecords(char* f_name) {
  FILE* f = fopen(f_name, "r");
  int f_lines = 0;
  char buffer[1024];
  while (fgets(buffer,sizeof(buffer),f)) f_lines++;
  fclose(f);
  return f_lines;
}

int inaltimeArbore(nod* root) {
  if (root) {
    int st = inaltimeArbore(root->st);
    int dr = inaltimeArbore(root->dr);
    return (st>dr ? st : dr) + 1;
  }
  return 0;
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

void afisareArbore(nod* root = NULL, Articol* heap = NULL, int heapSize = 0) {

  if (!heap && !root) {
    printf("Nicio structura de afisat!\n");
    return;
  }

  int inaltime = 0;
  int elemente = 0;

  if (root && !heap) {
    inaltime = inaltimeArbore(root);
    elemente = pow(2,inaltime);
  }

  if (heap && !root) {
    elemente = heapSize;
    inaltime = (log2(elemente));
  }


  int* arbore = (int*)malloc(sizeof(int)*elemente);
  for (int i=0; i<elemente; i++) {
      arbore[i] = 0;
  }

  if (root && !heap) {
    breadthFirst(root, arbore);
  }

  if (heap && !root) {
    for (int i=0; i<elemente; i++) {
      arbore[i] = heap[i].id;
    }
  }

  // afisare structura arbore
  char spacer[]=" ";
  for (int i=0; i<inaltime;i++) {
    for (int k=1;k<pow(2,inaltime-i)/2;k++) printf("%s",spacer);
    for (int j=pow(2,i)-1; j<pow(2,i+1)-1; j++) {
      if (arbore[j] != 0) {
        printf("%d",arbore[j]);
      } else {
        printf("%s",spacer);
      }
      for (int k=1;k<pow(2,inaltime-i);k++) printf("%s",spacer);
    }
    printf("\n");
  }
  free(arbore);
}

void freeTree(nod* root) {
  if (root) {
    if (root->st) {
      freeTree (root->st);
    }
    if (root->dr) {
    freeTree (root->dr);
    }
    free(root->info.nume);
    root->info.id = 0;
    root->info.marime = 0;
  }
}
