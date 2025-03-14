#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Returns the number of tokens by scanning the input.
   A token is delimited by spaces outside quotes. */
int get_token_count(char *input)
{
    int i = 0, count = 0;
    int sq = 0, dq = 0;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if (!input[i])
            break;
        count++;
        while (input[i])
        {
            if (input[i] == '\'' && !dq)
                sq = !sq;
            else if (input[i] == '"' && !sq)
                dq = !dq;
            if (!sq && !dq && input[i] == ' ')
                break;
            i++;
        }
    }
    return count;
}

/* Scans from index *i until the token ends.
   A token ends when a space is encountered outside any quotes.
   Returns the raw token length and updates *i to the character after the token. */
int get_token_length(char *input, int *i)
{
    int start = *i;
    int sq = 0, dq = 0;
    while (input[*i])
    {
        if (input[*i] == '\'' && !dq)
            sq = !sq;
        else if (input[*i] == '"' && !sq)
            dq = !dq;
        if (!sq && !dq && input[*i] == ' ')
            break;
        (*i)++;
    }
    return *i - start;
}

/* This function checks if the raw token (from input[start] for length characters)
   is composed entirely of adjacent quoted segments (with no unquoted parts).
   In that case, we want to remove each segment's external quotes,
   concatenate their content, and wrap the result with single quotes.
*/
int is_fully_quoted(char *input, int start, int length)
{
    int pos = start;
    int end = start + length;
    while (pos < end)
    {
        if (input[pos] == '\'' || input[pos] == '"')
        {
            char quote = input[pos];
            pos++;  // skip opening quote
            while (pos < end && input[pos] != quote)
                pos++;
            if (pos >= end || input[pos] != quote)
                return 0; // unmatched quote
            pos++;  // skip closing quote
        }
        else
            return 0; // found unquoted character
    }
    return 1;
}

/* Allocates a token string from input[start] for length characters.
   If the token is fully composed of quoted segments (adjacent),
   it removes each segment’s external quotes, concatenates the content,
   and then wraps the final string with single quotes.
   Otherwise, it uses the default behavior (removing external quotes if they match,
   or simply copying the raw token).
*/
char *allocate_token(char *input, int start, int length)
{
    int end = start + length;
    if (length >= 2 && is_fully_quoted(input, start, length))
    {
        // First, compute the total length of the inner content
        int pos = start;
        int content_len = 0;
        while (pos < end)
        {
            char quote = input[pos];
            pos++; // skip opening quote
            while (pos < end && input[pos] != quote)
            {
                content_len++;
                pos++;
            }
            pos++; // skip closing quote
        }
        // Allocate: 1 for opening single quote, content, 1 for closing, and null terminator.
        char *result = malloc(content_len + 2 + 1);
        if (!result)
            return NULL;
        int j = 0;
        result[j++] = '\''; // add starting single quote
        pos = start;
        while (pos < end)
        {
            char quote = input[pos];
            pos++; // skip opening quote
            while (pos < end && input[pos] != quote)
                result[j++] = input[pos++];
            pos++; // skip closing quote
        }
        result[j++] = '\''; // add closing single quote
        result[j] = '\0';
        return result;
    }
    else
    {
        /* Default behavior:
           If the token starts and ends with the same quote, remove those external quotes.
           Otherwise, simply copy the raw token.
        */
        if (length >= 2 && (input[start] == '\'' || input[start] == '"') &&
            input[end - 1] == input[start])
        {
            char ext = input[start];
            int content_len = 0;
            for (int i = start + 1; i < end - 1; i++)
            {
                if (input[i] != ext)
                    content_len++;
            }
            char *token = malloc(content_len + 2 + 1);
            if (!token)
                return NULL;
            int j = 0;
            token[j++] = ext;
            for (int i = start + 1; i < end - 1; i++)
            {
                if (input[i] != ext)
                    token[j++] = input[i];
            }
            token[j++] = ext;
            token[j] = '\0';
            return token;
        }
        else
        {
            char *token = malloc(length + 1);
            if (!token)
                return NULL;
            strncpy(token, input + start, length);
            token[length] = '\0';
            return token;
        }
    }
}

/* Fills the tokens array by extracting each token from the input. */
char **extract_tokens(char **tokens, char *input)
{
    int i = 0, j = 0, start, length;
    while (input[i])
    {
        while (input[i] == ' ')
            i++;
        if (!input[i])
            break;
        start = i;
        length = get_token_length(input, &i);
        tokens[j++] = allocate_token(input, start, length);
    }
    tokens[j] = NULL;
    return tokens;
}

/* Allocates and returns a NULL-terminated array of tokens parsed from input. */
char **tokenize(char *input)
{
    int count = get_token_count(input);
    char **tokens = malloc((count + 1) * sizeof(char *));
    if (!tokens)
        return NULL;
    return extract_tokens(tokens, input);
}

/* Test driver */
int main(void)
{
    char *tests[] = {
        "'a '\"b\"",
        "'jjhj'\"nnn\"",
        "'a'\"b\"",
        "\"hello world\"",
        "'hello world'",
        "plain unquoted",
        NULL
    };

    for (int i = 0; tests[i]; i++)
    {
        printf("Input: [%s]\n", tests[i]);
        char **tokens = tokenize(tests[i]);
        if (!tokens)
        {
            printf("Memory allocation failed\n");
            continue;
        }
        for (int j = 0; tokens[j]; j++)
        {
            printf("Token[%d]: [%s]\n", j, tokens[j]);
            free(tokens[j]);
        }
        free(tokens);
        printf("\n");
    }
    return 0;
}
