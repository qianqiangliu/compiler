#include <stdlib.h>
#include <string.h>

#include "token.h"

static struct list_head head = LIST_HEAD_INIT(head);

int token_add(enum token_type type, const char *text)
{
    struct token *token = malloc(sizeof(struct token));
    if (!token)
        return -1;
    char *tmp = strdup(text);
    if (!tmp) {
        free(token);
        return -1;
    }
    token->type = type;
    token->text = tmp;
    list_add_tail(&token->list, &head);
    return 0;
}

void token_iter(void (*visit)(struct token *))
{
    struct token *pos;

    list_for_each_entry(pos, &head, list) {
        visit(pos);
    }
}

char *token_to_string(enum token_type type)
{
    switch (type) {
    case Plus:
        return "Plus";
    case Minus:
        return "Minus";
    case Star:
        return "Star";
    case Slash:
        return "Slash";
    case Ge:
        return "Ge";
    case Gt:
        return "Gt";
    case Eq:
        return "Eq";
    case Le:
        return "Le";
    case Lt:
        return "Lt";
    case Semicolon:
        return "Semicolon";
    case LeftParen:
        return "LeftParen";
    case RightParen:
        return "RightParen";
    case Assignment:
        return "Assignment";
    case If:
        return "If";
    case Else:
        return "Else";
    case For:
        return "For";
    case Int:
        return "Int";
    case Id:
        return "Id";
    case IntLiteral:
        return "IntLiteral";
    case StringLiteral:
        return "StringLiteral";
    default:
        return "Unknow";
    }
}

void token_destroy(void)
{
    struct token *pos;
    struct token *tmp;

    list_for_each_entry_safe(pos, tmp, &head, list) {
        list_del(&pos->list);
        free(pos);
    }
}
