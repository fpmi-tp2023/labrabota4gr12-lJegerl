#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
        for(int i = 0; i < argc; i++) {
           printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
}

int main(int argc, char* argv[]) {
        sqlite3* db;
        char *zErrMsg = 0;
        int rc;
        char *sql;

        rc = sqlite3_open("lab4.db", &db);

        if(rc) {
           fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
           return 0;
        } else {
           fprintf(stdout, "Opened database successfully\n");
        }

        sql = "INSERT INTO UNIVERSITY (ID,NAME,AGE,ADDRESS,SALARY) " \
	      "VALUES (1, 'Yegor', 20, 'Zhodino', 100.00 ); " \
	      "INSERT INTO UNIVERSITY (ID,NAME,AGE,ADDRESS,SALARY) " \
              "VALUES (2, 'Dima', 21, 'Lido', 150.00 ); " \
	      "INSERT INTO UNIVERSITY (ID,NAME,AGE,ADDRESS,SALARY) " \
              "VALUES (3, 'Denis', 19, 'Minsk', 0.00 ); " \
	      "INSERT INTO UNIVERSITY (ID,NAME,AGE,ADDRESS,SALARY) " \
              "VALUES (4, 'Nikita', 20, 'Minsk', 300.00 );";

        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

        if(rc != SQLITE_OK) {
           fprintf(stderr, "SQL error: %s\n", zErrMsg);
        } else {
	   fprintf(stdout, "Created records successfully\n");
	}
}

