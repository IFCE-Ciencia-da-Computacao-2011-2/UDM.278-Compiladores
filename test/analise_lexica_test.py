from .test import Test

class AnaliseLexicaTest(Test):

    def test_nome_variavel_invalida(self):
        erro = 'interpretador:1:0 erro: ‘{}’ é um nome de variável inválido'
        
        self.assert_raises_error('1a', erro.format('1a'))
        self.assert_raises_error('mateus.moura', erro.format('mateus.moura'))
        self.assert_raises_error('mateus.moura.silva', erro.format('mateus.moura.silva'))

    def test_ponto_flutuante(self):
        erro = 'interpretador:1:0 erro: ‘{}’ - Pontos flutuantes não são aceitos pela linguagem'
        
        self.assert_raises_error('125.3', erro.format('125.3'))
        self.assert_raises_error('125.',  erro.format('125.'))
        self.assert_raises_error('125.3e-3', erro.format('125.3e-3'))
        self.assert_raises_error('125.3e+3', erro.format('125.3e+3'))
