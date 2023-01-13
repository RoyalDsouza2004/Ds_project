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
    bool book_seat ;
    char day[60];
}student;

student *class;


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
                            int n = 1;
                            printf("\n*********************************************************\n");
                            for(int i=0 ; i<rows ; i++)
                            {
                                for(int j=0 ; j< seats ; j++) 
                                {
                                    printf("%d\t" , n++);
                                }
                                printf("\n\n");
                            }
                            printf("**************************************************************\n");
                            printf("select student's seat number: "); 
                            scanf("%d" , &class_seat);

                            display_std_details(class + class_seat - 1);
                            break;

                        case 3: // this should be the first task to be done becuse if class is not created then student cant enter his details.
                            printf("enter the number of rows in the class: ");
                            scanf("%d" , &rows); 

                            printf("enter number of seats in each row: " );
                            scanf("%d" , &seats);
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
                            int n=1;
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
                            int n = 1;
                            printf("\n*********************************************************\n");
                            for(int i=0 ; i<rows ; i++)
                            {
                                for(int j=0 ; j< seats ; j++) 
                                {
                                    printf("%d\t" , n++);
                                }
                                printf("\n\n");
                            }
                            printf("**************************************************************\n");
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