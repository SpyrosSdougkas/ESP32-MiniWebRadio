#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

void urldecode(char* str) {
    uint16_t p1 = 0, p2 = 0;
    char     a, b;
    while(str[p1]) {
        if((str[p1] == '%') && ((a = str[p1 + 1]) && (b = str[p1 + 2])) && (isxdigit(a) && isxdigit(b))) {
            if(a >= 'a') a -= 'a' - 'A';
            if(a >= 'A') a -= ('A' - 10);
            else a -= '0';
            if(b >= 'a') b -= 'a' - 'A';
            if(b >= 'A') b -= ('A' - 10);
            else b -= '0';
            str[p2++] = 16 * a + b;
            p1 += 3;
        }
        else if(str[p1] == '+') {
            str[p2++] = ' ';
            p1++;
        }
        else { str[p2++] = str[p1++]; }
    }
    str[p2++] = '\0';
}

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    char* str = (char*)malloc(size + 1);
    memcpy(str, data, size);
    str[size] = '\0';
    urldecode(str);
    free(str);
    return 0;
}