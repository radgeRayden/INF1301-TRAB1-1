/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Módulo Matriz / Programação Modular
*  Gestor:  Flávio Bevilacqua
*  Autores: Gabriel Medeiros   - GM
*           Westerbly Snaydley - WS
*           Gustavo Aranha     - GA
*
*  $HA Histórico de evolução:
*       1.00   WS   03/09/2015 Versão inicial do módulo
*
***************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN



/*****  Dados encapsulados no módulo  *****/
   	
   	/* Ponteiro para nulo que identifica posições inválidas na matriz */
	tpNoMatriz* NULL_NO_MATRIZ = NULL;

/***** Protótipos das funções encapuladas no módulo *****/
	
	/* Função que retorna uma referência para um nó localizado nas coordenadas fornecidas, na matriz especificada */
	tpNoMatriz** MAT_GetNoPorCoordenada(int x, int y, tpMatriz* matriz);

	/* Função que destroi uma matriz recursivamente através do primeiro nó. Assertiva: o nó fornecido tem de ser o nó de origem. */
    void DestroiMatriz( tpNoMatriz *pNo, tpMatriz* matriz );

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma matriz com o tamanho especificado (n x n)
*
*  $EP Parâmetros
*	  $P matriz - referência de saída para a matriz
*	  $P n - tamanho do lado da matriz (o número de elementos da mesma será n x n)
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

	MAT_tpCondRet MAT_CriarMatriz(tpMatriz** matriz, int n) {
	  int i;
	  tpMatriz* pMatriz = NULL;

	  pMatriz = (tpMatriz* ) malloc( sizeof(tpMatriz ));
	  
	  if ( pMatriz == NULL )
	  {
	    return MAT_CondRetFaltouMemoria;
	  } /* if */
	      
	  //Alocação das referências para os nós (todas apontam para NULL inicialmente)
	  pMatriz->NosMatriz = (tpNoMatriz**) malloc(sizeof(tpNoMatriz*) * n * n);
	  
	  if(pMatriz->NosMatriz == NULL) {
	    return MAT_CondRetFaltouMemoria;
	  } /* if */
	  
	  for (i = 0; i < n * n; i++)
	  {
	    (pMatriz->NosMatriz[i]) = NULL;
	  } /* if */
	  
	  pMatriz->pNoOrigem = pMatriz->NosMatriz;
	  pMatriz->pNoCorr = pMatriz->NosMatriz;

	  *matriz = pMatriz;
	  (*matriz)->tamanho = n;
	  return MAT_CondRetOK ;
	} /* Fim função: MAT Criar Matriz */

/***********************************************************************
*
*  $FC Função: MAT Destruir Matriz
*
*  $ED Descrição da função
*     Destroi a matriz especificada, liberando a memória alocada por seus nós.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser destruída.
*     
*  $FV Valor retornado
*	 MAT_CondRetMatrizNaoExiste
*	 MAT_CondRetOK
*
***********************************************************************/

   	MAT_tpCondRet MAT_DestruirMatriz(tpMatriz* matriz) {
 
      if ( matriz != NULL )
      {
         DestroiMatriz( *matriz->pNoOrigem, matriz ) ;         
         free( matriz ) ;
      }
	  else {
	  	return MAT_CondRetMatrizNaoExiste;
      } /* if */
	  return MAT_CondRetOK;
   	} /* Fim função: MAT Destruir matriz */

  
/***********************************************************************
*
*  $FC Função: MAT Insere nó
*
*  $ED Descrição da função
*     Insere um nó na posição (x, y) especificada, com o conteúdo descrito.
*	  NOTA: Esta função NÃO altera o nó corrente da matriz.
*
*  $EP Parâmetros
*	  $P x - Coordenada x
*	  $P y - Coordenada y
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*	  $P conteudoLista - vetor de ponteiros para caracteres que serão inseridos na lista.
*
*   $FV Valor retornado
*	  MAT_CondRetMatrizNaoExiste
*	  MAT_CondRetCoordenadaForaDaMatriz
*	  MAT_CondRetFaltouMemoria
*     MAT_CondRetOK
*
***********************************************************************/

