import time
from Inertial import InertialSensor

sensor = InertialSensor

while(True):
    time.sleep(0.1)
    sensor.read_data()