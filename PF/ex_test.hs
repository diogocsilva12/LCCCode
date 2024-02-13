myintersperse :: a -> [a] -> [a]
myintersperse _ [] = []
myintersperse _ [x] = [x]
myintersperse n (x:xs) = x:n:(myintersperse n xs)

main :: IO ()
main = do
  let test1 = myintersperse 0 [1, 2, 3] == [1, 0, 2, 0, 3]
      test2 = myintersperse "foo" ["bar", "baz"] == ["bar", "foo", "baz"]
      test3 = myintersperse 'x' "abc" == "axbxc"
      testsPassed = and [test1, test2, test3]
  if testsPassed
    then putStrLn "All tests passed!"
    else putStrLn "Some tests failed."