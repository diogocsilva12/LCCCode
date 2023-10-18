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
inits l = inits (init l) ++ [l]

--14 apresente uma definição recursiva da função tails que calcula a lista dos prefixos de uma lista

tails :: [a] -> [[a]]
tails [] = [[]]
tails (x:xs) = (x:xs) : tails xs

--15 heads que recebe uma lista e produz a lista com o primeiro elemento de cada lista

heads :: [[a]] -> [a]
heads [] = []
heads ([]:ys) = heads ys
heads ((x:xs):ys) = x : heads ys

--16 total que recebe uma lista de listas e conta o total de elementos

total :: [[a]] -> Int
total [[]] = 0
total ([]:ys) = total ys
total ((x:xs):ys) = 1 + total (xs:ys)

--17 fun que recebe uma lista de triplo e produz a lista de pares com o primeiro e o terceiro elemento de cada triplo.

fun ::[(a,b,c)] -> [(a,c)]
fun [] = []
fun ((x,y,z):ys) = (x,z) : fun ys

--18. Defina a funcao cola :: [(String,b,c)] -> String que recebe uma lista de triplos e concatena as strings que estao na primeira componente dos triplos.

cola :: [(String,b,c)] -> String
cola [] = ""
cola ((s,y,z):ys) = s ++ cola ys

{-19. Defina a funcao idade :: Int -> Int -> [(String,Int)] -> [String] que recebe o ano,
a idade e uma lista de pares com o nome e o ano de nascimento de cada pessoa, e devolve a
listas de nomes das pessoas que nesse ano atingirao ou ja ultrapassaram a idade indicada.
Por exemplo, idade 2021 26 [("rui",1995), ("maria",2009), ("ana",1947)] corresponde
a ["rui","ana"].
-}

idade :: Int -> Int -> [(String,Int)] -> [String]
idade _ _ [] = []
idade ano idademin ((n,a):xs) | ano - a >= idademin = n : idade ano idademin xs
                              | otherwise = idade ano idademin xs

{-20. Apresente uma definicao recursiva da funcao,
powerEnumFrom :: Int -> Int -> [Int]
que dado um valor n e um valor m constroi a lista [n^0, . . . , n^m−1].
-}

powerEnumFrom :: Int -> Int -> [Int]    --TENTAR DECORAR ESTA
powerEnumFrom n 1 = [1]
powerEnumFrom n m
    | m > 1 = powerEnumFrom n (m - 1) ++ [n^(m-1)]
    | otherwise = []

--21 isPrime :: Int -> Bool que dado um int maior ou igual que 2 determina se o número é primo.
isPrime :: Int -> Bool
isPrime n = n >= 2 && isPrimeCheck n 2

isPrimeCheck :: Int -> Int -> Bool
isPrimeCheck n m |m*m > n = True
                 |mod n m == 0 = False
                 |otherwise = isPrimeCheck n (m+1)


--22 isPrefix que testa se uma lista é prefixo de outra 
isPrefixOf :: Eq a => [a] -> [a] -> Bool
isPrefixOf [] _ = True
isPrefixOf (x:xs) (y:ys) | x == y = isPrefixOf xs ys
                         | otherwise = False

--23 isSuffix que testa se uma lista é sufixo de outra  TENTAR DECORAR ESTA
isSuffixOf :: Eq a => [a] -> [a] -> Bool
isSuffixOf [] _ = True
isSuffixOf (_:_) [] = False
isSuffixOf xs ys = (last xs == last ys) && isSuffixOf (init xs) (init ys)

--24 

--25
elemIndices :: Eq a => a -> [a] -> [Int]
elemIndices _ [] = []
elemIndices x (h:t)
    | x == h = 0 : map (+1) (elemIndices x t)
    | otherwise = map (+1) (elemIndices x t)
