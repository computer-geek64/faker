// main.h

#ifndef FAKER_MAIN_H
#define FAKER_MAIN_H

struct identity;
int main();
void parseRandomUserJSON(struct identity *person, char *responseText);
void parseLocationIQJSON(struct identity *person, char *responseText);
void toLowerCase(char *str);

#endif
