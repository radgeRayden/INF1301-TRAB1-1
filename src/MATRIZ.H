#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: M�dulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: M�dulo Matriz / Programa��o Modular
*  Gestor:  Fl�vio Bevilacqua
*  Autores: Gabriel Medeiros   - GM
*           Westerbly Snaydley - WS
*           Gustavo Aranha     - GA
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*		4.00   GA    29/08/2015 Adapta��o das fun��es do m�dulo arvore.c para matriz.c
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo implementa um conjunto simples de fun��es para criar e
*     explorar matrizes n x n.
*     A matriz possui uma cabe�a que cont�m uma refer�ncia para um n� de origem (0,0)
*     e outra para um n� corrente da matriz.
*     Ap�s criada, uma matriz � vazia. Neste caso a origem e o n� corrente
*     ser�o nulos, embora a cabe�a esteja definida.
*     O n� corrente ser� nulo se e somente se a matriz estiver vazia.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

#include "LISTA.H"

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetFaltouMemoria = 1 ,
               /* Faltou mem�ria ao alocar dados */

         MAT_CondRetMatrizNaoExiste = 2 ,
               /* �rvore n�o existe */

         MAT_CondRetMatrizVazia = 3 ,
               /* �rvore est� vazia */

         MAT_CondRetNoEstaNaBorda = 4,
               /* N�o � poss�vel trafegar na referida dire��o j� que est� na borda da matriz */

		MAT_CondRetCoordenadaForaDaMatriz = 5
			/*Coordenadas fornecidas n�o se encontram dentro da matriz*/

   } MAT_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor do n� da matriz
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�. Guarda uma refer�ncia para os n�s adjacentes, seu conte�do
*    e suas coordenadas relativas � matriz na qual est� contido.
*
***********************************************************************/

   typedef struct tpNoMatriz {

         struct tpNoMatriz ** pNoN ;
               /* Ponteiro para Norte */

         struct tpNoMatriz ** pNoNE ;
               /* Ponteiro para Nordeste */

         struct tpNoMatriz ** pNoE ;
               /* Ponteiro para Leste */
               
         struct tpNoMatriz ** pNoSE ;
               /* Ponteiro para Sudeste */

         struct tpNoMatriz ** pNoS ;
               /* Ponteiro para Sul  */

         struct tpNoMatriz ** pNoSW ;
               /* Ponteiro par Sudoeste */

         struct tpNoMatriz ** pNoW ;
               /* Ponteiro para Oeste */

         struct tpNoMatriz ** pNoNW ;
               /* Ponteiro para Noroeste */
               
         LIS_tppLista Lista ;
               /* Ponteiro para a cabe�a da Lista */
               
        int coordenadaX;
        int coordenadaY;

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabe�a da matriz
*
*
*  $ED Descri��o do tipo
*  A cabe�a da matriz guarda os metadados relativos � matriz, al�m de refer�ncias para 
*  todos os seus n�s (por meio de um array), e em espec�fico para o n� de origem (0,0) e corrente.
*
***********************************************************************/

   typedef struct MAT_tpMatriz {

      tpNoMatriz** NosMatriz;

         tpNoMatriz ** pNoOrigem ;
               /* Ponteiro para a raiz da �rvore */

         tpNoMatriz ** pNoCorr ;
               /* Ponteiro para o n� corrente da matriz */
       
       int tamanho;
       /* Tamanho n do lado da matriz. O n�mero total de n�s da matriz se d� por n x n */

   } tpMatriz ;

/***********************************************************************
*
*  $FC Fun��o: MAT Criar matriz
*
*  $ED Descri��o da fun��o
*     Cria uma matriz vazia capaz de acomodar o n�mero de elementos especificado (n x n)
*
*  $EP Par�metros
*    $P matriz - refer�ncia de sa�da para a matriz
*    $P n - tamanho do lado da matriz (o n�mero de elementos da mesma ser� n x n)
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( tpMatriz** matriz, int n ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Destruir Matriz
*
*  $ED Descri��o da fun��o
*     Destroi a matriz especificada, liberando a mem�ria alocada por seus n�s.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser destru�da.
*     
*  $FV Valor retornado
*   MAT_CondRetMatrizNaoExiste
*   MAT_CondRetOK
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz(tpMatriz* matriz) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Insere n�
*
*  $ED Descri��o da fun��o
*     Insere um n� na posi��o (x, y) especificada, com o conte�do descrito.
*    NOTA: Esta fun��o N�O altera o n� corrente da matriz.
*
*  $EP Par�metros
*    $P x - Coordenada x
*    $P y - Coordenada y
*    $P matriz - Ponteiro para a matriz a ser manipulada
*    $P conteudoLista - vetor de ponteiros para caracteres que ser�o inseridos na lista.
*
*   $FV Valor retornado
*    MAT_CondRetMatrizNaoExiste
*    MAT_CondRetCoordenadaForaDaMatriz
*    MAT_CondRetFaltouMemoria
*     MAT_CondRetOK
*
***********************************************************************/

   MAT_tpCondRet MAT_InsereNo(int x, int y, tpMatriz* matriz, char** conteudoLista);

/***********************************************************************
*
*  $FC Fun��o: MAT Ir Norte
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Norte (x, y - 1) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrN ( tpMatriz * pMatriz );


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Sul
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Sul (x, y + 1) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/


   MAT_tpCondRet MAT_IrS( tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Leste
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Leste (x + 1, y) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrE ( tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Oeste
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Oeste (x - 1, y) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrW ( tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Noroeste
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Noroeste (x - 1, y - 1) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNW ( tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Nordeste
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Nordeste (x + 1, y - 1) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNE ( tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Sudeste
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Sudeste (x + 1, y + 1) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrSE ( tpMatriz * pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT Ir Sudoeste
*
*  $ED Descri��o da fun��o
*     Altera o n� corrente para o localizado ao Sudoeste (x - 1, y + 1) do n� corrente atual.
*
*  $EP Par�metros
*    $P matriz - Ponteiro para a matriz a ser manipulada
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEstaNaBorda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrSW ( tpMatriz * pMatriz ) ;

/***********************************************************************
*
*  $FC Fun��o: MAT Obter valor corrente
*
*  $ED Descri��o da fun��o
*     Obtem o valor do n� corrente na matriz especificada
*
*  $EP Par�metros
*     $P matriz - Ponteiro para a matriz cujo valor corrente � requerido
*    $P saida - Ponteiro para char que receber� o valor recuperado
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*
***********************************************************************/

	MAT_tpCondRet MAT_ObterValorCorr(tpMatriz* matriz, char * saida );

#undef MATRIZ_EXT

/********** Fim do m�dulo de defini��o: M�dulo �rvore **********/

#else
#endif
