/*! @file
  @brief
  Realtime multitask monitor for mruby/c
  Hardware abstraction layer
        for ESP32

  <pre>
  Copyright (C) 2016-2018 Kyushu Institute of Technology.
  Copyright (C) 2016-2018 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.
  </pre>
*/

/***** Feature test switches ************************************************/
/***** System headers *******************************************************/

/***** Local headers ********************************************************/
#include <Arduino.h>
#include "hal.h"

/***** Constat values *******************************************************/

/***** Macros ***************************************************************/
/***** Typedefs *************************************************************/
/***** Function prototypes **************************************************/
/***** Local variables ******************************************************/

/***** Global variables *****************************************************/
/***** Signal catching functions ********************************************/
/***** Local functions ******************************************************/

/***** Global functions *****************************************************/

//================================================================
/*!@brief
  initialize

*/
void hal_init(void)
{
}

int hal_write(int fd, const void *buf, int nbytes)
{
  char *t = (char *)buf;
  char tbuf[2];
  if (nbytes == 1)
  {
    tbuf[0] = *t;
    tbuf[1] = '\0';
    hal_write_string(tbuf);
    return nbytes;
  }
  hal_write_string(t);
  return nbytes;
}