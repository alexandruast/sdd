#include "utils.cpp"

int main() {
  // matrice zig-zag
  int random = 0;
  int linii = 10;

  // alocare memorie vector zig-zag si setare valoare coloane (1 - 10 random)
  int* coloane = (int*)malloc(sizeof(int)*linii);
  for (int i=0; i<linii; i++) {
    // numarul de coloane trebuie sa fie <> 0
    do {
      random = rand() % 10;
    } while (random == 0);
    coloane[i] = random;
  }

  // alocare memorie matrice zig-zag
  int** m = (int**)malloc(sizeof(int*)*linii);
  for (int i=0; i<linii; i++) {
    m[i] = (int*)malloc(sizeof(int)*coloane[i]);
  }

  // parcurgere si setare valori (0 - 255 random)
  for (int i=0; i<linii; i++) {
    for (int j=0; j<coloane[i]; j++) {
      m[i][j] = rand() % 255;
    }
  }

  // parcurgere si afisare valori
  for (int i=0; i<linii; i++) {
    for (int j=0; j<coloane[i]; j++) {
      printf("%d\t",m[i][j]);
      if (j == coloane[i]-1) printf("\n");
    }
  }

  // cleanup
  free(m);

  printf("Sfarsit demonstratie.\n");
  return 0;
}
