import express = require('express')
import https = require('../../utils/https')
import cheerio = require('cheerio')

const routes = express.Router()

const processText = (txt, limit=1) => txt.replace(/\n/g, '')
        .split(' ')
        .filter(i => i.length > limit)
        .join(' '); 

routes.get('/:recipeId', async function (req, res) {
  const { recipeId } = req.params
  const url = `https://cooking.nytimes.com/recipes/${recipeId}`
  try {
    const body = await https.get(url).then(res => {
      const $ = cheerio.load(res)
      const title = processText($('.recipe-title').text())
      const author = processText($('a.author').text())
      const img = $('div.media-container img').attr('src')
      const yieldValue = $('span.recipe-yield-value').first().text()
      const timeValue = $('span.recipe-yield-value').last().text()
      const description = $('div.topnote p').text()

      const ingredients = []
      const tips = []
      const steps = []

      $('ul.recipe-ingredients li').each((index, li) => {
        const ingredient = processText($(li).text())
        ingredients.push({ingredientName: ingredient})
      })
      const quantities = $('ul.recipe-ingredients span.quantity').each((index, span) => {
        const quantity= processText($(span).text(), 0)
        ingredients[index] = {...ingredients[index], quantity};
      })

      $('ol.recipe-steps li').each((index, step) => {
        const stepVal = processText($(step).text())
        steps.push(stepVal)
      })
      $('ul.recipe-notes li').each((index, tip) => {
        const tipVal = processText($(tip).text())
        tips.push(tipVal)
      })
      return {
        recipeId,
        title,
        author,
        yieldValue,
        timeValue,
        ingredients,
        img,
        description,
        steps,
        tips,
      }
    }).catch(err => (err))
    res.send(body)
  } catch (error) {
    res.status(500).send(error)
  }
  
});

module.exports = routes;
