from flask import Flask, render_template, request, redirect, url_for, session
from flask_session import Session
from helpers import * # import all helper function from helper.py

# Configure Application
app = Flask(__name__)

# Set the secret key for session
app.secret_key = '_5#y2LF4Qsbfiqbf2768er4vef6acg7egt7b9rgv634vbt7fgve'
app.config['SESSION_TYPE'] = 'filesystem' # use filesystem storage (server storage)
app.config['SESSION_PERMANENT'] = False
app.config["TEMPLATES_AUTO_RELOAD"] = True # Ensure templates are auto-reloaded, saves times
Session(app) 

# Load index
@app.route('/')
def index():
    session.clear()
    return render_template('home.html')

if __name__ == '__main__':
    app.run()
    # readserial('COM28', 9600)