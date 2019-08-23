import express = require('express');
import https = require('https');
import http = require('http');
import cheerio = require('cheerio');

const app: express.Application = express();

const httpGet = url => {
  return new Promise((resolve, reject) => {
    https.get(url, res => {
      res.setEncoding('utf8');
      let body = ''; 
      res.on('data', chunk => body += chunk);
      res.on('end', () => resolve(body));
    }).on('error', reject);
  });
};

app.get('/nyt-recipe', async function (req, res) {
  const url = 'https://cooking.nytimes.com/recipes/1019693-slow-cooker-chipotle-honey-chicken-tacos';
  const body = await httpGet(url).then(res => {
    const $ = cheerio.load(res)
    const title = $('.recipe-title')
      .text()
      .replace(/\n/g, '')
      .split(' ')
      .filter(i => i.length > 1)
      .join(' ')
    return {
      title
    }
  })
  res.send(body)
  .catch(err => console.log(err))
});

app.listen(3003, function () {
  console.log('listening on port 3003!');
});
