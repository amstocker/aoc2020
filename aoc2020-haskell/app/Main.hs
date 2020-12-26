module Main where

import System.Environment
import Common

main :: IO ()
main = getArgs >>= runDay . read . (!! 0)