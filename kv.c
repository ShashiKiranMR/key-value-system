/* Key Value Storage System */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<ctype.h>
#include<stdbool.h>

FILE *fp, *tmp;

int del(int key) {
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    char *token;
    int tmp_key;
    
    printf("Deleting the entry with %d as key\n", key);
    fp = fopen("database.txt", "r");
    if (fp == NULL)
        return 0;

    tmp = fopen("database.txt.tmp", "ab+");

    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        printf("%s\n", line);
        token = strsep(&line, ",");
        tmp_key = atoi(token);
        if (key != tmp_key) {
            fprintf(tmp, "%d,%s", tmp_key, line);
        }
    }
    fclose(fp);
    fclose(tmp);
    remove("database.txt");
    rename("database.txt.tmp", "database.txt");
    return 0;
}

int put(int key, int val) {
    printf("Inserting (%d, %d)\n", key, val);
    del(key);
    fp = fopen("database.txt", "a");
    fprintf(fp, "%d,%d\n", key, val);
    fclose(fp);
    return 0;
}

int get(int key) {
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    char *token;
    int tmp_key, val = 0;
    bool flag = false;
    
    printf("Getting the value of %d\n", key);
    fp = fopen("database.txt", "r");
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        printf("%s\n", line);
        while ((token = strsep(&line, ",")) != NULL) {
            if (flag) {
                val = atoi(token);
                printf("Found value=%d with key=%d\n", val, key);
                goto Done;
            }
            tmp_key = atoi(token);
            if (key == tmp_key) {
                flag = true;
            }
            else {
                continue;
            }
        }
    }
Done:
    fclose(fp);
    return val;
}

int clear() {
    printf("Clearing all the entries in the database\n");
    remove("database.txt");
    return 0;
}

int print_all() {
    printf("Printing all the elements in the database\n");
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    fp = fopen("database.txt", "r");
    while ((linelen = getline(&line, &linecap, fp)) > 0)
        printf("%s", line);
    
    fclose(fp);
    return 0;
}

int main(int argc, char **argv) {
    int i;
    char *token, *string, *to_free;
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    int inx = 0, key, val;
    char command;

    /* Process each command */
    for (i=1; i<argc; i++) {
        inx = 0;
        /* Parse each command */
        to_free = string = strdup(argv[i]);
        assert(string != NULL);
        while ((token = strsep(&string, ",")) != NULL) {
            /* If command valid, process it */
            if (token[0] == 'p' ||
                    token[0] == 'g' ||
                    token[0] == 'a' ||
                    token[0] == 'c' ||
                    token[0] == 'd')
                command = token[0];

            else if (isdigit(token[0])) {
                /* key */
                if (inx == 1) {
                    key = atoi(token);
                }

                /* value */
                if (inx == 2) {
                    val = atoi(token);
                }
            }
            inx++;
        }
        switch (command) {
            case 'p': put(key, val); break;
            case 'g': get(key); break;
            case 'a': print_all(); break;
            case 'c': clear(); break;
            case 'd': del(key); break;
        }
        free(to_free);
    }
    return 0;
}
