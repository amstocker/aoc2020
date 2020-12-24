module Common
    ( runDay
    ) where

import Day13
import Day19


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

errorMsg :: Day -> String
errorMsg n = "Day " ++ show n ++ " not completed yet ..."

runDay :: Day -> IO ()
runDay n = do
    contents <- readFile $ inputFilename n
    case lookup n dayList of
        Just run -> run contents
        Nothing -> putStrLn $ errorMsg n