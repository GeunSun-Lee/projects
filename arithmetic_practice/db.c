#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "db.h"

static int _print_cb(void *NU, int argc, char **argv, char **azColName)
{
	int i = 0;
	for (i = 0; i < argc; i++) {
		if (azColName[i] == NULL) continue;

		if (strncmp(azColName[i], "name", strlen(azColName[i])) == 0) {
			continue;
		}

		if (strncmp(azColName[i], "date", strlen(azColName[i])) == 0) {
			printf("|%s|", argv[i]);
		}

		if (strncmp(azColName[i], "score", strlen(azColName[i])) == 0) {
			int score = atoi(argv[i]) / 5;
			int j = 0;

			printf("[");
			for (j = 0; j < score; j++) {
				printf("■ ");
			}

			for (j = 0; j < COUNT - score; j++) {
				printf("□ ");
			}
			printf("]|%3d|\n", score * 5);
		}
	}

	return 0;
}

static int _exec_query(sqlite3 *db, char *sql)
{
	char *err_msg = NULL;
	int rc = 0;

	if (db == NULL) {
		printf("[ERR] DB is NULL\n");
		return -1;
	}

	if (sql == NULL) {
		printf("[ERR] sql is NULL\n");
		return -1;
	}

	rc = sqlite3_exec(db, sql, NULL, NULL, &err_msg);
	if (rc != SQLITE_OK) {
		printf("[ERR] Failed to execute SQL: %s\n", err_msg);
		free(err_msg);
		return -1;
	}

	free(err_msg);

	return 0;
}

int connect_db(sqlite3 **db)
{
	int rc = 0;
	char *sql = NULL;

	if (*db != NULL) {
		close_db(*db);
	}

	rc = sqlite3_open(DB_FILE, &(*db));

	if (rc != SQLITE_OK) {
		printf("[ERR] Failed to open a DB: %s\n", sqlite3_errmsg(*db));
		return -1;
	}

	return 0;
}

int close_db(sqlite3 *db)
{
	int rc = 0;

	if (db == NULL) {
		printf("[ERR] DB is NULL\n");
		return -1;
	}

	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) {
		printf("[ERR] Failed to close a DB: %s\n", sqlite3_errmsg(db));
		return -1;
	}

	db = NULL;

	return 0;
}

int insert_db(sqlite3 *db, int score, char *date)
{
	char sql[512] = { 0, };
	int ret = 0, rc = 0;

    if (db == NULL) {
        printf("[ERR] DB is NULL\n");
        return -1;
    }

    if (date == NULL) {
        printf("[ERR] date is NULL\n");
        return -1;
    }

	snprintf(sql, sizeof(sql), "CREATE TABLE IF NOT EXISTS  %s\
			(id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, \
             name TEXT,\
			 date TEXT NOT NULL,\
			 score INTEGER NOT NULL);\
			INSERT INTO %s(name, date, score)\
			VALUES('%s', '%s', %d);",
			DB_TABLE_NAME, DB_TABLE_NAME, USER_NAME, date, score * 5);

    rc = _exec_query(db, sql);
    if (rc == -1) {
        printf("[ERR] Failed to initialize a DB\n");
        return -1;
    }

    return 0;
}

int print_last_items(sqlite3 *db, int count)
{
	char sql[512] = { 0, };
	char *err_msg = NULL;

	int rc = 0;

	printf(" ================================================================ \n");
	printf(" \t\t\t\tHISTORY\n");
	printf(" ================================================================ \n");

	snprintf(sql, sizeof(sql), "SELECT * FROM %s\
			ORDER BY ROWID DESC LIMIT %d;",
			DB_TABLE_NAME, count);

	rc = sqlite3_exec(db, sql, _print_cb, NULL, &err_msg);
	if (rc != SQLITE_OK) {
		printf("[ERR] Failed to execute SQL: %s\n", err_msg);
		free(err_msg);
		return -1;
	}
	free(err_msg);

	return 0;
}
