#ifndef _GLOBALS_H
#define _GLOBALS_H

//--------------------------------------------------------------------
// Include Files
#include "lrun.h"
#include "web_api.h"
#include "lrw_custom_body.h"
#include "string.h"
//--------------------------------------------------------------------
// Global Variables
// Function to escape \r and \n in a LoadRunner parameter
void escape_newlines(char *input_param, char *output_param)
{
    char original[4096];
    char escaped[16384];  // Adjust if needed
    int i;
    char temp[2];

    // Get original parameter value
    strcpy(original, lr_eval_string(input_param));

    // Initialize escaped string
    escaped[0] = '\0';

    // Loop to escape \r and \n
    for(i = 0; original[i] != '\0'; i++)
    {
        if(original[i] == '\r')
            strcat(escaped, "\\\\\\\\r");   // \r ? \\r
        else if(original[i] == '\n')
            strcat(escaped, "\\\\\\\\n");   // \n ? \\n
        else
        {
            temp[0] = original[i];
            temp[1] = '\0';
            strcat(escaped, temp);
        }
    }

    // Save escaped value as LoadRunner parameter
    lr_save_string(escaped, output_param);
}
#endif // _GLOBALS_H
