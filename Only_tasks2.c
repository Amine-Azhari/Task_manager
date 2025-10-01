#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"


sqlite3 *db;

int initDB()
{
    char *err_msg = 0;
    int rc = sqlite3_open("tasks.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Impossible d'ouvrir la base %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS tasks ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "title TEXT NOT NULL,"
                      "due_date TEXT NOT NULL,"
                      "status TEXT DEFAULT 'PENDING');";

    rc = sqlite3_exec(db, sql, 0,0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur SQL %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;
    }
    return 0;
}


//Rajouter une tache
void addTask(const char *title, const char *due_date)
{
    char sql[256];
    sprintf(sql, "INSERT INTO tasks (title, due_date) VALUES ('%s', '%s');", title, due_date);

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0,0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur lors de l'ajout: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else {printf("Tache ajoutée avec succès.\n");}
}


int displayCallback(void *NotUsed, int argc, char **argv, char **colName)
{
    for (int i=0; i < argc; i++)
    {
        printf("%s: %s\t", colName[i], argv[i] ? argv[i] : NULL); //condition ? valeur si vrai : valeur si faux
    }

    printf("\n");
    return 0;
}

void displayTasks()
{
    const char *sql = "SELECT * FROM tasks;";
    char *err_msg = 0;

    int rc = sqlite3_exec(db, sql, displayCallback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Erreur SQL: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}



int main()
{
        if (initDB() != 0) return 1;

        int choice;
        do
        {
            printf("=== MENU ===\n");
            printf("1. Add task\n");
            printf("2. Display tasks\n");
            printf("0. Quitter\n");
            printf(">>");
            scanf("%d", &choice);

            if (choice == 1)
            {
                char title[50], due_date[20];
                printf("Enter your task: ");
                scanf("%s", title);
                printf("Enter the due date: ");
                scanf("%s", due_date);
                addTask(title, due_date);
            }
            else if (choice == 2)
            {
                displayTasks();
            }
        }while (choice != 0);

        sqlite3_close(db);
        return 0;

}
