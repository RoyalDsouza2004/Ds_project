#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int rows = 2 , columns =1 , seats=3 , n=1 ;

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
}student;

student *class;


void store_to_txtfile(int rows , int columns , FILE *fl)
{
    for(int i=0 ; i<(rows * columns) ; i++)
    {
        fputs( class[i].std_name , fl);
        fputs( "\n" , fl);
        fputs( class[i].Usn , fl);
        fputs( "\n" , fl);
        putw( class[i].phone , fl);
        fputs( "\n" , fl);
        putw( class[i].present , fl);
        fputs( "\n" , fl);
        putw( class[i].absent , fl);
        fputs( "\n" , fl);
        putw( class[i].seat_number , fl);
        fputs( "\n" , fl);
        if(class[i].book_seat == true)
        {
            fputs( "true" , fl);
            fputs( "\n" , fl);
        }
        else
        {
            fputs( "false" , fl);
            fputs( "\n" , fl);
        }
    }
}

void create(int row , int column)
{
    class = (student*) malloc(row * column * sizeof(student)); // dynamically allocating array of structures.

    for(int i=0 ; i<(rows * column) ; i++)
    {
        class[i].seat_number = n++;
        class[i].book_seat =false ;
    }
}

void seat_register(student *st, char name[20], char usn[10], long long phone )
{
    strcpy(st -> std_name , name);
    strcpy(st -> Usn , usn);
    st -> phone = phone ;
    st -> present = 0 ;
    st -> absent = 0 ;
    st -> book_seat = true; 
}

int main()
{
    char name[10]="royal" , roll_number[10]= "cs122";
    long long phone_number = 232323323;
    create(rows , seats);

    int class_seat = 2;
    strcpy(class[class_seat + 1].std_name , "royaldsouza");
    class[class_seat + 1].book_seat =true ;

    if(class[class_seat + 1].book_seat == true)
    {
        printf("seat is already booked try for another seat.\n");
    }
    else
    {
        seat_register(class + class_seat , name , roll_number , phone_number);
    }
}