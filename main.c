#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void RemoveDoubleSpaces(char *str) {
    int i, j;
    bool spaceFound = false;

    for (i = 0, j = 0; str[i]; i++) {
        if (str[i] != ' ') {
            str[j] = str[i];
            j++;
            spaceFound = false;
        } else {
            if (!spaceFound) {
                str[j] = str[i];
                j++;
            }
            spaceFound = true;
        }
    }

    str[j] = '\0';
}

int main() {
    ////////////////////////////////////////
    /// open/create file with current date as filename

    // prep datetime
    time_t currentTime;
    time(&currentTime);
    struct tm *timeinfo;
    timeinfo = localtime(&currentTime);

    // load datetime
    char shortDate[11];
    strftime(shortDate, sizeof(shortDate), "%d-%m-%Y", timeinfo);

    // open/create file
    char filename[15];
    snprintf(filename, sizeof(filename), "%s.txt", shortDate);
    FILE *file = fopen(filename, "a");

    // verify success
    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    ////////////////////////////////////////
    /// get and format todays current date

    char fullDate[10];
    strftime(fullDate, sizeof(fullDate), "%H:%M:%S", timeinfo);
    RemoveDoubleSpaces(fullDate);

    ////////////////////////////////////////
    /// dynamically sized input

    char *input = NULL;
    size_t bufferSize = 0;
    size_t charactersRead;

    printf(": ");

    charactersRead = getline(&input, &bufferSize, stdin);

    if (charactersRead == -1) {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }

    ////////////////////////////////////////
    /// format content

    char content[strlen(input) + 10];
    sprintf(content, "%s\n\t%s", fullDate, input);

    ////////////////////////////////////////
    /// write to file

    for (int i = 0; content[i] != '\0'; i++) {
        if (content[i] != '') {
            printf("%c :", content[i]);
            printf(" %d\n", content[i]);
            fprintf(file, "%c", content[i]);
        } else {
            if (content[i+3] == '~') {
                i += 3;
            } else {
                i += 2;
            }
        }
    }

    fprintf(file, "\n");
    
    ////////////////////////////////////////
    /// close up

    fclose(file);
    free(input);
    
    return 0;
}