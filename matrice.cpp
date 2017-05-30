#include "utils.cpp"

int main() {
  // matrice
  int linii = 10;
  int coloane = 10;

  // alocare memorie matrice
  int** m = (int**)malloc(sizeof(int*)*linii);
  for (int i=0; i<linii; i++) {
    m[i] = (int*)malloc(sizeof(int)*coloane);
  }

  // parcurgere si setare valori (0 - 255 random)
  for (int i=0; i<linii; i++) {
    for (int j=0; j<coloane; j++) {
      m[i][j] = rand() % 255;
    }
  }

  // parcurgere si afisare valori
  for (int i=0; i<linii; i++) {
    for (int j=0; j<coloane; j++) {
      printf("%d\t",m[i][j]);
      if (j == coloane-1) printf("\n");
    }
  }

  // cleanup
  free(m);

  printf("Sfarsit demonstratie.\n");
  return 0;
}
