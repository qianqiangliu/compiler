#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "token.h"

#define MAX_TOKEN_LEN 128

enum state {
    INIT,
    ID,
    GT,
    GE,
    ASSIGNMENT,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    SEMICOLON,
    LEFTPAREN,
    RIGHTPAREN,
    INT_LITERAL
};

/* TODO: the token size is constant, make it variable */
static char token_buffer[MAX_TOKEN_LEN];
static int token_buffer_index = 0;
static enum token_type token_type;

void token_buffer_init(void)
{
    token_buffer_index = 0;
    memset(token_buffer, 0, MAX_TOKEN_LEN);
}

void token_buffer_append(char ch)
{
    if (token_buffer_index == MAX_TOKEN_LEN)
        return;
    token_buffer[token_buffer_index] = ch;
    token_buffer_index++;
}

void check_keyword(void)
{
    if (strcmp(token_buffer, "int") == 0)
        token_type = Int;
    else if (strcmp(token_buffer, "if") == 0)
        token_type = If;
    else if (strcmp(token_buffer, "else") == 0)
        token_type = Else;
    else if (strcmp(token_buffer, "for") == 0)
        token_type = For;
}

enum state init_token(int ch)
{
    enum state state = INIT;

    if (token_buffer_index > 0) {
        check_keyword();
        token_add(token_type, token_buffer);
        token_buffer_init();
    }

    if (isalpha(ch)) {
        state = ID;
        token_type = Id;
        token_buffer_append(ch);
    } else if (isdigit(ch)) {
        state = INT_LITERAL;
        token_type = IntLiteral;
        token_buffer_append(ch);
    } else if (ch == '>') {
        state = GT;
        token_type = Gt;
        token_buffer_append(ch);
    } else if (ch == '+') {
        state = PLUS;
        token_type = Plus;
        token_buffer_append(ch);
    } else if (ch == '-') {
        state = MINUS;
        token_type = Minus;
        token_buffer_append(ch);
    } else if (ch == '*') {
        state = STAR;
        token_type = Star;
        token_buffer_append(ch);
    } else if (ch == '/') {
        state = SLASH;
        token_type = Slash;
        token_buffer_append(ch);
    } else if (ch == ';') {
        state = SEMICOLON;
        token_type = Semicolon;
        token_buffer_append(ch);
    } else if (ch == '(') {
        state = LEFTPAREN;
        token_type = LeftParen;
        token_buffer_append(ch);
    } else if (ch == ')') {
        state = RIGHTPAREN;
        token_type = RightParen;
        token_buffer_append(ch);
    } else if (ch == '=') {
        state = ASSIGNMENT;
        token_type = Assignment;
        token_buffer_append(ch);
    } else {
        state = INIT;
    }

    return state;
}

void tokenize(const char *script)
{
    int i;
    int len = strlen(script);
    enum state state = INIT;

    for (i = 0; i < len; i++) {
        switch (state) {
        case INIT:
            state = init_token(script[i]);
            break;
        case ID:
            if (isalpha(script[i]) || isdigit(script[i]))
                token_buffer_append(script[i]);
            else
                state = init_token(script[i]);
            break;
        case GT:
            if (script[i] == '=') {
                token_type = Ge;
                state = GE;
                token_buffer_append(script[i]);
            } else {
                state = init_token(script[i]);
            }
            break;
        case GE:
        case ASSIGNMENT:
        case PLUS:
        case MINUS:
        case STAR:
        case SLASH:
        case SEMICOLON:
        case LEFTPAREN:
        case RIGHTPAREN:
            state = init_token(script[i]);
            break;
        case INT_LITERAL:
            if (isdigit(script[i]))
                token_buffer_append(script[i]);
            else
                state = init_token(script[i]);
            break;
        default:
            break;
        }
    }
    /* read the last token */
    if (token_buffer_index > 0)
        init_token(script[i]);
}

void visit(struct token *token)
{
    printf("type: %s, text: %s\n", token_to_string(token->type), token->text);
}

int main(int argc, char **argv)
{
    char *script = "int age = 45;";
    printf("parse script: %s\n", script);
    tokenize(script);
    token_iter(visit);
    token_destroy();
    puts("---------------------");

    script = "price = (10 - 3) * 5;";
    printf("parse script: %s\n", script);
    tokenize(script);
    token_iter(visit);
    token_destroy();
    puts("---------------------");

    script = "if (age >= 45) b = 40;";
    printf("parse script: %s\n", script);
    tokenize(script);
    token_iter(visit);
    token_destroy();
    return 0;
}
