#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#pragma pack(push, 1)
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
void modify_student();
void show_students();
void search_student();
void clear_input_buffer();
void to_upper_case(char *str);

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
            printf("\n\nInvalid input. Please enter a number!\n");
            clear_input_buffer();
            getch();
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
            case 3:
            {
                modify_student();
                getch();
                break;
            }
            case 4:
            {
                show_students();
                getch();
                break;
            }
            case 5:
            {
                search_student();
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

void to_upper_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

void add_student()
{
    system("cls");
    printf("\n\n\t********Add Student********\n");
    struct student s;
    FILE *fp;

    fp = fopen("Student.dat" , "ab");
    if(fp == NULL)
    {
        printf("\nError opening Database (Student.dat) for writing.\n");
        printf("Press any key to continue...");
        return;
    }

    printf("Enter Serial No. (e.g., 1): ");
    if(scanf("%d" , &s.serial_number ) != 1)
    {
        printf("\nInvalid input. Please enter a number for Serial No.\n");
        clear_input_buffer();
        printf("Press any key to continue...");
        fclose(fp);
        return;
    }
    clear_input_buffer();

    printf("Enter student name: ");
    fgets(s.name , sizeof(s.name) , stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter student class (e.g., 10): ");
    if(scanf("%d" , &s.classes) != 1)
    {
        clear_input_buffer();
        printf("\nInvalid input. Please enter a number for class.\n");
        printf("Press any key to continue...");
        fclose(fp);
        return;
    }
    clear_input_buffer();

    printf("Enter student's section (e.g., A): ");
    fgets(s.sec , sizeof(s.sec) , stdin);
    s.sec[strcspn(s.sec, "\n")] = 0;
    to_upper_case(s.sec);

    printf("Enter student roll: ");
    if(scanf("%d" , &s.roll) != 1)
    {
        printf("\nInvalid input. Please enter a number for Roll.\n");
        clear_input_buffer();
        fclose(fp);
        return;
    }
    clear_input_buffer();

    printf("Enter student admission date (DD-MM-YYYY): ");
    fgets(s.addmission_date , sizeof(s.addmission_date) , stdin);
    s.addmission_date[strcspn(s.addmission_date, "\n")] = 0;

    printf("Enter student admission number/id: ");
    fgets(s.addmission_numbers , sizeof(s.addmission_numbers) , stdin);
    s.addmission_numbers[strcspn(s.addmission_numbers, "\n")] = 0;

    printf("Enter student phone number (10 digits): ");
    fgets(s.phnum , sizeof(s.phnum) , stdin);
    s.phnum[strcspn(s.phnum, "\n")] = 0;

    fwrite(&s , sizeof(s) , 1 ,fp);

    printf("\nStudent added successfully!\n");
    printf("Press any key to continue...");
    fclose(fp);
}

void delete_student()
{
    struct student s;
    int class_display;
    char sec_display[25];
    int roll_to_delete;
    int record = 0;
    FILE *fp, *ft;
    char confirm;
    char input_sec_upper[25];

    system("cls");
    printf("\n\t*********Delete Student********\n");

    printf("Enter Student class to delete from: ");
    if(scanf("%d" , &class_display) != 1)
    {
        clear_input_buffer();
        printf("\nInvalid input. Please enter a number for class.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    printf("Enter Student section to delete from: ");
    fgets(sec_display, sizeof(sec_display), stdin);
    sec_display[strcspn(sec_display, "\n")] = 0;

    strcpy(input_sec_upper, sec_display);
    to_upper_case(input_sec_upper);

    printf("Enter roll to delete: ");
    if(scanf("%d" , &roll_to_delete) != 1)
    {
        printf("\nInvalid roll number input. Press any key to continue...");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    printf("\nWARNING: Are you sure you want to delete student Roll %d from Class %d, Section %s? (Y/N): ",
             roll_to_delete, class_display, input_sec_upper);

    if (scanf(" %c", &confirm) != 1 || (toupper(confirm) != 'Y' && toupper(confirm) != 'N'))
    {
        clear_input_buffer();
        printf("\nInvalid confirmation input. Deletion cancelled.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    if (toupper(confirm) == 'N')
    {
        printf("\nDeletion cancelled by user.\n");
        printf("Press any key to continue...");
        return;
    }

    fp = fopen("Student.dat" , "rb");
    ft = fopen("Temp.dat", "wb");

    if(fp == NULL || ft == NULL)
    {
        printf("\nError opening database. Press any key to continue...");
        if (fp) fclose(fp);
        if (ft) fclose(ft);
        return;
    }

    while(fread(&s , sizeof(s) , 1 , fp) == 1)
    {
        if(s.roll == roll_to_delete &&
             s.classes == class_display &&
             strcmp(s.sec, input_sec_upper) == 0)
        {
            record = 1;
        }
        else
        {
            fwrite(&s , sizeof(s) , 1 , ft);
        }
    }

    fclose(fp);
    fclose(ft);

    if(record == 1)
    {
        if(remove("Student.dat") == 0)
        {
            if(rename("Temp.dat" , "Student.dat") == 0)
            {
                printf("\nStudent with roll %d deleted successfully.\n" , roll_to_delete);
            }
            else
            {
                printf("\nError occurred during file rename.\n");
                remove("Temp.dat");
            }
        }
        else
        {
            printf("\nError occurred while deleting original file (Student.dat).\n");
            remove("Temp.dat");
        }
    }
    else
    {
        remove("Temp.dat");
        printf("\nNo student found with roll %d, class %d, and section %s to delete.\n" , roll_to_delete, class_display, input_sec_upper);
    }

    printf("Press any key to continue...");
}

void modify_student()
{
    struct student s;
    int class_to_modify;
    char sec_to_modify[25];
    int roll_to_modify;
    long offset;
    int found = 0;
    char input_sec_upper[25];
    FILE *fp;

    system("cls");
    printf("\n\t*********Modify Student Details********\n");

    printf("Enter Student Class to modify: ");
    if(scanf("%d" , &class_to_modify) != 1)
    {
        clear_input_buffer();
        printf("\nInvalid input. Please enter a number for class.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    printf("Enter Student Section to modify: ");
    fgets(sec_to_modify, sizeof(sec_to_modify), stdin);
    sec_to_modify[strcspn(sec_to_modify, "\n")] = 0;
    strcpy(input_sec_upper, sec_to_modify);
    to_upper_case(input_sec_upper);

    printf("Enter Roll Number to modify: ");
    if(scanf("%d" , &roll_to_modify) != 1)
    {
        clear_input_buffer();
        printf("\nInvalid input. Please enter a number for Roll.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    fp = fopen("Student.dat" , "r+b");
    if(fp == NULL)
    {
        printf("\nError opening database (Student.dat) for modification.\n");
        printf("Press any key to continue...");
        return;
    }

    while(fread(&s , sizeof(s) , 1 , fp) == 1)
    {
        if(s.roll == roll_to_modify &&
             s.classes == class_to_modify &&
             strcmp(s.sec, input_sec_upper) == 0)
        {
            found = 1;
            offset = ftell(fp) - sizeof(s);

            printf("\n--- Current Details of Roll %d, Class %d, Section %s ---\n", s.roll, s.classes, s.sec);
            printf("Name: %s\n", s.name);
            printf("Admission ID: %s\n", s.addmission_numbers);
            printf("Phone: %s\n", s.phnum);
            printf("----------------------------------------------------------\n");

            printf("\nEnter New Details:\n");

            printf("Enter new student name: ");
            fgets(s.name , sizeof(s.name) , stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter new student class (%d): ", s.classes);
            if(scanf("%d" , &s.classes) != 1)
            {
                clear_input_buffer();
                printf("Error reading class. Modification cancelled.\n");
                found = 0;
                break;
            }
            clear_input_buffer();

            printf("Enter new student's section (%s): ", s.sec);
            fgets(s.sec , sizeof(s.sec) , stdin);
            s.sec[strcspn(s.sec, "\n")] = 0;
            to_upper_case(s.sec);

            printf("Enter new student roll (%d): ", s.roll);
            if(scanf("%d" , &s.roll) != 1)
            {
                clear_input_buffer();
                printf("Error reading roll. Modification cancelled.\n");
                found = 0;
                break;
            }
            clear_input_buffer();

            printf("Enter new student admission date (%s): ", s.addmission_date);
            fgets(s.addmission_date , sizeof(s.addmission_date) , stdin);
            s.addmission_date[strcspn(s.addmission_date, "\n")] = 0;

            printf("Enter new student admission number/id (%s): ", s.addmission_numbers);
            fgets(s.addmission_numbers , sizeof(s.addmission_numbers) , stdin);
            s.addmission_numbers[strcspn(s.addmission_numbers, "\n")] = 0;

            printf("Enter new student phone number (%s): ", s.phnum);
            fgets(s.phnum , sizeof(s.phnum) , stdin);
            s.phnum[strcspn(s.phnum, "\n")] = 0;

            fseek(fp , offset , SEEK_SET);

            fwrite(&s , sizeof(s) , 1 , fp);

            printf("\nStudent details modified successfully!\n");
            break;
        }
    }

    if(found == 0)
    {
        printf("\nNo student found with roll %d, class %d, and section %s.\n" , roll_to_modify, class_to_modify, input_sec_upper);
    }

    fclose(fp);
    printf("Press any key to continue...");
}

void show_students()
{
    struct student s;
    int count = 0;
    FILE *fp;

    system("cls");
    printf("\n\t*********Student List********\n\n");

    fp = fopen("Student.dat" , "rb");
    if(fp == NULL)
    {
        printf("Error opening database (Student.dat) for reading.\n");
        printf("Press any key to continue...");
        return;
    }

    printf("+------+----------------------+-------+------+-------+-----------+----------------+\n");
    printf("| S.No | Name                 | Class | Sec. | Roll  | Phone     | Admission ID   |\n");
    printf("+------+----------------------+-------+------+-------+-----------+----------------+\n");

    while(fread(&s , sizeof(s) , 1 , fp) == 1)
    {
        printf("| %-4d | %-20s | %-5d | %-4s | %-5d | %-9s | %-14s |\n",
               s.serial_number, s.name, s.classes, s.sec, s.roll, s.phnum, s.addmission_numbers);
        count++;
    }

    printf("+------+----------------------+-------+------+-------+-----------+----------------+\n");

    if (count == 0)
    {
        printf("\n\t\t\tDatabase is empty.\n");
    }
    else
    {
        printf("\nTotal Students in Database: %d\n", count);
    }

    fclose(fp);
    printf("Press any key to continue...");
}

void search_student()
{
    struct student s;
    int roll_to_search;
    int class_to_search;
    char sec_to_search[25];
    int found = 0;
    char input_sec_upper[25];
    FILE *fp;

    system("cls");
    printf("\n\t*********Search Student********\n");

    printf("Enter Student Class to search: ");
    if(scanf("%d" , &class_to_search) != 1)
    {
        clear_input_buffer();
        printf("\nInvalid input. Please enter a number for class.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    printf("Enter Student Section to search: ");
    fgets(sec_to_search, sizeof(sec_to_search), stdin);
    sec_to_search[strcspn(sec_to_search, "\n")] = 0;
    strcpy(input_sec_upper, sec_to_search);
    to_upper_case(input_sec_upper);

    printf("Enter Roll Number to search: ");
    if(scanf("%d" , &roll_to_search) != 1)
    {
        clear_input_buffer();
        printf("\nInvalid input. Please enter a number for Roll.\n");
        printf("Press any key to continue...");
        return;
    }
    clear_input_buffer();

    fp = fopen("Student.dat" , "rb");
    if(fp == NULL)
    {
        printf("\nError opening database (Student.dat) for reading.\n");
        printf("Press any key to continue...");
        return;
    }

    while(fread(&s , sizeof(s) , 1 , fp) == 1)
    {
        if(s.roll == roll_to_search &&
             s.classes == class_to_search &&
             strcmp(s.sec, input_sec_upper) == 0)
        {
            found = 1;
            printf("\nStudent Found!\n");
            printf("----------------------------------------------------------\n");
            printf("Serial No:        %d\n", s.serial_number);
            printf("Name:             %s\n", s.name);
            printf("Class/Section:    %d/%s\n", s.classes, s.sec);
            printf("Roll Number:      %d\n", s.roll);
            printf("Admission ID:     %s\n", s.addmission_numbers);
            printf("Admission Date:   %s\n", s.addmission_date);
            printf("Phone Number:     %s\n", s.phnum);
            printf("----------------------------------------------------------\n");
            break;
        }
    }

    if(found == 0)
    {
        printf("\nNo student found with roll %d, class %d, and section %s.\n" , roll_to_search, class_to_search, input_sec_upper);
    }

    fclose(fp);
    printf("Press any key to continue...");
}
