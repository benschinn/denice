import express = require('express')
import path = require('path')

const routesWrapper = (app) => {
  app.use('/nyt-recipe', require('./nyt-cooking')) 

  app.use(express.static(path.resolve(__dirname, '..', '..', 'build')));
  app.get('/*', (req, res) => {
      res.sendFile(path.resolve(__dirname, '..', '..', 'build', 'index.html'));
  });

}

module.exports = routesWrapper
