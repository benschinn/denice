WebAssembly.instantiateStreaming(fetch("denice.gc.wasm"))
  .then(wasmModule => {
    const result = wasmModule.instance.exports.add_one(3);
    const text = document.createTextNode(result);
    document.body.appendChild(text);
  });
