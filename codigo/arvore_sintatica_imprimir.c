#include <stdio.h>
#include <stdlib.h>
#include "arvore_sintatica.h"
#include "mensagem.h"

//////////////////////////////
// Declaração de funções de impressão
//////////////////////////////
typedef void (* FuncaoImpressao)(NoAST * no);

static FuncaoImpressao impressao_factory(NoAST * no);

static void ast_imprimir_tipo_constante(NoAST * no);
static void ast_imprimir_tipo_operacao_meio(NoAST * no);

//////////////////////////////
// Identificador
//////////////////////////////

static unsigned long int identificador = 0;

static char * gerar_identificador(char * nome) {
    identificador += 1;
    return mensagem_preparar("%s_%d", nome, identificador);
}

//////////////////////////////
// Imprimir
//////////////////////////////

void ast_imprimir(NoAST * raiz) {
    printf("Insira o código a seguir em http://www.webgraphviz.com/\n");
    
    // a [label="node"]; b [label="node"]; a->b
    printf("\n");
    printf("digraph program {\n");
    
    raiz->pai_identificador = "RAIZ__expressao__provisorio";
    FuncaoImpressao imprimir = impressao_factory(raiz);

    if (imprimir != NULL)
        imprimir(raiz);

    printf("}\n");
}

static FuncaoImpressao impressao_factory(NoAST * no) {
    if (no->tipo == AST_TIPO_CONSTANTE)
        return *ast_imprimir_tipo_constante;
    if (no->tipo == AST_TIPO_OPERACAO_MEIO)
        return *ast_imprimir_tipo_operacao_meio;

    return NULL;
}

static void ast_imprimir_tipo_constante(NoAST * no) {
    NoConstanteAST * constante = (NoConstanteAST *) no->no;

    no->identificador = gerar_identificador("constante");
    char * constante_identificador = gerar_identificador("atomo");

    // Pai
    if (no->pai_identificador != NULL)
        printf("%s -> %s; \n", no->pai_identificador, no->identificador);

    // Valor
    printf("%s [label=\"%s\"]; ", no->identificador, "atomo");

    if (no->simbolo_tipo == SIMBOLO_TIPO_INTEIRO)
        printf("%s [label=\"%d\"]; ", constante_identificador, constante->valor);
    else
        printf("%s [label=\"%s\"]; ", constante_identificador, constante->valor == FALSE ? "false" : "true");

    printf("%s -> %s; \n", no->identificador, constante_identificador);

    free(no->identificador);
    free(constante_identificador);
}

static void ast_imprimir_tipo_operacao_meio(NoAST * no) {
    FuncaoImpressao imprimir;
    NoOperacaoMeioAST * operacao_meio = (NoOperacaoMeioAST *) no->no;

    no->identificador = no->pai_identificador;

    char * expressao_esquerda_identificador = gerar_identificador("expressao");
    char * expressao_direita_identificador  = gerar_identificador("expressao");
    char * operacao_identificador = gerar_identificador("operacao");

    // Pai
    // Reaproveita o do pai. Por isso, não desaloca no fim

    // Esquerda
    printf("%s [label=\"%s\"]; ", expressao_esquerda_identificador, "expressao");
    printf("%s -> %s; \n", no->identificador, expressao_esquerda_identificador);

    operacao_meio->no_esquerdo->pai_identificador = expressao_esquerda_identificador;
    imprimir = impressao_factory(operacao_meio->no_esquerdo);
    imprimir(operacao_meio->no_esquerdo);

    // Meio
    printf("%s [label=\"%s\"]; ", operacao_identificador, operacao_meio->operacao);
    printf("%s -> %s; \n", no->identificador, operacao_identificador);

    // Direita
    printf("%s [label=\"%s\"]; ", expressao_direita_identificador, "expressao");
    printf("%s -> %s; \n", no->identificador, expressao_direita_identificador);

    operacao_meio->no_direito->pai_identificador = expressao_direita_identificador;
    imprimir = impressao_factory(operacao_meio->no_direito);
    imprimir(operacao_meio->no_direito);
    
    free(expressao_esquerda_identificador);
    free(expressao_direita_identificador);
    free(operacao_identificador);
}
