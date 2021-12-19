const app= require('./app')


app.listen(app.get('port'));
console.log('server port', app.get('port'))