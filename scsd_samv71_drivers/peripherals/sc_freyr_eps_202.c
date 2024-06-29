/*
 * sc_freyr_eps_202.c
 *
 * Created: 2024-06-29 6:01:47 PM
 *  Author: Amro
 */ 
#include "sc_freyr_eps_202.h"

static volatile SC_FREYR_EPS_202_SystemStatus_t system_status = 0;
static struct io_descriptor *SC_FREYR_EPS_202_Descriptor;
static uint8_t SC_FREYR_EPS_202_Buffer[57];

void SC_FREYR_EPS_202_Initialize() {
	i2c_m_sync_get_io_descriptor(&I2C_0, &SC_FREYR_EPS_202_Descriptor);
	i2c_m_sync_enable(&I2C_0);
	i2c_m_sync_set_slaveaddr(&I2C_0, 0x10, I2C_M_SEVEN);
}

SC_FREYR_EPS_202_SystemStatus_t SC_FREYR_EPS_202_SystemStatus() {
	SC_FREYR_EPS_202_Buffer[0] = 0x80;
	io_write(SC_FREYR_EPS_202_Descriptor, (uint8_t *)SC_FREYR_EPS_202_Buffer, 1);
	
	SC_FREYR_EPS_202_Buffer[0] = 0xFF;
	SC_FREYR_EPS_202_Buffer[1] = 0xFF;
	SC_FREYR_EPS_202_Buffer[2] = 0xFF;
	SC_FREYR_EPS_202_Buffer[3] = 0xFF;
	SC_FREYR_EPS_202_Buffer[4] = 0xFF;
	io_read(SC_FREYR_EPS_202_Descriptor, (uint8_t *) SC_FREYR_EPS_202_Buffer, 5);
	
	system_status.firmware_version = SC_FREYR_EPS_202_Buffer[0] >> 4;
	system_status.state = SC_FREYR_EPS_202_Buffer[0] & 0x0F;
	system_status.runtime_seconds = (SC_FREYR_EPS_202_Buffer[1] << 32) | (SC_FREYR_EPS_202_Buffer[2] << 16) | (SC_FREYR_EPS_202_Buffer[3] << 8) | SC_FREYR_EPS_202_Buffer[4];
	return system_status;
}

void SC_FREYR_EPS_202_NextExperimentPhase() {
	
}
