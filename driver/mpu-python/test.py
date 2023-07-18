import time
from Inertial import InertialSensor

sensor = InertialSensor()

while(True):
    time.sleep(0.1)
    print(sensor.read_data())