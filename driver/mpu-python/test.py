import time, socketio
from Inertial import InertialSensor

sio = socketio.Client()
sensor = InertialSensor()
connected = False

time.sleep(1) # delay necessary to allow mpu9250 to settle

@sio.event
def disconnect():
    connected = False

    print('disconnected from server')

@sio.event
def connect():
    connected = True
    print('connection established')

    sio.emit("ID", 'python-gyro-client')
    # print('recording data')
    initLoop()

def initLoop ():
    while connected:
        # try:
        print("EMITING")
        data = sensor.read_data()
        print(data)

        sio.emit('py-mpu',data)

sio.connect('http://192.168.2.11:3000')
sio.wait()