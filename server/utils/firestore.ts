import db = require('../db')

async function writeData(collectionName, id, data) {
  const recipeRef = db.collection(collectionName).doc(id);
  try {
    await recipeRef.set(data)
  } catch(err) {
    console.log(err)
  }
}

module.exports = {
  write: writeData
}
