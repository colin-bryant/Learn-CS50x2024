import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
# 这行代码将自定义的 usd 过滤器添加到 Flask 应用程序的 Jinja2 环境中，以便在模板中可以直接使用。
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    purchases=db.execute("SELECT * FROM purchases WHERE purchases.user_id = ?",user_id)
    current_cash =db.execute("SELECT users.cash FROM users WHERE users.id=?",user_id)

    if not purchases:
        return apology("You haven't purchased any stock.",400)
    total_price_sum = 0
    for purchase in purchases:
        # {'id': 2, 'user_id': 8, 'symbol': 'BABA', 'shares': 1, 'price': 80.04, 'total_price': 80.04}
           total_price_sum =  total_price_sum + purchase['total_price']
    total_cash =  total_price_sum + current_cash[0]['cash']
    return render_template('index.html',purchases=purchases,cash = current_cash[0]['cash'],total_cash=total_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        symbol=request.form.get('symbol')
        shares = request.form.get('shares')
        user_id =session['user_id']
        # {'price': 80.04, 'symbol': 'BABA'}  or None
        quote =lookup(symbol)
        if not symbol or  not shares or int(shares) <= 0 or not quote:
            return apology("Must provide a valid value.",400)
        # [{'cash': 10000}]
        current_cash =db.execute("SELECT users.cash FROM users WHERE users.id=?",user_id)

        total_price = quote['price'] * int(shares)

        new_cash = current_cash[0]['cash']-total_price

        if new_cash< 0:
            return apology("Your balance is insufficient.",400)
        purchases = db.execute("SELECT * FROM purchases WHERE purchases.user_id=? AND purchases.symbol = ?" ,user_id,symbol)
        if not purchases:
            db.execute("INSERT INTO purchases (user_id,symbol,shares,price,total_price) VALUES(?,?,?,?,?)",user_id,symbol,shares,quote['price'],total_price)
        else:
            new_shares = int(purchases[0]['shares']) + int(shares)
            new_price = quote['price']
            new_totle_price = new_price  * int(new_shares)

            db.execute("UPDATE purchases SET shares= ? ,price= ?,total_price=? WHERE purchases.user_id=? AND purchases.symbol = ? ",new_shares,new_price,new_totle_price,user_id,symbol)
        db.execute("UPDATE users SET cash = ? WHERE users.id= ?",new_cash,user_id)
        db.execute("INSERT INTO transaction_info(user_id,symbol,shares,price) VALUES(?,?,?,?)",user_id,symbol,shares,quote['price'])
        flash("Purchase successful!", "Brought")
        return  redirect("/", )


    return render_template("buy.html")

#-- 创建 purchases 表，用于记录购买情况
# CREATE TABLE IF NOT EXISTS purchases (
#     id INTEGER PRIMARY KEY AUTOINCREMENT,
#     user_id INTEGER NOT NULL,
#     symbol TEXT NOT NULL,
#     shares INTEGER NOT NULL,
#     price NUMERIC NOT NULL,
#     total_price NUMERIC NOT NULL,
#     FOREIGN KEY (user_id) REFERENCES users(id)
# );

# CREATE TABLE IF NOT EXISTS  transaction_info(
#     id INTEGER PRIMARY KEY AUTOINCREMENT,
#     user_id INTEGER NOT NULL,
#     symbol TEXT NOT NULL,
#     shares INTEGER NOT NULL,
#     price NUMERIC NOT NULL,
#     purchase_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
#     FOREIGN KEY (user_id) REFERENCES users(id)
# );

# -- 在 symbol 列上创建 UNIQUE 索引，确保股票代码唯一
# CREATE UNIQUE INDEX IF NOT EXISTS symbol_index ON purchases (symbol);

# -- 在 user_id 和 purchase_date 列上创建组合索引，加快查询效率
# CREATE INDEX IF NOT EXISTS user_purchase_date_index ON purchases (user_id, purchase_date);
# 给表添加新列
# ALTER TABLE purchases
# ADD COLUMN total_price NUMERIC NOT NULL DEFAULT 0;
#  删除某列
# ALTER TABLE purchases DROP COLUMN total_price;
# 删除所有列
# DELETE FROM purchases;
#  删除表
# DROP FROM purchases;
# 删除某条记录
# db.execute("DELETE FROM purchases WHERE id = ?", (1,))

# 某记录的某一列数据 更新
# UPDATE purchases SET symbol = 'NEW_SYMBOL' WHERE id = 1;
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transaction_info =db.execute("SELECT * FROM transaction_info")
    return render_template("history.html",transaction_info=transaction_info)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        flash('login success')
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not symbol or not quote:
            return render_template('quote.html')

        return render_template("quoted.html",quote = quote)

    return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not name or not password or not confirmation or  password != confirmation:
            return apology("Bad request ! ",400)
        existing_user = db.execute("SELECT * FROM users WHERE username = ?",name)
        if existing_user:
            return apology("Username already exists",400)
        hash=generate_password_hash(password)
        db.execute("INSERT INTO users(username,hash) VALUES(?,?)",name,hash)
        flash('register success')
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    purchases=db.execute("SELECT * FROM purchases WHERE purchases.user_id = ? " ,user_id)
    if not purchases:
         return apology("You have not any stocks ,go to buy",400)
    # purchase :{'id': 2, 'user_id': 8, 'symbol': 'BABA', 'shares': 1, 'price': 80.04, 'total_price': 80.04}

    symbols_seen =set()
    for purchase in purchases:
        if purchase['symbol'] not in symbols_seen :
            symbols_seen.add(purchase['symbol'])
    if request.method == "POST":
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')
        if int(shares) <= 0 or  not symbol:
             return apology("Must provide a valid value.",400)
        current_shares =db.execute("SELECT * FROM purchases WHERE purchases.user_id = ? and purchases.symbol= ? " ,user_id,symbol)


        if int(current_shares[0]['shares']) < int(shares):
            return apology("TOO MANY SHARES",400)
        new_shares =  int(current_shares[0]['shares']) - int(shares)
        quote=lookup(symbol)
        total_price = int(shares) * quote['price']
        if int(new_shares) <= 0:
            db.execute("DELETE FROM purchases WHERE purchases.user_id = ? AND purchases.symbol= ? ",user_id,symbol)
        else:

            new_price = quote['price']
            new_totle_price = new_price  * int(new_shares)
            print( new_price)
            db.execute("UPDATE purchases SET shares= ? ,price= ?,total_price=? WHERE purchases.user_id=? AND purchases.symbol = ? ",new_shares,new_price,new_totle_price,user_id,symbol)
        current_cash = db.execute("SELECT users.cash FROM users WHERE users.id = ?",user_id)[0]
        new_cash = total_price + float(current_cash['cash'])

        db.execute("UPDATE users SET cash = ? ",new_cash)
        db.execute("INSERT INTO transaction_info(user_id,symbol,shares,price) VALUES(?,?,?,?)",user_id,symbol,-int(shares),quote['price'])
        flash("Sell successful!", "Sell")
        return redirect('/')
    return  render_template("sell.html",symbols_seen=symbols_seen)
