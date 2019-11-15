#include "survey.h"

// Hash map entry for a <survey>.
typedef struct survey_entry
{
    char name[DATA_SIZE]; // The <survey>'s name is used as the key of this hash map entry.
    survey *mcqs; // The <survey> is used as the value of this hash map entry.
    struct survey_entry *next;
} survey_entry;

typedef struct survey_map
{
    survey_entry *entries;
} survey_map;

survey_map *create_survey_map();

// Creates a <survey_entry> using the <name>d <survey>.
survey_entry *create_survey_entry(char name[DATA_SIZE], survey *);

/*
    Adds the <name>d <survey> to the <survey_map>. If the <name> already exists, the <survey> will not be added. You
    can use <survey_exists()> to check if this function can add the <survey>.
*/
void add_survey(survey_map *, char name[DATA_SIZE], survey *);

/*
    Gets the <name>d <survey> from the <survey_map>. <NULL> will be returned if there is no <name>d <survey>. You can
    use <survey_exists()> to check if this can get a <survey>.
*/
survey *get_survey(survey_map *, char name[DATA_SIZE]);

// Returns whether the <survey_map> contains the <name> of a <survey>.
int survey_exists(survey_map *, char name[DATA_SIZE]);

// Frees the <survey_map>'s dynamically allocated memory..
void clear_survey_map(survey_map *);