module Example exposing (suite)

import Expect exposing (Expectation)
import Fuzz exposing (Fuzzer, int, list, string)
import Main
import Test exposing (..)


suite : Test
suite =
    describe "Add numbers"
        [ test "adds two numbers" <|
            \_ -> Expect.equal (Main.add 2 5) 7
        ]



-- todo "Implement our first test. See https://package.elm-lang.org/packages/elm-explorations/test/latest for how to do this!"
