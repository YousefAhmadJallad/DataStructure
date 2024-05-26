#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declare tree linkedlist
struct tree;
typedef struct tree *ptrt, *BST, *Tree;
typedef char string[100];

struct tree {
string word;//words in the dictionary
string meaning;//meaning in the dictionary
ptrt right;// pointers for right of the tree
ptrt left;// pointers for left of the tree
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

BST insert ( BST T, string word, string meaning)
{ //Tree empty, insert first element

    if ( T == NULL ) {
        T = (BST) malloc (sizeof(struct tree));

        if ( T == NULL )
 printf ("Out of space!!!");
 else
 {
 strcpy(T->word , word);
 strcpy(T->meaning , meaning);
T->right = NULL;
T->left = NULL;
 }
 }

 //Tree not empty, check to insert to left or right.
else if (strcasecmp(T->word, word)>0 )
        T->left = insert ( T->left , word,meaning);


else if (strcasecmp(T->word, word)< 0 )
        T->right = insert(T->right, word,meaning);



return T;
}

///////////////////////////////////////////////////////////////////////////////////
// the read function
BST read (Tree T){
    string word;
    string meaning;
    FILE * in = fopen("dictionary.txt","r");

if(in == NULL){
printf("there is an error with the file\n");
exit(0);
}

string line;
while(fgets(line,100,in) != NULL) {

    char *token = strtok(line,".");

        token = strtok(NULL, ":");

        while (token != NULL){

         strcpy(word,token);
        token = strtok(NULL, ".");
        strcpy(meaning,token);


        int c =0;

//clean the spaces
    for(int i=0;i< strlen(word); i++){

        if (isdigit(word[i]) && word[0] != ' '){

            c++;
        }
    }

    trim(word) ; // function that trim the string

    int d = (strlen(word)) - c;
    word[d] = '\0';

    ///////////////////////////////////////////////
     c =0;
//clean
    for(int i=0;i< strlen(meaning); i++){

        if (isdigit(meaning[i])){

            c++;
        }
    }

     d = (strlen(meaning)) - c;
    meaning[d] = '\0';
    //until here

      T = insert(T,word,meaning);
      token = strtok(NULL, ": ");
     }
}
return T;
}
//////////////////////////////////////////////////////////////////////////////////
//functions to search for the word and its meaning
void find (BST T, string word, string meaning)
{
    if (T != NULL){

    if(strcmpi(T ->word,word)==0)
    {
        printf("%s : %s\n\n" , T->word , T->meaning);
    }
    //if the entered word greater than the word in the node go left
     else if (strcasecmp(T->word, word) > 0)
        find(T->left, word, meaning);
    //if the entered word less than the word in the node go right
    else if (strcasecmp(T->word, word) < 0)
        find(T->right, word, meaning);
    }
    else printf("%s does not exist\n\n" , word) ;
}


void trim(char str[PATH_MAX])
{
        int i = 0, j = 0;
        char buf[PATH_MAX];
        strcpy(buf, str);
        for(;str[i] == ' ';i++);

        for(;str[i] != '\0';i++,j++)
                buf[j] = str[i];
        buf[j] = '\0';
        strcpy(str, buf);
}
//////////////////////////////////////////////////////////////////////////////////
// function to update the meaning of the word
BST update_meaning (BST T ,string word, string new_meaning)
{
    if(T != NULL){

    if (T != NULL){

    if(strcmpi(T ->word,word)==0)
    {
        strcpy(T ->meaning , new_meaning) ;
    }

     else if (strcasecmp(T->word, word) > 0)
        update_meaning(T->left, word, new_meaning);

    else if (strcasecmp(T->word, word) < 0)
        update_meaning(T->right, word, new_meaning);
    }
    else printf("%s does not exist\n\n" , word) ;


    }
return T ;
}
/////////////////////////////////////////////////////////////////////////////
//decalre a pointer that shows the minimum node
ptrt find_min (BST T)
{

    if (T ==NULL)//empty tree
        return NULL;
    else if (T->left == NULL)//node itself
        return(T);
    else
        return (find_min (T->left));//find min recursive
}
//function to delete a node
BST delete_fun (BST T, string word, string meaning)
{
    ptrt temp_cell, child;
    if (T==NULL)
        printf("the word does not exist\n\n");
        //if the entered word greater than the word in the node go left
    else if (strcasecmp(T->word, word) > 0)
    {
         T->left = delete_fun(T->left, word, meaning);
    }
    //if the entered word less than the word in the node go right
    else if (strcasecmp(T->word, word) < 0)
    {
        T->right = delete_fun(T->right, word, meaning);
    }
    //found the node and check if it has (right and left)
    else if (T->left && T->right)
    {
        temp_cell = find_min(T->right);
        strcpy(T ->word , temp_cell->word);
        strcpy(T ->meaning,temp_cell->meaning);
        T->right = delete_fun(T->right , T->word, T->meaning);

    }
    else
    {
        temp_cell = T;
        if(T->left == NULL)
            child = T->right;
        if (T->right == NULL)
            child = T->left;
        free(temp_cell);
        return child;
    }

return T;
}

////////////////////////////////////////////////////////////////////////////////
//function prints the data inside the dictionary
void print_fun (BST T)
{
    if (T != NULL)
    {
        print_fun(T->left);
        printf("\n%s:%s\n",T->word,T->meaning);
        printf("\n");
        print_fun(T->right);

    }
    return;

}
////////////////////////////////////////////////////////////////////////////////
//function prints the data start with the same letter
void print_letter (BST T, char letter)
{
    if (T != NULL)
    {
        if(letter == T->word[0])
        {

            printf("\n%s:%s\n",T->word,T->meaning);
            printf("\n");
        }
        else

            print_letter(T->left,letter);
            print_letter(T->right,letter);
    }
    return;

}

///////////////////////////////////////////////////////////////////////////////
//function to delete a a specific node
//same of the previous delete function
BST delete_letter (BST T, char letter)
{
    ptrt temp_cell, child;
    if (T==NULL)
        return T;
    if (letter <= T->word[0] )
    {
         T->left = delete_letter(T->left, letter);
    }

    if (letter >= T->word[0])
    {
        T->right = delete_letter(T->right, letter);
    }

    if (T->left && T->right)
    {
        temp_cell = find_min(T->right);
        strcpy(T ->word , temp_cell->word);
        strcpy(T ->meaning,temp_cell->meaning);
        T->right = delete_fun(T->right , T->word, T->meaning);
    }
    else
    {
        temp_cell = T;
        if(T->left == NULL)
            child = T->right;
        if (T->right == NULL)
            child = T->left;
        free(temp_cell);
        return child;
    }

return T;
}
///////////////////////////////////////////////////////////////////////////////
//function that print data in file
//same as print_fun
void printFile(BST T, FILE*in)
{
    if (T != NULL)
    {
        printFile(T->left,in);
        fprintf(in,"\n%s:%s\n",T->word,T->meaning);
        fprintf(in,"\n");
        printFile(T->right,in);


    }


}


///////////////////////////////////////////////////////////////////////////////
int main()
{
    string word;
    string meaning;
    Tree T = NULL;
    char letter;

    int choice = 0;
    printf("\n\n");
    printf("\t\t\t\t\t\tWELCOME!\t\t\n");
    printf("\t\t\t\t\t\tPROJECT 2\t\t\n");
    printf("\t\t\t\t\t------------------------\n");

    //while loop to execute the switch statement repeatedly
    while(1){
     printf("please pick an option: \n");
     printf("1-Read from files\n2-search for a word\n3-update meaning\n4-Add New word to dictionary\n5-Print the dictionary (Sorted in an alphabetic)\n6-Print words start with a specific letter\n7-Delete a word from dictionary\n8-Delete words (starts with a specific letter)\n9-Print Edited data on file\n10-Exit\n");
     scanf("%d",&choice);

     switch(choice){

 case 1://read the file
    T = read(T);
    break;

 case 2://search for a word
    printf("\nTHE WORD YOU SEARCHED FOR: \n");
    scanf("%s",word);
    find(T, word, meaning);
    break;


 case 3://update meaning
    printf("Enter The Word: \n") ;
    scanf("%s" , word) ;
    printf("Enter The Meaning: \n") ;
    scanf("%s" , meaning) ;
    T = update_meaning (T ,word, meaning) ;
    break;

 case 4://insert new node
     printf("Enter New word: \n");
     scanf("%s",word);
     printf("Enter Meaning of new word: \n");
     scanf("%s", meaning);
     T = insert(T,word,meaning);
     break;

 case 5://print data inside the dictionary
    print_fun(T);
    break;

 case 6://print data that starts with same letter
     printf("Enter the letter: \n");
     scanf(" %c", &letter);
     print_letter(T,letter);
     break;


 case 7://delete a word
     printf("Enter The Word: \n") ;
     scanf("%s" , word) ;
     T = delete_fun(T, word, meaning);
     break;

 case 8://delete letter
     printf("Enter the letter: \n");
     scanf(" %c", &letter);
     T = delete_letter(T, letter);
     break;



 case 9://print on file
     {
         FILE *in = fopen("dictionary.txt","w");
         printFile(T, in);
         break;
     }


 case 10://EXIT
    printf("----------Good Bye----------");
    exit(0);
    break;


     }

    }
}
