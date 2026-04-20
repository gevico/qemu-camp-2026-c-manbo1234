#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    if (url == NULL) {
        return -1;
    }

    char *copy = malloc(strlen(url) + 1);
    if (copy == NULL) {
        return -1;
    }
    strcpy(copy, url);

    char *query = strchr(copy, '?');
    if (query == NULL || *(query + 1) == '\0') {
        free(copy);
        return 0;
    }

    query++;
    char *token = strtok(query, "&");
    while (token != NULL) {
        char *eq = strchr(token, '=');
        if (eq != NULL) {
            *eq = '\0';
            printf("key = %s, value = %s\n", token, eq + 1);
        }
        token = strtok(NULL, "&");
    }

    free(copy);

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}
