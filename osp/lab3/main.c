#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "message.h"
#include "handler.h"

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

char *readFromFile(char *filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    free(f);

    string[fsize] = 0;

    return string;
}

int main() {
    char *string = readFromFile("../data.json");
    TMessage *message = createMessage(string);

    pthread_t tid; /* идентификатор потока */
    pthread_attr_t attr; /* отрибуты потока */

    /* получаем дефолтные значения атрибутов */
    pthread_attr_init(&attr);

    /* создаем новый поток */
    pthread_create(&tid, &attr, per_thread, message);

    /* ждем завершения исполнения потока */
    pthread_join(tid, NULL);

    free(string);
    free(message);
}