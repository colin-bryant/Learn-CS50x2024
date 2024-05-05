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
    # Validate submission
    # if not request.form.get("Name") or request.form.get("sport") not in SPORTS:
    #     return render_template("failure.html")
    if not request.form.get("name"):
        return render_template("failure.html")
    for sport in request.form.getlist("sport"):
        if sport not in SPORTS:
            return render_template("failure.html")
    # Confirm registration
    return render_template("success.html")

