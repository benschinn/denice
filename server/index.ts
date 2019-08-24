import express = require('express');
import cheerio = require('cheerio');
import https = require('./utils/https');

const app: express.Application = express();

const processText = (txt, limit=1) => txt.replace(/\n/g, '')
        .split(' ')
        .filter(i => i.length > limit)
        .join(' '); 

app.get('/nyt-recipe', async function (req, res) {
  const url = 'https://cooking.nytimes.com/recipes/1019693-slow-cooker-chipotle-honey-chicken-tacos';
  try {
    const body = await https.get(url).then(res => {
      const $ = cheerio.load(res)
      const title = processText($('.recipe-title').text())

      const ingredients = [];
      const ingredientsList = $('ul.recipe-ingredients li').each((index, li) => {
        const ingredient = processText($(li).text())
        ingredients.push({ingredientName: ingredient})
      })
      const quantities = $('ul.recipe-ingredients span.quantity').each((index, span) => {
        const quantity= processText($(span).text(), 0)
        console.log(quantity)
        ingredients[index] = {...ingredients[index], quantity};
      })

      return {
        title,
        ingredients
      }
    })
    res.send(body)
  } catch (error) {
    res.status(500).send(error)
  }
  
});

app.listen(3003, function () {
  console.log('listening on port 3003!');
});
