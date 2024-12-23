
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

//============> mnue
COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgColor << 4) | textColor);
}

void hideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void displayM(int selected)
{
    char arr[5][20] =
    {
        "Add Student",
        "Update Student",
        "Calculate Grades",
        "Display Results",
        "exit"
    };
    int n = 5;
    gotoxy(0,0);
    for (int i = 0; i < n; i++)
    {
        gotoxy(50, i+6);

        if (i == selected)
        {
            SetColor(12,0);
            printf(" %s \n", arr[i]);
        }
        else
        {
            SetColor(7,0);
            printf(" %s \n", arr[i]);
        }
    }
}

void displayP()
{
    gotoxy(30, 0);
    SetColor(12, 0);
    printf("=====================================================\n\n");
    SetColor(7, 0);
    gotoxy(30, 2);
    printf("\t\t\tAmira Ahmed Hashem\t\t");
    gotoxy(30, 4);
    SetColor(12, 0);
    printf("=====================================================\n");
}

//========>add student
struct Students
{
    int id;
    char name[10];
    double *scores;
    char **subjects;
    int numSubject;
};
typedef struct Students student;


void addStudents(student **s1, int *studentCount) {
    *s1 = (student *)realloc(*s1, (*studentCount + 1) * sizeof(student));
    student *newStudent = &(*s1)[*studentCount];
    system("cls");
    gotoxy(30, 0);
    SetColor(12, 0);
    printf("============= Add Student =============\n\n");
    SetColor(7, 0);

    printf("Enter student ID: ");
    scanf("%d", &newStudent->id);
    printf("Enter student name: ");
    scanf(" %s", newStudent->name);

    printf("Enter number of subjects: ");
    scanf("%d", &newStudent->numSubject);


    newStudent->subjects = (char **)malloc(newStudent->numSubject * sizeof(char *));
    newStudent->scores = (double *)malloc(newStudent->numSubject * sizeof(double));

    for (int i = 0; i < newStudent->numSubject; i++) {
        newStudent->subjects[i] = (char *)malloc(30 * sizeof(char));
        printf("Enter subject %d name: ", i + 1);
        scanf(" %s", newStudent->subjects[i]);
        printf("Enter score for %s: ", newStudent->subjects[i]);
        scanf("%lf", &newStudent->scores[i]);
    }

    (*studentCount)++;
    printf("Student added successfully!\n");
    printf("Press any key to continue...\n");
    getch();
}

void updata(student *s1, int studentCount) {
    system("cls");
    gotoxy(30, 0);
    SetColor(12, 0);
    printf("============= Update Student =============\n\n");
    SetColor(7, 0);

    int id;
    printf("Enter the ID of the student to update: ");
    scanf("%d", &id);

    int found = -1;
    for (int i = 0; i < studentCount; i++) {
        if (s1[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("No student found with this ID.\n");
        printf("Press any key to return to the menu...\n");
        getch();
        return;
    }

    printf("[1] Edit name\n[2] Edit subjects\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter new name: ");
        scanf(" %s", s1[found].name);
        printf("Name updated successfully!\n");
    } else if (choice == 2) {

        for (int i = 0; i < s1[found].numSubject; i++) {
            free(s1[found].subjects[i]);
        }
        free(s1[found].subjects);
        free(s1[found].scores);

        printf("Enter new number of subjects: ");
        scanf("%d", &s1[found].numSubject);


        s1[found].subjects = (char **)malloc(s1[found].numSubject * sizeof(char *));
        s1[found].scores = (double *)malloc(s1[found].numSubject * sizeof(double));

        for (int i = 0; i < s1[found].numSubject; i++) {
            s1[found].subjects[i] = (char *)malloc(30 * sizeof(char));
            printf("Enter subject %d name: ", i + 1);
            scanf(" %s", s1[found].subjects[i]);
            printf("Enter score for %s: ", s1[found].subjects[i]);
            scanf("%lf", &s1[found].scores[i]);
        }

        printf("Subjects and scores updated successfully!\n");
    }
    getch();
}

void calc(student *s1, int studentCount) {
    system("cls");
    gotoxy(30, 0);
    SetColor(12, 0);
    printf("============= Calculate Grades =============\n\n");
    SetColor(7, 0);
    double sum = 0, average;
    for (int i = 0; i < studentCount; i++) {
        // ===========> sum for each student
        sum = 0;
        for (int j = 0; j < s1[i].numSubject; j++) {
            sum += s1[i].scores[j];
        }

        average = sum / s1[i].numSubject;

        char grade;
        if (average >= 90) {
            grade = 'A';
        } else if (average >= 80) {
            grade = 'B';
        } else if (average >= 70) {
            grade = 'C';
        } else if (average >= 60) {
            grade = 'D';
        } else {
            grade = 'F';
        }

        printf("Student ID: %d\n", s1[i].id);
        printf("Name: %s\n", s1[i].name);
        printf("Average Score: %.2f\n", average);
        printf("Grade: %c\n\n", grade);
    }
    printf("Press any key to return to the menu...\n");
    getch();
}

int main() {
    int studentCount = 0;
    student *s1 = NULL;

    int selected = 0;
    int n = 5;
    char ch;
    hideCursor();

    while (1) {
        system("cls");
        displayP();
        displayM(selected);

        ch = getch();
        if (ch == -32) {
            ch = getch();
            switch (ch) {
                case 72:
                    selected = (selected - 1 + n) % n;
                    break;
                case 80:
                    selected = (selected + 1) % n;
                    break;
            }
        } else if (ch == 13) {
            if (selected == 0) {
                addStudents(&s1, &studentCount);
            } else if (selected == 1) {
                updata(s1, &studentCount);
            } else if (selected == 2) {
                calc(s1, &studentCount);
            } else if (selected == 3) {
                for (int i = 0; i < studentCount; i++) {
                    printf("Student ID: %d\n", s1[i].id);
                    printf("Name: %s\n", s1[i].name);
                    double total = 0;
                    for (int j = 0; j < s1[i].numSubject; j++) {
                        total += s1[i].scores[j];
                    }
                    double average = total / s1[i].numSubject;
                    printf("Average Score: %.2f\n", average);
                    if(total<=50)
                    {
                        SetColor(12,0);
                        printf("failer");
                    }
                    else if(total>50 &&total <=100)
                    {
                         SetColor(13, 0);
                        printf("succes");
                    }
                }
                getch();
            }
            else if(selected == 4){
                    SetColor(13,0);
                    return 0;

            }
        }
    }

    return 0;
}
