#include "inverted.h"

int update_database(hash_t *hash, Node **head, char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf(RED"[ERROR] Failed to open backup file: %s\n"RESET, filename);
        return FAILURE;
    }

    printf(MAGENTA"\n============================================================\n"RESET);
    printf(BLUE"                 UPDATING DATABASE FROM BACKUP               \n"RESET);
    printf(MAGENTA"============================================================\n"RESET);
    printf(CYAN"[INFO] Reading data from backup file: %s\n"RESET, filename);

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = '\0';

        if (line[0] != '#' || line[strlen(line) - 1] != '#')
        {
            printf(RED"[ERROR] Invalid format in backup file. Each line must start and end with '#'.\n"RESET);
            fclose(fp);
            return FAILURE;
        }

        line[strlen(line) - 1] = '\0';
        char *data = line + 1;

        char *token = strtok(data, ";");
        if (!token)
        {
            continue;
        }
        int index = atoi(token);

        char *word = strtok(NULL, ";");
        if (!word)
        {
            continue;
        }

        char *file_count_str = strtok(NULL, ";");
        if (!file_count_str)
        {
            continue;
        }
        int file_count = atoi(file_count_str);

        //printf(YELLOW"\n[ENTRY] Word: '%s' | Index: %d | File Count: %d\n"RESET, word, index, file_count);

        for (int i = 0; i < file_count; i++)
        {
            char *file_name = strtok(NULL, ";");
            char *count_str = strtok(NULL, ";");
            if (!file_name || !count_str)
            {
                break;
            }

            int count = atoi(count_str);
            insert_to_database(hash, index, word, file_name, count);
            remove_file(head, file_name);

            //printf(GREEN"   ↳ File: %-15s | Word Count: %d\n"RESET, file_name, count);
        }
    }

    fclose(fp);


    return SUCCESS;
}
