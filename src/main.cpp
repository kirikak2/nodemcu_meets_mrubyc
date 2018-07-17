#include <Arduino.h>
#include <mrubyc_for_ESP8266_Arduino.h>
#include "blink.h"

#define MEMORY_SIZE (1024 * 20)
static uint8_t memory_pool[MEMORY_SIZE];
unsigned char buff[10 * 1024];

static int first = 0;
static struct VM *vm;

void setup()
{
    Serial.begin(9600);
    delay(100);

    // initialize mruby/c
    mrbc_init_alloc(memory_pool, MEMORY_SIZE);
    init_static();

    vm = mrbc_vm_open(NULL);
    if (vm == NULL)
    {
        Serial.println("Can't open VM");
        return;
    }

    mrbc_define_methods(vm);
    if (mrbc_load_mrb(vm, ary) != 0)
    {
        Serial.println("Error: Illegal bytecode.\n");
        return;
    }
    mrbc_vm_begin(vm);
    mrbc_vm_run(vm);
    mrbc_vm_end(vm);
    mrbc_vm_close(vm);
    return;
}

void loop()
{
    delay(100);
}