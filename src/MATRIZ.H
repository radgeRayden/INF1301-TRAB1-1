#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo árvore
*
*  Arquivo gerado:              MATRIZ.H
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
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar árvores binárias.
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente da árvore.
*     A cada momento o módulo admite no máximo uma única árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     A árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente será nulo se e somente se a árvore estiver vazia.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif


/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetNaoCriouRaiz = 1 ,
               /* Não criou nó raiz */

         MAT_CondRetErroEstrutura = 2 ,
               /* Estrutura da árvore está errada */

         MAT_CondRetNaoEhFolha = 3 ,
               /* Não é folha relativa à direção de inserção desejada */

         MAT_CondRetMATRIZNaoExiste = 4 ,
               /* Árvore não existe */

         MAT_CondRetMATRIZVazia = 5 ,
               /* Árvore está vazia */

         MAT_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         MAT_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho na direção desejada */

         MAT_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar árvore
*
*  $ED Descrição da função
*     Cria uma nova árvore vazia.
*     Caso já exista uma árvore, esta será destruída.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( void ) ;


/***********************************************************************
*
*  $FC Função: ARV Destruir árvore
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da árvore, anulando a árvore corrente.
*     Faz nada caso a árvore corrente não exista.
*
***********************************************************************/

   void MAT_DestruirMatriz(void* matriz) ;


/***********************************************************************
*
*  $FC Função: ARV Adicionar filho à esquerda
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso não seja folha para a esquerda
*
***********************************************************************/

   //ARV_tpCondRet ARV_InserirEsquerda( char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: ARV Adicionar filho à direita
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso não seja folha para a direita
*
***********************************************************************/

   //ARV_tpCondRet ARV_InserirDireita( char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó pai
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetMATRIZNaoExiste
*     ARV_CondRetMATRIZVazia
*     ARV_CondRetNoEhRaiz
*
***********************************************************************/

   //ARV_tpCondRet ARV_IrPai( void ) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó à esquerda
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetMATRIZNaoExiste
*     ARV_CondRetMATRIZVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   //ARV_tpCondRet ARV_IrNoEsquerda( void ) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó à direita
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetMATRIZNaoExiste
*     ARV_CondRetMATRIZVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   //ARV_tpCondRet ARV_IrNoDireita( void ) ;


/***********************************************************************
*
*  $FC Função: ARV Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetMATRIZNaoExiste
*     ARV_CondRetMATRIZVazia
*
***********************************************************************/

   //ARV_tpCondRet ARV_ObterValorCorr( char * ValorParm ) ;

#undef MATRIZ_EXT

/********** Fim do módulo de definição: Módulo árvore **********/

#else
#endif
