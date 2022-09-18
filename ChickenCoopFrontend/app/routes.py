from flask import render_template, request
from app import app


@app.route('/')
@app.route('/index')
def index():
    states = {'InsideTemp': 70, 'InsideTempSP': 70, 'OutsideTemp': 60, 'InsideHum': 30, 'InsideHumSP': 30,
              'OutsideHum': 20, 'HeatLampState': 1, 'DoorState': 1, 'FanState': 0}
    chickens = "Shawna, Nat, Misty, Van, Tai, Lottie"
    return render_template('index.html', chickens = chickens, states = states)

@app.route('/helloesp')
def helloHandler():
    return 'Hello ESP!'

@app.route('/PointsList')
def returnPointsList():
    return 70

@app.route('/post', methods = ["POST"])
def post():
    print(request.data)
    return ''