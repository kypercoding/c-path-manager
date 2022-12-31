#include <hiredis/hiredis.h>


/**
 * Add a file directory to the Redis database via context.
*/
void addDirectory (redisContext *c, char *key, char *path);

/**
 * Get a file directory associated with key.
*/
char* getDirectory(redisContext *c, char *key);

/**
 * Remove a file directory from the Redis database
 * given a key.
*/
void removeDirectory (redisContext *c, char *key);

/**
 * Get a list of file directories from the Redis
 * database.
*/
redisReply* getAllDirectories(redisContext *c);

/**
 * Save all data in the background.
*/
void saveAllData(redisContext *c);
