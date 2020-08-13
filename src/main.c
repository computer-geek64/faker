// main.c

#include "main.h"
#include <stdio.h>
#include "curl_helper.c"

int main() {
    char *responseText = sendGetRequest("http://ipecho.net/plain");
    printf("IP Address: %s\n", responseText);
    free(responseText);
    return 0;
}