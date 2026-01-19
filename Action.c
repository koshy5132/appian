#include "lrun.h"
#include <string.h>

// ----------------------------------
// Escape a string for JSON/Appian request
// Converts:
//   \  -> \\
//   "  -> \"
//   \r -> \\r
//   \n -> \\n
// input_param: original LR parameter name (e.g., "{CorrValue}")
// output_param: new LR parameter name to save escaped value
// ----------------------------------
void lr_escape_for_json(char *input_param, char *output_param)
{
    char *src;                   // Pointer to original LR param value
    char temp[32768];            // Buffer for escaped value
    int i;                       // Index for source string
    int j;                       // Index for temp buffer

    src = lr_eval_string(input_param); // Get LR parameter value
    memset(temp, 0, sizeof(temp));     // Initialize buffer
    j = 0;

    for(i = 0; src[i] != '\0'; i++)
    {
        switch(src[i])
        {
            case '\\':
                temp[j++] = '\\';
                temp[j++] = '\\';
                break;
            case '\"':
                temp[j++] = '\\';
                temp[j++] = '\"';
                break;
            case '\r':
                temp[j++] = '\\';
                temp[j++] = 'r';
                break;
            case '\n':
                temp[j++] = '\\';
                temp[j++] = 'n';
                break;
            default:
                temp[j++] = src[i];
                break;
        }
    }

    temp[j] = '\0';
    lr_save_string(temp, output_param);
}


Action()
{
    // -----------------------------
    // Declare all variables on top
    // -----------------------------
    char *originalValue;          // Pointer to original value
    char escapedValue[32768];     // Buffer for escaped value
    char *paramName;              // Name of LR parameter
    char *escapedParamName;       // Name of escaped LR parameter
    int i;                        // General purpose index

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
