Appian's JSON handling evolved: older versions might have been more lenient or implicitly handled escapes, but newer versions strictly enforce standard JSON, requiring explicit escaping (e.g., \\n for newline, \\" for quotes, \\\\ for backslash) within a!toJson() or raw string inputs to correctly represent special characters, which older systems might have interpreted differently or passed through. The core issue is Appian enforcing stricter JSON compliance, meaning characters like " and \ must be escaped with a preceding backslash (\) within a JSON string to avoid syntax errors, a change from potentially looser old behavior or manual string construction. 
Why it Worked Before (Likely Scenarios):
Implicit Handling: Older Appian versions or specific integration configurations might have automatically handled certain escapes or accepted non-standard strings that were then interpreted by the receiving system.
Different Input Methods: You might have been using different functions or input methods (like directly pasting into an integration body vs. using a!toJson()) that behaved differently.
Loose Parsing by Target: The external system receiving the JSON might have had a more forgiving parser than Appian's built-in functions. 
How to Fix It Now (Standard JSON Practice):
Use a!toJson() with correct escaping:
Newlines: \\n
Double Quotes: \\" (e.g., {"key": "value with \\"quote\\" inside"})
Backslashes: \\\\ (e.g., {"path": "C:\\\\Users\\\\Data"}) 
