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

--9 Definição recursiva da função replicate que dado um inteiro n e um elemento x constroi uma lista com n elementos, todos iguais a x.

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

--26
{-6. Apresente uma definicao recursiva da funcao (pre-definida) nub :: Eq a => [a] -> [a] que
calcula uma lista com os mesmos elementos da recebida, sem repeticoes.
Por exemplo, nub [1,2,1,2,3,1,2] corresponde a [1,2,3].-}

mynub :: Eq a => [a] -> [a]
mynub [] = []
mynub (x:xs) | x `elem` xs = mynub xs
             | otherwise = x : mynub xs

--27 
{- Apresente uma definicao recursiva da funcao (pre-definida) delete :: Eq a => a -> [a]-> [a] que retorna a lista resultante de remover (a primeira ocorrencia de) um dado elemento
de uma lista.
Por exemplo, delete 2 [1,2,1,2,3,1,2] corresponde a [1,1,2,3,1,2]. Se nao existir nenhuma ocorrencia a funcao devera retornar a lista recebida-}

mydelete :: Eq a => a -> [a] -> [a]
mydelete n [] = []
mydelete n (x:xs) | n == x = xs
                  | otherwise = x: mydelete n xs


{-28. Apresente uma definicao recursiva da funcao (pre-definida) (\\):: Eq a => [a] -> [a] -> [a] que retorna a lista resultante de remover (as primeiras ocorrˆencias) dos elementos da
segunda lista da primeira.
Por exemplo, (\\)[1,2,3,4,5,1] [1,5] corresponde a [2,3,4,1].-}

mytracos :: Eq a => [a] -> [a] -> [a]
mytracos [] _ = []
mytracos l1 [] = l1
mytracos l1 (y:ys) = mytracos (mydelete y l1) ys

