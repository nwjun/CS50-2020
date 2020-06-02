#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main(int argc, string argv[])
{   
    string plain = NULL;
    char *p=argv[1];
    int i=0, alpha[26]= {0};
    
    if (argc == 2)
    {   
        while(*p)   //Check key
        {
            if((isalpha(*p)))
            {
                alpha[toupper(*p)-'A']++;
                
                if(alpha[toupper(*p)-'A'] > 1)
                {
                    printf("Error! Letter is used more than once!\n");
                    return 1;
                }
            }
            
            else
            { 
                printf("Error! Only alphabets!\n");
                return 1;   
            }
            p ++;
            i ++;
        }
        
        if(i != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        
        //get text 
        plain = get_string("plain text:");
        p = plain;
        
        //print cipher text
        printf("ciphertext: ");
        
        while(*p)
        {
            if(*p >= 'A' && *p <= 'Z')          //text is in uppercase
                printf("%c", toupper(argv[1][*p-'A']));
            else if(*p >= 'a' && *p <= 'z')     //text is in lowercase
                printf("%c", tolower(argv[1][*p-'a']));
            else                                //text other than alphabet
                printf("%c", *p);
            p ++;
        }
        printf("\n");    
        
        return 0;
        
    }
    
    else
    {
        printf("Error!\n");
        return 1;
    }
}