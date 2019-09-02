module Component {
 [@react.component]
let make = () =>
  <div>
    {ReasonReact.string("Component")}
  </div>; 
};

module Component1 {
 [@react.component]
let make = () =>
  <div>
    {ReasonReact.string("Component1")}
  </div>; 
};

let str = ReasonReact.string;
let push = ReasonReact.Router.push;
let handleClick = (_event) => Js.log("clicked!");

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  <div>
    <ul>
      <li onClick=(_evt => push("c"))>(str("c"))</li>
      <li onClick=(_evt => push("c1"))>(str("c1"))</li>
    </ul>
    <div>
     (
       switch(url.path) {
       | ["c"] => <Component />
       | ["c1"] => <Component1 />
       | _ => <Component />
       }
     ) 
    </div> 
  </div>
}
