#define DATA_SIZE 250 // Questions and options must contain at most these many characters.

typedef struct mcq
{
    char question[DATA_SIZE];
    char options[4][DATA_SIZE]; // Four options. Every option is a string containing at most <DATA_SIZE> characters.
} mcq;

typedef struct mcq_node
{
    mcq *data;
    struct mcq_node *next;
} mcq_node;

typedef struct survey
{
    mcq_node *head;
} survey;

// Creates an <mcq> from the <question> and <options>.
mcq *create_mcq(char question[DATA_SIZE], char options[4][DATA_SIZE]);

survey *create_survey();

// Creates an <mcq_node> to contain the <mcq>.
mcq_node *create_mcq_node(mcq *);

// Returns the new <survey>, which contains the <mcq>.
void add_mcq(survey *, mcq *);

// Frees the <survey>'s dynamically allocated memory.
void clear_survey(survey *);

// Whether the <question> exists in the <survey>.
int question_exists(char question[DATA_SIZE], survey *);