myEnum :: Int -> Int -> [Int]
myEnum n1 n2 | n1 >= n2 = []
             | otherwise = n1:myEnum(n1+1) n2


--1 5 -> [1,2,3,4,5]
{-for elem in range(n1,n2):
    [].append(elem)-}
