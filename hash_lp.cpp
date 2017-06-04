#include "utils.cpp"

int hash(int id, float marime, int hashSize) {
  int hashValue = int(round(id * marime)) % hashSize;
  return hashValue;
}

void adaugaArticolLP(Articol* hashLP, int hashSize, Articol articol) {
  int hashValue = hash(articol.id, articol.marime, hashSize);
  do {
    printf("%03d --> ",hashValue);
    afiseazaArticol(articol);
    if (hashLP[hashValue].id != NULL) {
      printf("Coliziune pe pozitia %d pentru articolul cu id %d!\n",hashValue, articol.id);
      hashValue++;
    } else break;
  } while (true);

  hashLP[hashValue] = articol;
}

void citesteArticoleLP(Articol* hashLP, char* f_name, int hashSize, int items) {
  // citire din fisier
  FILE* f = fopen(f_name,"r");
  Articol articol;
  for (int i=0; i<items; i++) {
    articol = citesteArticol(f);
    adaugaArticolLP(hashLP, hashSize, articol);
  }
  fclose(f);
}

Articol * cautaArticol(Articol* hashLP, int hashSize, int id, float marime) {
  int hashValue = hash(id, marime, hashSize);
  while (hashValue < hashSize) {
    if (hashLP[hashValue].id == NULL) return NULL;
    if (hashLP[hashValue].id != id) {
      printf("Coliziune pe pozitia %d pentru articolul cu id %d!\n",hashValue, id);
      hashValue++;
    } else break;
  }
  if (hashValue == hashSize) return NULL;
  return &hashLP[hashValue];
}

int main() {
  int hashSize = 256;
  // lista articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  int items = fileRecords(f_name);

  Articol* hashLP = (Articol*)malloc(sizeof(Articol)*hashSize);
  for (int i=0;i<256;i++) {
    hashLP[i].id = NULL;
    hashLP[i].marime = NULL;
  }

  citesteArticoleLP(hashLP, f_name, hashSize, items);

  // cautare hashLP
  while(true) {
    printf("Introduceti id-ul si marimea de cautat (2 4.83) :");
    int id = NULL;
    float marime = NULL;
    scanf("%d %f", &id, &marime);
    // iesire daca id = 0
    if (id == 0) break;
    Articol * p_articol = cautaArticol(hashLP, hashSize, id, marime);
    Articol articol;
    if (p_articol) {
      articol = * p_articol;
      afiseazaArticol(articol);
    } else {
      printf("Id-ul nu a fost gasit!\n");
    }
  }

  return 0;
}
