import express = require('express')
import routes = require('./routes')

const app: express.Application = express()

routes(app)

app.listen(3003, function () {
  console.log('listening on port 3003!');
})
