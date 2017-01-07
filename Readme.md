# Vando - Trabalho 1 de 2 de compiladores

## Executar

```bash
# Em Tools > Terminal
sh make.sh
```

## References
 * **Codio SSH**: https://codio.com/docs/ide/boxes/access/ssh-access/
 * **Terminal colors:** http://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
 * **Introdução aos Compiladores - Andrei de A. Formiga:**
   * **Book:** http://producao.virtual.ufpb.br/books/tautologico/compiladores-livro/livro/livro.pdf
   * **Code:** http://producao.virtual.ufpb.br/books/tautologico/compiladores-livro/livro/capitulos/code/cap2/minic/
 * **Flex & Bison:** http://shop.oreilly.com/product/9780596155988.do
 * **Flex examples:** https://github.com/westes/flex/tree/master/examples/manual
 * **?**: http://www.admb-project.org/tools/flex/compiler.pdf

## Grammar

### Variables definition

```
# Acceptable
int a, b, c;
int a, b, c;
# Unnacceptable
a int
int a, b, c
int a  b, c;
int bool;
```

```
DEFINICAO_VARIAVEIS -> TIPO DEFINICAO_VARIAVEIS_MEIO
                    |  TIPO DEFINICAO_VARIAVEL_FIM
DEFINICAO_VARIAVEIS_MEIO -> VARIAVEL VIRGULA DEFINICAO_VARIAVEIS_MEIO
                         |  VARIAVEL VIRGULA DEFINICAO_VARIAVEL_FIM
DEFINICAO_VARIAVEL_FIM -> VARIAVEL PONTO_VIRGULA

TIPO -> int | bool

VIRGULA       -> ,
PONTO_VIRGULA -> ;
```

### Variables attributions

### Numerical expressions

### Boolean expressions
