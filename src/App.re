let str = ReasonReact.string;
let pushRoute = ReasonReact.Router.push;

module Styles {
  open Css;

  let container = style([
    display(flexBox),
    justifyContent(center),
    alignItems(center),
    flexDirection(column),
    height(100. |> vh),
  ]); 

  let link = style([cursor(`pointer)]);
};

module AddNewRecipe {
  [@react.component]
  let make = () =>
    <div className=(Styles.container)>
      <form>
        <input type_="text" />  
        <button>(str("submit"))</button>
      </form>
      <p
        className=Styles.link
        onClick=(_evt => pushRoute("/recipes")) 
      >
        ("view recipes" |> str)
      </p>
    </div>; 
};

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  
  <>
    <div>
     (
       switch(url.path) {
       | [""] => <AddNewRecipe />
       | ["recipes"] => <Recipes />
       | _ => <AddNewRecipe />
       }
     ) 
    </div> 
  </>
}
