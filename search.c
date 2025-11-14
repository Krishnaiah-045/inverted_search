#include "inverted.h"

int search_database(hash_t *hash, char *s)
{
    if (!hash || !s || !s[0]) 
    {
        printf(RED"[ERROR] Invalid arguments to search.\n"RESET);
        return FAILURE;
    }

    int index;
    char ch = s[0];

    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        index = (ch & ~32) - 'A'; 
    else if (ch >= '0' && ch <= '9')
        index = 26;
    else
        index = 27;

    if (hash[index].h_link == NULL) 
    {
        printf(YELLOW"[INFO] No entries found in this index for '%s'.\n"RESET, s);
        return FAILURE;
    }

    main_t *maintemp = hash[index].h_link;

    while (maintemp != NULL) 
    {
        if (strcmp(maintemp->word, s) == 0) 
        {
            printf(MAGENTA"\n============================================================\n"RESET);
            printf(BLUE"                    SEARCH RESULT                            \n"RESET);
            printf(MAGENTA"============================================================\n"RESET);

            printf(GREEN" Word        : "RESET YELLOW"%-20s "RESET, maintemp->word);
            printf(BLUE"| File Count : %d\n"RESET, maintemp->file_count);

            sub_t *subtemp = maintemp->ms_link;
            while (subtemp != NULL) 
            {
                printf("     ↳ "CYAN"File: "RESET"%s  ", subtemp->file_name);
                printf(GREEN"| Word Count: %d\n"RESET, subtemp->word_count);
                subtemp = subtemp->s_link;
            }

            printf(MAGENTA"------------------------------------------------------------\n"RESET);
            printf(GREEN"[SUCCESS] Word '%s' found in the database.\n"RESET, s);
            printf(MAGENTA"============================================================\n"RESET);

            return SUCCESS;
        }
        maintemp = maintemp->m_link;
    }

   // printf(YELLOW"[INFO] Word '%s' not found in the database.\n"RESET, s);
    return FAILURE;
}
