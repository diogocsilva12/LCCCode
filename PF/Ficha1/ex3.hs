import Distribution.ModuleName (main)
import Distribution.Simple (KnownExtension(HexFloatLiterals))
type Hora = (Int,Int)

horavalida :: Hora -> Bool
horavalida (h,m) | h > 0 && h < 24 && 0 > m && m < 60 = True
                 | otherwise = False

comphoras :: Hora -> Hora -> Bool
comphoras (h1,m1) (h2,m2) | h2 > h1 = True
                          | h2 == h1 && m2 > m1 = True
                          | otherwise = False

convhm :: Hora -> Int
convhm (h,m) = 60*h + m

--d,e,f

