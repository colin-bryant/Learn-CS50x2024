# Implements a registration form using a select menu, validating sport server-side
from cs50 import SQL
from flask import Flask,render_template,request,redirect

app=Flask(__name__)

db=SQL("sqlite://froshims.db")

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
    name = request.form.get("Name")
    if not name:
        return render_template("error.html",message="Missing name")
    # Validate sport
    sport =request.form.get("sport")
    if not sport:
        return render_template("error.html",message="Missing sport")
    if sport not in SPORTS:
        return render_template("error.html",message="Invalid sport")        
    

    #Remember registrant
    REGISTRANTS[name] = sport

    # Confirm registration
    return redirect("/registrants")
@app.route('/registrants')
def registrants():
    return render_template("registrants.html",registrants = REGISTRANTS)