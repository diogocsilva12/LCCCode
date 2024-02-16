concatena :: [a] -> [a] -> [a]
concatena [] l2 = l2       
concatena (x:xs) l2 = x : concatena xs l2