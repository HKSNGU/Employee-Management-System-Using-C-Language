#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

COORD coord = {0, 0};

void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(){
    FILE *fp, *ft;
    char another, choice, count;

    struct emp{
        char name[40];
        int age;
        float salary;
    };
    struct emp e;

    char empName[40];
    long int resize;

    fp = fopen("EMP.DAT", "rb+");

    if(fp == NULL){
        fp = fopen("EMP.DAT", "wb+");
        if(fp == NULL){
            printf("Cannot open file");
            exit(1);
        }
    }

    resize = sizeof(e);

    while(1){
        system("cls");

        gotoxy(30, 10);
        printf("1. Add Record");
        
        gotoxy(30, 12);
        printf("2. List Record");

        gotoxy(30, 14);
        printf("3. Modify Record");

        gotoxy(30, 16);
        printf("4. Delete Record");

        gotoxy(30, 18);
        printf("5. Exit");

        gotoxy(30, 20);
        printf("Your Choice: ");

        fflush(stdin);
        choice = getche();

        switch(choice){
            case '1':
                system("cls");
                fseek(fp, 0, SEEK_END);

                another = 'y';
                while(another == 'y')
                {
                    printf("\n\nEnter name: ");
                    scanf("%s", e.name);
                    printf("\nEnter age: ");
                    scanf("%d", &e.age);
                    printf("\nEnter basic salary: ");
                    scanf("%f", &e.salary);

                    fwrite(&e, resize, 1, fp);
                    printf("\nData entered Successfully...\n");

                    printf("\nAdd another record(y/n) ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '2':
                system("cls");
                rewind(fp);
                printf("\nPress any key for next...\n");
                while(fread(&e, resize, 1, fp) == 1){
                    printf("\n%s %d %.2f", e.name, e.age, e.salary);
                    getch();
                }
                break;
            case '3':
                system("cls");
                another = 'y';
                while(another == 'y'){
                    printf("\n\nEnter the employee name to modify: ");
                    scanf("%s", empName);
                    rewind(fp);
                    count = 0;
                    while(fread(&e, resize, 1, fp) == 1){
                        if(strcmp(e.name, empName) == 0){
                            printf("\nEnter new name, age and basic salary: ");
                            scanf("%s %d %f", e.name, &e.age, &e.salary);
                            fseek(fp, -resize, SEEK_CUR);
                            fwrite(&e, resize, 1, fp);
                            count = 1;
                            break;
                        }
                    }
                    if(count == 1){
                        printf("\nData successfully modified...\n");
                    }
                    else{
                        printf("\nNo employee found for the name %s, try again...\n", empName);
                    }
                    printf("\nModify another record(y/n) ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '4':
                system("cls");
                another = 'y';
                while (another == 'y'){
                    printf("\n\nEnter name of employee to delete: ");
                    scanf("%s", empName);
                    ft = fopen("Temp.dat", "wb");
                    rewind(fp);
                    count = 0;
                    while(fread(&e, resize, 1, fp)){
                        if(strcmp(e.name, empName) != 0){
                            fwrite(&e, resize, 1, ft);
                        }
                        else count = 1;
                    }
                    if(count == 0) printf("\nNo employee found for the name %s, try again...\n", empName);
                    else printf("\nData successfully deleted...\n");
                    fclose(fp);
                    fclose(ft);
                    remove("EMP.DAT");
                    rename("Temp.dat", "EMP.DAT");
                    fp = fopen("EMP.DAT", "rb+");
                    printf("\nDelete another record(y/n) ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '5':
                fclose(fp);
                exit(0);
        }
    }
}