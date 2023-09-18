nRaizes :: Double -> Double -> Double -> Int
nRaizes a b c | delta > 0 = 2
              | delta < 0 = 0
              | delta == 0 = 1
              where delta = b^2 * 4*a*c
 
raizes :: Double -> Double -> Double -> [Double]
raizes a b c 
    | n == 0 = []
    | n == 1 = [-b / (2 * a)]
    | n == 2 = [(-b + sqrt(b^2 - 4*a*c)) / (2 * a), (-b - sqrt(b^2 - 4*a*c)) / (2 * a)]
    where n = nRaizes a b c
                 

