#if !defined(__DB_H__)
#define __DB_H__

#include <sqlite3.h>

#include "config.h"

int connect_db(sqlite3 **db);
int close_db(sqlite3 *db);
int insert_db(sqlite3 *db, int score, char *date);
int print_last_items(sqlite3 *db, int count);

#endif //__DB_H__
