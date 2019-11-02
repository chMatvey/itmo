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

char *substrByLast(char *str, char symbol) {
    int lastIndex = 0;
    int length = 0;

    while (str[length] != '\0') {
        if (str[length] == symbol) {
            lastIndex = length;
        }
        length++;
    }

    if (lastIndex != 0) {
        lastIndex++;
    }

    int resultLength = length - lastIndex;
    char *result = (char *) malloc(resultLength + 1);

    for (int i = lastIndex; i < length; i++) {
        result[i - lastIndex] = str[i];
    }

    return result;
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
    node_t *tmp = (node_t *) malloc(sizeof(node_t));
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
        char *dirName = substrByLast(sourceName, '/');

        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char *fileName = (char *) malloc(strlen(dirName) + strlen(entry->d_name) + 1);
                //strcpy(fileName, dirName);
                strcpy(fileName, "/");
                strcat(fileName, entry->d_name);

                char *fullName = (char *) malloc(dirLength + strlen(fileName) + 1);
                strcpy(fullName, sourceName);
                strcat(fullName, "/");
                strcat(fullName, entry->d_name);

                if (isDirectory(fullName)) {
                    getSourceFiles(result, fullName);
                } else if (isRegularFile(fullName)) {
                    add(&result->names, fileName);
                    add(&result->fullNames, fullName);
                    result->size++;
                }

                free(fileName);
                free(fullName);
            }
        }

        closedir(dir);
        free(entry);
        free(dirName);
    } else if (isRegularFile(sourceName)) {
        char *fileName = substrByLast(sourceName, '/');

        add(&result->names, fileName);
        add(&result->fullNames, sourceName);
        result->size = 1;

        free(fileName);
    }
}

void advancedPrint(char *str) {
    size_t length = strlen(str);
    size_t size = 0;

    while (size != length) {
        size_t s = write(STDOUT_FILENO, str + size, length - size);
        if (s == -1) {
            return;
        }
        size += s;
    }
}

void printError(char *buf) {
    advancedPrint(buf);
}

void printSystemError(char *filePath) {
    char *msg = strerror(errno);

    advancedPrint(msg);
    advancedPrint(filePath);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printError("Arguments must be: [flags] <sourcefile> <destination file>\n");
        return EINVAL;
    } else {
        int countFlags = argc - 3;
        char *flags[countFlags];
        for (int i = 0; i < countFlags; i++) {
            flags[i] = argv[i + 1];
        }

        char *sourceName = argv[1 + countFlags];

        if (!hasFlag(countFlags, flags, "-r") && isDirectory(sourceName)) {
            printError("Error: -r not specified; omitting directory\n");
            return EINVAL;
        }

        struct sourceFiles sources;
        sources.size = 0;
        sources.names = NULL;
        sources.fullNames = NULL;
        getSourceFiles(&sources, sourceName);

        int size = sources.size;
        if (size == 0) {
            printSystemError(sourceName);
            return EINVAL;
        }

        node_t *names;
        node_t *fullNames;
        char *destNames[size];

        char *dest = argv[2 + countFlags];

        if (isDirectory(dest)) {
            size_t destLength = strlen(dest);
            names = sources.names;

            for (int i = 0; i < size; i++) {
                const char *fileName = names->value;
                char *destFileName = NULL;
                destFileName = (char *) malloc(sizeof(char) * (destLength + strlen(fileName) + 1));

                strcpy(destFileName, dest);
                //strcat(destFileName, "/");
                strcat(destFileName, fileName);

                destNames[i] = strdup(destFileName);
                free(destFileName);

                names = names->next;
            }
        } else {
            if (size > 1) {
                printError("Cannot overwrite non-directory\n");
                printSystemError(dest);
                return errno;
            }
            if (!isRegularFile(dest)) {
                printSystemError(dest);
                return ENOENT;
            }
            destNames[0] = strdup(dest);
        }

        char buf;
        int sourceFile;
        int destFile;

        fullNames = sources.fullNames;
        names = sources.names;

        int hasVFlag = hasFlag(countFlags, flags, "-v");
        //int hasIFlag = hasFlag(countFlags, flags, "-i");

        for (int i = 0; i < size; i++) {
            sourceFile = open(fullNames->value, O_RDONLY);
            if (sourceFile == -1) {
                printSystemError(fullNames->value);
                return errno;
            }

            struct stat st;
            if (stat(fullNames->value, &st) != 0) {
                printSystemError(fullNames->value);
                return errno;
            }
            mode_t perm = st.st_mode;

            destFile = open(destNames[i], O_WRONLY | O_CREAT, perm);
            if (destFile == -1) {
                printSystemError(destNames[i]);
                return errno;
            }

            if (hasVFlag) {
                advancedPrint(fullNames->value);
                advancedPrint(" -> ");
                advancedPrint(destNames[i]);
                advancedPrint("\n");
            }

            while ((read(sourceFile, &buf, 1)) != 0) {
                write(destFile, &buf, 1);
            }

            close(sourceFile);
            close(destFile);
        }

        advancedPrint("FILES COPIED\n");

        for (int i = 0; i < size; i++) {
            free(destNames[i]);
        }
    }

    return 0;
}