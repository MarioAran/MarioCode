const { Router }=require('express')
const router = Router();
const admin = require('firebase-admin')

var serviceAccount = require("/Users/mario/github/MarioCode/Backend/firebase-node/node-firebase-example-a48a0-firebase-adminsdk-skq58-31f73e7b76.json")

admin.initializeApp({
    credential: admin.credential.cert(serviceAccount),
    databaseURL: 'https://node-firebase-example-a48a0-default-rtdb.europe-west1.firebasedatabase.app/'
});



const db = admin.database();


router.get('/', (req, res) => {
    res.render('index');
});

router.post('/new-contact',(req, res)=>{
    console.log(req.body);
    const newContact = {
        firstname: req.body.firstname,
        lastname: req.body.lastname,
        email: req.body.email,
        phone: req.body.phone
    }
    db.ref('contacts').push(req.body)
    res.send('received')
});

module.exports =router;