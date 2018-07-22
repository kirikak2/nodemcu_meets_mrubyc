#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "mrubyc_for_ESP8266_Arduino.h"
#include "user_interface.h"

#define MEMORY_SIZE (1024 * 20)
static uint8_t memory_pool[MEMORY_SIZE];
unsigned char buff[10 * 1024];
int buff_ptr = 0;

static int first = 0;
static struct VM *vm;

int status = WL_IDLE_STATUS;
WiFiServer server(33333);

const char ssid[] = "";
const char pass[] = "";

// prototype definition
int read_message(WiFiClient& client);
void mrubyc(uint8_t *mrbbuf);

void setup()
{
    Serial.begin(9600);
    delay(100);

    status = WiFi.begin(ssid, pass);
    Serial.printf("Connecting to %s", ssid);
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("Connected to wifi. IP Address: ");
    IPAddress myAddress = WiFi.localIP();
    Serial.println(myAddress);

    // initialize mruby/c
    mrbc_init_alloc(memory_pool, MEMORY_SIZE);
    init_static();
    vm = mrbc_vm_open(NULL);
    if (vm == NULL)
    {
        Serial.println("Can't open VM");
        return;
    }

    mrbc_define_methods();

    server.begin();
    Serial.println("Server started");
    Serial.printf("%d bytes memory available\n", system_get_free_heap_size());
}

void loop()
{
    WiFiClient client = server.available();
    client.setTimeout(1000);
    if(client) {
        while(client.connected()) {
            read_message(client);
        }
        Serial.println("Client Disconnected.");
        client.stop();
        delay(10);
    } else {
        delay(10);
    }
}

void mrubyc(uint8_t *mrbbuf) {
    if(mrbc_load_mrb(vm, mrbbuf) != 0) {
        Serial.println("mrbc_load_mrb error");
        return;
    }

    if(!first) {
        mrbc_vm_begin(vm);
    } else {
        vm->pc_irep = vm->irep;
        vm->pc = 0;
        vm->current_regs = vm->regs;
        vm->flag_preemption = 0;
        vm->callinfo_top = 0;
        vm->error_code = 0;
    }
    mrbc_vm_run(vm);
    Serial.printf("%d bytes memory available\n", system_get_free_heap_size());
    if(first == 0) first = 1;
}

int read_message(WiFiClient& client) {
    String currentLine = "";
    int remain = 4;
    int size = 0;
    unsigned char header[4];
    Serial.print("> ");
    while(client.connected()) {
        size = client.read(&header[4 - remain], remain);
        if(size < 0) {
            delay(10);
            continue;
        }
        if(size < remain) {
            delay(10);
            remain -= size;
            continue;
        }
        break;
    }
    uint16_t irep_len = bin_to_uint16(&header[2]);
    remain = irep_len;
    Serial.print("waiting recv:irep_len=");
    Serial.println(irep_len);
    while(client.connected()) {
        size = client.read(&buff[buff_ptr+(irep_len-remain)], remain);
        if(size < 0) {
            delay(10);
            continue;
        }
        if(size < remain) {
            remain -= size;
            delay(10);
            continue;
        }
        mrubyc(&buff[buff_ptr]);
        buff_ptr += irep_len;
        Serial.println("");
        return 0;
    }
    return -1;
}