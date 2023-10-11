--1 Apresentar uma definição recursiva da função enumFromTo :: Int -> Int -> [Int] que constroi a lista dos números inteiros compreendidos entre dois limites .
myEnumFromTo :: Int -> Int -> [Int]
myEnumFromTo x y | x > y = []
                 | otherwise = x : myEnumFromTo (x+1) y

--2 Apresentar uma definição recursiva da função enumFromThenTo :: Int -> Int -> Int -> [Int] que constroi a lista dos números inteiros compreendidos entre dois limites e espaçados por um valor constante
myEnumFromThenTo :: Int -> Int -> Int -> [Int]
myEnumFromThenTo x y z | x > y = []
                       | otherwise = x : myEnumFromThenTo (x+z) y z


--3 Definição recursiva de (++) que concatena duas listas
myconc :: [a] -> [a] -> [a]
myconc [] l = l
myconc (x:xs) l = x : myconc xs l 

--4 Definição recursiva de (!!) que dada uma lista e um inteiro, calcula o elemento da lista que se encontra nessa posição 
myfind :: [a] -> Int -> a
myfind (x:xs) 0 = x
myfind (x:xs) n = myfind xs (n-1)

--5 Apresente uma definicao recursiva da funcao (pre-definida) reverse :: [a] -> [a] que dada uma lista calcula uma lista com os elementos dessa lista pela ordem inversa.
myreverse :: [a] -> [a]
myreverse [] = []
myreverse (x:xs) =  myreverse xs ++ [x]