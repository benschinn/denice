const routesWrapper = (app) => {
  app.use('/nyt-recipe', require('./nyt-cooking')) 
}

module.exports = routesWrapper
