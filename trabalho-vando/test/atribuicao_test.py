from .test import Test

class AtribuicaoTest(Test):

    def test_atribuicao_variavel_nao_definida(self):
        erro = 'interpretador:1:0 erro: Variável ‘b’ não definida'

        self.assert_raises_error('bool a; b = true;', erro)
