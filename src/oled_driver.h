#ifndef OLED_H
#define OLED_H
#define F_CPU 4915200
#define ASCII_OFFSET ((volatile unsigned int) 32)

//#define oled_command_address ((volatile char*)0x1000)
//#define oled_data_address ((volatile char*)0x1200)

#include <stdint.h>
#include "menu.h"

void oled_init();
void oled_write_c(uint8_t command);
void oled_write_d(uint8_t data);
void oled_goto_line(int line);  //Funker
void oled_goto_column(int column);  //Funker
void oled_home(void);   //Funker
void oled_pos(int row,int column);


void oled_sram_write_d(uint8_t adr, uint8_t data);
void oled_sram_write_char(unsigned char c);
void oled_sram_write_string(char* str);
void oled_sram_reset(void);
void oled_sram_menu(Menu* menu, uint8_t line);
void oled_sram_clear_line(int line);
void oled_sram_arrow(uint8_t line);

void oled_draw();

#endif