import System.Win32 (xBUTTON1)
f x = 2 * x
g x = x + 1

f1 x = 2*x
g1 x = x + 1
res1 x = (f1.g1) x 