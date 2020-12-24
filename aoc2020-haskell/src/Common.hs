module Common
    ( runDay
    ) where

import Data.List

import qualified Day13
import qualified Day19

type DayNumber = Integer
data Day = Day
    { dayNumber :: DayNumber
    , run :: String -> IO ()
    }

dayList :: [Day]
dayList =
    [ Day 13 Day13.run
    , Day 19 Day19.run
    ]


inputDirectory :: FilePath
inputDirectory = "../"

inputFilename :: DayNumber -> FilePath
inputFilename n = inputDirectory ++ "day" ++ show n ++ "_input.txt"

runDay :: DayNumber -> IO ()
runDay n = do
    contents <- readFile $ inputFilename n
    case find ((== n) . dayNumber) dayList of
        Just (Day _ run) -> run contents