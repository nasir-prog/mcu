#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "stdio-task/stdio-task.h"
#include "protocol-task/protocol-task.h"
#include "led-task/led-task.h"
#include <stdint.h>

#define DEVICE_NAME "my-pico-device"
#define DEVICE_VRSN "v0.0.1"

void help_callback(const char* args);
void led_on_callback(const char *args);
void led_off_callback(const char *args);
void led_blink_callback(const char *args);
void mem_callback(const char *args);
void wmem_callback(const char *args);


void led_on_callback(const char* args)
{
    (void)args;
    led_task_state_set(LED_STATE_ON);
}

void led_off_callback(const char* args)
{
    (void)args;
    led_task_state_set(LED_STATE_OFF);
}

void led_blink_callback(const char* args)
{
    (void)args;
    led_task_state_set(LED_STATE_BLINK);
}

void version_callback(const char* args)
{
    (void)args;
    printf("device name: '%s', firmware version: %s\n", DEVICE_NAME, DEVICE_VRSN);
}

void led_blink_set_period_ms_callback(const char* args)
{
    uint period_ms = 0;

    sscanf(args, "%u", &period_ms);

    if (period_ms == 0)
    {
        printf("error: period must be greater than 0\n");
        return;
    }

    led_task_set_blink_period_ms(period_ms);
}

extern api_t device_api[];

void help_callback(const char* args)
{
    int i;

    (void)args;

    for (i=0; device_api[i].command_name!=NULL; i++)
    {
        printf("command '%s': '%s'\n",
               device_api[i].command_name,
               device_api[i].command_help);
    }
}

void mem_callback(const char *args)
{
    uint32_t addr;
    uint32_t value;
    int parsed;

    addr=0;
    value=0;

    parsed=sscanf(args, "%x", &addr);

    if (parsed != 1)
    {
        printf("Error: use mem <addr>\n");
        return;
    }

    value=*((volatile uint32_t *)addr);

    printf("addr: 0x%08x value: 0x%08x\n", addr, value);
}

void wmem_callback(const char *args)
{
    uint32_t addr;
    uint32_t value;
    int parsed;

    addr=0;
    value=0;

    parsed=sscanf(args, "%x %x", &addr, &value);

    if (parsed != 2)
    {
        printf("Error: use wmem <addr> <value>\n");
        return;
    }

    *((volatile uint32_t *)addr)=value;

    printf("write addr: 0x%08x value: 0x%08x\n", addr, value);
}

api_t device_api[] =
{
    {"version", version_callback, "get device name and firmware version"},
    {"on", led_on_callback, "turn led on"},
    {"off", led_off_callback, "turn led off"},
    {"blink", led_blink_callback, "blink led"},
    {"set_period", led_blink_set_period_ms_callback, "set led blink period in ms"},
    {"help", help_callback, "print commands description"},

    {
        "mem",
        mem_callback,
        "read from memory"
    },
    {
        "wmem",
        wmem_callback,
        "write in memory"
    },

    {NULL, NULL, NULL},
};

int main()
{
    led_task_init();
    stdio_init_all();
    sleep_ms(3000);

    stdio_task_init();
    protocol_task_init(device_api);
    printf("commands:\n");
for (int i = 0; device_api[i].command_name != NULL; i++)
{
    printf("%s\n", device_api[i].command_name);
}
    while (1)
    {
        protocol_task_handle(stdio_task_handle());
	led_task_handle();
    }

    return 0;
}
