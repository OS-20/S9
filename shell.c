#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void search(char mode, char *fname, char *pat) {
    FILE *fp = fopen(fname, "r");
    if (!fp) { printf("File not found!\n"); return; }

    char line[200]; int lineNo = 0, found = 0;
    while (fgets(line, sizeof(line), fp)) {
        lineNo++;
        char *p = line;
        while ((p = strstr(p, pat))) {
            found = 1;
            if (mode == 'f') { 
                printf("First occurrence at line %d: %s", lineNo, line);
                fclose(fp); return;
            } else if (mode == 'a')
                printf("Line %d: %s", lineNo, line);
            p += strlen(pat);
        }
    }
    if (!found && mode == 'f') printf("Pattern not found.\n");
    fclose(fp);
}

int main() {
    char input[100], *arg[5];

    while (1) {
        printf("myshell$ ");
        if (!fgets(input, sizeof(input), stdin)) break;

        int i = 0;
        arg[i] = strtok(input, " \t\n");
        if (!arg[i]) continue;
        while ((arg[++i] = strtok(NULL, " \t\n")));

        if (!strcmp(arg[0], "exit")) break;
        else if (!strcmp(arg[0], "search") && arg[1] && arg[2] && arg[3])
            search(arg[1][0], arg[2], arg[3]);
        else {
            if (fork() == 0) {
                execvp(arg[0], arg);
                perror("Command failed");
                exit(1);
            } else wait(NULL);
        }
    }
    return 0;
}
