#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "list.h"

enum token_type {
    Plus,
    Minus,
    Star,
    Slash,

    Ge,
    Gt,
    Eq,
    Le,
    Lt,

    Semicolon,
    LeftParen,
    RightParen,

    Assignment,

    If,
    Else,
    For,

    Int,

    Id,

    IntLiteral,
    StringLiteral
};

struct token {
    enum token_type type;
    char *text;
    struct list_head list;
};

int token_add(enum token_type type, const char *text);
void token_iter(void (*visit)(struct token *));
char *token_to_string(enum token_type type);
void token_destroy(void);

#endif /* _TOKEN_H_ */
