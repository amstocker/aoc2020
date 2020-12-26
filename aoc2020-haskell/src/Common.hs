module Common
    ( runDay
    ) where

import Data.List

import qualified Day13
import qualified Day19

type Day = Integer

dayList :: [(Day, String -> IO ())]
dayList =
    [ (13, Day13.run)
    , (19, Day19.run)
    ]


inputDirectory :: FilePath
inputDirectory = "../"

inputFilename :: Day -> FilePath
inputFilename n = inputDirectory ++ "day" ++ show n ++ "_input.txt"

runDay :: Day -> IO ()
runDay n = do
    contents <- readFile $ inputFilename n
    case lookup n dayList of
        Just run -> run contents