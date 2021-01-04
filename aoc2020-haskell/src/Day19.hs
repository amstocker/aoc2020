{-# LANGUAGE DeriveFunctor #-}
{-# LANGUAGE UndecidableInstances #-}

module Day19
    ( run
    ) where

import qualified Data.Char as Char
import qualified Data.Map as Map
import qualified Utils


type Label = Integer

data ParseExpr a
    = One Label [a]
    | Two Label [a] [a]
    | Term Label Char
    | Success
    | Failure
    deriving (Show, Eq, Functor)

type Rule = ParseExpr Label
type RuleMap = Map.Map Label Rule

newtype Fix f = Fix { unfix :: f (Fix f) }

instance (Show (f (Fix f))) => Show (Fix f) where
    showsPrec p (Fix f) = showsPrec p f

type ExprTree = Fix ParseExpr


-- this works for now, but should try to replace with regex...
ruleFromInput :: String -> (Label, Rule)
ruleFromInput string =
    let a:b:[] = Utils.splitBy ':' string
        label = read a
    in
        (label, makeExpr label . Utils.splitBy "|" . words $ b)
    where
        makeExpr = \label exprs -> case exprs of
            e1:[]
                | any Char.isLetter $ head e1 -> Term label (head . read $ head e1)
                | otherwise -> One label (map read e1)
            e1:e2:[] -> Two label (map read e1) (map read e2)

treeFromMap :: Label -> RuleMap -> ExprTree
treeFromMap root map = Fix $ case Map.lookup root map of
    Just e -> fmap (flip treeFromMap map) e
    Nothing -> Failure

-- rethink this whole function...
-- pruneLeft :: ExprTree -> Char -> ExprTree
-- pruneLeft tree c =
--     let
--         pruned = (== Empty) . unfix . flip pruneLeft c
--     in
--         Fix . flatten $ case unfix tree of
--             Empty -> Empty
--             Term n c'
--                 | c /= c' -> Empty
--                 | otherwise -> Term n c'
--             One n exprs -> case exprs of
--                 e:es
--                     | pruned e -> Empty
--                     | otherwise -> One n es
--             Two n (e1:e1s) (e2:e2s) -> case fmap pruned (e1, e2) of
--                 (True, True) -> Empty
--                 (True, False) -> One n e2s
--                 (False, True) -> One n e1s
--                 (False, False) -> Two n e1s e2s
--     where
--         flatten = \e -> case unfix e of
--             Two n e1s [] -> One n e1s  -- get this figured out, this is where the tree gets flattened
--             Two n [] e2s -> One n e2s
--             One n e1:[] -> unfix e1
--             One n [] -> Empty


run :: String -> IO ()
run input = 
    let
        rules:words:[] = Utils.splitByEmptyLine input
        ruleTree = treeFromMap 0 . Map.fromList . map ruleFromInput $ rules
        -- foldTree = foldl pruneLeft ruleTree
    in do
        print ruleTree
        print $ case unfix ruleTree of
            One _ _ -> True
            Two _ _ _ -> True
            Term _ _ -> True
            Success -> True
            Failure -> False
        -- print . length . filter ((/= Empty) . unfix) . map foldTree $ words