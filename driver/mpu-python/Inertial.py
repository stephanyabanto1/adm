import time, sys, json
import smbus2

MPU6050_ADDR = 0x68
PWR_MGMT_1   = 0x6B
SMPLRT_DIV   = 0x19
CONFIG       = 0x1A
GYRO_CONFIG  = 0x1B
ACCEL_CONFIG = 0x1C
INT_ENABLE   = 0x38
ACCEL_XOUT_H = 0x3B
ACCEL_YOUT_H = 0x3D
ACCEL_ZOUT_H = 0x3F
TEMP_OUT_H   = 0x41
GYRO_XOUT_H  = 0x43
GYRO_YOUT_H  = 0x45
GYRO_ZOUT_H  = 0x47
#AK8963 registers
AK8963_ADDR  = 0x0C
AK8963_ST1   = 0x02
HXH          = 0x04
HYH          = 0x06
HZH          = 0x08
AK8963_ST2   = 0x09
AK8963_CNTL  = 0x0A

bus =  smbus2.SMBus(1) # start comm with i2c bus

def read_raw_bits(register):
	# read accel and gyro values
	high = bus.read_byte_data(MPU6050_ADDR, register)
	low = bus.read_byte_data(MPU6050_ADDR, register+1)

	# combine higha and low for unsigned bit value
	value = ((high << 8) | low)
	
	# convert to +- value
	if(value > 32768):
		value -= 65536
	return value

class Gyroscope():
	def __init__(self) -> None:
		pass
	
	def read():
		gyro_x = read_raw_bits(GYRO_XOUT_H)
		gyro_y = read_raw_bits(GYRO_YOUT_H)
		gyro_z = read_raw_bits(GYRO_ZOUT_H)
		return gyro_x, gyro_y, gyro_z

class InertialSensor():
	def __init__(self) -> None:
		self.run_config()
		self.gyro = Gyroscope()

	def read_data(self):
		return self.gyro.read()

	def run_config(self):
		samp_rate_div = 0 # sample rate = 8 kHz/(1+samp_rate_div)
		bus.write_byte_data(MPU6050_ADDR, SMPLRT_DIV, samp_rate_div)
		time.sleep(0.1)
		# reset all sensors
		bus.write_byte_data(MPU6050_ADDR,PWR_MGMT_1,0x00)
		time.sleep(0.1)
		# power management and crystal settings
		bus.write_byte_data(MPU6050_ADDR, PWR_MGMT_1, 0x01)
		time.sleep(0.1)
		#Write to Configuration register
		bus.write_byte_data(MPU6050_ADDR, CONFIG, 0)
		time.sleep(0.1)
		#Write to Gyro configuration register
		gyro_config_sel = [0b00000,0b010000,0b10000,0b11000] # byte registers
		gyro_config_vals = [250.0,500.0,1000.0,2000.0] # degrees/sec
		gyro_indx = 0
		bus.write_byte_data(MPU6050_ADDR, GYRO_CONFIG, int(gyro_config_sel[gyro_indx]))
		time.sleep(0.1)
		#Write to Accel configuration register
		accel_config_sel = [0b00000,0b01000,0b10000,0b11000] # byte registers
		accel_config_vals = [2.0,4.0,8.0,16.0] # g (g = 9.81 m/s^2)
		accel_indx = 0                            
		bus.write_byte_data(MPU6050_ADDR, ACCEL_CONFIG, int(accel_config_sel[accel_indx]))
		time.sleep(0.1)
		# interrupt register (related to overflow of data [FIFO])
		bus.write_byte_data(MPU6050_ADDR, INT_ENABLE, 1)
		time.sleep(0.1)
	