#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>

#define MAX_WORDS 100

int main (void){
    string text=NULL;
    char *p;
    int letters = 0, words = 1, sentence = 0, index; 
    
    text = get_string("Text:");
    p=text;
    
    while((*p=toupper(*p))){
       if (*p == '!' || *p == '.' || *p == '?')
            sentence ++;
        else if (*p >= 'A' && *p<= 'Z')
            letters ++;
        else if (*p == ' ')
            words ++;
        else 
            ;
        p++;
    }
    
    index=round(0.0588f*((float)letters/words*100)-0.296f*((float)sentence/words*100)-15.8);
    
    if(index<1)
        printf("Before Grade 1\n");
    else if(index>16)
        printf("Grade 16+\n");
    else 
        printf("Grade %d\n", index);
        
    return 0;
}
