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

SSD_13XX *oled;
static uint16 getCommonColor(const char* colorName);

static void class_oled_new(mrb_vm *vm, mrb_value *v, int argc) {
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
      dc = GET_INT_ARG(2);
    } else {
      return;
    }
  } else {
    return;
  }
  Serial.printf("cs1 = %d dc= %d\n", cs1, dc);
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
}

static void class_oled_color(mrb_vm *vm, mrb_value *v, int argc) {
  if(argc == 1 && GET_TT_ARG(1) == MRB_TT_STRING) {
    const char* buf = (const char *)GET_STRING_ARG(1);
    SET_INT_RETURN(getCommonColor(buf));
  } else if(argc == 3 && GET_TT_ARG(1) == MRB_TT_FIXNUM &&
      GET_TT_ARG(2) == MRB_TT_FIXNUM && GET_TT_ARG(3) == MRB_TT_FIXNUM) {
      SET_INT_RETURN(oled->Color565(GET_INT_ARG(1), GET_INT_ARG(2), GET_INT_ARG(3)));
  } else {
    SET_INT_RETURN(0xFFFF);
  }
}

static void class_oled_print(mrb_vm *vm, mrb_value *v, int argc) {
  if(GET_TT_ARG(1) == MRB_TT_STRING) {
    oled->print((char *)GET_STRING_ARG(1));
  }
}

static void class_oled_fill_screen(mrb_vm *vm, mrb_value *v, int argc) {
}

static void class_oled_clear_screen(mrb_vm *vm, mrb_value *v, int argc) {
  oled->clearScreen();
}

static void class_oled_close(mrb_vm *vm, mrb_value *v, int argc) {
  delete(oled);
}

static void class_oled_set_background(mrb_vm *vm, mrb_value *v, int argc) {
  if(argc == 1 && GET_TT_ARG(1) == MRB_TT_FIXNUM) {
    uint16_t color = GET_INT_ARG(1);
    oled->setBackground(color);
    SET_INT_RETURN(color);
  } else {
    Serial.println("Error: Invalid color code. method: background=");
    SET_NIL_RETURN();
  }
}

static void class_oled_get_background(mrb_vm *vm, mrb_value *v, int argc) {
  SET_INT_RETURN(oled->getBackground());
}

static void class_oled_set_foreground(mrb_vm *vm, mrb_value *v, int argc) {
  if(argc == 1 && GET_TT_ARG(1) == MRB_TT_FIXNUM) {
    uint16_t color = GET_INT_ARG(1);
    oled->setForeground(color);
    SET_INT_RETURN(color);
  } else {
    Serial.println("Error: Invalid color code. method: foreground=");
    SET_NIL_RETURN();
  }
}

static void class_oled_get_foreground(mrb_vm *vm, mrb_value *v, int argc) {
  SET_INT_RETURN(oled->getForeground());
}

static void class_oled_draw_pixel(mrb_vm *vm, mrb_value *v, int argc) {
  if(argc == 2) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM) {
      oled->drawPixel((int16_t)GET_INT_ARG(1), (int16_t)GET_INT_ARG(2), oled->getForeground());
    }
  } else if(argc == 3) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM &&
        GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM) {
      oled->drawPixel((int16_t)GET_INT_ARG(1), (int16_t)GET_INT_ARG(2), (uint16_t)GET_INT_ARG(3));
    }
  } else {
    Serial.println("Error: Invalid argument. method: draw_pixel");
    SET_FALSE_RETURN();
  }
}

static void class_oled_draw_line(mrb_vm *vm, mrb_value *v, int argc) {
  uint16_t color = 0;
  if(argc == 4) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM) {
          color = oled->getForeground();
    }
  } else if(argc == 5) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM &&
        GET_TT_ARG(5) == MRB_TT_FIXNUM) {
          color = GET_INT_ARG(5);
    }
  } else {
    Serial.println("Error: Invalid argument. method: draw_line");
    SET_NIL_RETURN();
    return;
  }
  oled->drawLine((int16_t)GET_INT_ARG(1), (int16_t)GET_INT_ARG(2),
                  (int16_t)GET_INT_ARG(3), (int16_t)GET_INT_ARG(4), color);
}

static void class_oled_draw_rect(mrb_vm *vm, mrb_value *v, int argc) {
  uint16_t color = 0;
  if(argc == 4) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM) {
          color = oled->getForeground();
    }
  } else if(argc == 5) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM &&
        GET_TT_ARG(5) == MRB_TT_FIXNUM) {
          color = GET_INT_ARG(5);
    }
  } else {
    Serial.println("Error: Invalid argument. method: draw_rect");
    SET_NIL_RETURN();
    return;
  }
  oled->drawRect((int16_t)GET_INT_ARG(1), (int16_t)GET_INT_ARG(2),
                  (int16_t)GET_INT_ARG(3), (int16_t)GET_INT_ARG(4), color);
}

