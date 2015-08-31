/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <stdlib.h>
#include   <stdio.h>

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor do nó da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tpNoMatriz {

        struct tpNoMatriz * pNoN ; 
		/* Ponteiro para Norte */

		struct tpNoMatriz * pNoNE ; 
		 /* Ponteiro para Nordeste */ 

		struct tpNoMatriz * pNoE ; 
		/* Ponteiro para Leste */ 


		struct tpNoMatriz * pNoSE ; 
		/* Ponteiro para Sudeste */ 

		struct tpNoMatriz * pNoS ; 
		/* Ponteiro para Sul */ 

		struct tpNoMatriz * pNoSW ; 
		/* Ponteiro par Sudoeste */ 

		struct tpNoMatriz * pNoW ; 
		/* Ponteiro para Oeste */ 

		struct tpNoMatriz * pNoNW ; 
		/* Ponteiro para Noroeste */ 

		LIS_tppLista* Lista ; 
		/* Ponteiro para a cabeça da Lista */ 

		int coordenadaX; 
		int coordenadaY; 
} tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct MAT_tpMatriz {

		tpNoMatriz** NosMatriz;

         tpNoMatriz * pNoOrigem ;
               /* Ponteiro para a raiz da árvore */

         tpNoMatriz * pNoCorr ;
               /* Ponteiro para o nó corrente da matriz */
		 int tamanho;

   } tpMatriz ;

/*****  Dados encapsulados no módulo  *****/

	//static tpMatriz * pArvore = NULL ;
            /* Ponteiro para a cabe‡a da árvore */

/***** Protótipos das funções encapuladas no módulo *****/

   //static tpNoMatriz * CriarNo( char ValorParm ) ;

   //static ARV_tpCondRet CriarNoRaiz( char ValorParm ) ;

   //
   void DestroiMatriz( tpNoMatriz *pNo );

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
*  ****/

  /*MAT_tpCondRet MAT_CriarMatriz(tpMatriz** matriz, int n) {
  int i;
  tpMatriz* pMatriz = NULL;
  tpNoMatriz* noTemp = NULL;
  if (matriz* != NULL )
  {
    MAT_DestruirMatriz(matriz*) ;
  } /* if 
 
  pMatriz = ( tpMatriz* ) malloc( sizeof( tpMatriz )) ;
  if ( pMatriz == NULL )
  {
    return MAT_CondRetFaltouMemoria ;
  } /* if 
     
     
  pMatriz->nos = (tpNoMatriz**) malloc(sizeof(tpNoMatriz*) * n * n);
 
  if(pMatriz->nos == NULL) {
    return MAT_CondRetFaltouMemoria;
  }
 
  for (i = 0; i < n * n; i++)
  {
    pMatriz->nos = NULL;
  }
     
  pMatriz->pNoOrigem = pMatriz->nos[0];
  pMatriz->pNoCorr = pMatriz->nos[0];
 
  matriz* = pMatriz;
     
  return MAT_CondRetOK ;
 
} /* Fim função: MAT Criar Matriz */

/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/

   void MAT_DestruirMatriz(tpMatriz* matriz)
   {

      if ( matriz != NULL )
      {
         if ( matriz->pNoOrigem != NULL )
         {
            DestroiMatriz( matriz->pNoOrigem ) ;
         } /* if */
         free( matriz ) ;
         matriz = NULL ;
      } /* if */

   } /* Fim função: MAT Destruir matriz */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
