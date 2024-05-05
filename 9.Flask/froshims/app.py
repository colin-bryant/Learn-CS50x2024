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
@app.route("/register")  
def register():
    # Validate submission
    if not request.form.get("name") or request.form.get("sports") not in SPORTS:
        return render_template("failure.html")
    # Confirm registration
    return render_template("success.html")

