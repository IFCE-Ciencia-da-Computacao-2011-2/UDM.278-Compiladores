# Vando - Trabalho 1 de 2 de compiladores

## Execute

```bash
# Compile
sh make.sh
# Execute
./vando
```

## Tests

Due to the time taken, the tests were ~abandoned~ partially implemented
The structure of the tests is legal, you can take advantage of future work.

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

```
# Acceptable
int a1, b1, cad;
bool i,j;
a1 = 0
b1 = a1 + 40;
i = a1>b1;
j=(2+3) < (4+1);
```

