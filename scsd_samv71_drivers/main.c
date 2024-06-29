#include <atmel_start.h>
#include "peripherals/opt4003q1.h"

volatile uint32_t lux = 0;

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	OPT4003Q1_Initialize();

	/* Replace with your application code */
	while (1) {
		
		SC_FREYR_EPS_202_SystemStatus_t repsonse = SC_FREYR_EPS_202_SystemStatus();
		
	}
}
