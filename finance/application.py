import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    userId = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", userId)
    ownedStocks = db.execute("SELECT * FROM owned WHERE userId = ?", userId)
    # print(f"CURRENT_OWNED: {ownedStocks}")
    current_stocks = []
    totalBalance = user[0]["cash"]
    for index in range(len(ownedStocks)):
        newStock = {}
        # print(f"HIT: {ownedStocks[index]}")
        currentInfo = lookup(ownedStocks[index]["symbol"])
        newStock["symbol"] = ownedStocks[index]["symbol"]
        newStock["shares"] = ownedStocks[index]["shares"]
        newStock["price"] = currentInfo["price"]
        newStock["name"] = currentInfo["name"]
        current_stocks.append(newStock)
        totalBalance += float(ownedStocks[index]["shares"]) * currentInfo["price"]

    # print(f"HRERE: {current_stocks}, {totalBalance}")
    # print(user)
    return render_template("index.html", stocks=current_stocks, cash=user[0]["cash"], totalBalance=totalBalance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        shares = request.form.get("shares")
        symbol = request.form.get("symbol")
        data = lookup(symbol)

        userId = session["user_id"]
        user = db.execute("SELECT * FROM users WHERE id=?", userId)
        # print(f"USER FOUND: {user}")
        # print("CASH: ", user[0]["cash"])
        # print("DATA FOUND:", data)
        # print("FOUND: ", data["price"])
        # Ensure symbol was submitted
        if not symbol:
            return apology("Missing Symbol", 400)

        # Ensure symbol is valid
        elif data == None:
            return apology("Invalid Symbol", 400)

        # Ensure number of shares is valid
        elif not shares or not shares.isnumeric():
            return apology("Invalid number of shares", 400)

        # Ensure user can afford to buy number of shares
        elif user[0]["cash"] < (data["price"] * float(shares)):
            return apology("Not Sufficient Balance", 400)

        # Else, update DB
        else:
            newCash = user[0]["cash"] - (data["price"] * float(shares))

            # Check if user already owned this symbol
            owned = db.execute("SELECT * FROM owned WHERE symbol = ?", symbol)

            # print(f"OWNED: {owned}")
            # If user is owning this symbol before
            if len(owned) >= 1:
                # Update number of shares for this symbol in 'owned table'
                db.execute("UPDATE owned SET shares = ? WHERE userId = ? AND symbol = ?",
                           owned[0]["shares"] + int(shares), userId, symbol)

            # If user is not owning this symbol
            else:
                # Insert new symbol into 'owned' table
                db.execute("INSERT INTO owned(userId, symbol, shares) VALUES (?, ?, ?)", userId, symbol, shares)

            # Add information to transactions table
            db.execute("INSERT INTO transactions (symbol, action, price, shares, datetime, userId) VALUES(?, ?, ?, ?, ?, ?)",
                       symbol, "buy", data["price"], shares, datetime.now(), userId)

            # Update user's cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, userId)

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userId = session["user_id"]
    transData = db.execute("SELECT * FROM transactions WHERE userId = ?", userId)
    return render_template("history.html", data=transData)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("Invalid Symbol", 400)
        valid = lookup(request.form.get("symbol"))
        # print(valid)

        # Ensure symbol was valid
        if valid == None:
            return apology("Invalid Symbol", 400)

        # Render quoted with lookup information
        return render_template("quoted.html", valid=valid)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure confirmation matched with password
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("password do not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist in DB
        if len(rows) >= 1:
            return apology("invalid username and/or password", 400)

        # Ensure username exists and password is correct
        # if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
        #     return apology("invalid username and/or password", 403)

        # Insert new username to DB
        db.execute('INSERT INTO users(username, hash) VALUES(?, ?)',
                   request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    userId = session["user_id"]

    # Find all owned symbol
    ownedStocks = db.execute("SELECT symbol FROM owned WHERE userId = ?", userId)
    symbols = []
    for i in ownedStocks:
        # print(ownedStocks[i])
        symbols.append(i["symbol"])
    print(f"CURRENT OWNED: {symbols}")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # print(f"THIS IS SHARES IN SELL: {shares}")

        # Ensure input symbol does not exist in 'owned' table
        if symbol not in symbols:
            return apology("Invalid Symbol", 400)

        # Ensure input of shares is not blank
        if not shares:
            return apology("Invalid number of shares", 400)

        # Ensure input of shares does not larger than owned shares of that stock and not a positive integer
        ownedShares = db.execute("SELECT shares FROM owned WHERE userId = ? AND symbol = ?", userId, symbol)
        print(f"OWED_SHARES: {ownedShares[0]}")
        if int(shares) > ownedShares[0]["shares"] or not shares.isnumeric():
            return apology("Invalid number of shares", 400)

        # If all input are valid, update DB.
        else:
            # Lookup the current price
            data = lookup(symbol)

            # Find user info
            user = db.execute("SELECT * FROM users WHERE id = ?", userId)
            newCash = user[0]["cash"] + (data["price"] * float(shares))

            # Check if user already owned this symbol
            owned = db.execute("SELECT * FROM owned WHERE symbol = ?", symbol)

            # If user is selling all the current owned shares:
            if shares == ownedShares[0]["shares"]:
                # Delete the entry from 'owned' table
                db.execute("DELETE FROM owned WHERE userId = ? AND symbol = ?", userId, symbol)

            # If user is not selling all share of this symbol
            else:
                # UPDATE number of share 'owned' table
                db.execute("UPDATE owned SET shares = ? WHERE userId = ? AND symbol = ?",
                           ownedShares[0]["shares"] - int(shares), userId, symbol)

            owned = db.execute("SELECT * FROM owned WHERE symbol = ?", symbol)
            print(f"CHECK_AGAIN_OWNED: {owned}")

            # Add information to transactions table
            db.execute("INSERT INTO transactions (symbol, action, price, shares, datetime, userId) VALUES(?, ?, ?, ?, ?, ?)",
                       symbol, "sell", data["price"], shares, datetime.now(), userId)

            # Update user's cash
            db.execute("UPDATE users SET cash = ? WHERE id = ?", newCash, userId)

        return redirect("/")
    else:
        return render_template("sell.html", data=ownedStocks)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
