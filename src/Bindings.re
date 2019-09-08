//array
[@bs.send.pipe: array('a)] external push: 'a => array('a) = "";


//window
[@bs.val] [@bs.scope ("window", "history")]
external back: unit => unit = "";
