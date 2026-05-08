#include "protocol-task.h"
#include <stdio.h>
#include <string.h>

static api_t* api=NULL;
static int commands_count=0;

void protocol_task_init(api_t* device_api)
{
    api=device_api;
    commands_count=0;

    while (api[commands_count].command_name!=NULL)
    {
        commands_count++;
    }
}

void protocol_task_handle(char* command_string)
{
    const char* command_name;
    const char* command_args;
    char* space_symbol;
    int i;

    if (!command_string)
    {
        return;
    }

    command_name=command_string;
    command_args=NULL;
    space_symbol=strchr(command_string, ' ');

    if (space_symbol)
    {
        *space_symbol='\0';
        command_args=space_symbol+1;
    }
    else
    {
        command_args="";
    }

    printf("command name: '%s', command args: '%s'\n", command_name, command_args);

    for (i=0; api[i].command_name!=NULL; i++)
    {
        if (strcmp(command_name, api[i].command_name)!=0)
        {
            continue;
        }

        api[i].command_callback(command_args);
        return;
    }

    printf("command not found: '%s'\n", command_name);
}
