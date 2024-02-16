myintersperce :: Int ->  [a] -> [a]
myintersperce _ [] = []
myintersperce _ [x] = x
myintersperce n (x:xs) = x: n : myintersperce xs 