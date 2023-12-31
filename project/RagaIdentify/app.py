import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# Configure application
app = Flask(__name__)


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///music.db")

# Global vars:


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """ User Homepage"""
    return render_template("index.html")

@app.route("/history")
@login_required
def history():
    raga_search_history = db.execute("SELECT * FROM raga_searches WHERE user_id=?",session["user_id"])
    return render_template("history.html",raga_search_history=raga_search_history)


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

def special_character(string):
    special_char=re.compile('[@_!#$%^&*()<>?/}{~:]')
    if special_char.search(string) == None:
        return False
    else:
        return True


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
        if len(password) < 8 or not special_character(password):
            return apology("Password has to be atleast 8 characters long with atleast 1 special character")
        if password != confirmation:
            return apology("Password and confirmation don't match")
        db.execute(
            "INSERT INTO users(username, hash) VALUES (?,?)",
            username,
            generate_password_hash(password),
        )
        return render_template("message.html", placeholder="successfully registered!")

    else: # via the get-method
        return render_template("register.html")


@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def change_pass():
    if request.method == "POST":
        old_pass = request.form.get("old_password")
        new_pass = request.form.get("new_password")
        if len(new_pass) < 8 or not special_character(new_pass):
            return apology("Password has to be atleast 8 characters long with atleast 1 special character")
        corr_password = db.execute("SELECT hash FROM users WHERE id = ?",session["user_id"])[0]["hash"]
        if check_password_hash(corr_password,old_pass):
            db.execute(
                "UPDATE users SET hash = ? WHERE id = ?",
                generate_password_hash(new_pass),
                session["user_id"],
            )
            return redirect("/")
        else:
            return apology("Old password is incorrect")
    else:
        return render_template("change_password.html")

@app.route("/find_raga", methods = ["POST"])
@login_required
def find_raga():
    if request.method == "POST":
        r = request.form.get("R")
        g = request.form.get("G")
        m = request.form.get("M")
        p = request.form.get("P")
        d = request.form.get("D")
        n = request.form.get("N")
        if not r:
            r = 0
        if not g:
            g = 0
        if not m:
            m = 0
        if not p:
            p = 0
        if not d:
            d = 0
        if not n:
            n = 0
        raga_nos = int(db.execute("SELECT COUNT(*) AS count FROM ragas WHERE r = ? AND g = ? AND m = ? AND p = ? AND d = ? AND n = ? ", r,g,m,p,d,n,)[0]["count"])
        if raga_nos > 0:
            raga = db.execute("SELECT name FROM ragas WHERE r = ? AND g = ? AND m = ? AND p = ? AND d = ? AND n = ? ", r,g,m,p,d,n,)[0]["name"]
            raga_id = db.execute("SELECT id FROM ragas WHERE name = ? ", raga)[0]["id"]
            db.execute("INSERT INTO raga_searches(user_id, ragam) VALUES(?,?)", session["user_id"], raga)
            return render_template("raga.html", placeholder = raga, raga_id=raga_id)
        else:
            return render_template("message.html", placeholder = "could not find raga")

    else:
        return redirect("/")

@app.route("/songs", methods = ["GET", "POST"])
@login_required
def songs():
    if request.method == "POST":
        raga=request.form.get("name")
        songs = db.execute("SELECT name FROM songs WHERE ragam=?",raga)
        return render_template("search.html", songs=songs, raga=raga)
    else:
        return render_template("search.html")


@app.route("/help", methods = ["GET"])
def help():
        return render_template("help.html")

@app.route("/deleteaccount",  methods = ["GET","POST"])
@login_required
def delete_acc():
    if request.method == "POST":
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        corr_password = db.execute("SELECT hash FROM users WHERE id=?",session["user_id"])[0]["hash"]
        if check_password_hash(corr_password,password) and confirmation == "CONFIRM":
            db.execute("DELETE FROM raga_searches WHERE user_id=?",session["user_id"])
            db.execute("DELETE FROM users WHERE id = ?",session["user_id"],)
            logout()
        else:
            return apology("Could not delete account")
        return redirect("/")
    else:
        return render_template("delete.html")


@app.route("/changeusername", methods=["GET", "POST"])
@login_required
def change_name():
    if request.method == "POST":
        new_name = request.form.get("new_username")
        db.execute(
            "UPDATE users SET username = ? WHERE id = ?",
            new_name,
            session["user_id"],
        )
        return render_template("message.html", placeholder="Username changed successfully")
    else:
        return render_template("change_username.html")
