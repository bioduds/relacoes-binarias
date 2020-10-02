/** Author: Eduardo Capanema ********/
/** Email: eduardocapanema@ufmg.br **/
/** Mat: 2020041515 *****************/

#include <stdlib.h>
#include <stdio.h>

// consts e globais
#define MAX_VAL 50

// cabeçalhos de funções
void relacao_de_fecho( int** matriz, int size );
int is_transitiva( int** matriz, int size );
int is_assimetrica( int** matriz, int size );
int is_antisimetrica( int** matriz, int size );
int is_simetrica( int** matriz, int size );
int is_irreflexiva( int** matriz, int size );
int is_reflexiva( int** matriz, int size );


int main( int argc, char* argv[] ) {

  int n;
  scanf( "%d", &n);
  // printf("n is %d \n", n);

  if( n > MAX_VAL ) {
    printf( "Numero de entradas maior que o limite especificado!" );
    return 0;
  }

  int f[n];
  for ( int k=0; k<n; k++ ) {
    scanf( "%d", &f[k] );
  }

  int** matriz;
  matriz = ( int** ) malloc( sizeof( int* ) * (n+1) );
  for( int m=0; m<=n; m++ ) {
    matriz[m] = ( int* ) malloc( sizeof( int ) * (n+1) );
  }

  // preencher base usando posições 0,0 para delimitar submatriz com ref dos nos
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
  while ( ( rc = scanf( "%d", &a ) ) == 1 ) {
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
  }

  // vendo a matriz - codigo de teste - "descomente" para verificar
  // printf( "Mostrando a matriz\n" );
  // for( int v=0; v<=n; v++ ) {
  //   for( int w=0; w<=n; w++) {
  //     printf( "%d ", matriz[v][w] );
  //   }
  //   printf( "\n" );
  // }

  int reflexiva = is_reflexiva( matriz, n );
  int irreflexiva = is_irreflexiva( matriz, n );
  int simetrica = is_simetrica( matriz, n );
  int antisimetrica = is_antisimetrica( matriz, n );
  int assimetrica = is_assimetrica( matriz, n );
  int transitiva = is_transitiva( matriz, n );
  printf( "Relação de equivalência: %s \n", ( reflexiva && simetrica && transitiva ) ? "V" : "F" );
  printf( "Relação de ordem parcial: %s \n", ( reflexiva && transitiva && !antisimetrica ) ? "V" : "F" );
  relacao_de_fecho( matriz, n );

  // liberar memoria da matriz
  free( matriz );

  return 0;

}


/************************
Implementações de funções
________________________*/


/************************/
/*** RELACAO DE FECHO ***/
void relacao_de_fecho( int** matriz, int size ) {
  printf( "Fecho transitivo da relação: " );
  for( int i=1; i<=size; i++ ) {
    for( int j=1; j<=size; j++ ) {
      if( matriz[j][i] ) {
        if( i>=j ) {
          for( int k=1; k<=size; k++ ) { // OBS: para nossa análise de complexidade assintótica, este é nosso limite superior - O(n³)
            if( matriz[i][k] ) {
              printf( "(%d,%d); ", matriz[i][0], matriz[0][k] );
            }
          }
        }
      }
    }
  }
  printf( "\n" );
  return;
}
/*** RELACAO DE FECHO ***/
/************************/

/******************/
/*** TRANSITIVA ***/
int is_transitiva( int** matriz, int size ) {
  int is_it = 1;
  for( int i=1; i<=size; i++ ) {
    for( int j=1; j<=size; j++ ) {
      if( matriz[i][j] && i != j ) {
        for( int k=1; k<=size; k++ ) {
          if( matriz[j][k] && !matriz[i][k] ) {
            is_it = 0;
          }
        }
      }
    }
  }
  printf( "Transitiva: %s \n", ( is_it == 1 ) ? "V" : "F" );
  if( is_it == 0 ) {
    for( int i = 1; i<=size; i++ ) {
      for( int j = 1; j<=size; j++ ) {
        if( matriz[i][j] && i != j ) {
          for( int k=1; k<=size; k++ ) {
            if( matriz[j][k] && !matriz[i][k] ) {
              printf( "(%d,%d); ", matriz[i][0], matriz[0][k] );
            }
          }
        }
      }
    }
    printf( "\n" );
  }
  return is_it;
}
/*** TRANSITIVA ***/
/******************/

