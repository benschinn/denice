open Bindings
open List

let str = ReasonReact.string;

[@react.component]
let make = (~isLoading) => {
  let (bubbles, setBubbles) = React.useState(() => [{js|°|js},{js|ﾟ|js}, {js|º|js},{js|❍|js}, {js|｡|js}]);
  
  <div>
   <span>{js|( ˘ ³˘)ノ|js}->str</span>
   <span>(bubbles |> Array.of_list |> join(""))->str</span>
  </div>
}
