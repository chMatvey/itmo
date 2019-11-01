#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <dirent.h>
#include "errno.h"

const char *concatenate(const char *first, const char *second) {
    int firstLength = 0;
    int secondLength = 0;

    while (first[firstLength] != '\0') {
        firstLength++;
    }
    while (second[secondLength] != '\0') {
        secondLength++;
    }

    int length = firstLength + secondLength;
    char str[length + 1];

    for (int i = 0; i < length; i++) {
        if (i < firstLength) {
            str[i] = first[i];
        } else {
            str[i] = second[i - firstLength];
        }
    }
    str[length] = '\0';

    const char *result = malloc(length + 1);
    if (result == NULL) return NULL;
    result = &str[0];

    return result;
}

int length(const char *str) {
    int result = 0;
    while (str[result] != '\0') {
        result++;
    }

    return result;
}

int isRegularFile(const char *path) {
    struct stat statBuffer;
    if (stat(path, &statBuffer) != 0)
        return 0;

    return S_ISREG(statBuffer.st_mode);
}

int isDirectory(const char *path) {
    struct stat statBuffer;
    if (stat(path, &statBuffer) != 0)
        return 0;

    return S_ISDIR(statBuffer.st_mode);
}

int hasFlag(int flagCount, char *flags[], const char *flag) {
    for (int i = 0; i < flagCount; i++) {
        if (strcmp(flags[i], flag) == 0) return 1;
    }

    return 0;
}

typedef struct node {
    char *value;
    struct node *next;
} node_t;

void add(node_t **head, char *value) {
    node_t *tmp = malloc(sizeof(node_t));
    tmp->value = strdup(value);
    tmp->next = (*head);
    (*head) = tmp;
}

struct sourceFiles {
    int size;
    node_t *names;
    node_t *fullNames;
};

void getSourceFiles(struct sourceFiles *result, char *sourceName) {
    if (isDirectory(sourceName)) {
        DIR *dir = opendir(sourceName);
        struct dirent *entry;
        size_t dirLength = strlen(sourceName);

        while ((entry = readdir(dir)) != NULL) {
            char *fileName = entry->d_name;
            char *fullName = malloc(dirLength + strlen(fileName) + 1);
            strcpy(fullName, sourceName);
            strcat(fullName, "/");
            strcat(fullName, fileName);

            if (strcmp(fileName, ".") != 0 && strcmp(fileName, "..") != 0) {
                if (isDirectory(fullName)) {
                    getSourceFiles(result, fullName);
                } else {
                    add(&result->names, fileName);
                    add(&result->fullNames, fullName);
                    result->size++;
                }
            }

            free(fullName);
        }

        closedir(dir);
        free(entry);
    } else if (isRegularFile(sourceName)) {
        int lastIndexSlash = 0;
        int sourceLength = 0;

        while (sourceName[sourceLength] != '\0') {
            if (sourceName[sourceLength] == '/') {
                lastIndexSlash = sourceLength;
            }
            sourceLength++;
        }

        int fileNameLength = sourceLength - lastIndexSlash;
        int directoryNameLength = sourceLength - fileNameLength;

        char *fileName = malloc(fileNameLength);
        char *directoryName = malloc(directoryNameLength);

        for (int i = 0; i < sourceLength; i++) {
            if (i < lastIndexSlash) {
                directoryName[i] = sourceName[i];
            } else {
                fileName[i - lastIndexSlash] = sourceName[i];
            }
        }

        add(&result->names, fileName);
        add(&result->fullNames, sourceName);
        result->size = 1;

        free(fileName);
        free(directoryName);
    }
}

void printError(char *buf) {
    write(STDOUT_FILENO, buf, 50);
}

void printSystemError(char *filePath) {
    char *msg;
    if (errno == EPERM) {
        msg = "You don't have permisson to change group for file\n";
    } else if (errno == ENOENT) {
        msg = "Specified file does not exist\n";
    } else if (errno == ENOTDIR)
        msg = "Specified filePath is not correct\n";
    else if (errno == EACCES)
        msg = "You don't have permisson on one of the directories, where the searched file is hold\n";
    else {
        msg = "System error\n";
    }

    write(STDOUT_FILENO, msg, strlen(msg));
    write(STDOUT_FILENO, filePath, strlen(filePath));
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printError("Arguments must be: [flags] <sourcefile> <destination file>\n");
        exit(1);
    } else {
        int countFlags = argc - 3;
        char *flags[countFlags];
        for (int i = 0; i < countFlags; i++) {
            flags[i] = argv[i + 1];
        }

        char *sourceName = argv[1 + countFlags];

        if (!hasFlag(countFlags, flags, "-r") && isDirectory(sourceName)) {
            printError("Error: -r not specified; omitting directory");
            exit(0);
        }

        struct sourceFiles sources;
        sources.size = 0;
        sources.names = NULL;
        sources.fullNames = NULL;
        getSourceFiles(&sources, sourceName);

        int size = sources.size;
        if (size == 0) {
            printSystemError(sourceName);
            exit(0);
        }

        node_t *names;
        node_t *fullNames = sources.fullNames;
        char *destNames[size];

        char *dest = argv[2 + countFlags];

        if (isDirectory(dest)) {
            size_t destLength = strlen(dest);
            names = sources.names;

            for (int i = 0; i < size; i++) {
                const char *fileName = names->value;
                char *destFileName = NULL;
                destFileName = malloc(sizeof(char) * (destLength + strlen(fileName) + 1));

                strcpy(destFileName, dest);
                strcat(destFileName, "/");
                strcat(destFileName, fileName);

                destNames[i] = strdup(destFileName);
                free(destFileName);

                names = names->next;
            }
        } else {
            if (size > 1) {
                printError("Cannot overwrite non-directory\n");
                printSystemError(dest);
                exit(0);
            }
            if (!isRegularFile(dest)) {
                printSystemError(dest);
                exit(0);
            }
            destNames[0] = strdup(dest);
        }

        char buf;
        int sourceFile;
        int destFile;

        fullNames = sources.fullNames;

        for (int i = 0; i < size; i++) {
            sourceFile = open(fullNames->value, O_RDONLY);
            destFile = open(destNames[i], O_WRONLY | O_CREAT, 0641);

            while ((read(sourceFile, &buf, 1)) != 0) {
                write(destFile, &buf, 1);
            }

            close(sourceFile);
            close(destFile);
        }

        write(STDOUT_FILENO, "FILES COPIED\n", 15);
    }

    return 0;
}