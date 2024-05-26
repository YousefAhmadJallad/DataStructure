//note: I used Project 2 Dictionary

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 1000

int total =0;

struct hash;
typedef struct hash * ptr ;
typedef char string[100];

struct hash {
string word;
string meaning;
ptr next;

};
//////////////////////////////////////////////////////////////////
// insert function (to add new word to dictionary)
ptr insert (ptr hash, string word, string meaning)
{
    if(hash->next == NULL)
        ++total;

    ptr temp = (ptr) malloc (sizeof (struct hash));
    temp ->next = hash ->next;
    strcpy(temp->word, word);
    strcpy(temp->meaning, meaning);
    hash  ->next = temp;


}


/////////////////////////////////////////////////////////////////
// the read function
void read (ptr hash[size]){
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


    int sum=0;
    for (int i = 0; word[i] != '\0'; i++)
        sum += word[i];


    sum %= size;


      hash[sum]=insert(hash[sum],word,meaning);
      token = strtok(NULL, ": ");
     }
}

}
///////////////////////////////////////////////////////////////
//function to trim the word
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
/////////////////////////////////////////////////////////////////
//function to find word in the dictionary with the meaning
int Search (ptr hash, string word)
{



    /*    printf("%s\n",p->word);
        printf("sum=%d\n", sum);*/
    if(hash != NULL){
         if (strcasecmp(word, hash->word) == 0)
         {
             printf("%s\n", hash->meaning);
             return 1;
            }
            else
                return Search(hash->next, word);



}

return 0;
}


////////////////////////////////////////////////////////////////
//function to print the dictionary
void print (ptr hash[size])
{
    int x=1;
    for (int i=0; i<size; ++i)
    {
        ptr temp = hash[i]->next;
        while(temp !=NULL)
        {

            printf("%d) %s : %s\n", x,temp->word, temp->meaning);
            ++x;
            temp = temp->next;

        }

    }
}
////////////////////////////////////////////////////////////////
//function to delete a word in the dictionary
int delete_fun (ptr hash[size],string word)
{
     int sum=0;
    for (int j = 0; j<100; j++)
    {
        sum += word[j];
    }
    sum %= size;
    ptr p = hash[sum]->next;
    ptr y = hash[sum];
    while (p != NULL)
    {
        if (strcasecmp(word, p->word) == 0)
        {
            y->next = p->next;
            free (p);
            if(hash[sum]->next == NULL)
                --total;
            return 1;
        }

        p = p->next;
        y = y->next;

    }

return 0;
}
//////////////////////////////////////////////////////////
//print the hash table in including empty slots
void print_hash (ptr hash[size])
{
    int x=1;
    for (int i=0; i<size; ++i)
    {
        ptr temp = hash[i];
        while(temp !=NULL)
        {
            printf("%d) %s : %s\n", x,temp->word, temp->meaning);
            ++x;
            temp = temp->next;

        }

    }
}
///////////////////////////////////////////////////////////////
//Print the number of occupied slots, hash table size and the load factor
void LoadFactor ()
{
    printf("LoadFactor = %f\n occupied slots = %d\n size = %d\n", 1.0*total/size, total, size  );
}

//////////////////////////////////////////////////////////////////

//update meaning of word in the dictionary
int Update (ptr hash, string word)
{

if(hash != NULL){


         if (strcasecmp(word, hash->word) == 0)
         {
              printf("Enter New meaning: \n");
              string meaning;
              fgets(meaning , 100, stdin);
              fgets(meaning , 100, stdin);

              strcpy(hash->meaning, meaning);
              return 1;

         }

            else
                return Update(hash->next, word);
}

return 0;
}
//////////////////////////////////////////////////////
//save data in new file
void printFile(ptr hash[size])
{
    int x=1;
    FILE *in;
    in = fopen("dictionary_modified.txt","a");
    fprintf(in,"////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
    fprintf(in,"\n\nHash Table : \n");
    for(int i=0; i<size; ++i)
    {
        ptr T = hash[i]->next;
          while (T != NULL)
        {

            fprintf(in,"\n%d.%s:%s\n",x ,T->word,T->meaning);
            fprintf(in,"\n");
            T = T->next;
            x++;

        }

    }

fclose(in);
}


/////////////////////////////////////////////////////////////////
int main()
{

    ptr hash[size];
    for(int i=0; i<size; ++i)
    {
        hash [i] = (ptr) malloc (sizeof (struct hash));
        hash [i]->next = NULL;
    }


    string word;
    string meaning;



    int choice = 0;
    printf("\n\n");
    printf("\t\t\t\t\t\tWELCOME!\t\t\n");
    printf("\t\t\t\t\t\tPROJECT 3\t\t\n");
    printf("\t\t\t\t\t------------------------\n");
    while(1){
     printf("please pick an option: \n");
     printf("1-Read from files\n2-search for a word\n3-update meaning\n4-Add New word to dictionary\n5-Print the dictionary \n6-Print hash table including empty slots\n7-Delete a word from dictionary\n8-print occupied slots, hash table size, and load factor\n9-Print Edited data on file\n10-Exit\n");
     scanf("%d",&choice);

     switch(choice){

 case 1://read the file
    read(hash);
    break;

 case 2://search for a word
    printf("\nTHE WORD YOU SEARCHED FOR: \n");

    scanf("%s",word);
     int sum=0;
    for (int i = 0; word[i] != '\0' ; i++)
    {
        sum += word[i];
    }
    sum %= size;
    if(!Search(hash[sum],word))
        printf("the word does not exist\n");

    break;


 case 3://update meaning
    printf("Enter The Word: \n") ;
    scanf("%s" , word) ;
    sum =0;
    for (int i = 0; word[i] != '\0' ; i++)
    {
        sum += word[i];
    }
    sum %= size;
    if(!Update(hash[sum], word ))
        printf("the word does not exist\n");

    break;

 case 4://insert new node
     printf("Enter New word: \n");
     scanf("%s",word);
     printf("Enter Meaning of new word: \n");
     scanf("%s", meaning);
     sum =0;
    for (int i = 0; word[i] != '\0' ; i++)
    {
        sum += word[i];
    }
    sum %= size;
     insert(hash[sum] , word , meaning) ;
     break;

 case 5://print data inside the dictionary
    print(hash);
    break;

 case 6://Print hash table including empty slots
     printf("Entire Hash table Including empty slots: \n");
     print_hash(hash) ;
     break;


 case 7://delete a word
     printf("Enter The Word: \n") ;
     scanf("%s" , word) ;
      if(!delete_fun(hash,word))
        printf("the word does not exist\n");
     break;

 case 8://print occupied slots, hash table size, and load factor
     printf("the result will be as below: \n");
     LoadFactor() ;
     break;



 case 9://print on file
     {
         printFile(hash);
         printf("Saved To File!\n");
         break;
     }


 case 10://EXIT
    printf("----------Good Bye----------");
    exit(0);
    break;


     }

    }


    return 0;
}
