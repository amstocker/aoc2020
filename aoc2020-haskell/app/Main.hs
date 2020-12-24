module Main where

import System.Environment
import qualified Common

main :: IO ()
main = do
    (n:args) <- getArgs
    Common.runDay $ read n