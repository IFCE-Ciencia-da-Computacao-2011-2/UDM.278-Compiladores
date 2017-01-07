rm regras.tab.c regras.tab.h
rm gramatica.tab.c gramatica.tab.h
rm vando

bison -d gramatica.y
#flex -DYY_DECL="Token * yylex()" regras.lex
flex regras.lex
gcc -o vando regras.tab.c logica.c codigo.c tabela.c gramatica.tab.c mensagem.c
./vando #txt/teste.txt
#./vando txt/teste_erro.txt
