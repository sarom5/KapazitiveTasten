/*
 * capazitiveTasten.h
 *
 *  Created on: 13.05.2016
 *      Author: sascha
 */

#ifndef CAPAZITIVETASTEN_H_
#define CAPAZITIVETASTEN_H_

#include "main.h"
//#include <util/delay.h>

//#define DEBUG_TASTEN
//#define DEBUG_EINE_TASTE
/************************************************************************
 * Aktiviert den uart.
 * Legt auf den UART die anzahl der Zyklen.
 * Aktiviert den Debug-Pin (1) um den Begin eines Ladevorgangs am Oszi 
 * triggern zu können.
 */
#ifdef DEBUG_TASTEN_TRIGGER
#include "serial.h"
//Einstelugen Debug-Pin (1)
#define dbFlagPORT PORTD
#define dbFlagDDR DDRD
#define dbFlagPIN PIND
#define dbFlagPin PD6
#endif /* DEBUG_TASTEN */

//Einstellungen für die Taste 0-3
#define CAP_DDR0 DDRA
#define CAP_PORT0 PORTA
#define CAP_PIN0 PINA
#define MASK_SENSOR0		0b01010101
#define MASK_VERSORGER0 	0b10101010

//Einstellungen für die Tasten 4-7
#define CAP_DDR1 DDRC
#define CAP_PORT1 PORTC
#define CAP_PIN1 PINC
#define MASK_SENSOR1		0b01010101
#define MASK_VERSORGER1 	0b10101010

//Tastenzuordnung
#define T_HOCH 0
#define T_RUNTER 1
#define T_LINKS 2
#define T_RECHTS 3
#define T_ENTER 4
#define T_MENUE 5
#define T_WECKER 6
#define T_SNNOZE 7
#define T_PFEILMASKE 0x0F

//zyklen für unberührten Taster
#define CAP_TOLERANZ_AN 4
#define CAP_TOLERANZ_AUS 2
#define CAP_COUNT_MAX 6
#define CAP_COUNT_MIN -5
#define CAP_NUM 8
#define BUFFER_SIZE 32

void tasten_init();
uint8_t readCap(void);

#endif /* CAPAZITIVETASTEN_H_ */
