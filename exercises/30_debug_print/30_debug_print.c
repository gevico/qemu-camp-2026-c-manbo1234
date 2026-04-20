#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#if DEBUG_LEVEL == 1
#define DEBUG_PRINT(fmt, ...) printf("DEBUG: func=%s, line=%d\n", __func__, __LINE__)
#elif DEBUG_LEVEL == 2
#define DEBUG_PRINT(fmt, ...) printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#elif DEBUG_LEVEL >= 3
#define DEBUG_PRINT(fmt, ...) do { void *bt[16]; int n = backtrace(bt, 16); printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__); backtrace_symbols_fd(bt, n, fileno(stdout)); } while (0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif





























//! MUST BE ENSURE THE DEBUG_PRINT("x=%d", x) AT THE 48 LINE

// 测试代码
void test() {
    int x = 42;
    DEBUG_PRINT("x=%d", x);
}

int main() {
    test();
    return 0;
}
