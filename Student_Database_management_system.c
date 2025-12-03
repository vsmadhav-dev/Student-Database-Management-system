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
    char phnum[12];
    int classes;
    int serial_number;
    char addmission_numbers[50];
};

void add_student();
void delete_student();
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
            case 2:
            {
                delete_student();
                getch();
                break;
            }
            case 0:
            {
                printf("\nExiting the system. Goodbye!\n");
                return 0;
            }
            default:
            {
                printf("\nInvalid choice. Please try again.\n");
                getch();
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
    FILE *fp; // Local file pointer

    fp = fopen("Student.dat" , "ab");
    if(fp == NULL)
    {
        printf("Error opening Database (Student.dat) for writing.\n");
        printf("Press any key to continue...");
        return;
    }

    printf("Enter Serial No. ");
    if(scanf("%d" , &s.serial_number ) != 1)
    {
        printf("Enter number!\n");
        clear_input_buffer();
        printf("Press any key to continue...");
        fclose(fp);
        return;
    }
    clear_input_buffer();

    printf("Enter student name: ");
    fgets(s.name , sizeof(s.name) , stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter student class: ");
    if(scanf("%d" , &s.classes) != 1)
    {
        clear_input_buffer();
        printf("Enter student's class!\n");
        printf("Press any key to continue...");
        fclose(fp);
        return;
    }
    clear_input_buffer();

    printf("Enter student's section: ");
    fgets(s.sec , sizeof(s.sec) , stdin);
    s.sec[strcspn(s.sec, "\n")] = 0;

    printf("Enter student roll: ");
    if(scanf("%d" , &s.roll) != 1)
    {
        printf("Enter Roll!\n");
        clear_input_buffer();
        fclose(fp);
        return;
    }
    clear_input_buffer();

    printf("Enter student addmission date: ");
    fgets(s.addmission_date , sizeof(s.addmission_date) , stdin);
    s.addmission_date[strcspn(s.addmission_date, "\n")] = 0;

    printf("Enter student addmission number/id: ");
    fgets(s.addmission_numbers , sizeof(s.addmission_numbers) , stdin);
    s.addmission_numbers[strcspn(s.addmission_numbers, "\n")] = 0;

    printf("Enter student phone number: ");
    fgets(s.phnum , sizeof(s.phnum) , stdin);
    s.phnum[strcspn(s.phnum, "\n")] = 0;

    fwrite(&s , sizeof(s) , 1 ,fp);

    printf("Student added sucessfully\n");
    printf("Press any key to contiue...");
    fclose(fp);
}
void delete_student()
{
    struct student s;
    int class_display;
    char sec_display[25];
    int roll_to_delete;
    int record = 0;
    FILE *fp, *ft; // Local file pointers
    char confirm;

    char input_sec_upper[25];

    system("cls");
    printf("\n\t*********Delete Student********\n");

    printf("Enter Student class to delete from: ");
    if(scanf("%d" , &class_display) != 1)
    {
        clear_input_buffer();
        printf("Enter class!\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    printf("Enter Student section to delete from: ");
    fgets(sec_display, sizeof(sec_display), stdin);
    sec_display[strcspn(sec_display, "\n")] = 0;

    strcpy(input_sec_upper, sec_display);
    for (int i = 0; input_sec_upper[i]; i++) {
        input_sec_upper[i] = toupper(input_sec_upper[i]);
    }

    printf("Enter roll to delete: ");
    if(scanf("%d" , &roll_to_delete) != 1)
    {
        printf("Invalid roll number input. Press any key to continue...");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("\n⚠️ WARNING: Are you sure you want to delete student Roll **%d** from Class **%d**, Section **%s**? (Y/N): ",
             roll_to_delete, class_display, input_sec_upper);

    if (scanf(" %c", &confirm) != 1 || (toupper(confirm) != 'Y' && toupper(confirm) != 'N'))
    {
        clear_input_buffer();
        printf("Invalid confirmation input. Deletion cancelled.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    if (toupper(confirm) == 'N')
    {
        printf("Deletion cancelled by user.\n");
        printf("Press any key to continue...");
        return;
    }

    fp = fopen("Student.dat" , "rb");
    ft = fopen("Temp.dat", "ab");

    if(fp == NULL || ft == NULL)
    {
        printf("Error opening database. Press any key to continue...");
        if (fp) fclose(fp);
        if (ft) fclose(ft);
        return;
    }

    while(fread(&s , sizeof(s) , 1 , fp)== 1)
    {
        char stored_sec_upper[25];
        strcpy(stored_sec_upper, s.sec);
        for (int i = 0; stored_sec_upper[i]; i++) {
            stored_sec_upper[i] = toupper(stored_sec_upper[i]);
        }

        if(s.roll == roll_to_delete &&
             s.classes == class_display &&
             strncmp(stored_sec_upper, input_sec_upper, strlen(input_sec_upper)) == 0)
        {
            record = 1;
        }
        else
        {
            fwrite(&s , sizeof(s) , 1 , ft);
        }
    }

    fclose(fp);

    if(record == 1)
    {
        if(remove("Student.dat") == 0)
        {
            if(rename("Temp.dat" , "Student.dat") == 0)
            {
                printf("\n✅ Student with roll %d deleted successfully.\n" , roll_to_delete);
            }
            else
            {
                printf("\n❌ Error occurred during file rename.\n");
                remove("Temp.dat");
            }
        }
        else
        {
            printf("\n❌ Error occurred while deleting original file.\n");
            remove("Temp.dat");
        }
    }
    else
    {
        remove("Temp.dat");
        printf("\n⚠️ No student found with roll %d, class %d, and section %s to delete.\n" , roll_to_delete, class_display, input_sec_upper);
    }

    fclose(ft);
    printf("Press any key to continue...");
}
