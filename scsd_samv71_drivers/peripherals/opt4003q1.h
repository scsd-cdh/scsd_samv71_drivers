/*
 * opt4003.h
 *
 * Created: 2024-06-29 4:12:46 PM
 *  Author: Amro
 */ 


#ifndef OPT4003Q1_H_
#define OPT4003Q1_H_

#include <stdint.h>

void OPT4003Q1_Initialize();
uint32_t OPT4003Q1_ReadLux(uint8_t channel);
void OPT4003Q1_MODE_ONESHOT();

#endif /* OPT4003_H_ */