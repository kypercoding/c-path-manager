#include <hiredis/hiredis.h>
#include <string.h>
#include <unistd.h>

#include "db.h"


/**
 * Add a file directory to the Redis database via context.
*/
void addDirectory (redisContext *c, char *key, char *path) {
    if (strcmp(path, ".") == 0) {
        char *cwd;
        redisCommand(c, "SET directories:%s %s", key, getcwd(cwd, 0));
        return;
    }

    redisCommand(c, "SET directories:%s %s", key, path);
}

/**
 * Get a file directory associated with key.
*/
char* getDirectory(redisContext *c, char *key) {
    // declare a reply object
    redisReply *reply;

    // initialize reply object to result of GET command
    if (strstr(key, "directories:") != NULL) {
        reply = redisCommand(c, "GET %s", key);
    } else {
        reply = redisCommand(c, "GET directories:%s", key);
    }

    // return path in char* form
    return reply->str;
}

/**
 * Remove a file directory from the Redis database
 * given a key.
*/
void removeDirectory (redisContext *c, char *key) {
    if (strstr(key, "directories:") != NULL) {
        redisCommand(c, "DEL %s", key);
    } else {
        redisCommand(c, "DEL directories:%s", key);
    }
}

/**
 * Get a list of file directories from the Redis
 * database.
*/
redisReply* getAllDirectories(redisContext *c) {
    redisReply* reply = redisCommand(c, "KEYS directories:*");
    return reply;
}

/**
 * Save all data in the background.
*/
void saveAllData(redisContext *c) {
    redisCommand(c, "BGSAVE");
}
