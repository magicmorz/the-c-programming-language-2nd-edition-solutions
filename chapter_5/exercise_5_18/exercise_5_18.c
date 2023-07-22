#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum {
    NAME,
    PARENS,
    BRACKETS
};



void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];    /* type of last token */
char name[MAXTOKEN];     /* last token string */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];          /* output string */

#define BUFSIZE 100

char buf[BUFSIZE]; // Buffer for ungetch
int buf_pos = 0;   // Next free position in buf

// Get a character from input or from buffer if available
int getch(void) {
    return (buf_pos > 0) ? buf[--buf_pos] : getchar();
}

// Push character back into buffer
void ungetch(int c) {
    if (buf_pos >= BUFSIZE) {
        printf("ungetch: buffer full, character dropped\n");
    } else {
        buf[buf_pos++] = c;
    }
}

/* gettoken: Tokenizes the input by reading characters and classifying them into different types.
 *
 * This function reads characters from the input and groups them into specific tokens,
 * including data types, identifiers, keywords, operators, parentheses, and brackets.
 * It skips white spaces and tabs to find the start of the next token. It then analyzes
 * the characters to determine the type of token and stores it in the global variable
 * 'tokentype'. The actual token is stored in the global character array 'token'.
 *
 * Returns:
 * The function returns the type of the token encountered. It can be one of the following:
 *   - NAME: For an identifier or keyword.
 *   - PARENS: For parentheses '()'.
 *   - BRACKETS: For brackets '[]'.
 *   - Any other character: For operators or other non-special characters.
 *
 * Note:
 * This function uses a buffer ('buf') and a buffer position ('buf_pos') to support the
 * 'ungetch' function, which allows pushing back characters into the input stream. This
 * is useful for handling situations where a character is read but not used immediately,
 * so it can be pushed back to be processed later.
 *
 * Example usage:
 * int tokentype;
 * char token[MAXTOKEN];
 * while ((tokentype = gettoken()) != EOF) {
 *     // Process the token based on its type
 *     switch (tokentype) {
 *         case NAME:
 *             printf("Identifier or keyword: %s\n", token);
 *             break;
 *         case PARENS:
 *             printf("Parentheses: %s\n", token);
 *             break;
 *         case BRACKETS:
 *             printf("Brackets: %s\n", token);
 *             break;
 *         default:
 *             printf("Operator or character: %c\n", tokentype);
 *     }
 * }
 */

int gettoken(void) /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    // Skip white spaces and tabs
    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        // Read an identifier (name) or keyword
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c; // Return operator or other characters
    }
}

/* dcl: parse a declarator */
void dcl(void) {
    int ns;

    // Count the number of pointer symbols '*'
    for (ns = 0; gettoken() == '*';)
        ns++;

    // Parse the rest of the declarator
    dirdcl();

    // Append "pointer to" to the output string for each pointer symbol
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}

/* dirdcl: parse a direct declarator */ 
void dirdcl(void) {
    int type;

    // If the declarator starts with '(', it's a nested declarator
    if (tokentype == '(') {
        dcl();

        // Check if the nested declarator ends with ')'
        if (tokentype != ')')
            printf("error: missing )\n");
    } else if (tokentype == NAME) {
        // Save the name of the identifier
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        return;
    }

    // Process additional qualifiers or array dimensions
    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

int main(int argc, char const *argv[]) /* convert declaration to words */
{
    while (gettoken() != EOF) /* 1st token on line */ {
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';
        dcl(); /* parse rest of line */
        if (tokentype != '\n') {
            printf("syntax error\n");
        }
            printf("%s: %s %s\n", name, out, datatype);
    }

    return 0;
}
