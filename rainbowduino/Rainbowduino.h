/*
 * Rainbowduino.h version 3.0beta - A driver to run Seeedstudio 8x8 RBG LED Matrix
 * Based on Rainbow.h by Seedstudio.com -> http://www.seeedstudio.com/depot/rainbowduino-led-driver-platform-plug-and-shine-p-371.html
 * Copyright (c) 2013 Tobias Bielohlawek -> http://www.rngtng.com
 *
 */

#ifndef RAINBOWDUINO_h
#define RAINBOWDUINO_h

// include types & constants of Wiring core API
#include "Arduino.h"

//=============================================
//MBI5168
#define SH_DIR   DDRC
#define SH_PORT   PORTC

#define SH_BIT_SDI   0x01
#define SH_BIT_CLK   0x02

#define SH_BIT_LE    0x04
#define SH_BIT_OE    0x08
//============================================
#define clk_rising  {SH_PORT &= ~SH_BIT_CLK; SH_PORT |= SH_BIT_CLK; }
#define le_high     {SH_PORT |= SH_BIT_LE; }
#define le_low      {SH_PORT &= ~SH_BIT_LE; }
#define enable_oe   {SH_PORT &= ~SH_BIT_OE; }
#define disable_oe  {SH_PORT |= SH_BIT_OE; }

#define shift_data_1 {SH_PORT |= SH_BIT_SDI;}
#define shift_data_0 {SH_PORT &= ~SH_BIT_SDI;}

#define NUM_LINES 8
#define NUM_ROWS 24 // 3 BYTES per ROW  x 8 Lines = 24Bytes
#define MAX_NUM_FRAMES 10 // = 240Bytes

#define NUM_LEVEL 16

class Rainbowduino {

public:
  uint8_t frame_buffer[NUM_ROWS*MAX_NUM_FRAMES]; // [FRAME_BUFFER_SIZE]; //size of EEPROM -> to read faster??
  Rainbowduino();

  /////////////////////////
  void reset();
  uint8_t get_num_frames();

  void set_current_frame_nr(uint8_t frame_nr);
  uint8_t get_current_frame_nr();

  void next_frame();

  /////////////////////////
  void set_frame(uint8_t frame_nr, uint8_t* data);

  void set_frame_row(uint8_t frame_nr, uint8_t row, uint8_t data);
  uint8_t get_frame_row(uint8_t frame_nr, uint8_t row);

  //to set all 3 colors of each line
  void set_frame_line(uint8_t frame_nr, uint8_t x, uint8_t red, uint8_t green, uint8_t blue);

  //to set all 3 colors of each pixel
  void set_frame_pixel(uint8_t frame_nr, uint8_t x, uint8_t y, uint8_t red, uint8_t green, uint8_t blue);

  /////////////////////////
  void draw(uint8_t level = 8);

private:
  uint8_t num_frames;
  uint8_t current_frame_nr;
  word current_frame_offset;
  word off;  //buffer offset
  volatile uint8_t current_row;
  volatile uint8_t current_level;

  void draw_row(uint8_t row, uint8_t level, uint8_t r, uint8_t g, uint8_t b);
  void draw_color(uint8_t c);
  void enable_row(uint8_t row);
};

#endif //RAINBOWDUINO.h


