module Main where

import System.Environment
import Common

main :: IO ()
main = do
    (n:args) <- getArgs
    runDay $ read n