/*!@file
* NODE 2 MAIN FILE
*/
#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>

#include "can_driver.h"
#include "gameboard_driver.h"
#include "mcp2515_driver.h"
#include "MCP2515.h"
#include "motor_driver.h"
#include "pid.h"
#include "spi_driver.h"
#include "timer_driver.h"
#include "usart_driver.h"
#include "music_driver.h"


void main () {

  cli();
  string_init();
      _delay_ms(20);
  music_init();
      _delay_ms(20);
  can_init();
      _delay_ms(20);
  motor_init();
      _delay_ms(20);
  ir_adc_init();
      _delay_ms(20);
  solenoid_init();
      _delay_ms(20);
  game_board_init();
      _delay_ms(20);
  timer_init();
      _delay_ms(20);
  sei();

  CANmsg run_menu;
  run_menu.id = 0;
  run_menu.length = 1;
  run_menu.data[0] = 8;
  typedef enum {IDLE = 0, PINGPONG = 1}mode;
  mode MODE = IDLE;
  while (1){
      switch (MODE) {
        case IDLE:
           if (get_CAN_msg().id == 0 && get_CAN_msg().data[0] == 1){
               MODE = PINGPONG;

           }
           if (get_CAN_msg().id == 3){
              pid_set_difficulty(get_CAN_msg().data[0]);
           }
           if (get_CAN_msg().id == 7 && get_CAN_msg().data[0] == 1){
              music_init();
              music_play(SOVJET);
           }
           break;
        case PINGPONG:
            play_pingpong();
            MODE = IDLE;
            _delay_ms(100);
            can_send_msg(&run_menu);
            break;

    }
  }
}
