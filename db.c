#include "db.h"
#include <stdio.h>

int init_db(sqlite3 **db) {
    if (sqlite3_open("cms.db", db)) {
        printf("Cannot open database\n");
        return 0;
    }

    const char *sql =
        "CREATE TABLE IF NOT EXISTS posts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "title TEXT,"
        "content TEXT,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char *err = 0;
    if (sqlite3_exec(*db, sql, 0, 0, &err)) {
        printf("SQL error: %s\n", err);
        sqlite3_free(err);
        return 0;
    }

    return 1;
}

void close_db(sqlite3 *db) {
    sqlite3_close(db);
}

int create_post(sqlite3 *db, const char *title, const char *content) {
    char sql[512];
    sprintf(sql, "INSERT INTO posts (title, content) VALUES ('%s','%s');", title, content);
    return sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK;
}

int list_posts(sqlite3 *db) {
    const char *sql = "SELECT id, title, created_at FROM posts;";
    sqlite3_stmt *stmt;

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    printf("\nPosts:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("ID: %d | Title: %s | Created: %s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2));
    }

    sqlite3_finalize(stmt);
    return 1;
}

int get_post(sqlite3 *db, int id) {
    char sql[256];
    sprintf(sql, "SELECT title, content FROM posts WHERE id=%d;", id);

    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        printf("\nTitle: %s\nContent: %s\n",
               sqlite3_column_text(stmt, 0),
               sqlite3_column_text(stmt, 1));
    } else {
        printf("Post not found\n");
    }

    sqlite3_finalize(stmt);
    return 1;
}

int update_post(sqlite3 *db, int id, const char *title, const char *content) {
    char sql[512];
    sprintf(sql, "UPDATE posts SET title='%s', content='%s' WHERE id=%d;",
            title, content, id);
    return sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK;
}

int delete_post(sqlite3 *db, int id) {
    char sql[256];
    sprintf(sql, "DELETE FROM posts WHERE id=%d;", id);
    return sqlite3_exec(db, sql, 0, 0, 0) == SQLITE_OK;
}
