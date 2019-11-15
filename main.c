#include <stdio.h>
#include <string.h>

#include "surveys.h"

// Workaround for C's I/O bug. Call this after you performing an I/O operation which may leave characters behind.
void flush();

// Prompts the user for the survey's <name> (at most fifty characters), which will be unique in the <survey_map>.
void prompt_survey_name(char name[DATA_SIZE], survey_map *);

// Prompts the user to create a <survey>.
survey *prompt_survey();

// Prompts for an <mcq> for the <survey>.
mcq *prompt_mcq(survey *);

// Prompts the user for a <question> unique to the <survey>.
void prompt_question(char question[DATA_SIZE], survey *);

// Prompts the user for <options>.
void prompt_options(char options[4][DATA_SIZE]);

// Prompts the user to enter the <type> of <data>.
void prompt_data(char type[DATA_SIZE], char data[DATA_SIZE]);

// Returns whether the <value> is in the <values>. <values> is an array of <size> strings.
int contains_value(char value[DATA_SIZE], int size, char values[size][DATA_SIZE]);

// Interactively displays the <survey_map>.
void display(survey_map *);

void print_survey(survey *);

void print_mcq(mcq *);

int main()
{
    survey_map *map = create_survey_map();
    while (1)
    {
        printf("Enter 'c' to create a survey, 'v' to view a survey, and 'q' to quit: ");
        char option = getchar();
        flush();
        switch (option)
        {
            case 'c':
            {
                char name[DATA_SIZE];
                prompt_survey_name(name, map);
                add_survey(map, name, prompt_survey());
                break;
            }
            case 'v':
                display(map);
                break;
            case 'q':
                clear_survey_map(map);
                return 0;
            default:
                puts("Please enter a valid option.");
        }
    }
}

void flush()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void prompt_survey_name(char name[DATA_SIZE], survey_map *map)
{
    while (1)
    {
        prompt_data("survey's name", name);
        if (survey_exists(map, name))
            puts("That survey already exists.");
        else
            break;
    }
}

survey *prompt_survey()
{
    survey *s = create_survey();
    while (1)
    {
        printf("Enter 'a' to add an MCQ, and 's' to save the survey: ");
        char option;
        scanf("%c", &option);
        flush();
        switch (option)
        {
            case 'a':
                add_mcq(s, prompt_mcq(s));
                break;
            case 's':
                return s;
            default:
                puts("Please enter a valid option.");
        }
    }
}

mcq *prompt_mcq(survey *s)
{
    char question[DATA_SIZE];
    prompt_question(question, s);
    char options[4][DATA_SIZE];
    prompt_options(options);
    return create_mcq(question, options);
}

void prompt_question(char question[DATA_SIZE], survey *s)
{
    while (1)
    {
        prompt_data("the question", question);
        if (question_exists(question, s))
            puts("That question already exists.");
        else
            break;
    }
}

void prompt_options(char options[4][DATA_SIZE])
{
    for (int count = 0; count < 4; )
    {
        char option[DATA_SIZE];
        printf("Enter option %d: ", count + 1);
        scanf("%s", option);
        flush();
        if (contains_value(option, count, options))
            puts("Please enter a new option.");
        else
            strcpy(options[count++], option);
    }
}

void prompt_data(char type[DATA_SIZE], char data[DATA_SIZE])
{
    printf("Enter %s: ", type);
    scanf("%s", data);
    flush();
}

int contains_value(char value[DATA_SIZE], int size, char values[size][DATA_SIZE])
{
    for (int i = 0; i < size; i++)
        if (strcmp(value, values[i]) == 0)
            return 1;
    return 0;
}

void display(survey_map *map)
{
    if (map->entries == NULL)
    {
        puts("There are no surveys.");
        return;
    }
    puts("Here are the names of the surveys:");
    for (survey_entry *curr = map->entries; curr != NULL; curr = curr->next)
        puts(curr->name);
    char name[DATA_SIZE];
    while (1)
    {
        prompt_data("survey's name", name);
        if (!survey_exists(map, name))
            puts("That survey doesn't exist.");
        else
            break;
    }
    print_survey(get_survey(map, name));
}

void print_survey(survey *mcqs)
{
    if (mcqs->head == NULL)
    {
        puts("The survey is empty.");
        return;
    }
    mcq_node *node = mcqs->head;
    for (int count = 1; node != NULL; count++, node = node->next)
    {
        printf("\nMCQ %d:\n", count);
        print_mcq(node->data);
    }
    puts("");
}

void print_mcq(mcq *data)
{
    printf("Question: %s\n", data->question);
    for (int count = 0; count < 4; count++)
        printf("Option %d: %s\n", count + 1, data->options[count]);
}