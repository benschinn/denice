WebAssembly.instantiateStreaming(fetch("denice.gc.wasm"))
  .then(wasmModule => {
    const result = wasmModule.instance.exports.add_one(3);
    console.log(wasmModule.instance.exports)
    const text = document.createTextNode(result);
    document.body.appendChild(text);
  });
