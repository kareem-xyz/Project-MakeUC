from flask import Flask, jsonify, render_template
from serial import Serial
# Configure Application
app = Flask(__name__)
# Set the sessiono and data storage for app, used per user
app.secret_key = '_5#y2LF4Qsbfiqbf2768er4vef6acg7egt7b9rgv634vbt7fgve'
app.config['SESSION_TYPE'] = 'filesystem' # use filesystem storage (server storage)
app.config['SESSION_PERMANENT'] = False
app.config["TEMPLATES_AUTO_RELOAD"] = True # Ensure templates are auto-reloaded, saves times 

arduino_1 = Serial(port='COM9', baudrate=9600, timeout=0)
arduino_2 = Serial(port='COM11', baudrate=9600, timeout=0)


# Load index (Homepage)
@app.route('/')
def index():
    # close_serial_connection()
    sensor_data = [
    {'number':0,'name':'East Cairo', 'humidity': read_from_arduino(arduino_1)},
    {'number':1,'name':'West Cairo', 'humidity': read_from_arduino(arduino_2)}
    ]
    # return f"Sensor Value: {sensor_data}" if sensor_data else "No data received"
    return render_template('home.html', sensor_data=sensor_data) # Change number to the actual read value

# def close_serial_connection():
#     if arduino.is_open:
#         arduino.close()
        
def read_from_arduino(arduino_no):
    if arduino_no.in_waiting > 0:
        # CURRENTLY THIS POSTS ONLY ONE LINE. NEED TO SEE HOW TO ADD MULTIPLE VALUES
        data = arduino_no.readline().decode('utf-8').strip() # Read a line and decode it ()
        return data
    return None

@app.route('/refresh_values_')
def refresh_values():
    sensor_data = [
    {'number':0,'name':'Cairo Right', 'humidity': read_from_arduino(arduino_1)},
    {'number':1,'name':'Cairo Left', 'humidity': read_from_arduino(arduino_2)}
    ]
    return jsonify(sensor_data)

# Run App
if __name__ == '__main__':
    app.run()
    # readserial('COM28', 9600) USED FOR LOOP READING. NOT SURE OF IMPLEMENTATION YET