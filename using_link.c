#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int rows=0 , seats=0 , node=1 ;
float days = 0.0 ;

//creating a structure for storing student details.
typedef struct student_details
{
    char std_name[20];
    char Usn[10];
    long long phone;
    int present ;
    int absent;
    int seat_number;
    char day[50];
    student *point;
}student;

student *class = NULL , *temp;

void seat_register(student *st, char name[20], char usn[10], long long phone , int se , char d[50])
{
    strcpy(st -> std_name , name);
    strcpy(st -> Usn , usn);
    st -> phone = phone ;
    st -> present = 0;
    st -> absent = 0;
    st -> seat_number = se ;
    strcpy(st -> day , d);
    if(class == NULL)
        temp = class = st ;
    else 
    {
        temp -> point = st;
        temp = st ;
    }
}

void details_of_student(student *s)
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

bool traverse(int s)
{  
    student *temp1;
    temp1 = class;
    while(temp1!= NULL)
    {
        if(s == temp1 -> seat_number)
            return true;
        else 
            temp1 = temp1 -> point ;
    }
    return false;
}

int node_calculate()
{
    int count = 0;
    student *temp1;
    temp1 = class;
    while(temp1 != NULL)
    {
        count++;
        temp1 = temp1 -> point ;  
    }
    return count;
}

void main()
{
    int choice , seat_num ;

    main:
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
                           
                        case 2: 
                            int n = 1 ;
                            student *new ;
                            printf("\n");
                            for(int i=0 ; i< (rows * seats) ; i++)
                                printf("*");
                            printf("\n");
                            for(int i=0 ; i<rows ; i++)
                            {
                                for(int j=0 ; j< seats ; j++) 
                                {
                                    printf("%d\t" , n++);
                                }
                                printf("\n\n");
                            }
                            printf("\n");
                            for(int i=0 ; i< (rows * seats) ; i++)
                                printf("*");

                            printf("\nselect student's seat:");
                            scanf("%d" , &seat_num);

                            new = class ;
                            while(new!= NULL)
                            {
                                if(seat_num == new -> seat_number)
                                    break;
                                new = new->point;
                            }

                            details_of_student(new);
                            break;
            
                        case 3:     
                            printf("enter the number of rows in the class: ");
                            scanf("%d" , &rows); 
                            printf("enter number of seats in each row: " );
                            scanf("%d" , &seats);
                            break;
                           
                        case 4:
                    
                        case 5:
                            goto main;

                        case 6:

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
                        case 1:
                        student *newnode;
                        int n = 1 ;
                        char name[20] ,roll_number[10];
                        long long phone_number;
                        printf("\n");
                        for(int i=0 ; i< (rows * seats) ; i++)
                            printf("*");
                        printf("\n");
                        for(int i=0 ; i<rows ; i++)
                        {
                            for(int j=0 ; j< seats ; j++) 
                            {
                                printf("%d\t" , n++);
                            }
                            printf("\n\n");
                        }
                        printf("\n");
                        for(int i=0 ; i< (rows * seats) ; i++)
                            printf("*");
                        printf("\n");

                        retry:
                        printf("choose your seat: ");
                        scanf("%d", &seat_num);
                        if(seat_num > (rows * seats))
                        {
                            printf("you have chosen wrong seat number! try again.");
                            goto retry;
                        }
                        else if(traverse(seat_num) == true)
                        {
                            printf("seat is already booked try again.");
                            goto retry;
                        } 
                        else
                        {
                            newnode = (student*) malloc(sizeof(student));
                            seat_register(newnode , name , roll_number , phone_number , seat_num , "N");
                        }    
                        
                        case 2:

                        case 3:
                            goto main;

                        case 4:
                        

                        default:
                            printf("Give correct choice. :)\n");
                    }

                }
                break;

            case 3:
    
                return 0;

            default:
                printf("Wrong choice.... :0\n");
        }
        
    }while(choice != 3);

}