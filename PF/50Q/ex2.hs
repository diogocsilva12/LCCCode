myEnumFromThenTo :: Int -> Int -> Int -> [Int]
myEnumFromThenTo n1 interval n2 | n1 > n2 = []
                                | otherwise = n1 : myEnumFromThenTo (n1+(interval-1)) interval n2