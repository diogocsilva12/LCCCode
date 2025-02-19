

module MyLang where

-- Define a type for variables in our language.
data Vars = X1 | X2 deriving (Show,Eq)
-- A State is represented as a function mapping variables to integer values.
type State = Vars -> Int

-- Define the syntax for arithmetic expressions (AExp).
data AExp 
    = VAE Vars          -- Variable in an arithmetic expression
    | I Int             -- Integer constant (should be represented differently)
    | Sum AExp AExp     -- Addition of two arithmetic expressions
    | Mult AExp AExp    -- Multiplication of two arithmetic expressions
    deriving Show

-- Define the syntax for boolean expressions (BExp).
data BExp 
    = LE AExp AExp      -- Less than or equal comparison between two arithmetic expressions
    | Tt                -- Boolean constant: True
    | Ff                -- Boolean constant: False 
    | Neg BExp          -- Boolean negation
    | And BExp BExp     -- Boolean conjunction (AND operation)
    deriving Show

-- Define the syntax for programs (Prog).
data Prog 
    = Asg Vars AExp        -- Assignments
    | Seq Prog Prog        -- Sequential composition 
    | Cond BExp Prog Prog  -- Conditionals
    | While BExp Prog      -- While loops
    deriving Show

-- Define the syntax for programs (Prog) that can produce errors.
data EProg 
    = EAsg Vars AExp        -- Assignments
    | ESeq EProg EProg        -- Sequential composition 
    | ECond BExp EProg EProg  -- Conditionals
    | EWhile BExp EProg      -- While loops
    | Err
    deriving Show


-- Examples
x1PlusOne :: AExp
x1PlusOne = Sum (VAE X1) (I 1)
x2PlusOne :: AExp
x2PlusOne = Sum (VAE X2) (I 2)
tenPlusx2 :: AExp
tenPlusx2 = Sum (I 10) (VAE X2)
more :: AExp
more = Mult x1PlusOne x2PlusOne

--
neg :: AExp -> AExp
neg e = Mult e (I (-1))

sub:: AExp -> AExp -> AExp
sub e1 e2 = Sum e1 (neg e2)

-- Define the semantics of arithmetic expressions.
-- Given an arithmetic expression and a state, it evaluates to an integer.
semAE :: AExp -> State -> Int
semAE (VAE v) s = s v
semAE (I n) _ = n
semAE (Sum a1 a2) s = semAE a1 s + semAE a2 s
semAE (Mult a1 a2) s = semAE a1 s * semAE a2 s
-- Define the semantics of boolean expressions.
-- Given a boolean expression and a state, it evaluates to a boolean value.
x1PlusOne_Seq_x2PlusOne :: Seq (Asg X1 x1PlusOne) (Asg X2 x2PlusOne)
div = While Tt (Asg X1 x1PlusOne)

semBE :: BExp -> State -> Bool
semBE (LE a1 a2) s = semAE a1 s <= semAE a2 s
semBE Tt _ = True
semBE Ff _ = False
semBE (Neg b) s = not (semBE b s)
semBE (And b1 b2) s = semBE b1 s && semBE b2 s

chMem :: Vars -> Int -> State -> State
chMem x v s = \y -> if x == y then v else s y

-- Define the semantics of programs.
-- Given a program and an initial state, it produces a new state after execution.
semProg :: Prog -> State -> State
semProg (Asg v a) s = \x -> if x == v then semAE a s else s x
semProg (Seq p1 p2) s = semProg p2 (semProg p1 s)
semProg (Cond b p1 p2) s = if semBE b s then semProg p1 s else semProg p2 s
semProg (While b p) s = if semBE b s then semProg (While b p) (semProg p s) else s

-- Define the semantics of programs.  Given a program and an initial state, it
-- **possibly** produces a new state after execution.
semEProg :: Prog -> State -> Maybe State
semEProg = undefined


