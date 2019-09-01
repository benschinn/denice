let handleClick = (_event) => Js.log("clicked!");

[@react.component]
let make = () =>
  <div onClick={handleClick}>
    {ReasonReact.string("denice is nice")}
  </div>;
