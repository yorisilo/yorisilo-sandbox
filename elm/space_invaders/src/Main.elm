module Main exposing (main)

import Browser
import Css exposing (..)
import Html.Styled exposing (Html, button, div, text, toUnstyled)
import Html.Styled.Attributes exposing (css)
import Html.Styled.Events exposing (onClick)
import Time


type alias Model =
    { count : Int }


initialModel : () -> ( Model, Cmd Msg )
initialModel _ =
    ( { count = 0 }, Cmd.none )


type Msg
    = Increment Time.Posix
    | Decrement


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        Increment _ ->
            ( { model | count = model.count + 1 }, Cmd.none )

        Decrement ->
            ( { model | count = model.count - 1 }, Cmd.none )


view : Model -> Html Msg
view model =
    div []
        css
        [ [ backgroundColor "red"
          , left "20px"
          , width "200px"
          , position "absolute"
          ]
            [ text <| String.fromInt model.count ]
        ]


subscriptions : Model -> Sub Msg
subscriptions model =
    Time.every 1000 Increment


main : Program () Model Msg
main =
    Browser.element
        { init = initialModel
        , view = view
        , update = update
        , subscriptions = subscriptions
        }
