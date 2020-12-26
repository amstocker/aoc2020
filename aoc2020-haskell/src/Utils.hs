module Utils
    ( splitBy
    , splitByComma
    , splitByEmptyLine
    ) where

splitBy :: (Eq a) => a -> [a] -> [[a]]
splitBy _ [] = []
splitBy z xs = case break (== z) xs of
    (x, _:y) -> x:(splitBy z y)
    (x, []) -> [x]

splitByComma :: String -> [String]
splitByComma = splitBy ','

splitByEmptyLine :: String -> [[String]]
splitByEmptyLine = splitBy [] . lines