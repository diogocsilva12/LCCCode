
data Ponto = Cartesiano Double Double | Polar Double Double 
            deriving (Show,Eq)

--a)
posx :: Ponto -> Double
posx (Cartesiano x y ) = x
posx (Polar d a) = d * (cos a)

--b)
posy :: Ponto -> Double
posy (Cartesiano x y) = y
posy (Polar d a) = d * (sin a)

--c)
raio :: Ponto -> Double
raio (Cartesiano x y) = sqrt(x^2 + y^2)
raio (Polar d a) = d

--d)
--e)



