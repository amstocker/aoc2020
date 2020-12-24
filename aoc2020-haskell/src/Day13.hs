module Day13 (run) where

import Data.Char
import Utils

type Congruence = (Integer, Integer)

solveCongruence :: Congruence -> Congruence -> Congruence
solveCongruence (y0, a0) (y1, a1)
    | y0 `mod` a1 == y1 = (y0, lcm a0 a1)
    | otherwise         = solveCongruence (y0 + a0, a0) (y1, a1)

parseLine :: String -> [Congruence]
parseLine = 
    let pairToCongruence = \(i, x) -> ((-i) `mod` x, x)
        readPair = \(i, s) -> (i, read s)
    in map (pairToCongruence . readPair) . filter (all isNumber . snd) . enumerated
    where
        enumerated = zip [1..] . splitByCommas

run :: String -> IO ()
run = putStrLn . show . fst . foldl1 solveCongruence . parseLine . (!!1) . lines