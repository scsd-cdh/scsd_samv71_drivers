/*
 * sc_freyr_eps_202.h
 *
 * Created: 2024-06-29 5:50:03 PM
 *  Author: Amro
 */ 


#ifndef SC_FREYR_EPS_202_H_
#define SC_FREYR_EPS_202_H_

typedef struct {
	uint8_t firmware_version;
	uint8_t state;
	uint32_t runtime_seconds;
} SC_FREYR_EPS_202_SystemStatus_t;

void SC_FREYR_EPS_202_Initialize();
SC_FREYR_EPS_202_SystemStatus_t SC_FREYR_EPS_202_SystemStatus();
void SC_FREYR_EPS_202_NextExperimentPhase();


#endif /* SC_FREYR_EPS_202_H_ */