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

#ifndef MRBC_SRC_HAL_H_
#define MRBC_SRC_HAL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/***** Feature test switches ************************************************/
/***** System headers *******************************************************/
#include <unistd.h>

/***** Local headers ********************************************************/
#include "vm_config.h"

/***** Constant values ******************************************************/
/***** Macros ***************************************************************/
#ifndef MRBC_SCHEDULER_EXIT
#define MRBC_SCHEDULER_EXIT 1
#endif

  /***** Typedefs *************************************************************/
  /***** Global variables *****************************************************/
  /***** Function prototypes **************************************************/
  void mrbc_tick(void);
  void hal_delay(unsigned long t);

  void hal_init(void);
#define hal_enable_irq() ((void)0)
#define hal_disable_irq() ((void)0)
#define hal_idle_cpu() (hal_delay(1), mrbc_tick())

  /***** Inline functions *****************************************************/

  //================================================================
  /*!@brief
  Flush write baffer

  @param  fd    dummy, but 1.
*/

  int hal_write(int fd, const void *buf, int nbytes);
  inline static int hal_flush(int fd)
  {
    return fsync(1);
  }

  void hal_write_string(char *text);
  void hal_init_modem(void);
  void *hal_get_modem_obj(void);

#ifdef __cplusplus
}
#endif
#endif // ifndef MRBC_HAL_H_
