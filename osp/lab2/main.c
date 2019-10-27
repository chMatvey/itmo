#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int isRegularFile(char *path) {
    struct stat statBuffer;
    if (stat(path, &statBuffer) != 0)
        return 0;

    return S_ISREG(statBuffer.st_mode);
}

int isDirectory(char *path) {
    struct stat statBuffer;
    if (stat(path, &statBuffer) != 0)
        return 0;

    return S_ISDIR(statBuffer.st_mode);
}

int main(int argc, char *argv[]) {
    char buf;
    int sourceFile, destFile;

    if (argc < 3) {
        write(STDOUT_FILENO, "prgm1 <sourcefile> [flags] <destination file>\n", 50);
        exit(1);
    } else {
        char *sourceFileName = argv[1];

        sourceFile = open(sourceFileName, O_RDONLY);

        if (sourceFile == -1) {
            perror("SOURCE FILE ERROR");
            exit(0);
        } else {
            char *destFIleName = argv[2];

            if (isDirectory(destFIleName)) {
                int lastIndexSlash = 0;
                int sourceFileNameLength = 0;
                int destDirNameLength = 0;

                while(sourceFileName[sourceFileNameLength] != '\0') {
                    sourceFileNameLength++;
                }

                while(destFIleName[destDirNameLength] != '\0') {
                    destDirNameLength++;
                }

                for (int i = 0; i < sourceFileNameLength; i++) {
                    if (sourceFileName[i] == '/') {
                        lastIndexSlash = i;
                    }
                }

                int length = sourceFileNameLength - lastIndexSlash;
                int destFileNameLength = length + destDirNameLength;

                char name[destFileNameLength];

                for (int i = 0; i < destDirNameLength; i++) {
                    name[i] = destFIleName[i];
                }

                for (int i = 0; i < destFileNameLength; i++) {
                    name[destDirNameLength + i] = sourceFileName[lastIndexSlash + i];
                }

                destFIleName = &name[0];
            }

            destFile = open(destFIleName, O_WRONLY | O_CREAT, 0641);

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