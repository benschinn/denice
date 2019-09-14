//array
[@bs.send.pipe: array('a)] external push: 'a => array('a) = "";
[@bs.send.pipe: array('a)] external join: 'a => string = "";


//window
[@bs.val] [@bs.scope ("window", "history")]
external back: unit => unit = "back";
