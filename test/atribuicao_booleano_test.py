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

    def test_atribuicao_valor_inteiro_em_variavel_booleana(self):
        erro = 'macarronada'
        self.assert_raises_error('bool a; a = 3;', erro)

    def test_operacao_ilegal_meio_booleano(self):
        mensagem = """
        int inteiro;
        bool booleano;
        int resultado;

        resultado = {} {} {};
        """
        erro = 'macarronada'
        operacoes_ilegais = ['<', '<=', '>', '>=', '==', '!=', '%']

        for operacao in operacoes_ilegais:
            self.assert_raises_error(mensagem.format('inteiro', operacao, 'booleano'), erro)

        for operacao in operacoes_ilegais:
            self.assert_raises_error(mensagem.format('booleano', operacao, 'inteiro'), erro)
