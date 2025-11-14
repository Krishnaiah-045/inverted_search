#include "inverted.h"

int valid_filename(char *s)
{
    char *pos = strstr(s, ".txt");
    if (!pos || pos == s || *(pos + 4) != '\0')
        return FAILURE;
    return SUCCESS;
}

int is_file_empty(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);
    long size = ftell(fptr);
    rewind(fptr);
    return (size == 0);
}

int is_duplicate(Node *head, char *filename)
{
    Node *temp = head;
    while (temp)
    {
        if (strcmp(temp->file_name, filename) == 0)
            return SUCCESS;
        temp = temp->link;
    }
    return FAILURE;
}

void insert_file(Node **head, char *filename)
{
    Node *new = malloc(sizeof(Node));
    strcpy(new->file_name, filename);
    new->link = NULL;

    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        Node *temp = *head;
        while (temp->link != NULL)
            temp = temp->link;
        temp->link = new;
    }
}

int read_and_validate(int argc, char *argv[], Node **head)
{
    printf(BOLDWHITE"\n========== VALIDATING INPUT FILES ==========\n"RESET);

    for (int i = 1; i < argc; i++)
    {
        if (!valid_filename(argv[i]))
        {
            printf(RED"[ERROR] Invalid file name: '%s' (must end with .txt)\n"RESET, argv[i]);
            continue;
        }

        if (is_duplicate(*head, argv[i]))
        {
            printf(YELLOW"[WARNING] Duplicate file skipped: '%s'\n"RESET, argv[i]);
            continue;
        }

        FILE *fptr = fopen(argv[i], "r");
        if (!fptr)
        {
            printf(RED"[ERROR] Unable to open file: '%s'\n"RESET, argv[i]);
            continue;
        }

        if (is_file_empty(fptr))
        {
            printf(MAGENTA"[INFO] File is empty: '%s'\n"RESET, argv[i]);
            fclose(fptr);
            continue;
        }

        fclose(fptr);
        insert_file(head, argv[i]);
        printf(GREEN"[SUCCESS] File added: '%s'\n"RESET, argv[i]);
    }

    if (*head == NULL)
    {
        printf(RED"\nNo valid input files found.\n"RESET);
        return FAILURE;
    }

    printf(CYAN"\nAll valid files have been processed successfully.\n"RESET);
    return SUCCESS;
}

int is_hash_empty(hash_t *hash)
{
    int flag = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (hash[i].h_link != NULL)
            flag = 1;
    }

    if (flag)
        return FAILURE;
    else
        return SUCCESS;
}

void insert_to_database(hash_t *hash, int index, char *word, char *file_name, int word_count)
{
    main_t *mainTemp = hash[index].h_link;
    main_t *prev = NULL;

    while (mainTemp && strcmp(mainTemp->word, word) != 0)
    {
        prev = mainTemp;
        mainTemp = mainTemp->m_link;
    }

    if (mainTemp == NULL)
    {
        main_t *new_main = malloc(sizeof(main_t));
        if (!new_main)
        {
            printf(RED"[ERROR] Memory allocation failed for main node.\n"RESET);
            return;
        }

        strcpy(new_main->word, word);
        new_main->file_count = 1;
        new_main->m_link = NULL;
        new_main->ms_link = NULL;

        sub_t *new_sub = malloc(sizeof(sub_t));
        if (!new_sub)
        {
            printf(RED"[ERROR] Memory allocation failed for sub node.\n"RESET);
            free(new_main);
            return;
        }

        strcpy(new_sub->file_name, file_name);
        new_sub->word_count = word_count;
        new_sub->s_link = NULL;
        new_main->ms_link = new_sub;

        if (hash[index].h_link == NULL)
            hash[index].h_link = new_main;
        else
            prev->m_link = new_main;
    }
    else
    {
        sub_t *subTemp = mainTemp->ms_link;
        sub_t *subPrev = NULL;

        while (subTemp && strcmp(subTemp->file_name, file_name) != 0)
        {
            subPrev = subTemp;
            subTemp = subTemp->s_link;
        }

        if (subTemp == NULL)
        {
            sub_t *new_sub = malloc(sizeof(sub_t));
            if (!new_sub)
            {
                printf(RED"[ERROR] Memory allocation failed for sub node.\n"RESET);
                return;
            }

            strcpy(new_sub->file_name, file_name);
            new_sub->word_count = word_count;
            new_sub->s_link = NULL;
            subPrev->s_link = new_sub;
            mainTemp->file_count++;
        }
        else
        {
            subTemp->word_count++;
        }
    }
}

int remove_file(Node **head, char *filename)
{
    if (*head == NULL)
    {
        printf(RED"[ERROR] File list is empty.\n"RESET);
        return FAILURE;
    }

    Node *temp = *head;
    Node *prev = NULL;

    while (temp)
    {
        if (strcmp(temp->file_name, filename) == 0)
        {
            if (temp == *head)
            {
                *head = temp->link;
                free(temp);
                return SUCCESS;
            }
            else
            {
                prev->link = temp->link;
                free(temp);
                return SUCCESS;
            }
        }
        prev = temp;
        temp = temp->link;
    }
    return SUCCESS;
}
