from .test import Test

class DeclaracaoVariaveisTest(Test):

    def test_declaracao_case_sensitive(self):
        self.assert_raises_error('INT a;', '1.1-1.1: error: syntax error')

    def test_declaracao_variaveis_iguais(self):
        mensagem1 = """
int a;
int a;
        """
        mensagem2 = 'int a, a, b;';
        mensagem3 = 'int a, b, a;';

        erro = 'interpretador:{}:0 erro: Variável ‘a’ já foi declarado previamente'

        self.assert_raises_error(mensagem1, erro.format(2))
        self.assert_raises_error(mensagem2, erro.format(1))
        self.assert_raises_error(mensagem3, erro.format(1))

    def test_declaracao_variaveis_nome_constante_1(self):
        erro = 'interpretador:1:0 erro: Palavras reservadas e números são nomes de variáveis inválidos'

        self.assert_raises_error('int true;', erro)
        self.assert_raises_error('int false;', erro)
        self.assert_raises_error('int 1;', erro)
        self.assert_raises_error('int b1, 1, b2;', erro)
        self.assert_raises_error('int 1, b1, b2;', erro)
        self.assert_raises_error('int b1, b2, 1;', erro)
