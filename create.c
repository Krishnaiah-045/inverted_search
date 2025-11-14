#include "inverted.h"

int create_database(hash_t *hash, Node **head)
{
    if (*head == NULL)
    {
        printf(RED"[ERROR] No files available for processing.\n"RESET);
        return FAILURE;
    }

    Node *temp = *head;
    Node *prev_temp = NULL;
    FILE *fptr;
    char word[100];

    while (temp != NULL)
    {
        fptr = fopen(temp->file_name, "r");
        if (!fptr)
        {
            printf(RED"[ERROR] Could not open file: %s\n"RESET, temp->file_name);
            temp = temp->link;
            continue;
        }

        printf(CYAN"[INFO] Reading data from file: %s\n"RESET, temp->file_name);

        while (fscanf(fptr, "%99s", word) != EOF)
        {
            int index;
            char ch = word[0];

            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
                index = (ch & ~32) - 'A';
            else if (ch >= '0' && ch <= '9')
                index = 26;
            else
                index = 27;

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
                    fclose(fptr);
                    return FAILURE;
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
                    fclose(fptr);
                    return FAILURE;
                }

                strcpy(new_sub->file_name, temp->file_name);
                new_sub->word_count = 1;
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

                while (subTemp && strcmp(subTemp->file_name, temp->file_name) != 0)
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
                        fclose(fptr);
                        return FAILURE;
                    }

                    strcpy(new_sub->file_name, temp->file_name);
                    new_sub->word_count = 1;
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

        fclose(fptr);
        printf(GREEN"[SUCCESS] Finished processing file: %s\n"RESET, temp->file_name);

        prev_temp = temp;
        temp = temp->link;
        remove_file(head, prev_temp->file_name);
    }

    printf(BLUE"\n[INFO] All files processed successfully. Database creation complete.\n"RESET);
    return SUCCESS;
}
