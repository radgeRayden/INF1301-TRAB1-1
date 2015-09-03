#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
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
*     Versão  Autor    Data     Observações
*		4.00   GA    29/08/2015 Adaptação das funções do módulo arvore.c para matriz.c
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar matrizes n x n.
*     A matriz possui uma cabeça que contém uma referência para um nó de origem (0,0)
*     e outra para um nó corrente da matriz.
*     Após criada, uma matriz é vazia. Neste caso a origem e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a matriz estiver vazia.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif


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
               /* Faltou memória ao alocar dados */

         MAT_CondRetMatrizNaoExiste = 2 ,
               /* Árvore não existe */

         MAT_CondRetMatrizVazia = 3 ,
               /* Árvore está vazia */

         MAT_CondRetNoEstaNaBorda = 4,
               /* Não é possível trafegar na referida direção já que está na borda da matriz */

		MAT_CondRetCoordenadaForaDaMatriz = 5
			/*Coordenadas fornecidas não se encontram dentro da matriz*/

   } MAT_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor do nó da matriz
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó. Guarda uma referência para os nós adjacentes, seu conteúdo
*    e suas coordenadas relativas à matriz na qual está contido.
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
               /* Ponteiro para a cabeça da Lista */
               
        int coordenadaX;
        int coordenadaY;

   } tpNoMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça da matriz
*
*
*  $ED Descrição do tipo
*  A cabeça da matriz guarda os metadados relativos à matriz, além de referências para 
*  todos os seus nós (por meio de um array), e em específico para o nó de origem (0,0) e corrente.
*
***********************************************************************/

   typedef struct MAT_tpMatriz {

      tpNoMatriz** NosMatriz;

         tpNoMatriz ** pNoOrigem ;
               /* Ponteiro para a raiz da árvore */

         tpNoMatriz ** pNoCorr ;
               /* Ponteiro para o nó corrente da matriz */
       
       int tamanho;
       /* Tamanho n do lado da matriz. O número total de nós da matriz se dá por n x n */

   } tpMatriz ;

/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma matriz vazia capaz de acomodar o número de elementos especificado (n x n)
*
*  $EP Parâmetros
*    $P matriz - referência de saída para a matriz
*    $P n - tamanho do lado da matriz (o número de elementos da mesma será n x n)
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( tpMatriz** matriz, int n ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir Matriz
*
*  $ED Descrição da função
*     Destroi a matriz especificada, liberando a memória alocada por seus nós.
*
*  $EP Parâmetros
*    $P matriz - Ponteiro para a matriz a ser destruída.
*     
*  $FV Valor retornado
*   MAT_CondRetMatrizNaoExiste
*   MAT_CondRetOK
*
***********************************************************************/

   void MAT_DestruirMatriz(tpMatriz* matriz) ;

/***********************************************************************
*
*  $FC Função: MAT Insere nó
*
*  $ED Descrição da função
*     Insere um nó na posição (x, y) especificada, com o conteúdo descrito.
*    NOTA: Esta função NÃO altera o nó corrente da matriz.
*
*  $EP Parâmetros
*    $P x - Coordenada x
*    $P y - Coordenada y
*    $P matriz - Ponteiro para a matriz a ser manipulada
*    $P conteudoLista - vetor de ponteiros para caracteres que serão inseridos na lista.
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
*  $FC Função: MAT Ir Norte
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Norte (x, y - 1) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Sul
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Sul (x, y + 1) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Leste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Leste (x + 1, y) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Oeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Oeste (x - 1, y) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Noroeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Noroeste (x - 1, y - 1) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Nordeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Nordeste (x + 1, y - 1) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Sudeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Sudeste (x + 1, y + 1) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Ir Sudoeste
*
*  $ED Descrição da função
*     Altera o nó corrente para o localizado ao Sudoeste (x - 1, y + 1) do nó corrente atual.
*
*  $EP Parâmetros
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
*  $FC Função: MAT Obter valor corrente
*
*  $ED Descrição da função
*     Obtem o valor do nó corrente na matriz especificada
*
*  $EP Parâmetros
*     $P matriz - Ponteiro para a matriz cujo valor corrente é requerido
*    $P saida - Ponteiro para char que receberá o valor recuperado
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*
***********************************************************************/

	MAT_tpCondRet MAT_ObterValorCorr(tpMatriz* matriz, char * saida );

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo árvore **********/

#else
#endif
