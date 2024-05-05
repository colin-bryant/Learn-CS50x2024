from flask import Flask,render_template,request

app = Flask(__name__)

@app.route('/')

def index():
    
   # name = request.args.get('name','world') # ' ' default value   request.args['name']
    # return render_template('index.html',name=name)
    return render_template('index.html')
def greet():
    name = request.args.get('name','world')
    return render_template('greet.index.html',name=name)