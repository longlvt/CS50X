from cs50 import SQL
# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

userId = 1
symbol = "a"
ownedShares = db.execute("SELECT shares FROM owned WHERE userId = ? AND symbol = ?", userId, symbol)
print(ownedShares)