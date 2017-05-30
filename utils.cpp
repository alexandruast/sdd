#include <stdio.h>
#include <stdlib.h>
#include <cstring>

/** ToDo:
    structuri avansate - arbori, stack, queue, sortari etc...
    implementat functii stergere
**/

struct Articol {
  int id;
  char* nume;
  float marime;
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

Articol deepCopy(Articol articol) {
  Articol temp;
  temp.id = articol.id;
  temp.nume = (char*)malloc(sizeof(char)*strlen(articol.nume) + 1);
  strcpy(temp.nume, articol.nume);
  temp.marime = articol.marime;
  return temp;
}

void afiseazaArticol(Articol articol) {
  printf("%d\t%s\t%0.2f\n", articol.id, articol.nume, articol.marime);
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
