Action()
{
    // Example: save original value
    lr_save_string("Hello\r\nWorld!\rThis is a test.\nEnd.", "CorrValue");

    // Call the reusable function
    escape_newlines("{CorrValue}", "CorrValue_Escaped");

    // Output for verification
    lr_output_message("Original Value:\n%s", lr_eval_string("{CorrValue}"));
    lr_output_message("Escaped Value:\n%s", lr_eval_string("{CorrValue_Escaped}"));

    return 0;
}