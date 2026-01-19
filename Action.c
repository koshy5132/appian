
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
    char *src = lr_eval_string(input_param); // Get the value of the LR param
    char temp[32768] = {0};                  // Make sure buffer is large enough
    int j = 0;

    for (int i = 0; src[i] != '\0'; i++)
    {
        switch (src[i])
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
    // Simulate a correlation value that has CRLF, quotes, and backslashes
    lr_save_string("Hello \"World\"\r\nThis is line2\\end", "CorrValue");

    // Escape for Appian JSON
    lr_escape_for_json("{CorrValue}", "CorrValue_Escaped");

    // Print to verify
    lr_output_message("Original Value: %s", lr_eval_string("{CorrValue}"));
    lr_output_message("Escaped Value : %s", lr_eval_string("{CorrValue_Escaped}"));

    // Use in a POST request
    web_custom_request("MyRequest",
        "URL=https://dummy.example.com/api",
        "Method=POST",
        "Body={\"text\":\"{CorrValue_Escaped}\"}",
        LAST);

    return 0;
}
