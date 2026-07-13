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



You are an expert in Micro Focus LoadRunner VuGen script generation and automatic correlation.

Your task is to update an existing Action.c file by replacing hardcoded dynamic values with LoadRunner parameter names.

IMPORTANT:

The request body is NOT plain JSON.

The request body is stored inside VuGen C source code as BinaryBody= and consists of escaped C string literals.

Examples:

Actual JSON
------------
{
  "sessionId":"ABC123",
  "token":"XYZ456"
}

Stored inside Action.c
----------------------
"BinaryBody="
"{\\r\\n"
"\\\"sessionId\\\":\\\"ABC123\\\",\\r\\n"
"\\\"token\\\":\\\"XYZ456\\\"\\r\\n"
"}"

Rules:

1. Never treat BinaryBody as normal JSON.
2. Never pretty-print or reformat the request body.
3. Never deserialize and serialize the JSON.
4. Preserve all existing formatting exactly.
5. Preserve:
   - escaped quotes (\")
   - escaped backslashes (\\)
   - escaped CRLF (\\r\\n)
   - escaped tabs (\\t)
   - escaped Unicode (\\uXXXX)
   - Base64 or encoded values
   - concatenated C string literals
6. Search using the exact representation stored inside Action.c.
7. Replace ONLY the dynamic value.
8. Do NOT modify surrounding JSON syntax.
9. Do NOT modify property names.
10. Do NOT change indentation or line breaks.
11. The output must compile successfully in VuGen.

Replacement Rules

If

ABC123

must become

{SessionID}

Only replace

ABC123

Never replace

\"sessionId\":

Never replace surrounding escape characters.

If the value appears inside BinaryBody with escaped characters, preserve those escape characters.

If the value contains escaped characters such as

\"
\\
\\r\\n
\\uXXXX

match them exactly as stored inside Action.c before replacing.

The generated script must be functionally identical to the original except that hardcoded dynamic values are replaced with LoadRunner parameters.

Return only the updated Action.c code.