MAT_tpCondRet MAT_InsereNo(int x, int y, tpMatriz* matriz, char** conteudoLista) {
  tpNoMatriz* novoNo;
  tpNoMatriz** temp = NULL;
  int i;
  LIS_tppLista lista = NULL;
  
  if(matriz == NULL) {
	return MAT_CondRetMatrizNaoExiste;
  }

  temp = MAT_GetNoPorCoordenada(x, y, matriz);
  if(temp == &NULL_NO_MATRIZ) {
	return MAT_CondRetCoordenadaForaDaMatriz;
  }
  novoNo = (tpNoMatriz*)malloc(sizeof(tpNoMatriz));
  
  if(novoNo == NULL) {
    return MAT_CondRetFaltouMemoria;
  }
  

  lista = LIS_CriarLista(NULL);
  for(i = 0; i < sizeof(conteudoLista) / sizeof(char*); i++) {
	LIS_InserirElementoApos(lista, conteudoLista[i]);
  }

  novoNo->coordenadaX = x;
  novoNo->coordenadaY = y;
  novoNo->Lista = lista;
  
  *temp = novoNo;
  
  	/* Seguindo a representação da matriz na seguinte forma (ex. matriz 3x3):
	 	| x - 1, y - 1          x, y - 1         x + 1, y - 1 |
	 
	 	| x - 1, y              x, y             x + 1, y     |

	 	| x - 1, y + 1          x, y + 1         x + 1, y + 1 |

	*/

  //norte
  novoNo->pNoN = (MAT_GetNoPorCoordenada(x, y - 1, matriz));
  //nordeste
  novoNo->pNoNE = (MAT_GetNoPorCoordenada(x + 1, y - 1, matriz));
  //leste
  novoNo->pNoE = (MAT_GetNoPorCoordenada(x + 1, y, matriz));
  //sudeste
  novoNo->pNoSE = (MAT_GetNoPorCoordenada(x + 1, y + 1, matriz));
  //sul
  novoNo->pNoS = (MAT_GetNoPorCoordenada(x, y + 1, matriz));
  //sudoeste
  novoNo->pNoSW = (MAT_GetNoPorCoordenada(x - 1, y + 1, matriz));
  //oeste
  novoNo->pNoW = (MAT_GetNoPorCoordenada(x - 1, y, matriz));
  //noroeste
  novoNo->pNoNW = (MAT_GetNoPorCoordenada(x - 1, y - 1, matriz));
  
  return MAT_CondRetOK;
}

/* Fim função: MAT InsereNo*/

/***********************************************************************
*
*  $FC Função: MAT Ir Norte
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Norte (x, y - 1) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

	MAT_tpCondRet MAT_IrN ( tpMatriz * pMatriz ) {

	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoN == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoN;

	  return MAT_CondRetOK ;
	} /* Fim função: MAT Ir Norte */

/***********************************************************************
*
*  $FC Função: MAT Ir Nordeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Nordeste (x + 1, y - 1) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

	MAT_tpCondRet MAT_IrNE ( tpMatriz * pMatriz ) {

	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoNE == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoNE;

	  return MAT_CondRetOK ;
	} /* Fim função: MAT Ir Nordeste */

/***********************************************************************
*
*  $FC Função: MAT Ir Leste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Leste (x + 1, y) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/
	MAT_tpCondRet MAT_IrE ( tpMatriz * pMatriz ) {

	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoE == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoE;

	  return MAT_CondRetOK ;
  	} /* Fim função: MAT Ir Leste */

/***********************************************************************
*
*  $FC Função: MAT Ir Sudeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Sudeste (x + 1, y + 1) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

	MAT_tpCondRet MAT_IrSE ( tpMatriz * pMatriz ) {

	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoSE == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoSE;

	  return MAT_CondRetOK ;
  	} /* Fim função: MAT Ir Sudeste */

/***********************************************************************
*
*  $FC Função: MAT Ir Sul
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Sul (x, y + 1) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

MAT_tpCondRet MAT_IrS ( tpMatriz * pMatriz ) {
	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoS == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoS;

	  return MAT_CondRetOK ;
  } /* Fim função: MAT Ir Sul */

/***********************************************************************
*
*  $FC Função: MAT Ir Sudoeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Sudoeste (x - 1, y + 1) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/
	MAT_tpCondRet MAT_IrSW ( tpMatriz * pMatriz ) {
	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoSW == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoSW;

	  return MAT_CondRetOK ;
  	}  /* Fim função: MAT Ir Sudoeste */

