-- a) dobros que recebe uma lista e produz a lista em que cada elemento é o dobro do valor correspontente na lista de entrada
dobros :: [Float] -> [Float]
dobros []= [] 
dobros (x:xs) = x*2 : dobros xs

--b) numOcorre :: Char -> String -> Int que calcula o número de vezes que um char ocorre numa string
numOcorre :: Char -> String -> Int
numOcorre _ [] = 0
numOcorre c (x:xs) | c == x = 1 + numOcorre c xs
                   | otherwise = numOcorre c xs

--c) positivos que testa se uma lista só tem elementos positivos
positivos :: [Int] -> Bool
positivos [] = True
positivos (x:xs) | x > 0 = positivos (xs)
                 | otherwise = False

--d) soPos que retira todos os elementos não positivos de uma lista de inteiros
soPos :: [Int] -> [Int] 
soPos [] = []
soPos (x:xs) | x > 0 = x : soPos xs
             | otherwise = soPos xs

--e)somaNeg  que soma todos os números negativos da lista de entrada
somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (x:xs) | x < 0 = x + somaNeg xs
               | otherwise = somaNeg xs

--f) tresUlt que devolve os ultimos três elementos de uma lista. Se a lista de entrada tiver menos de três elementos, devolve a propria lista
tresUlt :: [a] -> [a]
tresUlt [] = []
tresUlt [x] = [x]
tresUlt [x, y] = [x, y]
tresUlt [x, y, z] = [x, y, z]
tresUlt (x:xs) = tresUlt xs

--g) segundos que calcula a lista das segundas componentes dos pares
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((x,y):xs) = y : segundos xs

--h) nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool que testa se um elemento aparace na lista como primeira componente de alguns dos pares
-- Eq a diz que a deve ser uma instância da classe Eq que é usada para tipos que suportam operações de igualdade.

nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros n [] = False
nosPrimeiros n ((x,y):xs) | n == x = True
                          | otherwise = nosPrimeiros n xs

--i) sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c) que soma uma lista de triplos componente a componente
--Restrição do tipo Num, indica que o tipo a deve ser uma instância da classe do tipo Num, que é usada para representar tipos numericos, como intieros e números de ponto.
sumTriplos :: (Num a, Num b, Num c) => [(a, b, c)] -> (a, b, c)
sumTriplos [] = (0, 0, 0)
sumTriplos ((a, b, c):xs) = (a + a', b + b', c + c')
                            where (a', b', c') = sumTriplos xs 

            

