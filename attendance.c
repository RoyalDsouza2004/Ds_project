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
    char Usn[10];
    long long phone;
    int present ;
    int absent;
    bool book_seat ;
    char day[60];
}student;

student *class;

void store_to_txtfile(int row , int column , FILE *fl)
{

    fprintf(fl , "%d,%d,%g\n" , rows , seats , days );
    
    fclose(fl);

    fl = fopen("student data.txt" , "w");

    for(int i=0 ; i<(row * column) ; i++)
    { 
        fprintf(fl , "%s,%s,%lld,%d,%d,%s,%d\n" , class[i].std_name ,class[i].Usn , class[i].phone , class[i].present , class[i].absent , class[i].day , class[i].book_seat);
    }

    fclose(fl);
}

void get_from_txtfile()
{
    
    FILE *data;

    data = fopen("class.txt" , "r");

    if(data == NULL || !data)
    return;

    fscanf(data , "%d,%d,%g\n" , &rows , &seats , &days);

    fclose(data);

    class = (student*) malloc(rows * seats * sizeof(student));

    data = fopen("student data.txt" , "r");

    int bol ;
    int records = 0 , read = 0;
    do
    {
        read = fscanf(data , "%19[^,],%9[^,],%lld,%d,%d,%59[^,],%d\n", class[records].std_name , class[records].Usn , &class[records].phone , &class[records].present , &class[records].absent , class[records].day , &bol );
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
    ++days;
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

    printf("Enter the absentees seat numbers in order: (i.e increasing order like 1 2 3 etc...)");
    for(int i=0 ; i<ab ; i++)
    {
        printf("\nStudent %d: " , i + 1);
        scanf("%d" , &seat_num[i]);
    }
    int j = 0 , in = 0;

    while(in <=(rows*seats))
    {
        if(class[in-1].book_seat == false)
            in++;
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
        printf("Percentage: %g\n" , ((s -> present) / days) * 100 );

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
    printf("all student details:");
    
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
                    printf("1:take the attendance.\n2:check student details.\n3:create the class.\n4:erase the content(delete everything).\n5:back to main menu.\n6:exit the program.\nenter the choice: "); //if choice was 1 then this menu will be displayed.
                    scanf("%d", &ch1);

                    switch(ch1)
                    {
                        case 1:
                            attendance(class); // teacher can take the attendance from here.
                            break;

                        case 2: // teacher can check the individual student information.
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
                            break;

                        case 3: // this should be the first task to be done becuse if class is not created then student cant enter his details.
                            printf("enter the number of rows in the class: ");
                            scanf("%d" , &rows); 

                            printf("enter number of seats in each row: " );
                            scanf("%d" , &seats);

                            create(rows , seats);
                            break;

                        case 4:
                            FILE *ptr;
                            ptr = fopen("student data.txt" , "w");
                            fclose(ptr);
                            ptr = fopen("class.txt" , "w");
                            fclose(ptr);
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
                    printf("1:register the seat.\n2:check your details.\n3:Back to main menu.\n4:exit the program.\nEnter the choice: "); //if choice was 2 then this menu will be displayed.
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
                            goto main_menu; // this will take back to main menu.

                        case 4:
                            goto exit; // terminates the program.

                        default:
                            printf("Give correct choice. :)\n");
                    }

                }
                break;

            exit:
            case 3:
                FILE *att;
                att = fopen("class.txt" , "w");
                if(!att)
                {
                    printf("error while exiting the program your data maybe lost.:( ");
                    return 1;
                }
                store_to_txtfile(rows , seats , att);
                printf("program is succesfully exited.....");
                return 0;

            default:
                printf("Wrong choice.... :0\n");
        }
        
    }while(choice != 3);

    return 0;

}