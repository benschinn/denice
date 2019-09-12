open Bindings
open List

let str = ReasonReact.string;

[@react.component]
let make = (~isLoading) => {
  let (bubbles, setBubbles) = React.useState(() => [|{js|°|js},{js|ﾟ|js}, {js|º|js},{js|❍|js}, {js|｡|js}|]);
  React.useEffect1(() => {
    let animationFrame = Js_global.setInterval(() => {
      //setBubbles(_ => [tl(bubbles), [hd(bubbles)]] |> flatten)
      setBubbles(_ => Array.append(bubbles |> slice2(1,4), [|bubbles[0]|]))
      //setBubbles(_ => [Js.Math.random_int(0,100) |> string_of_int]);
    }, 400);
    Some(() => Js_global.clearInterval(animationFrame))
  }, [|isLoading|]);
  
  <div>
   <span>{js|( ˘ ³˘)ノ|js}->str</span>
   <span>(bubbles |> join(""))->str</span>
  </div>
}
