data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

next :: Semaforo -> Semaforo
next cor
    | cor == Verde = Amarelo
    | cor == Amarelo = Vermelho
    | cor == Vermelho = Verde

stop :: Semaforo -> Bool
stop cor | cor == Vermelho = False
         | otherwise = True


safe :: Semaforo -> Semaforo -> Bool
safe cruz1 cruz2 | (cruz1 == Vermelho && cruz2 == Vermelho) = True
                 |otherwise = True

