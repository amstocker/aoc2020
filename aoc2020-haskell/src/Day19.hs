{-# LANGUAGE DeriveFunctor #-}

module Day19
    ( run
    ) where

import qualified Data.Char as Char
import qualified Data.Map as Map
import qualified Utils


type Label = Integer

data Expr a
    = Only1 Label a
    | Only2 Label a a
    | Or1 Label a a
    | Or2 Label (a, a) (a, a)
    | Or12 Label a (a, a)
    | Or23 Label (a, a) (a, a, a)
    | Terminal Label Char
    | Empty
    deriving (Show, Eq, Functor)

type Rule = Expr Label
type RuleMap = Map.Map Label Rule

newtype Fix f = Fix { unpack :: f (Fix f) }

treeFromMap :: RuleMap -> Label -> Fix Expr
treeFromMap map root = case Map.lookup root map of
    Just e -> Fix $ fmap (treeFromMap map) e
    Nothing -> Fix Empty

ruleFromInput :: String -> (Label, Rule)
ruleFromInput string =
    let (a, _:b) = break (== ':') string
        label = read a
    in
        (label, makeExpr label (Utils.splitBy "|" . words $ b))
    where
        makeExpr = \label exprs -> case exprs of
            e1:[]
                | any Char.isLetter $ head e1 -> Terminal label (head . read $ head e1)
                | otherwise -> makeOnlyExpr label (map read e1)
            e1:e2:[] -> makeOrExpr label (map read e1) (map read e2)
        makeOnlyExpr = \label expr -> case expr of
            n1:[] -> Only1 label n1
            n1:n2:[] -> Only2 label n1 n2
        makeOrExpr = \label expr1 expr2 -> case (expr1, expr2) of
            (n1:[], m1:[]) -> Or1 label n1 m1
            (n1:n2:[], m1:m2:[]) -> Or2 label (n1, n2) (m1, m2)
            (n1:[], m1:m2:[]) -> Or12 label n1 (m1, m2)
            (n1:n2:[], m1:m2:m3:[]) -> Or23 label (n1, n2) (m1, m2, m3)


run :: String -> IO ()
run input = 
    let
        (rules, _:words) = break (== []) $ lines input
        ruleTree = treeFromMap . Map.fromList . map ruleFromInput $ rules
    in
        putStrLn input