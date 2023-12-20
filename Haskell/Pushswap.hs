{-
-- EPITECH PROJECT, 2023
-- B-PDG-300-MAR-3-1-PDGRUSH1-mohamied-amine.agaba
-- File description:
-- Pushswap
-}

import System.Environment
import System.Exit

myHead :: [a] -> a
myHead (x:_) = x
myHead [] = error "empty list"

myLength :: [a] -> Int
myLength [] = 0
myLength (_:a) = (myLength a) + 1

argsToNum :: [String] -> [Int]
argsToNum [] = []
argsToNum a = map read a                -- read : Transforme string en int | map : Divise la String en liste de int  

argsToAray :: String -> [String]
argsToAray str = (words str)            -- words : fonction système qui sépare un string en liste de string(myStrToWordArray)

funDoAll :: [String] -> [Char] -> [Int] -> [String] -> IO ()
funDoAll args [] l ops | funSort l == True = putStrLn("OK")
                       | otherwise = exitWith (ExitFailure 84)
funDoAll [] op l ops = exitWith (ExitFailure 84) 
funDoAll args op l ops | (funSort (fun l [] ops) == True 
                        && myLength (fun l [] ops) > 0) = putStrLn ("OK")
                       | otherwise = putStrLn ("KO")

main :: IO ()
main = do
    args <- getArgs                     -- Récupérer les nombres aprés le "./"
    op <- getLine                       -- Récupérer les instructions (après le "echo")
    let l = argsToNum args              -- Transforme les int en liste d'int
    let ops = words op                  -- Transforme les args en liste d'args
    funDoAll args op l ops

    -- if (myLength args == 0 || myLength op == 0)
    --     then exitWith (ExitFailure 84)
    --     else if (funSort (fun l [] ops) == True && myLength (fun l [] ops) > 0) 
    --         then putStrLn ("OK")
    --         else putStrLn ("KO")

fun :: [Int] -> [Int] -> [String] -> [Int]
fun la lb [] = la
fun la lb ("sa":tail) = fun (funS la) lb tail
fun la lb ("sb":tail) = fun la (funS lb) tail
fun la lb ("sc":tail) = fun (funS la) (funS lb) tail
fun la lb ("pa":tail) = fun (funPBis la lb) (funP lb) tail
fun la lb ("pb":tail) = fun (funP la) (funPBis lb la) tail
fun la lb ("ra":tail) = fun (funR la) lb tail
fun la lb ("rb":tail) = fun la (funR lb) tail
fun la lb ("rr":tail) = fun (funR la) (funR lb) tail
fun la lb ("rra":tail) = fun (funRr la) lb tail
fun la lb ("rrb":tail) = fun la (funRr lb) tail
fun la lb ("rrr":tail) = fun (funRr la) (funRr lb) tail

funS :: [Int] -> [Int]
funS [] = []
funS (a:[]) = [a]
funS (a:b:xs) = (b:a:xs)

funPBis :: [Int] -> [Int] -> [Int]
funPBis a [] = []
funPBis (a:[]) b = [a]
funPBis a (b:tail) = b:a 

funP :: [Int] -> [Int]
funP [] = []
funP (a:[]) = [a]
funP a = drop 1 a

funR :: [Int] -> [Int]
funR [] = []
funR (a:xs) = reverse $ a:(reverse xs)

funRr :: [Int] -> [Int]
funRr [] = []
funRr a = init((last a):a)

funTest :: [Int] -> Bool
funTest (head:tail) | head <= (myHead tail) = True
                    | otherwise = False

funSort :: [Int] -> Bool
funSort [] = True
funSort (head:[]) = True
funSort (head:tail) | myLength (head:tail) == 2 = funTest (head:tail)
                    | otherwise = if head <= (myHead tail) then
                                      funSort tail
                                  else False
