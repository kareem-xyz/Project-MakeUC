from flask import Flask, render_template
from helpers import * # import all helper function from helper.py

# Configure Application
app = Flask(__name__)
# Set the sessiono and data storage for app, used per user
app.secret_key = '_5#y2LF4Qsbfiqbf2768er4vef6acg7egt7b9rgv634vbt7fgve'
app.config['SESSION_TYPE'] = 'filesystem' # use filesystem storage (server storage)
app.config['SESSION_PERMANENT'] = False
app.config["TEMPLATES_AUTO_RELOAD"] = True # Ensure templates are auto-reloaded, saves times 

# Load index (Homepage)
@app.route('/')
def index():
    # close_serial_connection()
    # sensor_data = read_from_arduino()
    # return f"Sensor Value: {sensor_data}" if sensor_data else "No data received"
    sensor_data = [
        {'number':0,'name':'Cairo Right', 'humidity':10},
        {'number':1,'name':'Cairo Left', 'humidity':90}
        ]
    return render_template('home.html', sensor_data=sensor_data) # Change number to the actual read value

# Run App
if __name__ == '__main__':
    app.run()
    # readserial('COM28', 9600) USED FOR LOOP READING. NOT SURE OF IMPLEMENTATION YET