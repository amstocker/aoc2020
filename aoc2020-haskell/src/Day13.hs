module Day13 (run) where

import Data.Char
import Utils

-- An element x in the group Z/nZ represented as a tuple (x, n)
type CyclicElem = (Integer, Integer)

-- Given elements (x1, n1) and (x2, n2) where n1 and n2 are coprime,
-- computes the isomorphism
--      Z/(n1)Z + Z/(n2)Z -> Z/(n1*n2)Z
cyclicIso :: CyclicElem -> CyclicElem -> CyclicElem
cyclicIso (x1, n1) (x2, n2)
    | x1 `mod` n2 == x2 = (x1, n1 * n2)
    | otherwise         = cyclicIso (x1 + n1, n1) (x2, n2)

-- Solves the system of K equations
--      x = x1 `mod` n1
--      ...
--      x = xK `mod` nK
-- where n1, ..., nK are coprime.
solver :: [CyclicElem] -> Integer
solver = fst . foldl1 cyclicIso

parseLine :: String -> [CyclicElem]
parseLine = 
    let pairToCyclicElem = \(i, x) -> ((-i) `mod` x, x)
        readPair = \(i, s) -> (i, read s)
        clean = filter (all isNumber . snd)
    in map (pairToCyclicElem . readPair) . clean . enumeratedItems
    where
        enumeratedItems = zip [1..] . splitByCommas

run :: String -> IO ()
run = putStrLn . show . solver . parseLine . (!!1) . lines