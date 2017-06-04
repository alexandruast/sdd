#include "utils.cpp"

struct nodLista {
  Articol info;
  nodLista* next;
};

int hash(int id, float marime, int hashSize) {
  int hashValue = int(round(id * marime)) % hashSize;
  return hashValue;
}

void adaugaArticolC(nodLista** hashC, int hashSize, Articol articol) {
  int hashValue = hash(articol.id, articol.marime, hashSize);
  nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
  nodLista* curent;
  printf("%03d --> ",hashValue);
  afiseazaArticol(articol);
  nou->info = articol;
  nou->next = NULL;
  // nu avem cap
  if (!hashC[hashValue]) {
    hashC[hashValue] = nou;
  } else {
    // avem cap
    curent = hashC[hashValue];
    int link = 0;
    do {
      printf("Coliziune pe pozitia %d:%d pentru articolul cu id %d!\n", hashValue, link, articol.id);
      if (curent->next) {
        curent = curent->next;
        link++;
      } else break;
    } while(true);
    curent->next = nou;
  }
}

void citesteArticoleC(nodLista** hashC, char* f_name, int hashSize, int items) {
  // citire din fisier
  FILE* f = fopen(f_name,"r");
  Articol articol;
  for (int i=0; i<items; i++) {
    articol = citesteArticol(f);
    adaugaArticolC(hashC, hashSize, articol);
  }
  fclose(f);
}

Articol * cautaArticol(nodLista** hashC, int hashSize, int id, float marime) {
  int hashValue = hash(id, marime, hashSize);
  nodLista* curent = hashC[hashValue];
  int link = 0;
  while (curent) {
    if (curent->info.id != id) {
      printf("Coliziune pe pozitia %d:%d pentru articolul cu id %d!\n",hashValue, link, id);
      curent = curent->next;
      link++;
    } else break;
  }
  if (curent == NULL) return NULL;
  return &curent->info;
}

int main() {
  int hashSize = 4;
  // lista articole
  char f_name[] = "data-structures.in";
  // citire numar de linii din fisier
  int items = fileRecords(f_name);

  nodLista** hashC = (nodLista**)malloc(sizeof(nodLista*)*hashSize);
  for (int i=0; i<hashSize;i++)hashC[i] = NULL;
  citesteArticoleC(hashC, f_name, hashSize, items);

  // cautare hash nodListaing
  while(true) {
    printf("Introduceti id-ul si marimea de cautat (2 4.83) :");
    int id = NULL;
    float marime = NULL;
    scanf("%d %f", &id, &marime);
    // iesire daca id = 0
    if (id == 0) break;
    Articol * p_articol = cautaArticol(hashC, hashSize, id, marime);
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
