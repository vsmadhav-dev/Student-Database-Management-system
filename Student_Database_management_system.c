#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>

struct student
{
    char name[200];
    int roll;
    char sec[25];
    char addmission_date[12];
    int phnum;
    int classes;
    int serial_number;
    char addmission_numbers[50];
};
FILE *fp;
void add_student();
void clear_input_buffer();
int main()
{

 int ch;
 while(1)
 {
      system("cls");
     printf("\n\n\t************Welcome to student database management system************\n");
     printf("1.Add Student\n");
     printf("2.Delete Student\n");
     printf("3.Modify Student details\n");
     printf("4.Show Students list\n");
     printf("5.Search Student\n");
     printf("0.Exit\n");
     printf("Enter your choice: ");
     if(scanf("%d" , &ch) != 1)
     {
         printf("Enter Number!\n");

         clear_input_buffer();
         continue;
         getch();
     }
     clear_input_buffer();
     switch(ch)
     {
     case 1:
        {
            add_student();
            getch();
            break;
        }
     }
 }
}
void clear_input_buffer() {
    int c;
   while ((c = getchar()) != '\n' && c != EOF) {

    }
}
void add_student()
{
    system("cls");
    printf("\n\n\t********Add Student********\n");
    struct student s;
    fp = fopen("Student.dat" , "ab");
    printf("Enter Serial No. ");
    if(scanf("%d" , s.serial_number ) != 1)
    {
        printf("Enter number!\n");
        clear_input_buffer();
        printf("Press any key to continue...");
        return;


    }
    clear_input_buffer();
}
