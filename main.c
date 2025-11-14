#include "inverted.h"

int main(int argc, char *argv[])
{
    Node *head = NULL;

    printf("\n" MAGENTA "============================================================\n" RESET);
    printf(BOLD BLUE "               WELCOME TO INVERTED SEARCH ENGINE             \n" RESET);
    printf(MAGENTA "============================================================\n" RESET);

    if (argc < 2)
    {
        printf("\n" MAGENTA "============================================================\n" RESET);
        printf(BOLD BLUE "                   INVERTED SEARCH ENGINE                    \n" RESET);
        printf(MAGENTA "============================================================\n" RESET);
        printf(CYAN "Usage:\n" RESET);
        printf(WHITE "   %s <input_file1> <input_file2> ...\n", argv[0]);
        printf(CYAN "Example:\n" RESET);
        printf(WHITE "   %s sample1.txt sample2.txt\n", argv[0]);
        printf(MAGENTA "============================================================\n" RESET);
        return FAILURE;
    }

    if (read_and_validate(argc, argv, &head) == 0)
    {
        printf("\n" RED "[ERROR] Input file validation failed!\n" RESET);
        printf(WHITE "        One or more input files are invalid or unreadable.\n" RESET);
        printf(WHITE "        Please verify filenames and access permissions.\n" RESET);
        return FAILURE;
    }

    printf(YELLOW "\n[INFO] Input files validated successfully.\n" RESET);
    printf(CYAN "------------------------------------------------------------\n" RESET);
    printf(BLUE " Files to be processed:\n" RESET);

    Node *temp = head;
    int i = 1;
    while (temp != NULL)
    {
        printf(WHITE "   [%02d] %s\n" RESET, i, temp->file_name);
        i++;
        temp = temp->link;
    }

    printf(CYAN "------------------------------------------------------------\n" RESET);

    hash_t hash[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        hash[i].index = i;
        hash[i].h_link = NULL;
    }

    char buffer[100];
    int option;

    while (1)
    {
        printf("\n" CYAN "----------------------- MAIN MENU ---------------------------\n" RESET);
        printf(WHITE "   [1] Create Database\n" RESET);
        printf(WHITE "   [2] Display Database\n" RESET);
        printf(WHITE "   [3] Search Database\n" RESET);
        printf(WHITE "   [4] Update Database\n" RESET);
        printf(WHITE "   [5] Save Database\n" RESET);
        printf(WHITE "   [6] Exit Program\n" RESET);
        printf(CYAN "------------------------------------------------------------\n" RESET);
        printf(BYELLOW "Enter your choice [1-6]: " RESET);

        if (scanf("%d", &option) != 1)
        {
            printf("\n" RED "[ERROR] Invalid input. Please enter a numeric value (1–6).\n" RESET);
            while (getchar() != '\n');
            continue;
        }

        switch (option)
        {
            case 1:
                if (!head)
                {
                    printf(YELLOW "[INFO] No new files available for database creation.\n" RESET);
                    break;
                }
                if (create_database(hash, &head) == SUCCESS)
                    printf(GREEN "[SUCCESS] Database created successfully.\n" RESET);
                else
                    printf(RED "[FAILURE] Database creation failed.\n" RESET);
                break;

            case 2:
                if (is_hash_empty(hash) == FAILURE)
                {
                    if (display_database(hash) == SUCCESS)
                        printf(GREEN "[SUCCESS] Database displayed successfully.\n" RESET);
                    else
                        printf(RED "[FAILURE] Error displaying database.\n" RESET);
                }
                else
                    printf(YELLOW "[INFO] Database is empty. Nothing to display.\n" RESET);
                break;

            case 3:
                if (is_hash_empty(hash) == FAILURE)
                {
                    printf(BYELLOW "Enter the word to search: " RESET);
                    scanf("%99s", buffer);
                    if (search_database(hash, buffer) == SUCCESS)
                        printf(GREEN "[SUCCESS] Word '%s' found in the database.\n" RESET, buffer);
                    else
                        printf(YELLOW "[INFO] Word '%s' not found in the database.\n" RESET, buffer);
                }
                else
                    printf(YELLOW "[INFO] Database is empty. Please create it first.\n" RESET);
                break;

            case 4:
                if (is_hash_empty(hash) == SUCCESS)
                {
                    printf(BYELLOW "Enter the backup filename to update from: " RESET);
                    scanf("%99s", buffer);
                    if (update_database(hash, &head, buffer) == SUCCESS)
                        printf(GREEN "[SUCCESS] Database updated successfully.\n" RESET);
                    else
                        printf(RED "[FAILURE] Database update failed.\n" RESET);
                }
                else
                    printf(RED "[FAILURE] Database already exists. Update not possible.\n" RESET);
                break;

            case 5:
                if (is_hash_empty(hash) == FAILURE)
                {
                    printf(BYELLOW "Enter the filename to save the database: " RESET);
                    scanf("%99s", buffer);
                    if (Save_database(hash, buffer) == SUCCESS)
                        printf(GREEN "[SUCCESS] Database saved successfully.\n" RESET);
                    else
                        printf(RED "[FAILURE] Error saving database.\n" RESET);
                }
                else
                    printf(YELLOW "[INFO] Database is empty. Nothing to save.\n" RESET);
                break;

            case 6:
                printf("\n" CYAN "[EXIT] Exiting program... Goodbye!\n" RESET);
                printf(MAGENTA "============================================================\n" RESET);
                return 0;

            default:
                printf(RED "[ERROR] Invalid choice. Please select option 1–6.\n" RESET);
        }
    }

    return 0;
}
