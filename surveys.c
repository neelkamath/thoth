#include <stdlib.h>
#include <string.h>

#include "surveys.h"

survey_map *create_survey_map()
{
    survey_map *map = malloc(sizeof(map));
    map->entries = NULL;
    return map;
}

survey_entry *create_survey_entry(char name[DATA_SIZE], survey *s)
{
    survey_entry *entry = malloc(sizeof(survey_entry));
    strcpy(entry->name, name);
    entry->mcqs = s;
    entry->next = NULL;
    return entry;
}

void add_survey(survey_map *map, char name[DATA_SIZE], survey *s)
{
    survey_entry *entry = create_survey_entry(name, s);
    entry->next = map->entries;
    map->entries = entry;
}

survey *get_survey(survey_map *map, char name[DATA_SIZE])
{
    int found = 0;
    survey_entry *curr = map->entries;
    for (; curr != NULL; curr = curr->next)
        if (strcmp(curr->name, name) == 0)
        {
            found = 1;
            break;
        }
    return found ? curr->mcqs : NULL;
}

int survey_exists(survey_map *map, char name[DATA_SIZE])
{
    return get_survey(map, name) != NULL;
}

void clear_survey_map(survey_map *map)
{
    survey_entry *prev = NULL;
    for (survey_entry *curr = map->entries; curr != NULL; prev = curr, curr = curr->next)
    {
        if (prev != NULL)
            clear_survey(prev->mcqs);
        free(prev);
    }
    free(prev);
    free(map);
}