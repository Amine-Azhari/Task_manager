#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    char title[20];
    char due_date[20];
    char status[20];
}task;

typedef struct
{
    char category[20];
    float amount;
    char date[20];
    char type[10];
}budget;

typedef struct
{
    char name[20];
    int streak;
    char last_date[20];
}habit;


void displayTasks(task tasks[], int n) {
    system("cls");
    printf("TASKS\n");
    if (tasks == NULL || n == 0)
    {
        printf("NO TASK\n");
        return;
    }
    printf("id  |     title     |    due_date    |    status    |\n");
    for (int i = 0; i < n; i++) {
        printf("%d5  |    %5s    |    %5s    |    %5s    |\n",
               i+1,
               tasks[i].title,
               tasks[i].due_date,
               tasks[i].status);
    }
}

void displayBudgets(budget budgets[], int n) {
    system("cls");
    printf("BUDGETS\n");
    if (budgets == NULL || n == 0)
    {
        printf("NO BUDGET\n");
        return;
    }
    printf("id  |   category   |   amount   |   date   |   type   |\n");
    for (int i = 0; i < n; i++) {
        printf("%d  |   %s   |   %f €   |   %s   |   %s   |\n",
               i+1,
               budgets[i].category,
               budgets[i].amount,
               budgets[i].date,
               budgets[i].type);
    }
}

void displayHabits(habit habits[], int n) {
    system("cls");
    printf("HABITS\n");
    if (habits == NULL || n == 0)
    {
        printf("NO HABIT\n");
        return;
    }
    printf("id   |    name    |   streak   |   last_date   |\n");
    for (int i = 0; i < n; i++) {
        printf("%5d  |   %10s   |   %10d   |   %10s   |\n",
               i+1,
               habits[i].name,
               habits[i].streak,
               habits[i].last_date);
    }
}

int main()
{
        task *tasks = NULL;
        int countTASK = 0;
        budget *budgets = NULL;
        int countBUDGET = 0;
        habit *habits = NULL;
        int countHABIT = 0;

        printf("=== MENU ===\n");
        printf("1. Add task\n");
        printf("2. Display tasks\n");
        printf("3. Add budget\n");
        printf("4. Display budget\n");
        printf("5. Add habit\n");
        printf("6. Display habits\n");
        printf("0. Quitter\n");
        printf(">>");

        int choice;
        scanf(" %d", &choice);
        while (choice != 0)
        {
            switch (choice)
            {
            case 1:
                {
                char title[20];
                char due_date[20];
                printf("enter your task:");
                scanf(" %s", title);
                printf("enter the due date:");
                scanf(" %s", due_date);
                task new_task;
                strcpy(new_task.title, title);
                strcpy(new_task.due_date, due_date);
                strcpy(new_task.status, "UNFINISHED");
                countTASK++;
                task *temp_tasks = realloc(tasks, countTASK * sizeof(task));
                if (temp_tasks == NULL)
                {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                tasks = temp_tasks;
                tasks[countTASK - 1] = new_task;
                break;
                }
            case 2:
                displayTasks(tasks, countTASK);
                break;
            case 3:
                {
                char category[20];
                int amount;
                char date[20];
                char type[10];
                printf("enter the category:");
                scanf(" %s", category);
                printf("enter the amount:");
                scanf(" %f", &amount);
                printf("enter the date:");
                scanf(" %s", date);
                printf("enter the type (In/Out):");
                scanf(" %s", type);
                budget new_budget;
                strcpy(new_budget.category, category);
                strcpy(new_budget.date, date);
                new_budget.amount = amount;
                strcpy(new_budget.type, type);
                countBUDGET++;
                budget *temp_budgets = realloc(budgets, countBUDGET * sizeof(budget));
                if (temp_budgets == NULL)
                {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                budgets = temp_budgets;
                budgets[countBUDGET - 1] = new_budget;
                break;
                }
            case 4:
                displayBudgets(budgets, countBUDGET);
                break;
            case 5:
                {
                char name[20];
                int streak;
                char last_date[20];
                printf("enter your habit:");
                scanf(" %s", name);
                printf("enter the last time played:");
                scanf(" %s", last_date);
                habit new_habit;
                strcpy(new_habit.name, name);
                strcpy(new_habit.last_date, last_date);
                new_habit.streak = 5;
                countHABIT++;
                habit *temp_habits = realloc(habits, countHABIT * sizeof(habit));
                if (temp_habits == NULL)
                {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                habits = temp_habits;
                habits[countHABIT - 1] = new_habit;
                break;
                }
            case 6:
                displayHabits(habits, countHABIT);
                break;
            }

        printf("=== MENU ===\n");
        printf("1. Add task\n");
        printf("2. Display tasks\n");
        printf("3. Add budget\n");
        printf("4. Display budget\n");
        printf("5. Add habit\n");
        printf("6. Display habits\n");
        printf("0. Quitter\n");
        printf(">>");
        scanf(" %d", &choice);
        }

}
