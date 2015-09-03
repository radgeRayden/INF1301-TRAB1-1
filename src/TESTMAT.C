/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
*
*  Nome da base de software:     Exemplo de teste automatizado
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
*       1.00   GM   01/00/2015  Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo Matriz. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo Matriz:
*
*     =criar       - chama a função ARV_CriarArvore( )
*     =insdir <Char>
*                   - chama a função ARV_InserirDireita( <Char> )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     "=insesq" <Char>
*                   - chama a função ARV_InserirEsquerda( <Char> )
*     "=irpai"      - chama a função ARV_IrPai( )
*     "=iresq"      - chama a função ARV_IrEsquerda( )
*     "=irdir"      - chama a função ARV_IrDireita( )
*     "=obter" <Char>
*                   - chama a função ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a função ARV_DestruirArvore( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include	<stdlib.h>
#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "matriz.h"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_MAT_CMD     "=criar"
#define     DESTROI_CMD       "=destroi"
#define     INS_NO_CMD        "=inserir"
#define     IR_NORTE_CMD      "=irN"
#define     IR_NORDESTE_CMD   "=irNE"
#define     IR_LESTE_CMD      "=irE"
#define     IR_SUDESTE_CMD    "=irSE"
#define     IR_SUL_CMD        "=irS"
#define     IR_SUDOESTE_CMD   "=irSW"
#define     IR_OESTE_CMD      "=irW"
#define     IR_NOROESTE_CMD   "=irNW" 
#define     OBTER_VAL_CMD     "=obter"
/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TMAT Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/
   tpMatriz* pMatriz[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      MAT_tpCondRet CondRetObtido   = MAT_CondRetOK ;
      MAT_tpCondRet CondRetEsperada = MAT_CondRetOK ;
      MAT_tpCondRet CondRetDada     = MAT_CondRetOK ;
                                      /* inicializa para qualquer coisa */

      char ValorEsperado = '?'  ;
      char ValorObtido   = '!'  ;
      char ValorDado     = '\0' ;
      int  NumLidos = -1 ;
      int nTemp, xTemp, yTemp, indexTemp;
      char c; //char que armazenará a saída do obter valor corrente
	  char* conteudoLista[1];
      TST_tpCondRet Ret ;

      /* Testar MAT Criar Matriz */

         if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iii" ,
                               &indexTemp, &nTemp, &CondRetEsperada) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarMatriz( &pMatriz[indexTemp], nTemp ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar matriz." );

         } /* fim ativa: Testar MAT Criar Matriz */

      /* Testar MAT Inserir Nó */
         else if ( strcmp( ComandoTeste , INS_NO_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iciii" ,
                               &indexTemp, &ValorDado , &xTemp, &yTemp, &CondRetEsperada ) ;
            if ( NumLidos != 5 )
            {
               return TST_CondRetParm ;
            } /* if */

			conteudoLista[0] = (char*)malloc(sizeof(char));
			if(conteudoLista[0] == NULL) {
				return TST_CondRetMemoria; //erro de alocação durante o teste
			}
			*conteudoLista[0] = ValorDado;
            CondRetObtido =  MAT_InsereNo(xTemp, yTemp, pMatriz[indexTemp], conteudoLista);

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir o nó." );

         } /* fim ativa: Testar MAT Inserir Nó */

      /* Testar MAT Ir Norte */

         else if ( strcmp( ComandoTeste , IR_NORTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrN ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Norte." );

         } /* fim ativa: Testar MAT Ir Norte */

 /* Testar MAT Ir Nordeste */

         else if ( strcmp( ComandoTeste , IR_NORDESTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrNE ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Nordeste." );

         } /* fim ativa: Testar MAT Ir Nordeste */

       /* Testar MAT Ir Leste */

         else if ( strcmp( ComandoTeste , IR_LESTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrE ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Leste." );

         } /* fim ativa: Testar MAT Ir Leste */
 
       /* Testar MAT Ir Sudeste */

         else if ( strcmp( ComandoTeste , IR_SUDESTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrSE ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Sudeste." );

         } /* fim ativa: Testar MAT Ir Sudeste */

       /* Testar MAT Ir Sul */

         else if ( strcmp( ComandoTeste , IR_SUL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrS ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Sul." );

         } /* fim ativa: Testar MAT Ir Sul */

      /* Testar MAT Ir Sudoeste */

         else if ( strcmp( ComandoTeste , IR_SUDOESTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrSW ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Sudoeste." );

         } /* fim ativa: Testar MAT Ir Sudoeste */

      /* Testar MAT Ir Oeste */

         else if ( strcmp( ComandoTeste , IR_OESTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrW ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Oeste." );

         } /* fim ativa: Testar MAT Ir Oeste */

      /* Testar MAT Ir Noroeste */

         else if ( strcmp( ComandoTeste , IR_NOROESTE_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" , &indexTemp, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_IrNW ( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao mover ao Noroeste." );

         } /* fim ativa: Testar MAT Ir NOROESTE */

      /* Testar MAT Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ici", &indexTemp, &ValorEsperado, &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ObterValorCorr( pMatriz[indexTemp], &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );
			if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conteúdo do nó está errado." ) ;

         } /* fim ativa: Testar MAT Obter valor corrente */

      /* Testar MAT Destruir Matriz */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &indexTemp, &CondRetEsperada) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm;
            } /* if */

            CondRetObtido = MAT_DestruirMatriz( pMatriz[indexTemp] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir Matriz." );
		 }
 /* fim ativa: Testar MAT Destruir Matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TMAT Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

