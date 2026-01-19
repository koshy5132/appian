#ifndef GLOBALS_H
#define GLOBALS_H

#include "lrun.h"

/*
 * Function: remove_newlines
 * Purpose : Completely remove all CR (\r) and LF (\n) characters
 */
void remove_newlines(char *input_param, char *output_param)
{
    char *orig;
    char cleaned[16384];  // big enough buffer
    int i, j = 0;

    /* Get pointer to the evaluated string */
    orig = lr_eval_string(input_param);

    /* Loop through each character */
    for (i = 0; orig[i] != '\0'; i++)
    {
        if (orig[i] != '\r' && orig[i] != '\n')
        {
            cleaned[j++] = orig[i];  // keep normal chars
        }
        /* else skip CR/LF */
    }

    cleaned[j] = '\0';  // terminate string

    /* Save cleaned string as LoadRunner parameter */
    lr_save_string(cleaned, output_param);
}

#endif




Action()
{
    /* Example with actual CRLF inside parameter */
    lr_save_string("Line1\r\nLine2\r\nLine3", "CorrValue");

    /* Remove all CRLF */
    remove_newlines("{CorrValue}", "CorrValue_Clean");

    lr_output_message("Original: [%s]", lr_eval_string("{CorrValue}"));
    lr_output_message("Cleaned : [%s]", lr_eval_string("{CorrValue_Clean}"));

    return 0;
}
