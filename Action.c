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
    char escaped[8192];

    // Simulated correlation value (from server)
    lr_save_string("Line1\r\nLine2\r\nLine3", "CorrValue");

    // Escape CRLF so JSON parser interprets it correctly
    escape_crlf(lr_eval_string("{CorrValue}"), escaped);
    lr_save_string(escaped, "CorrValue_Escaped");

    lr_output_message("Escaped value sent in JSON:\n%s", lr_eval_string("{CorrValue_Escaped}"));

    web_custom_request("AppianJSON",
        "URL=http://dummy.test/appian",
        "Method=POST",
        "Body={\"text\":\"{CorrValue_Escaped}\"}",
        LAST
    );

    return 0;
}



/******************************************/

Action()
{
    FILE *fp;
    char *filename = "C:\\Temp\\requestBody.txt";

    // Simulated correlation value with CRLF
    char *corrValue = lr_eval_string("{CorrValue}");

    // Write it to a file exactly as-is (including CRLF)
    fp = fopen(filename, "w");
    if (fp == NULL) {
        lr_error_message("Cannot create file: %s", filename);
        return -1;
    }
    fputs(corrValue, fp);  // writes real CRLF characters
    fclose(fp);

    // Send request using BODYFILE
    web_custom_request("AppianJSON",
        "URL=http://dummy.test/appian",
        "Method=POST",
        "EncType=application/json",
        "BodyFile=C:\\Temp\\requestBody.txt",
        LAST
    );

    lr_output_message("Request sent with real CRLF in body from file.");

    return 0;
}


/**********************/



#include "lrun.h"
#include <string.h>
#include <stdio.h>

Action()
{
    // ---------------------------
    // Variable declarations at top
    // ---------------------------
    char requestBody[8192];        // buffer for request body
    char escaped[8192];            // buffer if you want to escape CRLF for JSON
    int len;                        // length of request body
    char *corrValue;                // correlation value from server

    // ---------------------------
    // Step 1: Simulate server response / correlation
    // ---------------------------
    lr_save_string("Line1\r\nLine2\r\nLine3", "ServerResponse");

    // Capture correlation value (here we just simulate)
    lr_save_string(lr_eval_string("{ServerResponse}"), "CorrValue");
    corrValue = lr_eval_string("{CorrValue}");

    // ---------------------------
    // Step 2: Copy correlation value into request buffer
    // ---------------------------
    strcpy(requestBody, corrValue);

    // Length of request body (required for BodyBinary)
    len = (int)strlen(requestBody);

    // ---------------------------
    // Step 3: Send JSON request with real CRLF preserved
    // ---------------------------
    web_add_auto_header("Content-Type", "application/json", LAST);

    web_custom_request("AppianJSON",
        "URL=http://dummy.test/appian",  // replace with real Appian URL
        "Method=POST",
        "BodyBinary=", requestBody, len,
        LAST
    );

    // ---------------------------
    // Step 4: Log output for verification
    // ---------------------------
    lr_output_message("Correlation value (original):\n%s", corrValue);
    lr_output_message("Request body sent with real CRLF.");

    return 0;
}



