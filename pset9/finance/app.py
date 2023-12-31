import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import date

today = str(date.today())

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Global vars:
cur_stock_prices = {}
user_stocks = {}
user_cash = 0.0


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
    # user_data = db.execute("SELECT users.cash, transactions.stock_symbol, transactions.shares_no, transactions.stock_price, transaction_type FROM users JOIN transactions ON users.id = transactions.user_id WHERE users.id = ?", session["user_id"])
    user_cash = float(
        db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    )
    bought_stocks_list = db.execute(
        "SELECT stock_symbol, shares_no FROM transactions WHERE user_id = ? AND transaction_type = 'buy'",
        session["user_id"],
    )
    bought_stocks = {}
    for each_stock in bought_stocks_list:
        if each_stock["stock_symbol"] in bought_stocks:
            bought_stocks[each_stock["stock_symbol"]] += each_stock["shares_no"]
        else:
            bought_stocks[each_stock["stock_symbol"]] = each_stock["shares_no"]

    sold_stocks_list = db.execute(
        "SELECT stock_symbol, shares_no FROM transactions WHERE user_id = ? AND transaction_type = 'sell'",
        session["user_id"],
    )
    sold_stocks = {}
    for each_stock in sold_stocks_list:
        if each_stock["stock_symbol"] in sold_stocks:
            sold_stocks[each_stock["stock_symbol"]] += each_stock["shares_no"]
        else:
            sold_stocks[each_stock["stock_symbol"]] = each_stock["shares_no"]

    for stock, shares in bought_stocks.items():
        user_stocks[stock] = shares
    for stock, shares in sold_stocks.items():
        user_stocks[stock] -= shares
    # Edge case not handled: where use buys and sells some shares in a stock, but net shares is 0 at the end. That stock should be removed from display (instead of showing number of shares as 0)
    # bought_stocks = db.execute("SELECT stock_symbol, shares_no FROM transactions WHERE user_id = ? AND transaction_type = 'buy'", session["user_id"])
    # sold_stocks = db.execute("SELECT stock_symbol, shares_no FROM transactions WHERE user_id = ? AND transaction_type = 'sell'", session["user_id"])
    # user_stocks = db.execute("SELECT users.cash, transactions.stock_symbol, transactions.shares_no FROM users JOIN transactions ON users.id = transactions.user_id WHERE user_id = ?", session["user_id"])
    for stock in user_stocks:
        cur_stock_prices[stock] = float(lookup(stock)["price"])
    return render_template(
        "index.html",
        user_stocks=user_stocks,
        cur_stock_prices=cur_stock_prices,
        user_cash=user_cash,
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        shares_no = int(request.form.get("shares"))
        if not lookup(stock_symbol):
            return apology("Invalid stock symbol")
        elif shares_no <= 0:
            return apology("Invalid number of shares")
        else:
            stock_price = float(lookup(stock_symbol)["price"])
            cur_cash = float(
                db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
            )
            if cur_cash < shares_no * stock_price:
                return apology(
                    "You cannot afford those many shares at the current price"
                )
            else:
                username = db.execute(
                    "SELECT username FROM users WHERE id = ?", session["user_id"]
                )[0]["username"]
                db.execute(
                    "UPDATE users SET cash = ? WHERE id = ?",
                    (cur_cash - (shares_no * stock_price)),
                    session["user_id"],
                )
                db.execute(
                    "INSERT INTO transactions(user_id, username, stock_symbol, shares_no, stock_price, date, transaction_type) VALUES (?,?,?,?,?,?,?)",
                    session["user_id"],
                    username,
                    stock_symbol,
                    shares_no,
                    stock_price,
                    today,
                    "buy",
                )

    else:
        return render_template("buy.html")
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_transactions = db.execute(
        "SELECT * FROM users JOIN transactions ON users.id = transactions.user_id WHERE users.id = ?",
        session["user_id"],
    )
    return render_template("history.html", user_transactions=user_transactions)


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
        return render_template("quoted.html", placeholder=lookup(symbol))
    else:  # via the get-method
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        users = db.execute("SELECT * FROM users WHERE username = ?", username)
        if not username:
            return apology("Please enter a username")
        if len(users) == 1:
            return apology(
                "That username already exists, please choose a different one"
            )
        if not password:
            return apology("Please enter a password")
        if password != confirmation:
            return apology("Password and confirmation don't match")
        db.execute(
            "INSERT INTO users(username, hash) VALUES (?,?)",
            username,
            generate_password_hash(password),
        )
        return render_template("success.html", placeholder="successfully registered!")

    else: # via the get-method
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        sell_shares = int(request.form.get("shares"))
        sell_stock = request.form.get("symbol")
        if sell_shares > int(user_stocks[sell_stock]):
            return apology("You don't hold those many shares in the stock")
        else:
            stock_price = float(lookup(sell_stock)["price"])
            username = db.execute(
                "SELECT username FROM users WHERE id = ?", session["user_id"]
            )[0]["username"]
            updated_cash = float(
                db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]) + (stock_price * sell_shares)
            db.execute(
                "INSERT INTO transactions(user_id, username, stock_symbol, shares_no, date, stock_price, transaction_type) VALUES (?,?,?,?,?,?,'sell')",
                session["user_id"],
                username,
                sell_stock,
                sell_shares,
                today,
                stock_price,
            )
            db.execute(
                "UPDATE users SET cash = ? WHERE id = ?",
                (updated_cash),
                session["user_id"],
            )

    else:
        return render_template("sell.html", user_stocks=user_stocks)
    return redirect("/")

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def change_pass():
    if request.method == "POST":
        new_pass = request.form.get("new_password")
        db.execute(
            "UPDATE users SET hash = ? WHERE id = ?",
            generate_password_hash(new_pass),
            session["user_id"],
        )
        return redirect("/")
    else:
        return render_template("change_password.html")
