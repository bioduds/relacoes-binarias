#include <stdlib.h>
#include <stdio.h>

// consts e globais
#define MAX_VAL 51

// cabeçalhos de funções
void is_reflexiva( int** matriz, int size );

int main( int argc, char* argv[] ) {

  /* precisamos ler uma entrada
6 3 4 5 6 7 8
3 5
5 7
7 3
5 3
7 5
3 7
4 6
6 8
8 4
6 4
8 6
4 8
3 3
4 4
5 5
6 6
7 7
8 8 
  */

  int n;
  scanf( "%d", &n);
  printf("n is %d \n", n);

  int f[n];
  for ( int k=0; k<n; k++ ) {
    scanf( "%d", &f[k] );
    //printf( "PEGUEI %d \n", f[k] );
  }

  int** matriz;
  matriz = ( int** ) malloc( sizeof( int* ) * (n+1) );
  for( int m=0; m<=n; m++ ) {
    matriz[m] = ( int* ) malloc( sizeof( int ) * (n+1) );
  }

  // preencher base
  for( int z=0; z<=n; z++) {
    for( int x=0; x<=n; x++) {
      if( z == 0 && x == 0) {
        matriz[z][x] = 0;
      }
      else if( z == 0 ) {
        matriz[z][x] = f[x-1];
      } else if( x == 0 ) {
        matriz[z][x] = f[z-1];
      } else {
        matriz[z][x] = 0;
      }      
    }
  }
  
  int a, b;
  int rc;
  while ( (rc = scanf( "%d", &a ) ) == 1 ) {
    scanf( "%d", &b );

    int lb = 0;
    int cb = 0;

    // percorrer linha 0 e coluna 0
    for( lb=0; lb<=n; ++lb ) {
      for( cb=0; cb<=n; ++cb ) {

        if( matriz[lb][0] == a && matriz[0][cb] == b ) {
          matriz[lb][cb] = 1;
        }

      }
    }

    // joga na matriz
    //matriz[c1]c2] = 1;
    //printf( "pegando par %d %d \n", a, b );
  }

  // vendo a matriz
  printf( "Bora ver a matriz\n");
  for( int v=0; v<=n; v++) {
    for( int w=0; w<=n; w++) {
      printf( "%d ", matriz[v][w] );
    }
    printf( "\n");
  }

  // teremos uma matriz

  /*
  int ** matriz;
  matriz = (int **) malloc (sizeof(int *) * NUMERO_DE_LINHAS);

  for( i=0; i<NUMERO_DE_LINHAS; i++ ) {
    matriz[i] = (int *) malloc (sizeof(int) * NUMERO_DE_COLUNAS);
  }  
  */



  /* precisamos fornecer uma saida

Reflexiva: V
Irreflexiva: F
(3,3); (4,4); (5,5); (6,6); (7,7); (8,8);
Simétrica: V
Anti-simétrica: F
(3,5); (5,3); (3,7); (7,3); (4,6); (6,4); (4,8); (8,4); (5,7); (7,5); (6,8); (8,6);
Assimétrica: F
Transitiva: V
Relação de equivalência: V
Relação de ordem parcial: F
Fecho transitivo da relação: (3,3); (3,5); (3,7); (4,4); (4,6); (4,8); (5,3); (5,5); (5,7); (6,4); (6,6); (6,8); (7,3); (7,5); (7,7); (8,4); (8,6); (8,8);

  */

  is_reflexiva( matriz, n );

  // liberar memoria da matriz
  free (matriz);

  return 0;
}



/*************************
 implementacoes de funcoes
*************************/
void is_reflexiva( int** matriz, int size ) {
  int is_it = 1;
  for( int i = 1; i<=size; i++ ) {
    for( int j = 1; j<=size; j++ ) {
      //  printf(" Oiando [%d,%d]: %d ", i, j, matriz[i][j] );
       if( i == j ) {
         if( matriz[i][j] == 0 ) {
           is_it = 0;
         }
       }
    }
  }
  printf( "Reflexiva: %s \n", ( is_it == 0 ) ? "F" : "T" );
  if( is_it == 0 ) {
    for( int i = 1; i<=size; i++ ) {
      for( int j = 1; j<=size; j++ ) {
        //  printf(" Oiando [%d,%d]: %d ", i, j, matriz[i][j] );
        if( i == j ) {
          if( matriz[i][j] == 0 ) {
            printf( "(%d,%d); ", matriz[i][0], matriz[0][j] );
          }
        }
      }
    }
    printf( "\n" );
  }
  return;
}


