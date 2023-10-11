**Exercício 1**
1. Indique como é que o interpretador de Haskell avalia as expressoes das alıneas que se seguem, apresentando a cadeia de reducao de cada uma dessas expressoes (i.e., os varios passos intermedios ate se chegar ao valor final).

a) Considere a seguinte definicao:
funA :: [Double] -> Double
funA [] = 0
funA (y:ys) = y^2 + (funA ys)
Diga, justificando, qual e o valor de funA [2,3,5,1].

O valor de funA vai ser determinado da seguinte forma: 
Sendo que inicialmente a string não é vazia, ele vai fazer funA (2:[3,5,1]) = 2^2 + (funA[3,5,1]). Logo 2^2 + 3^2 + funA[5,1] ... até a lista ser vazia e chegar a um ponto em que temos 2^2 + 3^2 + 5^2 + 1^2 + [] = 40


