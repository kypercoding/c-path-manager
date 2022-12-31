#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hiredis/hiredis.h>

#include "db.h"


/**
 * Creates a new connection to Redis.
*/
redisContext* makeConnection(char **argv, int argc, int d) {
  if (argc != d && argc != d + 2) {
      printf("error: please enter the correct arguments\n");
      return NULL;
    }

    // check argument length and create default
    // or custom redis connections
    if (argc == d) {
      return redisConnect("127.0.0.1", 6379);
    }

    return redisConnect(argv[d + 1], atoi(argv[d + 2]));
}


/**
 * Main method for directory program.
*/
int main (int argc, char **argv) {
  // declare Redis context
  redisContext* c;

  if (argc == 1) {
    printf("error: please provide correct arguments!\n");
    return 1;
  }

  // checks arguments for command
  if (strcmp(argv[1], "set") == 0) {
    redisContext* c = makeConnection(argv, argc, 4);

    if (c == NULL) {
      return 1;
    }

    // sets a directory
    addDirectory(c, argv[2], argv[3]);

  } else if (strcmp(argv[1], "get") == 0) {
    redisContext* c = makeConnection(argv, argc, 3);

    if (c == NULL) {
      return 1;
    }

    // gets a directory
    char* dir = getDirectory(c, argv[2]);

    printf("%s\n", dir);

  } else if (strcmp(argv[1], "remove") == 0) {
    redisContext* c = makeConnection(argv, argc, 3);

    if (c == NULL) {
      return 1;
    }

    // removes a directory
    removeDirectory(c, argv[2]);

  } else if (strcmp(argv[1], "list") == 0) {
    redisContext* c = makeConnection(argv, argc, 2);

    if (c == NULL) {
      return 1;
    }

    // gets list of keys from Redis
    redisReply* r = getAllDirectories(c);

    if (c == NULL) {
      return 1;
    }

    int i;

    // for each key, print it out along with its
    // value
    for (i = 0; i < r->elements; i++) {
      // get key and value strings
      char* key = r->element[i]->str;
      char* value = getDirectory(c, key);

      // print out output
      printf("%s > %s\n", key + 12, value);
    }

  } else if (strcmp(argv[1], "reset") == 0) {
    redisContext* c = makeConnection(argv, argc, 2);

    if (c == NULL) {
      return 1;
    }

    // gets list of keys from Redis
    redisReply* r = getAllDirectories(c);
    int i;

    // for each key, print it out along with its
    // value
    for (i = 0; i < r->elements; i++) {
      // get key and value strings
      char* key = r->element[i]->str;
      removeDirectory(c, key);
    }

  } else {
    printf("error: unknown command: see readme for correct commands!\n");
    return 1;
  }

  if (c != NULL) {
    saveAllData(c);
    redisFree(c);
  }

  return 0;
}