*  ****/

  MAT_tpCondRet MAT_CriarMatriz(tpMatriz** matriz, int n) {
  int i;
  tpMatriz* pMatriz = NULL;
  tpNoMatriz* noTemp = NULL;
  if (*matriz != NULL )
  {
    MAT_DestruirMatriz(*matriz) ;
  } /* if */

  pMatriz = (tpMatriz* ) malloc( sizeof(tpMatriz )) ;
  if ( pMatriz == NULL )
  {
    return MAT_CondRetFaltouMemoria ;
  } /* if */
      
      
  pMatriz->NosMatriz = (tpNoMatriz**) malloc(sizeof(tpNoMatriz*) * n * n);
  
  if(pMatriz->NosMatriz == NULL) {
    return MAT_CondRetFaltouMemoria;
  }
  
  for (i = 0; i < n * n; i++)
  {
    pMatriz->NosMatriz = NULL;
  }
      
  pMatriz->pNoOrigem = pMatriz->NosMatriz[0];
  pMatriz->pNoCorr = pMatriz->NosMatriz[0];

  *matriz = pMatriz;
      
  return MAT_CondRetOK ;
} /* Fim função: MAT Criar Matriz */
  
//função auxiliar
//assume que o tamanho está correto
tpNoMatriz** MAT_GetNoPorCoordenada(int x, int y, tpMatriz* matriz) {
  int n = matriz->tamanho;
  int index = y * n + x;
  if(index < 0 || index > n*n)
    return NULL;
  return matriz->NosMatriz + (y * n + x);
}

MAT_tpCondRet MAT_InsereNo(int x, int y, tpMatriz* matriz, LIS_tppLista* lista) {
  tpNoMatriz* novoNo = (tpNoMatriz*)malloc(sizeof(tpNoMatriz));
  if(novoNo == NULL) {
    return MAT_CondRetFaltouMemoria;
  }
    
  novoNo->Lista = lista;  
  *(MAT_GetNoPorCoordenada(x, y, matriz)) = novoNo;
  
  //norte
  novoNo->pNoN = *(MAT_GetNoPorCoordenada(x, y - 1, matriz));
  //nordeste
  novoNo->pNoNE = *(MAT_GetNoPorCoordenada(x - 1, y - 1, matriz));
  //leste
  novoNo->pNoE = *(MAT_GetNoPorCoordenada(x + 1, y, matriz));
  //sudeste
  novoNo->pNoSE = *(MAT_GetNoPorCoordenada(x + 1, y + 1, matriz));
  //sul
  novoNo->pNoS = *(MAT_GetNoPorCoordenada(x, y + 1, matriz));
  //sudoeste
  novoNo->pNoN = *(MAT_GetNoPorCoordenada(x - 1, y + 1, matriz));
  //oeste
  novoNo->pNoW = *(MAT_GetNoPorCoordenada(x - 1, y, matriz));
  //noroeste
  novoNo->pNoNW = *(MAT_GetNoPorCoordenada(x - 1, y - 1, matriz));
  
  return MAT_CondRetOK;
}

/***
Função: MAT Ir Norte
* ****/

MAT_tpCondRet MAT_IrN ( tpMatriz* pMatriz )
{
  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( pMatriz->pNoCorr->coordenadaY == 0 )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoN ;

  return MAT_CondRetOK ;
  } 
 /* Fim função: MAT Ir Norte */

/***
Função: MAT Ir Nordeste
* ****/
MAT_tpCondRet MAT_IrNE ( tpMatriz * pMatriz )
{
  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */
  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */
  if ( (pMatriz->pNoCorr->coordenadaY == 0 ) || ( pMatriz->pNoCorr->coordenadaX == pMatriz->tamanho - 1) )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */
  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoNE ;
  return MAT_CondRetOK ;
  }  /* Fim função: MAT Ir Nordeste */

/***
Função: MAT Ir Leste
* ****/
MAT_tpCondRet MAT_IrE ( tpMatriz * pMatriz )
{

  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( pMatriz->pNoCorr->coordenadaX == pMatriz->tamanho - 1 )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoE ;

  return MAT_CondRetOK ;
  } 
 /* Fim função: MAT Ir Leste */

/***
Função: MAT Ir Sudeste
* ****/

MAT_tpCondRet MAT_IrSE ( tpMatriz * pMatriz )
{

  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( (pMatriz->pNoCorr->coordenadaY == pMatriz->tamanho - 1 ) || ( pMatriz->pNoCorr->coordenadaX == pMatriz->tamanho - 1) )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoSE ;

  return MAT_CondRetOK ;
  } 
 /* Fim função: MAT Ir Sudeste */

