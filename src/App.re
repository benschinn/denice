let str = ReasonReact.string;
let push = ReasonReact.Router.push;

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
 [@react.component]
let make = () =>
  <div>
    {ReasonReact.string("Recipe List")}
  </div>; 
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let _ = React.useEffect0(() => {
    Js.Promise.(
      Firestore.db##collection("recipes")##get()
      |> then_(querySnapshot=> {
           querySnapshot
           |> Js.Array.forEach(d => Js.log(d##data()))
           |> resolve
      })
    );
    None;
  });
  <div>
    <ul>
      <li onClick=(_evt => push("/"))>(str("home"))</li>
      <li onClick=(_evt => push("recipes"))>(str("recipes"))</li>
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
