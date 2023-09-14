--perimetro circunferência = r*pi*2
perimetro :: Float -> Float
perimetro r = r*3.14*2

--distancia entre dois pontos é sqrt((x2-x1)^2 + (y2-y1)^2)
dist :: (Double,Double) -> (Double,Double) -> Double
dist (x1,y1) (x2,y2) = sqrt ((x2-x1)**2 + (y2-y1)**2)

primUlt :: [a] -> (a,a)
primUlt l = (head l, last l)

--um número é multiplo de outro se o resto da divisão(mod) é 0 
multiplo :: Int -> Int -> Bool
multiplo a b = a `mod` b == 0

truncaImpar :: [a] -> [a]
truncaImpar l | even (length l) = l
              | otherwise = tail l

max2 :: Int -> Int -> Int
max2 a b | a > b = a
         | otherwise = b

max3 :: Int -> Int -> Int -> Int
max3 a b c | max2 a b > c = max2 a b
           | otherwise    = c
