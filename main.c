#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

// Function prototypes
void list_commands(char *file_path);
void add_command(char *command, char *file_path);
void remove_command(int commandId, char *file_path);
void run_command(int command_id, char *file_path);

#define MAX_COMMANDS 100
#define MAX_COMMAND_LENGTH 100
#define CONFIG_DIR "/.config/pin"
#define CONFIG_FILE "/commands.txt"

// Main loop

char *get_commands_file_path() {
    struct passwd *pw = getpwuid(getuid()); // Get user's home directory
    char *homedir = pw->pw_dir; // Get user's home directory

    // Allocate memory for config directory and file path
    char *config_dir = malloc(strlen(homedir) + strlen(CONFIG_DIR) + 1);
    char *file_path = malloc(strlen(homedir) + strlen(CONFIG_DIR) + strlen(CONFIG_FILE) + 1);

    if (config_dir == NULL || file_path == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    // Create config directory if it doesn't exist
    strcpy(config_dir, homedir);
    strcat(config_dir, CONFIG_DIR);
    mkdir(config_dir, 0700);


    // Create file path
    strcpy(file_path, config_dir);
    strcat(file_path, CONFIG_FILE);

    free(config_dir);
    return file_path;
}

int main(int argc, char *argv[]) {

    // Load commands

    char *file_path = get_commands_file_path();

    if (access(file_path, F_OK) != 0) {
        FILE *fp = fopen(file_path, "w");
        if (fp == NULL) {
            printf("Error opening file\n");
            exit(1);
        }
        fclose(fp);
    }

    // Flag parsing

    if (argc < 2) {
        printf("Usage: pin <command>\n");
        printf("Commands:\n");
        printf("  ls: List commands\n");
        printf("  add: Add command\n");
        printf("  rm: Remove command\n");
        printf("  run: Run command\n");
        return 1;
    }

    if (strcmp(argv[1], "ls") == 0) {
        list_commands(file_path);
    } else if (strcmp(argv[1], "add") == 0) {
        if (argc < 3) {
            printf("Usage: pin add <command>\n");
            return 1;
        }
        add_command(argv[2], file_path);
    } else if (strcmp(argv[1], "rm") == 0) {
        if (argc < 3) {
            printf("Usage: pin rm <id>\n");
            return 1;
        }
        int id = atoi(argv[2]);
        remove_command(id, file_path);
    } else if (strcmp(argv[1], "run") == 0) {
        if (argc < 3) {
            printf("Usage: pin run <id>\n");
            return 1;
        }
        int id = atoi(argv[2]);
        run_command(id, file_path);
    } else {
        printf("Invalid command\n");
    }

    return 0;
}

// CLI commands

void run_command(int command_id, char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char line[MAX_COMMAND_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (i == command_id) {
            system(line);
            break;
        }
        i++;
    }
}

void list_commands(char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char line[MAX_COMMAND_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%d: %s", i, line);
        i++;
    }   
}

void add_command(char *command, char *file_path) {
    FILE *fp = fopen(file_path, "a");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    fprintf(fp, "%s\n", command);
    fclose(fp);
    printf("Successfully added command %s\n", command);
}

void remove_command(int command_id, char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    FILE *temp_fp = fopen("temp.txt", "w");
    if (temp_fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    char line[MAX_COMMAND_LENGTH];
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (i != command_id) {
            fprintf(temp_fp, "%s", line);
        }
        i++;
    }
    fclose(fp);
    fclose(temp_fp);
    remove(file_path);
    rename("temp.txt", file_path);
    printf("Successfully removed command %d\n", command_id);
}

//////////// Testing ////////////

void test_get_commands_file_path() {
    char *file_path = get_commands_file_path();
    printf("File path: %s\n", file_path);
    free(file_path);
}
