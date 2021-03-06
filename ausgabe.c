/*
 * ausgabe.c
 *
 * Created: 07.06.2016 17:46:17
 *  Author: campe
 */ 
#include "ausgabe.h"



volatile static uint8_t ausgabe = 0;
static int8_t licht_scale = 0;
static int8_t audio_scale = 0;

#ifdef PWM_TIMER
ISR(TIMER2_OVF_vect) {
	if((ausgabe & (1<<T_HOCH)) && PWM_LICHT < 255) {
		PWM_LICHT++;
	}
	if((ausgabe & (1<<T_RUNTER)) && PWM_LICHT) {
		PWM_LICHT--;
	}
	if((ausgabe & (1<<T_RECHTS)) && PWM_AUDIO < 255) {
		PWM_AUDIO++;
	}
	if((ausgabe & (1<<T_LINKS)) && PWM_AUDIO) {
		PWM_AUDIO--;
	}
}
#endif

void init_aus() {
	AUS_DDR = 0xFF;
	AUS_SYS_DDR |= (1<<AUS_TAST_TON);
#ifdef PWM_TIMER
	TIMSK |= (1<<OCIE2);
	sei();
#endif
}

void aus_refrech() {
	if(ausgabe) {
		AUS_SYS_PORT |= (1<<AUS_TAST_TON);
		SYS_PORT |= ( 1<< LED);
	} else {
		AUS_SYS_PORT &= ~(1<<AUS_TAST_TON);
		SYS_PORT &= ~( 1<< LED);
	}
	if(AUS_SYS_PIN & (1<<AUS_MAN_P)) { 
		AUS_PORT = ausgabe;
		AUS_TIMER_AUS;
	} else { //Blockade aller Pfeiltasten
		AUS_PORT = ausgabe & MAN_AUS_MASK;
		//Lautst�rke und Helligkeit
#ifdef PWM_TIMER
		if(ausgabe & T_PFEILMASKE) {
			AUS_TIMER_AN;
		} else {
			AUS_TIMER_AUS;
		}
#else
		if((ausgabe & (1<<T_HOCH)) && PWM_LICHT < 255) {
			licht_scale++;
		}
		if((ausgabe & (1<<T_RUNTER)) && PWM_LICHT) {
			licht_scale--;
		}
		if((ausgabe & (1<<T_RECHTS)) && PWM_AUDIO < 255) {
			audio_scale++;
		}
		if((ausgabe & (1<<T_LINKS)) && PWM_AUDIO) {
			audio_scale--;
		}

		if(licht_scale >= PWM_SCALE_MAX){
			PWM_LICHT++;
			licht_scale = 0;
		}
		if(licht_scale <= PWM_SCALE_MIN){
			PWM_LICHT--;
			licht_scale = 0;
		}

		if(audio_scale >= PWM_SCALE_MAX){
			PWM_AUDIO++;
			audio_scale = 0;
		}
		if(audio_scale <= PWM_SCALE_MIN){
			PWM_AUDIO--;
			audio_scale = 0;
		}
#endif
	}
}

void aus_set(uint8_t val) {
#ifdef DEBUG_TASTEN
	uart_putc(val);
	uart_putc('\n');
#endif
	ausgabe = val;
	aus_refrech();
}
