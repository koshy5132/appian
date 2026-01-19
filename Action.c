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
