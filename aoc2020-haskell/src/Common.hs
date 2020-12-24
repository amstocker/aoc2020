module Common
    ( runDay
    ) where

import Day13
-- import Day19
-- etc...

dayMap = [ (13, Day13.run) ]


inputDirectory :: FilePath
inputDirectory = "../"

inputFilename :: Integer -> FilePath
inputFilename n = inputDirectory ++ "day" ++ show n ++ "_input.txt"

runDay :: Integer -> IO ()
runDay n = do
    contents <- readFile $ inputFilename n
    let (Just run) = lookup n dayMap
    run contents