#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>

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

    const char *result = (char *) malloc(length + 1);
    if (result == NULL) return NULL;
    result = &str[0];

    return result;
}

int main(int argc, char *argv[]) {
    char buf;
    int sourceFile, destFile;

    if (argc < 3) {
        write(STDOUT_FILENO, "prgm1 <sourcefile> [flags] <destination file>\n", 50);
        exit(1);
    } else {
        const char *sourceFileName = argv[1];

        sourceFile = open(sourceFileName, O_RDONLY);

        if (sourceFile == -1) {
            perror("SOURCE FILE ERROR");
            exit(0);
        } else {
            const char *dest = argv[2];

            if (isDirectory(dest)) {
                int lastIndexSlash = 0;
                int sourceFileNameLength = 0;

                while (sourceFileName[sourceFileNameLength] != '\0') {
                    if (sourceFileName[sourceFileNameLength] == '/') {
                        lastIndexSlash = sourceFileNameLength;
                    }
                    sourceFileNameLength++;
                }

                int fileNameLength = sourceFileNameLength - lastIndexSlash;

                char name[fileNameLength + 1];
                for (int i = lastIndexSlash; i < sourceFileNameLength; i++) {
                    name[i - lastIndexSlash] = sourceFileName[i];
                }
                name[fileNameLength] = '\0';

                const char *fileName = (char *) malloc(fileNameLength + 1);
                fileName = &name[0];

                const char *destFileName = concatenate(dest, fileName);

                if (destFileName == NULL) exit(1);

                destFile = open(destFileName, O_WRONLY | O_CREAT, 0641);
            } else {
                destFile = open(dest, O_WRONLY | O_CREAT, 0641);
            }

            if (destFile == -1) {
                perror("DESTINATION FILE ERROR");
                exit(0);
            } else {
                while ((read(sourceFile, &buf, 1)) != 0) {
                    write(destFile, &buf, 1);
                }
                write(STDOUT_FILENO, "FILES COPIED\n", 15);

                close(sourceFile);
                close(destFile);
            }
        }
    }

    return 0;
}