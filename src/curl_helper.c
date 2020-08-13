// curl_helper.c

#include "curl_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

struct responseText {
    char *text;
    size_t len;
};

size_t writeCallback(void *ptr, size_t size, size_t nmemb, struct responseText *r) {
    size_t resizeLength = r->len + size * nmemb;
    r->text = realloc(r->text, resizeLength + 1);
    if(r->text == NULL) {
        printf("Out of memory\n");
        exit(1);
    }

    memcpy(r->text + r->len, ptr, size * nmemb);
    r->text[resizeLength] = '\0';
    r->len = resizeLength;
    return size * nmemb;
}

char* sendGetRequest(char *url) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();

    if(curl == NULL) {
        exit(1);
    }

    struct responseText r;
    r.len = 0;
    r.text = malloc(r.len + 1);
    if(r.text == NULL) {
        printf("Out of memory\n");
        exit(1);
    }
    r.text[0] = '\0';
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &r);

    CURLcode responseCode = curl_easy_perform(curl);

    if(responseCode != CURLE_OK) {
        exit(responseCode);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return r.text;
}