/***********************************************************************
*
*  $FC Função: MAT Ir Oeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Oeste (x - 1, y) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

	MAT_tpCondRet MAT_IrW ( tpMatriz * pMatriz ) {
	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoW == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoW;

	  return MAT_CondRetOK ;
  	}  /* Fim função: MAT Ir Oeste */

/***********************************************************************
*
*  $FC Função: MAT Ir Noroeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Noroeste (x - 1, y - 1) do nó corrente atual.
*
*  $EP Parâmetros
*	  $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

	MAT_tpCondRet MAT_IrNW ( tpMatriz * pMatriz ) {
	  if ( pMatriz == NULL )
	  {
	     return MAT_CondRetMatrizNaoExiste ;
	  } /* if */

	  if ( *pMatriz->pNoCorr == NULL )
	  {
	     return MAT_CondRetMatrizVazia ;
	  } /* if */

	  if ( (*pMatriz->pNoCorr)->pNoNW == &NULL_NO_MATRIZ )
	  {
	     return MAT_CondRetNoEstaNaBorda ;
	  } /* if */

	  pMatriz->pNoCorr = (*pMatriz->pNoCorr)->pNoNW;

	  return MAT_CondRetOK ;
  	}  /* Fim função: MAT Ir Noroeste */

/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $ED Descrição da função
*     Obtem o valor do nó corrente na matriz especificada
*
*  $EP Parâmetros
*     $P matriz - Ponteiro para a matriz cujo valor corrente é requerido
*	  $P saida - Ponteiro para char que receberá o valor recuperado
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*
***********************************************************************/
	MAT_tpCondRet MAT_ObterValorCorr( tpMatriz *matriz, char * saida )
	{
		if(matriz==NULL) {
			return MAT_CondRetMatrizNaoExiste;
		}
		
		if(*matriz->pNoCorr == NULL) {
			return MAT_CondRetMatrizVazia;
		}	
		
		*saida = *(char*)LIS_ObterValor((*matriz->pNoCorr)->Lista);
		
	    return MAT_CondRetOK;
   } /* Fim função: MAT Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MAT Destruir a estrutura da matriz
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL e correspondente ao nó de origem da matriz (exceto em recursão)
*
*  $ED Descrição da função
*     Destroi uma matriz recursivamente através do primeiro nó.
*
*  $EP Parâmetros
*     $P pNo - Ponteiro para o nó que inicia a propagação
*	  $P matriz - Ponteiro para a matriz a ser destruída
*
***********************************************************************/

	void DestroiMatriz( tpNoMatriz * pNo, tpMatriz* matriz ) {
		if(pNo == NULL) {
			return;
		}
	    
	    if ( pNo->pNoE != &NULL_NO_MATRIZ ) {
	        DestroiMatriz( *pNo->pNoE, matriz) ;
	    } /* if */

	    if ( pNo->pNoS != &NULL_NO_MATRIZ) {
	        DestroiMatriz( *pNo->pNoS, matriz) ;
	    } /* if */

		LIS_EsvaziarLista(pNo->Lista);
		  
		*(MAT_GetNoPorCoordenada(pNo->coordenadaX, pNo->coordenadaY, matriz)) = NULL;
		  
	    free( pNo ) ;
	} /* Fim função auxiliar: MAT Destroi Matriz */
	    
/***********************************************************************
*
*  $FC Função: MAT Recupera nó por coordenada
*
*  $ED Descrição da função
*     Recupera um nó localizado nas coordenadas especificadas, ou um
*     ponteiro para NULL caso a posição seja inválida.
*
*  $EP Parâmetros
*     $P x - Coordenada X (eixo horizontal)
*	  $P y - Coordenada y (eixo vertical)
*	  $P matriz - Ponteiro para a matriz que contem o nó requisitado
*
***********************************************************************/
      
	tpNoMatriz** MAT_GetNoPorCoordenada(int x, int y, tpMatriz* matriz) {
	  int n = matriz->tamanho;
	  int index = y * n + x;

	  //Checagem para identificar se os parâmetros condizem com o tamanho da matriz
	  if((y * n < 0 || x < 0) || (y > n - 1 || x > n - 1)) {
	    return &NULL_NO_MATRIZ;
	  } /* if */

	  return matriz->NosMatriz + index;
	} /* Fim função: MAT Recuperar nó em coordenada específica */



/********** Fim do módulo de implementação: Módulo matriz **********/
