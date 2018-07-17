/*
  ext_ssd13xx.cpp

  Wrapper library OLED module(SSD13xx) for mruby/c
  Copyright (c) 2018, Toshio Maki All rights reserved.
*/

#include <SPI.h>
#include "SSD_13XX.h"
#include "Arduino.h"
#include "mrubyc_for_ESP8266_Arduino.h"
#include "ext.h"

static void class_oled_new(mrb_vm *vm, mrb_value *v, int argc) {
  SSD_13XX *oled;
  uint8_t errorCode = 0;

  int32_t cs1, dc;
  if(argc == 2) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM) {
      cs1 = GET_INT_ARG(1);
    } 
    else {
      return;
    }

    if(GET_TT_ARG(2) == MRB_TT_FIXNUM) {
      dc = GET_INT_ARG(1);
    } else {
      return;
    }
  } else {
    return;
  }
  oled = new SSD_13XX(cs1, dc);
  oled->begin();

  errorCode = oled->getErrorCode();
  if(errorCode != 0) {
    Serial.printf("Init error!\n");
    if(bitRead(errorCode, 0)) {
      Serial.printf("MOSI or SCLK pin mismatch!\n");
    }
    if(bitRead(errorCode, 1)) {
      Serial.printf("CS or DC pin mismatch!\n");
    }
    return;
  }
  mrb_value ret = {.tt = MRB_TT_HANDLE};
  ret.handle = (RObject*)oled;
  oled->clearScreen();
  oled->print("Hello World");
  SET_RETURN(ret);
}

static void class_oled_print(mrb_vm *vm, mrb_value *v, int argc) {
  Serial.println("call OLED print");
  if(GET_TT_ARG(1) == MRB_TT_STRING) {
    ((SSD_13XX*)v->handle)->print((const char *)GET_STRING_ARG(1));
  }
}

void define_oled_class(mrb_vm *vm)
{
  mrb_class *class_oled;
  class_oled = mrbc_define_class(vm, "Oled", mrbc_class_object);
  mrbc_define_method(vm, class_oled, "new", class_oled_new);
//  mrbc_define_method(0, class_oled, "rotation=", class_oled_set_rotation);
//  mrbc_define_method(0, class_oled, "rotation", class_oled_get_rotation);
//  mrbc_define_method(0, class_oled, "fill_screen", class_oled_fill_screen);
//  mrbc_define_method(0, class_oled, "background=", class_oled_set_background);
//  mrbc_define_method(0, class_oled, "background", class_oled_get_background);
//  mrbc_define_method(0, class_oled, "foreground=", class_oled_set_foreground);
//  mrbc_define_method(0, class_oled, "foreground", class_oled_get_foreground);
//  mrbc_define_method(0, class_oled, "clear", class_oled_clear_screen);
//  mrbc_define_method(0, class_oled, "draw_pixel", class_oled_draw_pixel);
//  mrbc_define_method(0, class_oled, "draw_line", class_oled_draw_line);
//  mrbc_define_method(0, class_oled, "draw_rect", class_oled_draw_rect);
//  mrbc_define_method(0, class_oled, "fill_rect", class_oled_fill_rect);
//  mrbc_define_method(0, class_oled, "draw_triangle", class_oled_draw_triangle);
//  mrbc_define_method(0, class_oled, "fill_triangle", class_oled_fill_triangle);
//  mrbc_define_method(0, class_oled, "draw_circle", class_oled_draw_circle);
//  mrbc_define_method(0, class_oled, "fill_circle", class_oled_fill_circle);
//  mrbc_define_method(0, class_oled, "draw_round_rect", class_oled_draw_round_rect);
//  mrbc_define_method(0, class_oled, "fill_round_rect", class_oled_fill_round_rect);
//  mrbc_define_method(0, class_oled, "draw_mesh", class_oled_draw_mesh);
//  mrbc_define_method(0, class_oled, "draw_arc", class_oled_draw_arc);
//  mrbc_define_method(0, class_oled, "draw_ellipse", class_oled_draw_ellipse);
//  mrbc_define_method(0, class_oled, "set_text_color", class_oled_set_text_color);
//  mrbc_define_method(0, class_oled, "set_text_scale", class_oled_set_text_scale);
//  mrbc_define_method(0, class_oled, "text_wrap", class_oled_set_text_wrap);
//  mrbc_define_method(0, class_oled, "set_char_spacing", class_oled_set_char_spacing);
  mrbc_define_method(vm, class_oled, "print", class_oled_print);
//  mrbc_define_method(0, class_oled, "define_scroll_area", class_oled_define_scroll_area);
//  mrbc_define_method(0, class_oled, "scroll", class_oled_scroll);
//  mrbc_define_method(0, class_oled, "cursor=", class_oled_set_cursor);
//  mrbc_define_method(0, class_oled, "cursor", class_oled_get_cursor);
}
