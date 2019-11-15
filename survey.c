#include <stdlib.h>
#include <string.h>

#include "survey.h"

mcq *create_mcq(char question[DATA_SIZE], char options[4][DATA_SIZE])
{
    mcq *new_mcq = malloc(sizeof(mcq));
    strcpy(new_mcq->question, question);
    for (int count = 0; count < 4; count++)
        strcpy(new_mcq->options[count], options[count]);
    return new_mcq;
}

survey *create_survey()
{
    survey *s = malloc(sizeof(survey));
    s->head = NULL;
    return s;
}

mcq_node *create_mcq_node(mcq *data)
{
    mcq_node *node = malloc(sizeof(mcq_node));
    node->data = data;
    node->next = NULL;
    return node;
}

void add_mcq(survey *s, mcq *new_mcq)
{
    mcq_node *node = create_mcq_node(new_mcq);
    node->next = s->head;
    s->head = node;
}

void clear_survey(survey *s)
{
    mcq_node *prev = NULL;
    for (mcq_node *curr = s->head; curr != NULL; prev = curr, curr = curr->next)
    {
        if (prev != NULL)
            free(prev->data);
        free(prev);
    }
    free(prev);
    free(s);
}

int question_exists(char question[DATA_SIZE], survey *s)
{
    for (mcq_node *node = s->head; node != NULL; node = node->next)
        if (strcmp(node->data->question, question) == 0)
            return 1;
    return 0;
}