{-29
Apresente uma definicao recursiva da funcao (pre-definida) union :: Eq a => [a] -> [a] -> [a] que retorna a lista resultante de acrescentar `a primeira lista os elementos da segunda
que nao ocorrem na primeira.
Por exemplo, union [1,1,2,3,4] [1,5] corresponde a [1,1,2,3,4,5].
-}

myunion :: Eq a => [a] -> [a] -> [a]
myunion [] l = l
myunion l [] = l
myunion l (x:xs) | x `elem` l = myunion l xs
                 | otherwise = myunion (l ++ [x]) xs

{-30. Apresente uma definicao recursiva da funcao (pre-definida) intersect :: Eq a => [a] -> [a] -> [a] que retorna a lista resultante de remover da primeira lista os elementos que nao
pertencem a segunda.
Por exemplo, intersect [1,1,2,3,4] [1,3,5] corresponde a [1,1,3].-}

myintersect :: Eq a => [a] -> [a] -> [a]
myintersect [] l = []
myintersect l [] = l
myintersect (x:xs) l2 | x `elem` l2 = x:myintersect xs l2
                      | otherwise = myintersect xs l2

{-31. Apresente uma definicao recursiva da funcao (pre-definida) insert :: Ord a => a -> [a]-> [a] que dado um elemento e uma lista ordenada retorna a lista resultante de inserir
ordenadamente esse elemento na lista.
Por exemplo, insert 25 [1,20,30,40] corresponde a [1,20,25,30,40]-}

myinsert :: Ord a => a -> [a]-> [a]
myinsert n [] = [n]
myinsert n (x:xs) | n <= x = n:x:xs
                  | otherwise = x: myinsert n xs

{-32. Apresente uma definicao recursiva da funcao (pre-definida) unwords :: [String] -> String que junta todas as strings da lista numa so, separando-as por um espaco.
Por exemplo, unwords ["Programacao", "Funcional"] corresponde a "Programacao Funcional".-}

myunwords :: [String] -> String
myunwords [] = ""
myunwords (x:xs) = x ++ " " ++ myunwords xs

{-33 Apresente uma definicao recursiva da funcao (pre-definida) unlines :: [String] -> String que junta todas as strings da lista numa so, separando-as pelo caracter ’\n’.
Por exemplo, unlines ["Prog", "Func"] corresponde a "Prog\nFunc\n".-}

myunlines :: [String] -> String
myunlines [] = ""
myunlines (x:xs) = x ++ "\n" ++ myunlines xs

{-34. Apresente uma definicao recursiva da funcao pMaior :: Ord a => [a] -> Int que dada uma lista nao vazia, retorna a posicao onde se encontra o maior elemento da lista. As posi¸c˜oes
da lista comecam em 0, i.e., a funcao devera retornar 0 se o primeiro elemento da lista for o maior. !! DECORAR -}


pMaior :: Ord a => [a] -> Int
pMaior [_] = 0
pMaior (h:t)
    | h >= (t !! x) = 0
    | otherwise = 1 + x
    where x = pMaior t

{-35. Apresente uma definicao recursiva da funcao (pre-definida) lookup :: Eq a => a -> [(a,b)] -> Maybe b que retorna uma lista constru´ıda a partir de elementos de uma lista (o segundo
argumento) atendendo a uma condicao dada pelo primeiro argumento.
Por exemplo, lookup ’a’ [(’a’,1),(’b’,4),(’c’,5)] corresponde a lista Just 1.-}

mylookup :: Eq a => a -> [(a,b)] -> Maybe b
mylookup n [] = Nothing
mylookup n ((x,xs):ys) | n == x = Just xs
                       | otherwise = mylookup n ys

{-36 Defina a funcao preCrescente :: Ord a => [a] -> [a] calcula o maior prefixo crescente de uma lista.
Por exemplo, preCrescente [3,7,9,6,10,22] corresponde a [3,7,9].-}
preCrescente :: Ord a => [a] -> [a]
preCrescente [] = []
preCrescente (x:y:xs) | x <= y = x : preCrescente (y:xs)
                      | otherwise = [x]

{-37. Apresente uma definicao recursiva da funcao iSort :: Ord a => [a] -> [a] que calcula
o resultado de ordenar uma lista. Assuma, se precisar, que existe definida a funcao insert
:: Ord a => a -> [a] -> [a] que dado um elemento e uma lista ordenada retorna a lista
resultante de inserir ordenadamente esse elemento na lista.-}

iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort (x:xs) = myinsert x (iSort xs)

{-
38. Apresente uma definicao recursiva da funcao menor :: String -> String -> Bool que
dadas duas strings, retorna True se e so se a primeira for menor do que a segunda, segundo
a ordem lexicografica (i.e., do dicionario)
Por exemplo, menor "sai" "saiu" corresponde a True enquanto que menor "programacao"
"funcional" corresponde a False.
-}
--isto não faz comparar lexiografica mas sim comparação por tamanho de strings
menor :: String -> String -> Bool
menor "" s2 = True
menor s1 "" = False
menor s1 s2 | length s1 < length s2 = True
            | otherwise = False


-- podemos comparar chars em ordem lexiografica se usarmos < ou >.
menor2 :: String -> String -> Bool
menor2 "" s2 = True
menor2 s1 "" = False
menor2 (x:xs) (y:ys) | x < y = True
                     | x == y = menor2 xs ys
                     |otherwise = False

{-39. Considere que se usa o tipo [(a,Int)] para representar multi-conjuntos de elementos de a.
Considere ainda que nestas listas nao ha pares cuja primeira componente coincida, nem cuja
segunda componente seja menor ou igual a zero.
Defina a funcao elemMSet :: Eq a => a -> [(a,Int)] -> Bool que testa se um elemento
pertence a um multi-conjunto.
Por exemplo, elemMSet ’a’ [(’b’,2), (’a’,4), (’c’,1)] corresponde a True enquanto
que elemMSet ’d’ [(’b’,2), (’a’,4), (’c’,1)] corresponde a False.-}

elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet n [] = False
elemMSet n ((x,xs):ys) | n == x = True
                       | otherwise = elemMSet n ys

{-40. Considere que se usa o tipo [(a,Int)] para representar multi-conjuntos de elementos de a.
Considere ainda que nestas listas nao ha pares cuja primeira componente coincida, nem cuja
segunda componente seja menor ou igual a zero.
Defina a funcao converteMSet :: [(a,Int)] -> [a] que converte um multi-conjuto na
lista dos seus elementos
Por exemplo, converteMSet [(’b’,2), (’a’,4), (’c’,1)] corresponde a "bbaaaac".-}

converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((x,xs):ys) | xs > 0 = x:converteMSet ((x,xs-1):ys)
                         | otherwise = converteMSet ys

{-41. Considere que se usa o tipo [(a,Int)] para representar multi-conjuntos de elementos de a.
Considere ainda que nestas listas nao ha pares cuja primeira componente coincida, nem cuja
segunda componente seja menor ou igual a zero.
Defina a funçao insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)] que acrescenta
um elemento a um multi-conjunto.
Por exemplo, insereMSet ’c’ [(’b’,2), (’a’,4), (’c’,1)] corresponde a [(’b’,2),
(’a’,4), (’c’,2)].-}

insereMSet :: Eq a => a ->[(a,Int)] -> [(a,Int)]
insereMSet n [] = []
insereMSet n ((x,xs):ys) | n == x = (x,xs+1):ys
                         | otherwise = (x,xs) : insereMSet n ys

{-42. Considere que se usa o tipo [(a,Int)] para representar multi-conjuntos de elementos de a.
Considere ainda que nestas listas nao ha pares cuja primeira componente coincida, nem cuja
segunda componente seja menor ou igual a zero.
Defina a funcao removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)] que remove um
elemento a um multi-conjunto. Se o elemento nao existir, deve ser retornado o multi-conjunto
recebido.
Por exemplo, removeMSet ’c’ [(’b’,2), (’a’,4), (’c’,1)] corresponde a [(’b’,2),
(’a’,4)].-}

removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet n [] = []
removeMSet n ((x,xs):ys) | n == x = removeMSet n ys
                         | otherwise = (x,xs) : removeMSet n ys

{-43
Considere que se usa o tipo [(a,Int)] para representar multi-conjuntos de elementos de a.
Considere ainda que nestas listas nao ha pares cuja primeira componente coincida, nem cuja
segunda componente seja menor ou igual a zero.

Defina a funcao constroiMSet :: Ord a => [a] -> [(a,Int)] dada uma lista ordenada
por ordem crescente, calcula o multi-conjunto dos seus elementos.
Por exemplo, constroiMSet "aaabccc" corresponde a [(’a’,3), (’b’,1), (’c’,3)].
-}

constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] = []
constroiMSet (x:xs) = insereMSet x (constroiMSet xs)

{-44 Apresente uma definicao recursiva da funcao pre-definida partitionEithers :: [Either
a b] -> ([a],[b]) que divide uma lista de Either s em duas listas.
-}

partitionEithers ::  [Either a b] -> ([a],[b])
partitionEithers [] = ([],[])
partitionEithers l = (lefts l , rights l)

lefts :: [Either a b] -> [a]
lefts [] = []
lefts ((Left a) :t) = a : lefts t 
lefts ((Right b) :t) = lefts t

rights :: [Either a b] -> [b]
rights [] = []
rights ((Left a):t) = rights t 
rights ((Right b):t) = b : rights t

{-45  Apresente uma definicao recursiva da funcao pre-definida catMaybes :: [Maybe a] -> [a]
que colecciona os elementos do tipo a de uma lista.
-}
catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (Nothing : xs) = catMaybes xs
catMaybes (Just x : xs)  = x:catMaybes xs

{-46
data Movimento = Norte | Sul | Este | Oeste
                deriving Show
Defina a funcao caminho :: (Int,Int) -> (Int,Int) -> [Movimento] que, dadas as posicoes
inicial e final (coordenadas) do robot, produz uma lista de movimentos suficientes para que o
robot passe de uma posição para a outra.
-}

data Movimento = Norte | Sul | Este | Oeste
                deriving Show
caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x1,y1) (x2,y2) | x1 == x2 && y1 == y2 = []
                        | x1 < x2 = Este : caminho (x1+1,y1) (x2,y2)
                        | x1 > x2 = Oeste : caminho (x1-1,y1) (x2,y2)
                        | y1 < y2 = Norte : caminho (x1,y1+1) (x2,y2)
                        | y1 > y2 = Sul : caminho (x1,y1-1) (x2,y2)

{-47. Consider o seguinte tipo de dados,
data Movimento = Norte | Sul | Este | Oeste
deriving Show
Defina a funcao hasLoops :: (Int,Int) -> [Movimento] -> Bool que dada uma posicao
inicial e uma lista de movimentos (correspondentes a um percurso) verifica se o robot alguma
vez volta a passar pela posicao inicial ao longo do percurso correspondente. Pode usar a
funcao posicao definida acima.
-}

-- ?? por favor não sair...

{-
48. Considere os seguintes tipos para representar pontos e rectangulos, respectivamente. Assuma
que os rectangulos tem os lados paralelos aos eixos e sao representados apenas por dois dos
pontos mais afastados.
type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto
-}

type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto

isQuadrado :: Rectangulo -> Bool
isQuadrado (Rect (x1,y1) (x2,y2)) = altura == largura
  where largura = abs(x2-x1)
        altura = abs(y2-y1)

contaQuadrados :: [Rectangulo] -> Int
contaQuadrados [] = 0
contaQuadrados (x:xs) | isQuadrado x = 1 + contaQuadrados xs
                      | otherwise = contaQuadrados xs


{-49. Considere os seguintes tipos para representar pontos e rectangulos, respectivamente. Assuma
que os rectangulos tem os lados paralelos aos eixos e s˜ao representados apenas por dois dos
pontos mais afastados.
type Ponto = (Float,Float)
data Rectangulo = Rect Ponto Ponto
Defini a funcao areaTotal :: [Rectangulo] -> Float que, dada uma lista com rectangulos,
determina a area total que eles ocupam-}

calcArea (Rect (x1,y1) (x2,y2)) = altura * largura
    where largura = abs(x2-x1)
          altura = abs(y2-y1)

areaTotal :: [Rectangulo] -> Float
areaTotal [] = 0
areaTotal (x:xs) = calcArea x + areaTotal xs


{-50 Considere o seguinte tipo para representar o estado de um equipamento.
data Equipamento = Bom | Razoavel | Avariado
deriving Show
Defina a funcao naoReparar :: [Equipamento] -> Int que determina a quantidade de
equipamentos que nao estao avariados.-}
  
data Equipamento = Bom | Razoavel | Avariado
    deriving (Show,Eq)

naoReparar :: [Equipamento] -> Int
naoReparar [] = 0
naoReparar (x:xs) | x == Avariado = naoReparar xs
                  | otherwise = 1 + naoReparar xs 
 




