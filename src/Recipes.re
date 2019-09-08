open Bindings;

let str = ReasonReact.string;

type t = {
  .
  "title": string,
};

type action = 
  | SetRecipes(array(t));

type state = {
  recipes: array(t),
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
      | SetRecipes(data) => {recipes: data}
      },
      {recipes: [||]},
      );

  let _ = React.useEffect0(() => {
    Js.Promise.(
      Firestore.db##collection("recipes")##get()
      |> then_(querySnapshot => {
      let recipes = [||];
      querySnapshot
        |> Js.Array.forEach(d => {
        recipes |> push(d##data());
        Js.log("");
        });
      dispatch(SetRecipes(recipes)) |> resolve; 
      })
    );
    None;
  });
  <div className=Styles.container>
    <h1 className=Styles.title>"Recipe List" -> str</h1>
    <ul>
    (
      React.array(
        state.recipes
        |> Array.mapi((i, recipe) => <li key=(i |> string_of_int)>(recipe##title |> str)</li>)
        )
    )
    </ul>
    <p onClick=(_evt => back())>"back" -> str</p>
  </div>; 
}

