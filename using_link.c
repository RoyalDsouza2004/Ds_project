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

void main()
{
    int choice ;

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
            
                        case 3: 
                           
                        case 4:
                    
                        case 5:
                

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
                           

                        case 2:

                        case 3:
                            

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