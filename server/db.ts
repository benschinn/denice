import admin = require('firebase-admin')

const serviceAccount = require('./db_config.json')

admin.initializeApp({
    credential: admin.credential.cert(serviceAccount)
});

const db = admin.firestore();

module.exports = db;

