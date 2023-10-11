{-Uma forma de representar polinómios de uma varíavel é usar listas de monómios representados por pares (coeficiente, expoente)
type Polinomio = [Monomio]
type Monomio = (Float,Int)

Ex.: [(2,3),(3,4),(5,3),(4,5)] representa o polinomio 2x^3+3x^4+5x^3+4x^5-}

--a)conta :: Int -> Polinómio -> Int de forma a que ( conta n p ) indica quantos monómios de grau n existem em p.
type Polinomio = [Monomio]
type Monomio = (Float,Int)
conta :: Int -> Polinomio -> Int 
conta n ((x,y):xs) | n == y = 1 + conta n xs
                   | otherwise = conta n xs


--b) grau que indica o grau do polinómio
grau :: Polinomio -> Int
grau [] = 0  
grau ((x, y):xs) = max y (grau xs)

--c)selgrau que seleciona os monomios com um dado grau de um polinomio
selgrau :: Int -> Polinomio -> Polinomio
selgrau n [] = []
selgrau n ((x,y):xs) | n == y = (x,y) : selgrau n xs
                     | otherwise = selgrau n xs