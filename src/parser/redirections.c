#include "parser.h"
#include "lexer.h"

static void push_back(t_lexer_token **list, t_lexer_token *new)
{
    t_lexer_token *curr;

    if (*list == NULL)
    {
        new->prev = NULL;
        *list = new;
        return ;
    }
    curr = *list;
    while (curr->next != NULL)
        curr = curr->next;
    curr->next = new;
    new->prev = curr;
}

void add_new_redirect(t_parser *parser, t_lexer_token *token)
{
    t_lexer_token *new;
    size_t first;
    size_t second;

    new = get_lexer_new_node(ft_strdup(token->next->str), token->token_type);
    if (!new)
        return ; // handle this error
    push_back(&parser->redirs, new);
    first = token->index;
    second = token->next->index;
    delete_node_by_index(&parser->lexer_list, first);
    delete_node_by_index(&parser->lexer_list, second);
    parser->redirs_count += 1;
}

/*
 * Не удаляет строку имя куда редирект происходит, проверить работу функции delete_node_by_index
 * Скорее всего, неправильно связывает ссылки после удаления в середине списка
 */
void collect_redirections(t_parser *parser)
{
    t_lexer_token *curr;

    curr = parser->lexer_list;
    while (curr && curr->token_type == WORD)
        curr = curr->next;
    if (curr == NULL || curr->token_type == PIPE)
        return ; // It will exit here, because curr will be NULL (in while we will pass all elements)
    if (curr->next == NULL)
        parser_error(PLACEHOLDER, NULL, 0, 0); //!!!//! // pipe or redirect on the end of sequence
    if (curr->next->token_type > WORD)
        parser_error(PLACEHOLDER, NULL, 0, 0); // two tokens
    if (curr->token_type >= GREAT && curr->token_type <= L_LESS)
        add_new_redirect(parser, curr); // Here need to save collected redirect to parser->redirs
    collect_redirections(parser);
}
