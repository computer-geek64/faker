// main.c

#include "main.h"
#include <stdio.h>
#include <string.h>
#include "curl_helper.c"
#include "cJSON/cJSON.c"

struct identity {
    int male;
    char *title;
    char *firstName;
    char *lastName;
    int age;
    char *dob;
    char *address;
    double latitude;
    double longitude;
    char *email;
    char phone[15];
    char ssn[12];
};

int main(int argc, char **argv) {
    srand(time(NULL));
    struct identity person;

    person.male = rand() % 2;
    int arg = 0;
    while(arg < argc) {
        if(strcmp(argv[arg], "-g") == 0 && arg < argc - 1) {
            person.male = argv[arg + 1][0] == 'm' || argv[arg + 1][0] == 'M';
        }
        arg++;
    }

    for(int i = 1; i < 14; i++) {
        person.phone[i] = '0' + rand() % 10;
    }
    person.phone[0] = '(';
    person.phone[4] = ')';
    person.phone[5] = ' ';
    person.phone[9] = '-';
    person.phone[14] = '\0';

    char randomUserURL[48];
    sprintf(randomUserURL, "https://randomuser.me/api/?nat=us&gender=%s", person.male ? "male" : "female");
    char *responseText = sendGetRequest(randomUserURL);
    parseRandomUserJSON(&person, responseText);
    free(responseText);

    char locationIQURL[77 + strlen(person.address) + 1];
    sprintf(locationIQURL, "https://us1.locationiq.com/v1/search.php?key=a6485e7c311089&format=json&q=%s,us", person.address); // 77
    responseText = sendGetRequest(locationIQURL);
    parseLocationIQJSON(&person, responseText);
    free(responseText);

    char emailFirstName[strlen(person.firstName) + 1];
    char emailLastName[strlen(person.lastName) + 1];
    strcpy(emailFirstName, person.firstName);
    strcpy(emailLastName, person.lastName);
    toLowerCase(emailFirstName);
    toLowerCase(emailLastName);

    sprintf(person.email, "%s.%s@gmail.com", emailFirstName, emailLastName);

    printf("%s. %s %s\n", person.title, person.firstName, person.lastName);
    printf("Age %d, born %s\n", person.age, person.dob);
    printf("%s\n", person.address);
    printf("%f, %f\n", person.latitude, person.longitude);
    printf("%s\n", person.email);
    printf("%s\n", person.phone);

    return 0;
}

void parseRandomUserJSON(struct identity *person, char *responseText) {
    cJSON *json = cJSON_Parse(responseText);
    cJSON *curr = json->child->child->child;
    while(curr->next != NULL) {
        if(strcmp(curr->string, "name") == 0) {
            person->title = curr->child->valuestring;
            person->firstName = curr->child->next->valuestring;
            person->lastName = curr->child->next->next->valuestring;
        }
        else if(strcmp(curr->string, "location") == 0) {
            person->address = curr->child->child->next->valuestring;
        }
        else if(strcmp(curr->string, "email") == 0) {
            person->email = curr->valuestring;
        }
        else if(strcmp(curr->string, "dob") == 0) {
            person->dob = curr->child->valuestring;
            person->age = curr->child->next->valueint;
        }

        curr = curr->next;
    }
}

void parseLocationIQJSON(struct identity *person, char *responseText) {
    cJSON *json = cJSON_Parse(responseText);
    cJSON *curr = json->child->child;
    while(curr->next != NULL) {
        if(strcmp(curr->string, "display_name") == 0) {
            person->address = curr->valuestring;
        }
        else if(strcmp(curr->string, "lat") == 0) {
            person->latitude = atof(curr->valuestring);
        }
        else if(strcmp(curr->string, "lon") == 0) {
            person->longitude = atof(curr->valuestring);
        }

        curr = curr -> next;
    }
}

void toLowerCase(char *str) {
    for(int i = 0; i < strlen(str); i++) {
        str[i] += str[i] >= 65 && str[i] <= 90 ? 32 : 0;
    }
}