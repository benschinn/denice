import https = require('https');

const httpsGet = url => {
  return new Promise((resolve, reject) => {
    https.get(url, res => {
      res.setEncoding('utf8');
      let body = ''; 
      res.on('data', chunk => body += chunk);
      res.on('end', () => resolve(body));
    }).on('error', reject);
  });
};

module.exports = {
  get: httpsGet
}
