# Vando - Trabalho 1 de 2 de compiladores

## Execute

```bash
# Em Tools > Terminal
sh make.sh
```

## Tests

### Execute

```bash
python3 test.py
```

### Add new tests

1. Add a method in a `test/*_test.py` file or create a new `test/*_test.py` extending `Test` (`test/test.py`);
2. If a new test class has been created, import it in `./test.py`.

## References
 * **Codio SSH**: https://codio.com/docs/ide/boxes/access/ssh-access/
 * **Terminal colors:** http://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
 * **Introdução aos Compiladores - Andrei de A. Formiga:**
   * **Book:** http://producao.virtual.ufpb.br/books/tautologico/compiladores-livro/livro/livro.pdf
   * **Code:** http://producao.virtual.ufpb.br/books/tautologico/compiladores-livro/livro/capitulos/code/cap2/minic/
 * **Flex & Bison:** http://shop.oreilly.com/product/9780596155988.do
 * **Flex examples:** https://github.com/westes/flex/tree/master/examples/manual
 * **?**: http://www.admb-project.org/tools/flex/compiler.pdf
 * **AST in C**: https://efxa.org/2014/05/25/how-to-create-an-abstract-syntax-tree-while-parsing-an-input-stream/

## Grammar

### Variables definition

```
# Acceptable
int a, b, c;
int a, b; bool c;
# Unnacceptable
a int
int a, b, c
int a  b, c;
int bool;
```

```
DEFINICAO_VARIAVEIS -> TIPO DEFINICAO_VARIAVEIS_MEIO
                    |  TIPO DEFINICAO_VARIAVEL_FIM
DEFINICAO_VARIAVEIS_MEIO -> VARIAVEL , DEFINICAO_VARIAVEIS_MEIO
                         |  VARIAVEL , DEFINICAO_VARIAVEL_FIM
DEFINICAO_VARIAVEL_FIM -> VARIAVEL ;

TIPO -> int | bool
```

### Variables attributions

### Numerical expressions

### Boolean expressions

```
# Acceptable
a = true;
a = false;
b = a < a2;
c = not a;
# Unnacceptable
d = not 2;
```

```
ATRIBUICAO -> VARIAVEL = EXPRESSAO
EXPRESSAO  -> EXPRESSAO
           |  OPERACAO_INICIO EXPRESSAO
           |  ( EXPRESSAO )

OPERACAO_INICIO -> not

// Definir ordem
OPERACAO_MEIO -> <
              |  <=
              |  >
              |  >=
              |  ==
              |  !=
              |  and
              |  or
```