/***
Função: MAT Ir Sul
* ****/

MAT_tpCondRet MAT_IrS ( tpMatriz * pMatriz )
{

  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( pMatriz->pNoCorr->coordenadaY == pMatriz->tamanho - 1 )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoS ;

  return MAT_CondRetOK ;
  } 
 /* Fim função: MAT Ir Sul */

/***
Função: MAT Ir Sudoeste
* ****/

MAT_tpCondRet MAT_IrSW ( tpMatriz * pMatriz )
{

  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( (pMatriz->pNoCorr->coordenadaX == 0 ) || ( pMatriz->pNoCorr->coordenadaY == pMatriz->tamanho - 1) )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoSW ;

  return MAT_CondRetOK ;
  }  /* Fim função: MAT Ir Sudoeste */

/***
Função: MAT Ir Oeste
* ****/

MAT_tpCondRet MAT_IrW ( tpMatriz * pMatriz )
{

  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( pMatriz->pNoCorr->coordenadaX == 0 )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoW ;

  return MAT_CondRetOK ;
  }  /* Fim função: MAT Ir Oeste */

/***
Função: MAT Ir Noroeste
* ****/

MAT_tpCondRet MAT_IrNW ( tpMatriz * pMatriz )
{

  if ( pMatriz == NULL )
  {
     //return MAT_CondRetMatrizNaoExiste ;
  } /* if */

  if ( pMatriz->pNoCorr == NULL )
  {
     //return MAT_CondRetMatrizVazia ;
  } /* if */

  if ( (pMatriz->pNoCorr->coordenadaX == 0 ) || ( pMatriz->pNoCorr->coordenadaY == 0) )
  {
     //return MAT_CondRetNoEstaNaBorda ;
  } /* if */

  pMatriz->pNoCorr = pMatriz->pNoCorr->pNoNW ;

  return MAT_CondRetOK ;
  }  /* Fim função: MAT Ir Noroeste */

/***************************************************************************
*
*  Função: MAT Obter valor corrente
*  ****/

   MAT_tpCondRet MAT_ObterValorCorr(tpMatriz* matriz, LIS_tppLista * ValorParm )
   {

      if ( matriz == NULL )
      {
         //return MAT_CondRetMatrizNaoExiste ;
      } /* if */
      if ( matriz->pNoCorr == NULL )
      {
         //return MAT_CondRetMatrizVazia ;
      } /* if */
      /*while(matriz->pNoCorr->Valor!=NULL)
      {
        if(LIS_InserirElementoApos(* ValorParm ,LIS_ObterValor(matriz->pNoCorr->Valor))!=LIS_CondRetOK)
        {
          //return LIS_CondRetFaltouMemoria;
        }
        /*if(LIS_tpCondRet LIS_AvancarElementoCorrente( matriz->pNoCorr->Valor , 1 ) == LIS_CondRetOK)
        {
          *ValorParm->pElemCorr = *ValorParm->pElemCorr->pProx;
        }
      }*/
      /*IrInicioLista(matriz->pNoCorr->Valor);
      IrInicioLista(*ValorParm);*/
    
      
      return MAT_CondRetOK ;

   } /* Fim função: MAT Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
*
***********************************************************************/

   /*tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if 

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   /*ARV_tpCondRet CriarNoRaiz( char ValorParm )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if 
      } /* if 

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if 
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if 

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiMatriz(tpNoMatriz *pNo)
   {
      if ( pNo->pNoE != NULL ) {
         DestroiMatriz( pNo->pNoE );
       /* if */
	  }
      if(pNo->pNoS != NULL)
         DestroiMatriz( pNo->pNoS ) ;
       /* if */

      free( pNo ) ;

   } /* Fim função: MAT Destruir a estrutura da matriz */

/********** Fim do módulo de implementação: Módulo matriz **********/

