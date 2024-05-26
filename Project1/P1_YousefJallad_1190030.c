#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declare the LinkedList for the students
struct Course ;
typedef struct Course * ptrc ;
typedef char String[100] ;

struct Course {
String name; //course name
String CourseId ; // course ID number Example (COMP231)
int regYear ; // registration year for attendance people
int limit ; // maximum number of students
int counter; //to move on each course
struct Students* Stud[100]; //array linkedlist (connect the courses linked list and the students linked list)
struct Sudents* watingList [1000]; //number of the students on the course waiting list
ptrc next ;

};
typedef ptrc LinkedList ;




///////////////////////////////////////////////////////////////////////////////////////////////

//declare the LinkedList for the students
struct Students ;
typedef struct Students * ptrs ;
typedef char String[100] ;

struct Students {

String name ; //students name
int Id ; //students id number example(1190030)
String CourseId[10]; // courses registered
int regyear; // (his/her) registration year
int counter; // to move on each student
ptrs next ;

};
typedef ptrs LinkedList1 ;
//////////////////////////////////

//function to find the registration year for the student
int reg_fun (int Id)
{
    int reg;
    reg = Id / 10000;
    return reg;
}

/////////////////


//insert the courses node into its linkedlist
void insert1(LinkedList L , ptrc header , ptrc newNode)
{
    ptrc p = header ;

    newNode ->next = p ->next ;
    p ->next = newNode ;

    newNode->counter = 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////
//function to print the courses linked list
void print(LinkedList L)
{
   ptrc p = L ->next ;

    for(int i = 0 ; p != NULL ; ++i)
    {
        printf("%d)name : %s    ID : %s     reg : %d     limit : %d\n" , i+1 , p ->name , p->CourseId , p ->regYear , p ->limit) ;
        p = p ->next ;
    }


}
//////////////////////////////////////////////////////////////////////////////////////////

//insert the students node into its linkedlist
void insert2(LinkedList1 L , ptrs header , ptrs newNode)
{
    ptrs p = header ;

    newNode ->next = p ->next ;
    p ->next = newNode ;

    newNode->counter = 0;

}

//////////////////////////////////////////////////////////////////////

//function to print the students linked list
void print2(LinkedList1 T)
{
     ptrs p = T ->next ;

    for(int i = 0 ; p != NULL ; ++i)
    {
        printf("%d)name : %s    ID : %d  " , i+1 , p ->name , p->Id );
        for (int j = 0; j <10; ++j)
        {
            printf("CourseId[%d]: %s\t", j+1, p->CourseId[j]);
        }
        printf("\n");
        p = p ->next ;
    }

}


///////////////////////////////////////////////////////////////////////////////////////////////

//function to connect the courses linkedlist and students linked list
void link (LinkedList L, LinkedList1 T)
{
    ptrc CoursePointer = L->next;
    ptrs StudentPointer = T->next;
    int k;

    while(StudentPointer != NULL){

            CoursePointer = L ->next ;

     while(CoursePointer != NULL)
    {

       for (int j=0; j<10; j++)

        {

            //here we let the courses move on each students to check if he registered in this class,
            //and to check if the course reached the limit of students,
            //then if the students reached the limit of courses,
            //and finally to check if he is old enough to register
            if(strcmp(CoursePointer->CourseId,StudentPointer->CourseId[j]) == 0 && CoursePointer->counter < CoursePointer->limit && StudentPointer->counter < 5 && CoursePointer->regYear > StudentPointer->regyear )
            {

                // we make a pointer called new student to save the data in it
                ptrs NewStudent =(LinkedList1) malloc(sizeof(struct Students)) ;
                NewStudent->next = NULL;
                strcpy(NewStudent->name, StudentPointer->name);
                NewStudent->Id = StudentPointer->Id;
                CoursePointer->counter++;
                StudentPointer->counter++;

                for (int i =0; i < 10; i++)
                {
                    strcpy(NewStudent->CourseId[i] ,StudentPointer->CourseId[i]);
                }
                NewStudent->counter = StudentPointer->counter;
                for(k=0; k<100 && CoursePointer->Stud[k] != NULL; k++)
                {
                    if(CoursePointer->Stud[k] == NULL)
                    {
                        break;
                    }
                }

                CoursePointer->Stud[k] = NewStudent;
            }

                //this condition is the same of the previous one but in it we put the student in the waiting list
                else if(strcmp(CoursePointer->CourseId,StudentPointer->CourseId[j]) == 0 && CoursePointer->counter >= CoursePointer->limit && StudentPointer->counter < 5 && CoursePointer->regYear > StudentPointer->regyear)
                {
                ptrs NewStudent =(LinkedList1) malloc(sizeof(struct Students)) ;
                NewStudent->next = NULL;
                strcpy(NewStudent->name, StudentPointer->name);
                NewStudent->Id = StudentPointer->Id;
                StudentPointer->counter++;
                for (int i =0; i < 10; i++)
                {
                    strcpy(NewStudent->CourseId[i] ,StudentPointer->CourseId[i]);
                }
                NewStudent->counter = StudentPointer->counter;
                for(k=0; k<100 && CoursePointer->watingList[k] != NULL; k++)
                {
                    if(CoursePointer->watingList[k] == NULL)
                    {
                        break;
                    }

                }

                CoursePointer->watingList[k] = NewStudent;

                }

            }
            CoursePointer =CoursePointer->next;
        }
                    StudentPointer = StudentPointer -> next ;

    }
}
///////////////////////////////////////////////////////////////////////////////

//this function to sort the student in each course based on there id number
void sort1(LinkedList CourseHead){

    ptrc coursePointer = CourseHead ->next ;
    String nameTemp ;
    int idTemp ;
    String coursesTemp[10] ;
    int regYearTemp ;

    while(coursePointer != NULL){

        for(int i = 0 ; i < 100 ; ++i){
            for(int j = i+1 ; j < 100; ++j)
            {

            if(coursePointer ->Stud[i] == NULL || coursePointer ->Stud[j] == NULL)
                    break ;

        else if(coursePointer ->Stud[i] ->Id > coursePointer->Stud[j]->Id)
        {
            //temp = array[i]
            strcpy(nameTemp , coursePointer->Stud[i]->name );

            idTemp = coursePointer->Stud[i]->Id;
            for (int k =0; k < 10 && coursePointer ->Stud[i] ->CourseId[k] != NULL; ++k){
                strcpy(coursesTemp[k], coursePointer->Stud[i]->CourseId[k]);}
            regYearTemp = coursePointer->Stud[i]->regyear ;

            //array[i]=array[j]
            strcpy(coursePointer->Stud[i]->name , coursePointer->Stud[j]->name);
            coursePointer->Stud[i]->Id = coursePointer->Stud[j]->Id;
            for (int k =0; k < 10 && coursePointer ->Stud[i]->CourseId[k] != NULL; ++k)
                strcpy(coursePointer->Stud[i]->CourseId[k] ,coursePointer->Stud[j]->CourseId[k]) ;
            coursePointer->Stud[i]->regyear = coursePointer->Stud[j]->regyear ;

            //array[j] = temp
            strcpy(coursePointer->Stud[j]->name, nameTemp );
            coursePointer->Stud[j]->Id = idTemp;
            for (int k =0; k < 10 && coursePointer ->Stud[i]->CourseId[k] != NULL; ++k)
                strcpy(coursePointer->Stud[j]->CourseId[k], coursesTemp[k]);
            coursePointer->Stud[j]->regyear = regYearTemp ;

        }
    }

    }

    coursePointer = coursePointer ->next ;
    }
printFun(CourseHead);
}
////////////////////////////////////////////////////////////////////////////
//this function to sort courses based on courses name
void sort2 (LinkedList CourHead){

    ptrc coursePointer = CourHead ->next ;
    ptrc c ;
    String CourseNameTemp;
    String CourseIdTemp;
    int counterTemp;


    while(coursePointer != NULL){

    c = coursePointer ->next ;

    while(c != NULL){

                if(strcmp(coursePointer->name , c->name) < 0)
                   {
                       //temp = array[0]
                       strcpy(CourseNameTemp, c ->name);
                       strcpy(CourseIdTemp, c ->CourseId);
                       counterTemp = c ->counter ;

                       //array[i] = array[j]
                       strcpy(c ->name, coursePointer ->name);
                       strcpy(c ->CourseId , coursePointer ->CourseId);
                       c ->counter = coursePointer->counter;

                       //array[j] = temp
                       strcpy(coursePointer ->name , CourseNameTemp);
                       strcpy(coursePointer ->CourseId , CourseIdTemp);
                       coursePointer->counter = counterTemp ;

                   }

 c = c ->next ;

            }


coursePointer = coursePointer ->next ;

    }
    printFun(CourHead);


}

/////////////////////////////////////////////////////////////
//this function is to print the number of registered students in each class
void blalao (LinkedList CoursHead)
{
    ptrc coursePointer = CoursHead->next;
    ptrc c;
    while(coursePointer != NULL){
            c = coursePointer->next;

        if(coursePointer ->counter < 5)
        {
            printf("%s                 %s          students = %d\n" , coursePointer ->name , coursePointer ->CourseId , coursePointer ->counter) ;

        }

    coursePointer = coursePointer ->next ;


    }

}
//////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////////

//function to print the data
void printFun (LinkedList L)
{
    printf("\n\n THE FUNCTION PRINTS: \n\n");
    ptrc p = L->next;
    while (p != NULL)
    {
         printf("Course name : %s   Course ID : %s \n" , p ->name , p->CourseId );
        for (int i = 0; i <100 && p->Stud[i] !=NULL; ++i)
        {
            printf(" [%s]            [%d] \n" , p ->Stud [i]->name, p->Stud[i]->Id);
        }
        p = p->next;
        printf("\n");

    }



}


///////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
     LinkedList L = (LinkedList)malloc(sizeof(struct Course)) ;
     L ->next = NULL ;
      LinkedList1 T = (LinkedList1)malloc(sizeof(struct Students)) ;
    T ->next = NULL ;

    int choice = 0;
    String Info ;
    char *linker ;
    FILE *p = fopen("Courses.txt" , "r");

   printf("\n\n");
   printf("\t\t\t\t\t\tWELCOME!\t\t\n");
   printf("\t\t\t\t\t\tPROJECT 1\t\t\n");
   printf("\t\t\t\t\t------------------------\n");

//while loop to execute the switch statement repeatedly
    while(1){

     printf("please pick an option: \n");
     printf("1-Read from files and move to lists\n2-Print the Sorted students list\n3-Print the sorted courses list\n4-print all courses that has less than 5 students\n5-quit the program\n");

      scanf("%d",&choice);

    switch(choice){

    case 1://read form the file

    for(int i = 0 ; fgets(Info , 100 , p) != NULL ; ++i)
    {

        ptrc l = (ptrc)malloc(sizeof(struct Course)) ;

        linker = strtok(Info , ",") ;
        strcpy(l ->name , linker) ; // for course name



        linker = strtok(NULL , ",") ;
        strcpy(l->CourseId , linker) ; // for course id



        linker = strtok(NULL , ",") ;
        l ->regYear = strtod(linker , &linker) ; // for regYear

        linker = strtok(NULL , ",") ;
        l ->limit = strtod(linker , &linker) ; // for limit

        // loop to check if there is a spaces in course id
        for(int i = 0 ; i < 10 ; ++i)// Supposing That The Course Id Is Not Longer Than 10
            if(l ->CourseId[i] == '\n' || l ->CourseId[i] == ' ')
                l ->CourseId[i] = '\0' ;


        insert1(L,L,l);
    }

   //print(L);
//////////////////////////////

    //read and inserts students file into nodes
    FILE *z = fopen("Students.txt" , "r") ;

    String Infos ;
    char *linkers ;

    for(int i = 0 ; fgets(Infos , 100 , z) != NULL ; ++i){

        ptrs t = (ptrs)malloc(sizeof(struct Students)) ;

        linkers = strtok(Infos , "#") ;
        strcpy(t ->name , linkers) ; // student name

        linkers = strtok(NULL , "#") ;
        t->Id = strtod(linkers , &linkers) ; // student id

        t->regyear = reg_fun(t->Id); //register year

        //loop to move in each course
        for (int i = 0; linkers = strtok(NULL , "#") ; ++i)
            {
                strcpy(t->CourseId[i] , linkers) ; //course id
            }

            //loop to check that there is spaces in course id
            for(int i = 0 ; i < 10 ; ++i){
            for(int j = 0 ; j < 100 ; ++j)
            if(t ->CourseId[i][j] == '\n' || t ->CourseId[i][j] == ' ')
                t ->CourseId[i][j] = '\0' ;
            }


        insert2(T,T,t) ;

    }

    link(L, T);

        break;

    case 2://sort students based on id
         printf("\nTHE SORTED STUDENT LIST AS FOLLOWS\n");
        sort1(L);
       break;


    case 3://sort courses based on courses name
        printf("\nTHE SORTED COURSES LIST AS FOLLOWS\n");
        sort2(L);
        break;


    case 4://show number of students on each course
        printf("\nTHE COURSES THAT CONTAIN LESS THAN 5 STUDENTS AS FOLLOWS\n");
         blalao(L);
         break;
    case 5://quit program
        printf("----------Good Bye----------");
        exit(0);
        break;


    }

    }

    return 0;
}
