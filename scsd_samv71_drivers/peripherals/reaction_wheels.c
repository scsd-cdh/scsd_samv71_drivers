#include <atmel_start.h>
#include "driver_init.h"
#include "utils.h"

// Command IDs
#define CMD_SET_SPEED 0x02
#define CMD_SET_TORQUE 0x03
#define CMD_CONTROL_MODE 0x0A
#define CMD_MOTOR_ON 0x07
#define CMD_SET_PWM 0x21

#define CUBEWHEEL_ADDRESS 0x68 // CubeWheel I2C address (0xD0 shifted right by 1 bit)

#define TRUE 1

static struct io_descriptor *CubeWheel_Descriptor;
static struct i2c_m_sync_desc *i2cdesc;

static uint8_t CubeWheel_Buffer[8];

static uint8_t write_buffer[10];
static volatile uint32_t val[8];

enum CubeWheel_ControlMode {
	MODE1,
	MODE2,
	MODE3	
};

uint32_t CubeWheel_ControlModeToSpeedController(CubeWheel_ControlMode mode) {
	write_buffer[0] = CMD_CONTROL_MODE;
	write_buffer[1] = mode;
	return io_write(CubeWheel_Descriptor, (uint8_t *) write_buffer, 2);
}

uint32_t CubeWheel_SetSpeedMax()  {
	write_buffer[0] = CMD_SET_SPEED;
	write_buffer[1] = 0xFF;
	write_buffer[2] = 0x00;
	return io_write(CubeWheel_Descriptor, (uint8_t *) write_buffer, 3);
}

uint32_t CubeWheel_SetTorqueMax() {
	write_buffer[0] = CMD_SET_TORQUE;
	write_buffer[1] = 0xF0;
	write_buffer[2] = 0x00;
	return io_write(CubeWheel_Descriptor, (uint8_t *) write_buffer, 3);
}

uint32_t CubeWheel_MotorOn() {
	write_buffer[0] = CMD_MOTOR_ON;
	write_buffer[1] = 0x01;
	uint16_t bytes_written = io_write(CubeWheel_Descriptor, (uint8_t *) write_buffer, 2);
}

void CubeWheel_Initialize() {
	i2c_m_sync_get_io_descriptor(&I2C_0, &CubeWheel_Descriptor);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, CUBEWHEEL_ADDRESS, I2C_M_SEVEN);
}

uint8_t Read_TelemetryID() {
	write_buffer[0] = 128;
	io_write(CubeWheel_Descriptor, (uint8_t*) write_buffer, 1);
	
	CubeWheel_Buffer[0] = 0x00;
	CubeWheel_Buffer[1] = 0x00;
	CubeWheel_Buffer[2] = 0x00;
	CubeWheel_Buffer[3] = 0x00;
	CubeWheel_Buffer[4] = 0x00;
	CubeWheel_Buffer[5] = 0x00;
	CubeWheel_Buffer[6] = 0x00;
	CubeWheel_Buffer[7] = 0x00;
	
	val[0] = io_read(CubeWheel_Descriptor, (uint8_t*) CubeWheel_Buffer, 8);;
	return val;
}

int main(void)
{
	atmel_start_init();
	
	
	//uint8_t bufferoff[] = { 0x01 , 0x90 };
	//uint8_t bufferon[] = { 0x01 , 0x91 };
	
	
	CubeWheel_Initialize();
	CubeWheel_ControlModeToSpeedController();
	CubeWheel_SetSpeedMax();
	CubeWheel_SetTorqueMax();
	CubeWheel_MotorOn();
	while(1){
		Read_TelemetryID();
	}
	
}

/*
void setup(io_descriptor I2C_0_io) {

	i2c_m_sync_get_io_descriptor(&I2C_0, &I2C_0_io);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, CUBEWHEEL_ADDRESS, I2C_M_SEVEN);
	
}

void loop() {
	readSpeed();
}

void SetSpeedMax(io_descriptor i2c0)  {
	uint8_t message[] = { b1 CMD_SET_SPEED, 0xFF,0x00 };
	io_write(&I2C_0, CUBEWHEEL_ADDRESS, 2)
	
	
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	io_write.write(CMD_SET_SPEED); // Send the command ID for setting speed
	Wire.write(0xFF); // High byte of speed (maximum value)
	Wire.write(0x00); // Low byte of speed (maximum value)
	Wire.endTransmission();
	Serial.println("Speed is set to maximum");
}

void SetTorqueMax() {
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	Wire.write(CMD_SET_TORQUE); // Send the command ID for setting torque
	Wire.write(0xF0); // High byte of torque (maximum value)
	Wire.write(0x00); // Low byte of torque (maximum value)
	Wire.endTransmission();
	Serial.println("Torque is set to maximum");
}

void ControlModeToDutyCycle() {
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	Wire.write(CMD_CONTROL_MODE); // Send the command ID for control mode
	Wire.write(0x02); // Set control mode to speed controller
	Wire.endTransmission();
	Serial.println("Control mode set to speed controller");
}

void SetPWM() {
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	Wire.write(CMD_SET_PWM); // Send the command ID for control mode
	// Wire.write(); // Set control mode to speed controller
	Wire.endTransmission();
	Serial.println("Control mode set to speed controller");
}

void MotorOn() {
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	Wire.write(CMD_MOTOR_ON); // Send the command ID to turn on the motor
	Wire.write(0x01); // Turn the motor on
	Wire.endTransmission();
	Serial.println("Motor is ON");
}


void readSpeed(){
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	Wire.write(0x89);
	Wire.endTransmission(false);

	Wire.requestFrom(CUBEWHEEL_ADDRESS, 6); // Request 8 bytes of telemetry data (example size)
	while (Wire.available()) {
		uint16_t x = 0;
		uint16_t c = Wire.read(); // Receive a byte as character
		c = c << 8;

		x = Wire.read();
		x = x | c;

		Serial.print(x); // Print the received byte in hexadecimal format
		Serial.print(' ');
	}
	Serial.println();

	Wire.endTransmission();
}

void requestIdentificationTelemetry() {
	Wire.beginTransmission(CUBEWHEEL_ADDRESS);
	Wire.write(0x80); // Send the telemetry ID for identification
	Wire.endTransmission(false); // Send repeated start condition

	Wire.requestFrom(CUBEWHEEL_ADDRESS, 8); // Request 8 bytes of telemetry data (example size)

	while (Wire.available()) {
		char c = Wire.read(); // Receive a byte as character
		Serial.print(c, HEX); // Print the received byte in hexadecimal format
		Serial.print(' ');
	}
	Serial.println();
}
*/
