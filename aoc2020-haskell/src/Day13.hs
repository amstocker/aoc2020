module Day13 (run) where

import Data.Char
import Utils

-- Represents a congruence
--      y `mod` a
-- as a tuple (y, a)
type Congruence = (Integer, Integer)

-- Solves the system of equations
--      x = y0 `mod` a0
--      x = y1 `mod` a1
-- and returns the congruence (x, lcm(a0, a1))
solveCongruence :: Congruence -> Congruence -> Congruence
solveCongruence (y0, a0) (y1, a1)
    | y0 `mod` a1 == y1 = (y0, lcm a0 a1)
    | otherwise         = solveCongruence (y0 + a0, a0) (y1, a1)

-- Solves the system of equations
--      x = y0 `mod` a0
--      ...
--      x = yN `mod` aN
solveCongruences :: [Congruence] -> Integer
solveCongruences = fst . foldl1 solveCongruence

parseLine :: String -> [Congruence]
parseLine = 
    let pairToCongruence = \(i, x) -> ((-i) `mod` x, x)
        readPair = \(i, s) -> (i, read s)
        clean = filter (all isNumber . snd)
    in map (pairToCongruence . readPair) . clean . enumerated
    where
        enumerated = zip [1..] . splitByCommas

run :: String -> IO ()
run = putStrLn . show . solveCongruences . parseLine . (!!1) . lines