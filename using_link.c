#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
int rows=0 , seats=0 , nodes=0 ;
float days = 0.0 ;

//creating a structure for storing student details.
struct student
{
    char std_name[20];
    char Usn[10];
    long long phone;
    int present ;
    int absent;
    int seat_number;
    char day[60];
    struct student *point;
    bool indecator;
};

struct student *class = NULL , *temp;

void seat_register(struct student *st, char name[20], char usn[10], long long phone , int se , char d[1])
{
    strcpy(st -> std_name , name);
    strcpy(st -> Usn , usn);
    st -> phone = phone ;
    st -> present = 0;
    st -> absent = 0;
    st -> seat_number = se ;
    strcpy(st -> day , d);
    if(class == NULL)
    {
        temp = class = st ;
        st -> point = NULL;
    }
    else 
    {
        temp -> point = st;
        st -> point = NULL;
        temp = st ;
    }
    st ->indecator = false;
}

void details_of_student(struct student *s)
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

void absent(int ab)
{
    struct student *temp1;
    temp1 = class;
    while(temp1!=NULL)
    {
        if(ab == temp1 -> seat_number)
        {
            temp1 -> absent++;
            strcat(temp1 -> day , "A");
            temp1 -> indecator = true;
            break;
        }
        temp1 = temp1 -> point;
    }
}

void present(int ab)
{
    struct student *temp1;
    temp1 = class;
    while(temp1!=NULL)
    {
        if(ab == temp1 -> seat_number)
        {
            temp1 -> present++;
            strcat(temp1 -> day , "P");
            temp1 -> indecator = true;
            break;
        }
        temp1 = temp1 -> point;
    }
}

bool traverse(int s)
{  
    struct student *temp1;
    temp1 = class;
    while(temp1!= NULL)
    {
        if(s == temp1 -> seat_number)
            return true;
        temp1 = temp1 -> point ;
    }
    return false;
}

int main()
{
    int choice , seat_num , n = 1;

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
                            ++days;
                            struct student *s;

                            int op ;
                            printf("Options:\n1:give absentees seat number.\n2:give present student's seat number\n3:all present\nchoose your choice: ");
                            scanf("%d" , &op);

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
                            n = 1;

                            if(op == 1)
                            {
                                int ab , ab1;
                                printf("give number of students absent for the class: ");
                                scanf("%d" , &ab);
                                for(int i=0 ; i<ab ; i++)
                                {
                                    printf("student %d: " , i+1);
                                    scanf("%d" , &ab1);
                                    absent(ab1);      
                                }
                                struct student *newnode;
                                newnode = class;
                                while (newnode!=NULL)
                                {
                                    if(newnode -> indecator == false)
                                    {
                                        newnode -> present++;
                                        newnode = newnode -> point;
                                    }
                                }   
                            }
                            else if(op == 2)
                            {
                                int pr , pr1;
                                printf("give number of students present for the class: ");
                                scanf("%d" , &pr);
                                for(int i=0 ; i<pr ; i++)
                                {
                                    printf("student %d: " , i+1);
                                    scanf("%d" , &pr1);
                                    present(pr1);      
                                }
                                struct student *newnode;
                                newnode = class;
                                while (newnode!=NULL)
                                {
                                    if(newnode -> indecator == false)
                                    {
                                        newnode -> absent++;
                                    }
                                }   
                            }
                            else if(op == 3)
                            {
                                struct student *newnode;
                                newnode = class;
                                while (newnode!=NULL)
                                {
                                    newnode -> present++ ;
                                    newnode = newnode -> point ;
                                }
                            }
                            else
                                printf("wrong choice.");

                            struct student *t;
                            t = class;
                            while(t!=NULL)
                            {
                                t -> indecator = false;
                                t = t -> point;
                            }                            
                            break;

                        case 2: 
                            struct student *new;
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
                            n = 1;

                            rev1:
                            printf("\nselect student's seat:");
                            scanf("%d" , &seat_num);

                            if(seat_num > (rows * seats))
                            {
                                printf("you have chosen wrong seat number! try again.");
                                goto rev1;
                            }
                            else
                            {
                                new = class ;
                                while(new!= NULL)
                                {
                                    if(seat_num == new -> seat_number)
                                        break;
                                    new = new -> point;
                                }
                                details_of_student(new);
                            }    
                            break;
            
                        case 3:     
                            printf("enter the number of rows in the class: ");
                            scanf("%d" , &rows); 
                            printf("enter number of seats in each row: " );
                            scanf("%d" , &seats);
                            break;
                           
                        // case 4:
                    
                        case 5:
                            goto main;

                        case 6:
                            goto exit;

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
                        struct student *newnode;
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
                        n = 1 ;

                        retry:
                        printf("choose your seat: ");
                        scanf("%d", &seat_num);
                        
                        if(seat_num > (rows * seats))
                        {
                            printf("wrong seat number retry.");
                            goto retry;
                        }

                        if(traverse(seat_num) == true)
                        {
                            printf("seat is already booked try again.");
                            goto retry;
                        }

                        printf("\nenter your details: \n");

                        printf("enter your name : ");
                        scanf("%s",name);

                        printf("enter your USN: ");
                        scanf("%s",roll_number); 

                        printf("enter your phone number: ");
                        scanf("%lld",&phone_number); 

                        newnode = (struct student*) malloc(sizeof(struct student));
                        seat_register(newnode , name , roll_number , phone_number , seat_num , "N");
                        nodes++;
                         
                        break; 
                        
                        case 2:
                            struct student *new;
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
                            n = 1;

                            rev2:
                            printf("\nselect your seat number:");
                            scanf("%d" , &seat_num);

                            if(seat_num > (rows * seats))
                            {
                                printf("you have chosen wrong seat number! try again.");
                                goto rev2;
                            }
                            else if (traverse(seat_num) == false)
                            {
                                printf("student not found. try again");
                                goto rev2;
                            }
                            
                            else
                            {
                                new = class ;
                                while(new!= NULL)
                                {
                                    if(seat_num == new -> seat_number)
                                        break;
                                    new = new -> point;
                                }
                                details_of_student(new);
                            }    
                            break;

                        case 3:
                            goto main;

                        case 4:
                            goto exit ;

                        default:
                            printf("Give correct choice. :)\n");
                    }

                }
                break;

            exit:
            case 3:
                return 0;

            default:
                printf("Wrong choice.... :0\n");
        }
        
    }while(choice != 3);

}