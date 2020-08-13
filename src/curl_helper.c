// curl_helper.c

#include "curl_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>


size_t writeCallback(void *ptr, size_t size, size_t nmemb, char *responseText) {
    size_t resizeLength = size * nmemb + sizeof(*responseText) - 1;
    responseText = realloc(responseText, resizeLength + 1);
    if (responseText == NULL) {
        printf("Out of memory\n");
        exit(1);
    }

    memcpy(responseText + sizeof(*responseText) - 1, ptr, size * nmemb);
    responseText[resizeLength] = '\0';
    return size * nmemb;
}

char* sendGetRequest(char *url) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();

    if(curl == NULL) {
        exit(1);
    }

    char *responseText = malloc(1 * sizeof(char));
    if(responseText == NULL) {
        printf("Out of memory\n");
        exit(1);
    }
    responseText[0] = '\0';
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, responseText);

    CURLcode responseCode = curl_easy_perform(curl);

    if(responseCode != CURLE_OK) {
        exit(responseCode);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return responseText;
}