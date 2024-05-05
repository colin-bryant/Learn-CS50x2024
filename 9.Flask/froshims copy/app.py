# Implements a registration form using a select menu, validating sport server-side

from flask import Flask,render_template,request

app=Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Ultimate Frisbee",
]

@app.route("/")

def index():
    return render_template("index.html",sports=SPORTS)

@app.route("/register",methods=["POST"] )  
def register():
    # Validate name
    name = request.form.get("name")
    if not name:
        return render_template("error.html",message="Missing name")
    
    # Confirm registration
    return render_template("success.html")

