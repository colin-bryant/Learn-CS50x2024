from flask import Flask,render_template,request

app = Flask(__name__)

@app.route('/')
def index():
    
   # name = request.args.get('name','world') # ' ' default value   request.args['name']
    # return render_template('index.html',name=name)
    return render_template('index.html')
@app.route('/greet',methods=['GET','POST'])
def greet():
    name = request.args.get('name','world')
    return render_template('greet.html',name=name)