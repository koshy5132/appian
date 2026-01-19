#ifndef GLOBALS_H
#define GLOBALS_H

#include "lrun.h"
#include <string.h>

// ---------------------------
// Large buffers declared globally
// ---------------------------
char g_escapedBuffer[32768];   // Buffer for escaped strings

// ---------------------------
// Function to escape CRLF, quotes, backslash for JSON
// ---------------------------
void lr_escape_for_json(char *input_param, char *output_param)
{
    char *src;  // Pointer to original LR param value
    int i, j;   // Indexes

    src = lr_eval_string(input_param);
    memset(g_escapedBuffer, 0, sizeof(g_escapedBuffer)); // Clear buffer
    j = 0;

    for(i = 0; src[i] != '\0'; i++)
    {
        switch(src[i])
        {
            case '\\':
                g_escapedBuffer[j++] = '\\';
                g_escapedBuffer[j++] = '\\';
                break;
            case '\"':
                g_escapedBuffer[j++] = '\\';
                g_escapedBuffer[j++] = '\"';
                break;
            case '\r':
                g_escapedBuffer[j++] = '\\';
                g_escapedBuffer[j++] = 'r';
                break;
            case '\n':
                g_escapedBuffer[j++] = '\\';
                g_escapedBuffer[j++] = 'n';
                break;
            default:
                g_escapedBuffer[j++] = src[i];
                break;
        }
    }

    g_escapedBuffer[j] = '\0';
    lr_save_string(g_escapedBuffer, output_param);
}

#endif



#include "globals.h"

Action()
{
    // -----------------------------
    // Declare only small local variables
    // -----------------------------
    char *paramName;
    char *escapedParamName;

    // -----------------------------
    // Simulate correlation value
    // -----------------------------
    lr_save_string("Hello \"World\"\r\nThis is line2\\end", "CorrValue");
    paramName = "{CorrValue}";
    escapedParamName = "CorrValue_Escaped";

    // -----------------------------
    // Escape CRLF and special chars
    // -----------------------------
    lr_escape_for_json(paramName, escapedParamName);

    // -----------------------------
    // Output for verification
    // -----------------------------
    lr_output_message("Original Value: %s", lr_eval_string("{CorrValue}"));
    lr_output_message("Escaped Value : %s", lr_eval_string("{CorrValue_Escaped}"));

    // -----------------------------
    // Use in a POST request
    // -----------------------------
    web_custom_request("MyRequest",
        "URL=https://dummy.example.com/api",
        "Method=POST",
        "Body={\"text\":\"{CorrValue_Escaped}\"}",
        LAST);

    return 0;
}

