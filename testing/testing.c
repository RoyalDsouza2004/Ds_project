/*
    Team members:
        Royal dsouza
        Poornesh Nayak

    Project name : attendance

    Description: This program helps the teacher to take the attendance very easily just he/she has
    to put the absentees seat number to make the student absent.
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int rows=0 , seats=0 , n=1 ;
float days = 0.0 ;

//creating a structure for storing student details.
typedef struct student_details
{
    char std_name[20];
    char Usn[11];
    long long phone;
    int present ;
    int absent;
    bool book_seat ;
    char day[60];
}student;

student *class;

int store_to_txtfile()
{
    FILE *att;
    att = fopen("class.txt" , "w");
    if(!att)
    {
        printf("error while exiting the program your data maybe lost.:( ");
        return 1;
    }

    fprintf(att , "%d,%d,%g\n" , rows , seats , days );

    for(int i=0 ; i<(rows * seats) ; i++)
    { 
        fprintf(att , "%s,%s,%lld,%d,%d,%s,%d\n" , class[i].std_name ,class[i].Usn , class[i].phone , class[i].present , class[i].absent , class[i].day , class[i].book_seat);
    }

    fclose(att);
    return 0;
}

void get_from_txtfile()
{
    
    FILE *data;

    data = fopen("class.txt" , "r");

    if(data == NULL || !data)
    return;

    fscanf(data , "%d,%d,%g\n" , &rows , &seats , &days);

    class = (student*) malloc(rows * seats * sizeof(student));

    int bol ;
    int records = 0 , read = 0;
    do
    {
        read = fscanf(data , "%19[^,],%10[^,],%lld,%d,%d,%59[^,],%d\n", class[records].std_name , class[records].Usn , &class[records].phone , &class[records].present , &class[records].absent , class[records].day , &bol );
        if(bol == 0)
            class[records].book_seat = false ;
        else 
            class[records].book_seat = true ;
        if(read == 7)
            records++;

        if(read != 7 && !feof(data))
        {
            printf("not success.\n");
            exit(1);
        }
        if(ferror(data))
        {
            printf("not success.\n");
            exit(1);
        }
    }while (!feof(data));

    fclose(data);
}

//creating a class structure.
void create(int rows , int column)
{
    class = (student*) malloc(rows * column * sizeof(student)); // dynamically allocating array of structures.
    for(int i=0 ; i<(rows* column) ; i++)
    {
        strcpy(class[i].std_name , "no name");
        strcpy(class[i].Usn , "mite");
        class[i].phone = 0;
        class[i].present = 0;
        class[i].absent = 0;
        class[i].book_seat = false ;
        strcpy(class[i].day , "D");
    }
}

// taking the attendance.
void attendance(student *s)
{
    days++;
    int ab ;
    printf("Enter the number of students absent for the class: ");
    scanf("%d" , &ab);

    int  seat_num[ab];

    printf("\n*********************************************************\n");
    for(int i=0 ; i<rows ; i++)
    {
        for(int j=0 ; j< seats ; j++) 
        {
            printf("%d\t", n++);
        }
        printf("\n\n");
    }
    printf("**************************************************************\n");
    n = 1;

    printf("Enter the absentees seat numbers in order: (i.e increasing order like 1 2 3 etc...)\n");
    for(int i=0 ; i<ab ; i++)
    {
        printf("Student %d: " , i + 1);
        scanf("%d" , &seat_num[i]);
    }
    int j = 0 , in = 1;

    while(in <=(rows*seats))
    {
        if(s[in-1].book_seat == false)
        {
            s[in-1].absent++;
            strcat(s[in-1].day , "A");
            in++;
        }
        else
        {
            if(in == seat_num[j])
            {
                s[in-1].absent++; //this line will make student absent 
                strcat(s[in-1].day , "A");
                j++;
            }
            else 
            {
                s[in-1].present++; //this line will make student present
                strcat(s[in-1].day , "P");
            }  
            in++;
        }   
    }
}


// student details will be displayed here.
void display_std_details(student *s)
{
    printf("\nStudent details are : \n");

    printf("Name : %s\n" , s -> std_name); 

    printf("USN: %s\n" , s -> Usn);

    printf("Phone number: %lld\n" , s -> phone);

    printf("Number of days present: %d\n" , s -> present);

    if(days == 0)
        printf("percentage: 0 ( because no class is taken)\n");
    else
        printf("Percentage: %.2f%c\n" , ((s -> present) / days) * 100 , '%');

    printf("Number of days absent: %d\n\n" , s -> absent);

}

// giving student to choose his / her seat
void seat_register(student *st, char name[20], char usn[10], long long phone )
{
    strcpy(st -> std_name , name);
    strcpy(st -> Usn , usn);
    st -> phone = phone ;
    st -> book_seat = true; 
}

void all_std_details()
{
    printf("all student details:\nseat number  name                  usn         ");
    for(int i = 1 ; i <= days ; i++)
        printf("day%d ", i);
    printf("  present  absent  present(%c)\n" , '%');

    for(int i = 0 ; i< (rows * seats) ; i++)
    {
        if(class[i].book_seat == true)
        {
            printf("%-11d  %-20s  %-10s  " , i+1 , class[i].std_name , class[i].Usn);
            for(int j = 1 ; j<= days ; j++)
            {
                printf("%4c " , class[i].day[j]);
            }
            printf("  %7d  %6d  %10.2f\n" , class[i].present , class[i].absent , ((class[i].present) / days) * 100);  
        } 
    }   
}

int main()
{
    get_from_txtfile();

    int choice , class_seat = 0 ;

    main_menu:
    printf("1:Administrator.\n2:student.\n3:exit.\nEnter the choice: "); // main menu
    scanf("%d", &choice);

    do
    {

        switch(choice)
        {
            case 1:
                int ch1;
                while(1)
                {
                    printf("1:take the attendance.\n2:check student details.\n3:create the class.\n4:change the contents.\n5:back to main menu.\n6:exit the program.\nenter the choice: "); //if choice was 1 then this menu will be displayed.
                    scanf("%d", &ch1);

                    switch(ch1)
                    {
                        case 1:
                            attendance(class); // teacher can take the attendance from here.
                            store_to_txtfile();
                            break;

                        case 2: // teacher can check student information.
                            int op;
                            printf("options:\n1:for checking the individual student details.\n2:all student details.\nchoose your choice: ");
                            scanf("%d" , &op);
                            if(op == 1)
                            {
                                printf("\n*********************************************************\n");
                                for(int i=0 ; i<rows ; i++)
                                {
                                    for(int j=0 ; j< seats ; j++) 
                                    {
                                        printf("%d\t", n++);
                                    }
                                    printf("\n\n");
                                }
                                printf("**************************************************************\n");
                                n = 1;
                                printf("select student's seat number: "); 
                                scanf("%d" , &class_seat);

                                display_std_details(class + class_seat - 1);
                            }
                            else if(op == 2)
                                all_std_details();
                            else 
                                printf("wrong choice.");
                           
                            break;

                        case 3: // this should be the first task to be done becuse if class is not created then student cant enter his details.
                            printf("enter the number of rows in the class: ");
                            scanf("%d" , &rows); 

                            printf("enter number of seats in each row: " );
                            scanf("%d" , &seats);

                            create(rows , seats);
                            store_to_txtfile();
                            break;

                        case 4:
                            int new;
                            printf("\noptions:\n1:erase the content(delete everything).\n2:reset the data.\nenter the choice: ");
                            scanf("%d" , &new);
                            if(new == 1)
                            {
                                FILE *ptr;
                                ptr = fopen("class.txt" , "w");
                                fclose(ptr);
                                days = 0 , rows = 0 , seats = 0;
                                free(class);
                            }
                            else if(new == 2) 
                            {
                                for(int i=0 ; i<(rows* seats) ; i++)
                                {
                                    strcpy(class[i].std_name , "no name");
                                    strcpy(class[i].Usn , "mite");
                                    class[i].phone = 0;
                                    class[i].present = 0;
                                    class[i].absent = 0;
                                    class[i].book_seat = false ;
                                    strcpy(class[i].day , "D");
                                }
                                days = 0;
                                store_to_txtfile();
                            }
                            else
                                printf("wrong choice.");

                            store_to_txtfile();
                            
                            break;
                            
                        case 5:
                            goto main_menu; // it will go back to main menu

                        case 6:
                            goto exit; //terminates the program.

                        default:
                            printf("Give the proper choice please!\n");
                    }
                }
                break; 

            case 2:
                int ch2;
                while(1)
                {
                    printf("1:register the seat.\n2:check your details.\n3:Un-register your seat.\n4:Back to main menu.\n5:exit the program.\nEnter the choice: "); //if choice was 2 then this menu will be displayed.
                    scanf("%d" , &ch2);

                    switch (ch2)
                    {
                        case 1: // student can register his seat from here.
                            char name[20] ,roll_number[10];
                            long long phone_number;
                            printf("\n**********************seats available***********************\n");
                            for(int i=0 ; i<rows ; i++)
                            {
                                for(int j=0 ; j< seats ; j++) 
                                {
                                    printf("%d\t", n++);
                                }
                                printf("\n\n");
                            }
                            printf("**************************************************************\n");
                            n = 1;
                            
                            reg:
                            printf("Choose your seat: ");
                            scanf("%d" , &class_seat);

                            if(class[class_seat - 1].book_seat == false)
                            {
                                printf("\nenter your details: \n");

                                printf("enter your name : ");
                                scanf("%s",name);

                                printf("enter your USN: ");
                                scanf("%s",roll_number); 

                                printf("enter your phone number: ");
                                scanf("%lld",&phone_number); 
                                seat_register(class + class_seat -1 , name , roll_number , phone_number);
                            }
                            else
                            {
                                printf("seat is already booked try again.\n");
                                goto reg;
                            }
                            store_to_txtfile();
                            break;

                        case 2: // student can check his details.
                            printf("\n*********************************************************\n");
                            for(int i=0 ; i<rows ; i++)
                            {
                                for(int j=0 ; j< seats ; j++) 
                                {
                                    printf("%d\t", n++);
                                }
                                printf("\n\n");
                            }
                            printf("**************************************************************\n");
                            n = 1;
                            printf("select your seat number: ");
                            scanf("%d" , &class_seat);

                            display_std_details(class + class_seat - 1);
                            break;
                        
                        case 3:
                            int st_number;
                            printf("\n*********************************************************\n");
                            for(int i=0 ; i<rows ; i++)
                            {
                                for(int j=0 ; j< seats ; j++) 
                                {
                                    printf("%d\t", n++);
                                }
                                printf("\n\n");
                            }
                            printf("**************************************************************\n");
                            n = 1;
                            printf("choose your seat: ");
                            scanf("%d" , &st_number);

                            strcpy(class[st_number-1].std_name , "no name");
                            strcpy(class[st_number-1].Usn , "mite");
                            class[st_number-1].phone = 0;
                            class[st_number-1].present = 0;
                            class[st_number-1].absent = days;
                            class[st_number-1].book_seat = false ;
                            strcpy(class[st_number-1].day , "D");
                            for(int i = 1 ; i<= days ; i++)
                                strcat(class[i].day , "A");

                            printf("succesfully deleted your information.\n");
                            store_to_txtfile();

                            break;

                        case 4:
                            goto main_menu; // this will take back to main menu.

                        case 5:
                            goto exit; // terminates the program.

                        default:
                            printf("Give correct choice. :)\n");
                    }

                }
                break;

            exit:
            case 3:
                store_to_txtfile();
                printf("program is succesfully exited.....");
                return 0;

            default:
                printf("Wrong choice.... :0\n");
        }
        
    }while(choice != 3);

    return 0;

}