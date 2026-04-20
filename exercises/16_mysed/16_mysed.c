#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    const char* old_begin = strchr(cmd + 2, '/');
    if (old_begin == NULL) {
        return -1;
    }

    const char* new_begin = strchr(old_begin + 1, '/');
    if (new_begin == NULL) {
        return -1;
    }

    size_t old_len = (size_t)(old_begin - (cmd + 2));
    size_t new_len = (size_t)(new_begin - old_begin - 1);

    *old_str = malloc(old_len + 1);
    *new_str = malloc(new_len + 1);
    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        *old_str = NULL;
        *new_str = NULL;
        return -1;
    }

    memcpy(*old_str, cmd + 2, old_len);
    (*old_str)[old_len] = '\0';
    memcpy(*new_str, old_begin + 1, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char *pos = strstr(str, old);
    if (pos == NULL) {
        return;
    }

    char buffer[MAX_LINE_LENGTH];
    size_t prefix_len = (size_t)(pos - str);
    snprintf(buffer, sizeof(buffer), "%.*s%s%s", (int)prefix_len, str, new, pos + strlen(old));
    strncpy(str, buffer, MAX_LINE_LENGTH - 1);
    str[MAX_LINE_LENGTH - 1] = '\0';
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
