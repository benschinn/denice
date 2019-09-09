open Bindings;

external toUnit : 'a => unit = "%identity";

let str = ReasonReact.string;

type t = {
  .
  "title": string,
};

type action = 
  | SetLoading(bool)
  | SetRecipes(array(t));

type state = {
  recipes: array(t),
  isLoading: bool,
};

module Styles {
  open Css;

  let container = style([
    display(flexBox),
    justifyContent(center),
    alignItems(center),
    flexDirection(column),
    height(100. |> vh),
  ]); 

  let title = style([fontSize(rem(1.25))]);
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(
    (state, action) => 
    switch(action) {
      | SetRecipes(data) => {
        Js.log("setRecipes set");
        {...state, recipes: data}
      }
      | SetLoading(l) => {
        Js.log("loading dispatched");
        {...state, isLoading: l}
      }
      },
      {recipes: [||], isLoading: false},
      );

  let _ = React.useEffect0(() => {
    dispatch(SetLoading(true));
    Js.Promise.(
      Firestore.db##collection("recipes")##get()
      |> then_(querySnapshot => {
      let recipes = [||];
      querySnapshot
        |> Js.Array.forEach(d => {
        recipes 
        |> push(d##data())
        |> toUnit
        });
      dispatch(SetLoading(false));
      dispatch(SetRecipes(recipes)) |> resolve; 
      })
    ) |> ignore;
    None;
  }, );
  <div className=Styles.container>
    <h1 className=Styles.title>"Recipe List" -> str</h1>
    (state.isLoading ?
    <div>"loading..."->str</div>
    : <ul>
    (
      React.array(
        state.recipes
        |> Array.mapi((i, recipe) => <li key=(i |> string_of_int)>(recipe##title |> str)</li>)
        )
    )
    </ul>)
    <p onClick=(_evt => back())>"back" -> str</p>
  </div>; 
}

