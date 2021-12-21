/* Key Value Storage System */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

int put(int key, int val) {
    printf("Inserting (%d, %d)\n", key, val);
    return 0;
}

int get(int key) {
    printf("Getting the value of %d\n", key);
    return 0;
}

int del(int key) {
    printf("Deleting the entry with %d as key\n", key);
    return 0;
}

int clear() {
    printf("Clearing all the entries in the database\n");
    return 0;
}

int print_all() {
    printf("Printing all the elements in the database\n");
    return 0;
}

int main(int argc, char **argv) {
    int i;
    char *token, *string, *to_free;
    FILE *fp;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;

    /* Load the database */
    fp = fopen("database.txt", "ab+");
    assert(fp != NULL);

    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        printf("input: %s\n", line);
    }

    /* Process each command */
    for (i=1; i<argc; i++) {
        /* Parse each command */
        to_free = string = strdup(argv[i]);
        assert(string != NULL);
        while ((token = strsep(&string, ",")) != NULL) {
            /* If command valid, process it */
            printf("%s\n", token);
        }
        free(to_free);
        
        printf("%s\n", argv[i]);
    }
    return 0;
}