/*******************/
/*** ASSIMÉTRICA ***/
int is_assimetrica( int** matriz, int size ) {
  int is_it = 1;
  for( int i = 1; i<=size; i++ ) {
    for( int j = 1; j<=size; j++ ) {
      if( matriz[i][j] && matriz[j][i] ) {
        is_it = 0;
      }
    }
  }
  printf( "Assimétrica: %s \n", ( is_it == 1 ) ? "V" : "F" );
  return is_it;
}
/*** ASSIMÉTRICA ***/
/*******************/

/**********************/
/*** ANTI-SIMÉTRICA ***/
int is_antisimetrica( int** matriz, int size ) {
  int is_it = 0;
  for( int i = 1; i<=size; i++ ) {
    for( int j = 1; j<=size; j++ ) {
      if( ( matriz[i][j] && matriz[j][i] ) && i != j ) {
        is_it = 1;
      }
    }
  }
  printf( "Anti-simétrica: %s \n", ( is_it == 1 ) ? "F" : "V" );
  if( is_it == 1 ) {
    for( int i = 1; i<=size; i++ ) {
      for( int j = 1; j<=size; j++ ) {
        if( i<j ) {
          if( ( matriz[i][j] && matriz[j][i] ) && i != j ) {
              printf( "(%d,%d); ", matriz[i][0], matriz[0][j] );
              printf( "(%d,%d); ", matriz[0][j], matriz[i][0] );
          }
        }
      }
    }
    printf( "\n" );
  }
  return is_it;
}
/*** ANTI-SIMÉTRICA ***/
/**********************/

/*****************/
/*** SIMÉTRICA ***/
int is_simetrica( int** matriz, int size ) {
  int is_it = 1;
  for( int i=1; i<=size; i++ ) {
    for( int j=1; j<=size; j++ ) {
      if( matriz[i][j] && !matriz[j][i] ) {
        is_it = 0;
      }
    }
  }
  printf( "Simétrica: %s \n", ( is_it == 1 ) ? "V" : "F" );
  if( is_it == 0 ) {
    for( int i=1; i<=size; i++ ) {
      for( int j=1; j<=size; j++ ) {
        if( matriz[i][j] && !matriz[j][i] ) {
          printf( "(%d,%d); ", matriz[0][j], matriz[i][0] );
        }
      }
    }
    printf( "\n" );
  }
  return is_it;
}
/*** SIMÉTRICA ***/
/*****************/

/*******************/
/*** IRREFLEXIVA ***/
int is_irreflexiva( int** matriz, int size ) {
  int is_it = 0;
  for( int i = 1; i<=size; i++ ) {
    for( int j = 1; j<=size; j++ ) {
      //  printf(" Oiando [%d,%d]: %d ", i, j, matriz[i][j] );
       if( i == j ) {
         if( matriz[i][j] == 1 ) {
           is_it = 1;
         }
       }
    }
  }
  printf( "Irreflexiva: %s \n", ( is_it == 1 ) ? "F" : "V" );
  if( is_it == 1 ) {
    for( int i = 1; i<=size; i++ ) {
      for( int j = 1; j<=size; j++ ) {
        if( i == j ) {
          if( matriz[i][j] == 1 ) {
            printf( "(%d,%d); ", matriz[i][0], matriz[0][j] );
          }
        }
      }
    }
    printf( "\n" );
  }
  return is_it;
}
/*******************/
/*** IRREFLEXIVA ***/

/*****************/
/*** REFLEXIVA ***/
int is_reflexiva( int** matriz, int size ) {
  int is_it = 1;
  for( int i = 1; i<=size; i++ ) {
    for( int j = 1; j<=size; j++ ) {
       if( i == j ) {
         if( matriz[i][j] == 0 ) {
           is_it = 0;
         }
       }
    }
  }
  printf( "Reflexiva: %s \n", ( is_it == 0 ) ? "F" : "V" );
  if( is_it == 0 ) {
    for( int i = 1; i<=size; i++ ) {
      for( int j = 1; j<=size; j++ ) {
        if( i == j ) {
          if( matriz[i][j] == 0 ) {
            printf( "(%d,%d); ", matriz[i][0], matriz[0][j] );
          }
        }
      }
    }
    printf( "\n" );
  }
  return is_it;
}
/*** REFLEXIVA ***/
/*****************/