static void class_oled_fill_rect(mrb_vm *vm, mrb_value *v, int argc) {
  uint16_t color1 = 0;
  uint16_t color2 = 0;
  if(argc == 4) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM) {
          color1 = oled->getForeground();
          color2 = oled->getForeground();
    }
  } else if(argc == 5) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM &&
        GET_TT_ARG(5) == MRB_TT_FIXNUM) {
          color1 = GET_INT_ARG(5);
          color2 = GET_INT_ARG(5);
    }
  } else if(argc == 6) {
    if(GET_TT_ARG(1) == MRB_TT_FIXNUM && GET_TT_ARG(2) == MRB_TT_FIXNUM &&
        GET_TT_ARG(3) == MRB_TT_FIXNUM && GET_TT_ARG(4) == MRB_TT_FIXNUM &&
        GET_TT_ARG(5) == MRB_TT_FIXNUM && GET_TT_ARG(6) == MRB_TT_FIXNUM) {
          color1 = GET_INT_ARG(5);
          color2 = GET_INT_ARG(6);
      }
  } else {
    Serial.println("Error: Invalid argument. method: fill_rect");
    SET_NIL_RETURN();
    return;
  }
  oled->fillRect((int16_t)GET_INT_ARG(1), (int16_t)GET_INT_ARG(2),
                  (int16_t)GET_INT_ARG(3), (int16_t)GET_INT_ARG(4), color1, color2);

}

static uint16 getCommonColor(const char* colorName) {
  const char *colors[] = {
    "BLACK", "WHITE", "NAVY", "DARKGREEN", "DARKCYAN",
    "MAROON", "PURPLE", "ORANGE", "PINK", "OLIVE",
    "BLUE", "RED", "GREEN", "CYAN", "MAGENTA",
    "YELLOW", "BRIGHT_RED", "LIGHT_GREY", "DARK_GREY", "GREENYELLOW"
  };

  const uint16 colorCode[] = {
    0x0000, 0xFFFF, 0x000F, 0x03E0, 0x03EF,
    0x7800, 0x780F, 0xFD20, 0xF81F, 0x7BE0,
    0x001F, 0xF800, 0x07E0, 0x07FF, 0xF81F,
    0xFFE0, 0xF810, 0xC618, 0x7BEF, 0xAFE5
  };

  for(unsigned int i = 0; i < sizeof(colors); i++) {
    if(strcmp_P(colors[i], colorName) == 0) {
      return colorCode[i];
    }
  }
  return 0xFFFF;
}

void define_oled_class()
{
  mrb_class *class_oled;
  class_oled = mrbc_define_class(0, "Oled", mrbc_class_object);
  mrbc_define_method(0, class_oled, "initialize", class_oled_new);
  mrbc_define_method(0, class_oled, "color", class_oled_color);
//  mrbc_define_method(0, class_oled, "rotation=", class_oled_set_rotation);
//  mrbc_define_method(0, class_oled, "rotation", class_oled_get_rotation);
  mrbc_define_method(0, class_oled, "fill_screen", class_oled_fill_screen);
  mrbc_define_method(0, class_oled, "background=", class_oled_set_background);
  mrbc_define_method(0, class_oled, "background", class_oled_get_background);
  mrbc_define_method(0, class_oled, "foreground=", class_oled_set_foreground);
  mrbc_define_method(0, class_oled, "foreground", class_oled_get_foreground);
  mrbc_define_method(0, class_oled, "clear", class_oled_clear_screen);
  mrbc_define_method(0, class_oled, "draw_pixel", class_oled_draw_pixel);
  mrbc_define_method(0, class_oled, "draw_line", class_oled_draw_line);
  mrbc_define_method(0, class_oled, "draw_rect", class_oled_draw_rect);
  mrbc_define_method(0, class_oled, "fill_rect", class_oled_fill_rect);
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
  mrbc_define_method(0, class_oled, "print", class_oled_print);
//  mrbc_define_method(0, class_oled, "define_scroll_area", class_oled_define_scroll_area);
//  mrbc_define_method(0, class_oled, "scroll", class_oled_scroll);
//  mrbc_define_method(0, class_oled, "cursor=", class_oled_set_cursor);
//  mrbc_define_method(0, class_oled, "cursor", class_oled_get_cursor);
  mrbc_define_method(0, class_oled, "close", class_oled_close);
}