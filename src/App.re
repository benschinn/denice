let str = ReasonReact.string;
let pushRoute = ReasonReact.Router.push;
[@bs.send.pipe: array('a)] external push: 'a => array('a) = "";

external toFirestoreDoc : 'a  => Js.t('a) = "%identity";

module AddNewRecipe {
  [@react.component]
  let make = () =>
    <div>
      <form>
        <input type_="text" />  
        <button>(str("submit"))</button>
      </form>
    </div>; 
};

module RecipeList {
  type t = Js.t(ReactHooksTemplate.Firestore.d);

  type action = 
    | SetRecipes(array(t));

  type state = {
    recipes: array(t),
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
    <div>
      {ReasonReact.string("Recipe List")}
    </div>; 
  }
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  
  <div>
    <ul>
      <li onClick=(_evt => pushRoute("/"))>(str("home"))</li>
      <li onClick=(_evt => pushRoute("recipes"))>(str("recipes"))</li>
    </ul>
    <div>
     (
       switch(url.path) {
       | [""] => <AddNewRecipe />
       | ["recipes"] => <RecipeList />
       | _ => <AddNewRecipe />
       }
     ) 
    </div> 
  </div>
}
