/*
 * opt4003q1.c
 *
 * Created: 2024-06-29 4:24:00 PM
 *  Author: Amro
 */ 

#include "opt4003q1.h"
#include "driver_init.h"

static struct io_descriptor *OPT4003Q1_Descriptor;
static uint8_t OPT4003Q1_Buffer[10];

void OPT4003Q1_Initialize() {
	i2c_m_sync_get_io_descriptor(&I2C_0, &OPT4003Q1_Descriptor);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x45, I2C_M_SEVEN);
	
	OPT4003Q1_Buffer[0] = 0x0A;
	OPT4003Q1_Buffer[1] = 0x32;
	OPT4003Q1_Buffer[2] = 0x38;
	io_write(OPT4003Q1_Descriptor, (uint8_t *)OPT4003Q1_Buffer, 3);
}

uint32_t OPT4003Q1_ReadLux(uint8_t channel) {
	uint32_t lux = 0;
	
	OPT4003Q1_Buffer[0] = 0x00;
	io_write(OPT4003Q1_Descriptor, (uint8_t *)OPT4003Q1_Buffer, 1);
	
	OPT4003Q1_Buffer[0] = 0x00;
	OPT4003Q1_Buffer[1] = 0x00;
	OPT4003Q1_Buffer[2] = 0x00;
	OPT4003Q1_Buffer[3] = 0x00;
	io_read(OPT4003Q1_Descriptor, (uint8_t *) OPT4003Q1_Buffer, 4);
	
	uint8_t exponent = OPT4003Q1_Buffer[0] >> 4;
	uint16_t msb = ((OPT4003Q1_Buffer[0] & 0x0F) << 8) | OPT4003Q1_Buffer[1];
	uint16_t lsb = OPT4003Q1_Buffer[2];

	uint32_t mantissa = (msb << 8) + lsb;
	uint32_t adc_codes = mantissa << exponent;
	lux = adc_codes * 535E-6;
	
	return lux;
}

void OPT4003Q1_MODE_ONESHOT(){
	
	OPT4003Q1_Buffer[0] = 0x0A;
	OPT4003Q1_Buffer[1] = 0x32;
	OPT4003Q1_Buffer[2] = 0x28;
	
	/* write command
	OPT4003Q1_Buffer[0] = 0x0A;
	OPT4003Q1_Buffer[1] = 0x72;
	OPT4003Q1_Buffer[2] = 0x28;
	*/
	io_write(OPT4003Q1_Descriptor, (uint8_t *)OPT4003Q1_Buffer, 3);
	
}