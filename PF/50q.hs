--1 Apresentar uma definição recursiva da função enumFromTo :: Int -> Int -> [Int] que constroi a lista dos números inteiros compreendidos entre dois limites .
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}
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


--6 Take que dado um inteiro n e uma lista l calcula a lista com os n primeiros elementos de l.
myTake :: Int -> [a] -> [a] 
myTake 0 _ = []
myTake _ [] = []
myTake n (x:xs) = x : myTake (n-1) xs

--7 drop que dado um inteiro n e uma lista l calcula a lista sem os n primeiros elementos de l

myDrop :: Int -> [a] -> [a]
myDrop 0 xs = xs
myDrop _ [] = []
myDrop n (x:xs) = myDrop (n-1) xs

--8 zip que constroi a lista de pares a partir de duas listas
myzip :: [a] -> [b] -> [(a,b)]
myzip [] _ = []
myzip _ [] = []
myzip (x:xs) (y:ys) = (x, y) : myzip xs ys

--9 Definição recursiva da função replicate que dado um inteiro n e um elemento x constroi uma lista com n elementos, todos iguais a x.Applicative

myreplicate :: Int -> a -> [a]
myreplicate 0 _ = []
myreplicate n x = x : myreplicate (n-1) x

--10 Definição recursiva de intersperse que dado um elemento e uma lista, constrói uma lista em que o elemento fornecido é intercalado entre os elementos de uma lista fornecida.

myinter :: a -> [a] -> [a]
myinter _ [] = []
myinter n [x] = [x]
myinter n (x:xs) = x : n : myinter n xs

--11 group :: Eq a => [a] -> [[a]] que agrupa elementos iguais e consecutivos de uma lista
--dificial
--mygroup :: Eq a => [a] -> [[a]]
--mygroup [] = [[]]
--mygroup (x:xs) | x == xs = x:xs: mygroup xs
--               | otherwise = [x] : mygroup xs
               
--12 concat apresenta uma definição recursiva que concatena as listas de uma lista
myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat ((x:xs):ys) = x : myconcat (xs:ys)

--13 inits que calcula a lista dos prefixos de uma lista

inits :: [a] -> [[a]]
inits [] = [[]]
inits (x:xs) = [] : map (x:) (inits xs)

--14 apresente uma definição recursiva da função tails que calcula a lista dos prefixos de uma lista

tails :: [a] -> [[a]]
tails [] = [[]]
tails (x:xs) = (x:xs) : tails xs

--15 heads que recebe uma lista e produz a lista com o primeiro elemento de cada lista

heads :: [[a]] -> [a]
heads [] = []
heads ([]:ys) = heads ys
heads ((x:xs):ys) = x : heads ys 