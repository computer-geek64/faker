// curl_helper.h

#ifndef FAKER_CURL_HELPER_H
#define FAKER_CURL_HELPER_H

struct responseText;
size_t writeCallback(void *ptr, size_t size, size_t nmemb, struct responseText *r);
char* sendGetRequest(char *url);

#endif