rm vando

cd codigo
rm regras.tab.c regras.tab.h
rm gramatica.tab.c gramatica.tab.h

bison -d gramatica.y
flex regras.lex

gcc -o vando regras.tab.c logica.c tabela.c gramatica.tab.c mensagem.c arvore_sintatica.c arvore_sintatica_imprimir.c
mv vando ..
cd ..
#python3 test.py
