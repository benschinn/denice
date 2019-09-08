type config = {
  .
   "apiKey": string,
   "authDomain": string,
   "projectId": string
};

type d;

type p = {
  .
  [@bs.meth] "data": unit => Js.t(d),
};

type collection = {
  .
  [@bs.meth] "get": unit => Js.Promise.t(array(p)),
};

type firestore = {
  .
  [@bs.meth] "collection": string => collection,
};

type t = {
  .
  [@bs.meth] "initializeApp": config => unit,
  [@bs.meth] "firestore": unit => firestore
};

[@bs.module] external config : config  = "./firebase.config.json";

[@bs.module] external firebase : t = "firebase";

let _ = firebase##initializeApp(config);

let db = firebase##firestore();
