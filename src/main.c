// main.c

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "main.h"

int sendGetRequest(char *url) {
    CURL *curl;
    CURLcode response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(!curl) {
        exit(1);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);

    response = curl_easy_perform(curl);

    if(response != CURLE_OK) {
        printf("HTTP Error %d\n", response);
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return response;
}

int main() {
    printf("CURLE_OK: %d\n", CURLE_OK);
    int responseCode = sendGetRequest("http://ipecho.net/plain");
    printf("Response code: %d\n", responseCode);
    return 0;
}