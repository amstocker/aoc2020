module Utils
    (splitByCommas
    ) where

splitByCommas :: String -> [String]
splitByCommas [] = []
splitByCommas s = case break (== ',') s of
    (x, _:y) -> x:(splitByCommas y)
    (x, []) -> [x]