#include "lrun.h"
#include <string.h>

// Escape CRLF for JSON
void escape_crlf(const char *input, char *output) {
    int i, j = 0;
    for(i = 0; input[i] != '\0'; i++) {
        if(input[i] == '\r') {
            output[j++] = '\\';
            output[j++] = 'r';
        }
        else if(input[i] == '\n') {
            output[j++] = '\\';
            output[j++] = 'n';
        }
        else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

Action()
{
    char escaped[8192];  // make big enough for your value

    // Assume CorrValue is captured
    escape_crlf(lr_eval_string("{CorrValue}"), escaped);

    lr_save_string(escaped, "CorrValue_Escaped");

    // Use in JSON body
    web_custom_request("AppianJSON",
        "URL=https://example.com/appian",
        "Method=POST",
        "Body={\"text\":\"{CorrValue_Escaped}\"}",
        LAST
    );

    return 0;
}
