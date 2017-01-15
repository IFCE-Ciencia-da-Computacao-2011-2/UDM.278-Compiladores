from .test import Test

class AtribuicaoBooleanoTest(Test):

    def test_atribuicao_constante(self):
        self.assert_not_raises_error('bool a; a = true;')
        self.assert_not_raises_error('bool a; a = false;')

    def test_atribuicao_not(self):
        self.assert_not_raises_error('bool a; a = not false;')
        self.assert_not_raises_error('bool a; a = not true;')
        self.assert_not_raises_error('bool a; a = not a;')

    def test_atribuicao_id(self):
        self.assert_not_raises_error(
            """
            bool a, b;
            a = false;
            b = a;
            """
        )
    def test_atribuicao_id_errado(self):
        erro = 'interpretador:1:0 erro: Variável ‘a’ é do tipo ‘bool’, mas está sendo atribuído um valor do tipo ‘int’'
        self.assert_raises_error('bool a; int b; a = b;', erro)

    def test_atribuicao_valor_inteiro_em_variavel_booleana(self):
        erro = 'interpretador:1:0 erro: Variável ‘a’ é do tipo ‘bool’, mas está sendo atribuído um valor do tipo ‘int’'
        self.assert_raises_error('bool a; a = 3;', erro)

    def test_operacao_comparacao(self):
        mensagem = """
        int a, b;
        bool c;
        a = 0;
        b = 3;
        c = a {} b;
        """

        operacoes = ['<', '<=', '>', '>=', '==', '!=']
        for operacao in operacoes:
            self.assert_not_raises_error(mensagem.format(operacao))
    
    def test_operacao_parenteses(self):
        mensagem = """
        int a, b;
        bool c;
        a = 0;
        b = 3;
        c = a < (b + 3);
        """

        self.assert_not_raises_error(mensagem)

    '''
    def test_operacao_ilegal_meio_booleano(self):
        mensagem = """
        int inteiro;
        bool booleano;
        int resultado;

        resultado = {} {} {};
        """
        erro = 'erro: Variável ‘resultado’ é do tipo ‘int’, mas está sendo atribuído um valor do tipo ‘bool’'
        operacoes_ilegais = ['<', '<=', '>', '>=', '==', '!=', '%']

        for operacao in operacoes_ilegais:
            self.assert_raises_error(mensagem.format('inteiro', operacao, 'booleano'), erro)

        for operacao in operacoes_ilegais:
            self.assert_raises_error(mensagem.format('booleano', operacao, 'inteiro'), erro)
    '''