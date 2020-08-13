// main.c

#include "main.h"
#include <stdio.h>
#include "curl_helper.c"
#include "cJSON.c"

int main() {
    char *responseText = sendGetRequest("https://randomuser.me/api/");
    //printf("%s\n", responseText);
    cJSON *json = cJSON_Parse(responseText);
    free(responseText);
    printf("%s\n", cJSON_Print(json));
    return 0;
}