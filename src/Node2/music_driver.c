#define F_CPU 16000000
#include "music_driver.h"
#include "pitches.h"
#include "songs.h"
#include <stdio.h>
#include <util/delay.h>
#include <float.h>


void music_init(){

    /*Set PE3 as pwm output*/
    DDRE |= (1 << PE3);

    /*Mode 12 CTC*/
    TCCR3B |= (1 << WGM33) | (1 << WGM32);

    /*For generating a waveform output in CTC
    mode*/
    TCCR3A = (1 << COM3A0);

    /*64 bit Prescaler*/
    TCCR3B |= (1 << CS31) | ( 1 << CS30);


}


void music_play(song title){

  switch (song) {
    case MARIO:
        int size = sizeof(mario_melody)/sizeof(int);
        //Iterate through all notes of the song
        for (int current_note = 0; current_note < size; current_note++){

            //Calculating the note duration - 1sec/Notetype eg. 1000/8
            float note_duration = 1000/mario_tempo[current_note]

            music_buzzer(mario_melody[current_note], note_duration);

            //Small delay between notes
            float note_delay = note_duration * 1.30
            _delay_ms((int)note_delay);

            //Stop current note
            music_buzzer(0, note_duration);
        }

  }



}


void music_buzzer(uint16_t freq, uint16_t length){

/*

pwm = clock / 2 * Prescaler

*/
  int pwm_signal = (F_CPU/(2*64*feq)) - 1;

  /*IC3 defines top value of counter, hence our freq*/
  IC3 = pwm_signal;
  for (int i = 1; i < length; i++){
        _delay_ms(1);
    }

}