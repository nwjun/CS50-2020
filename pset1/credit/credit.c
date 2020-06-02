#include <stdio.h>
#include <cs50.h>

long first_two_digits(long a, int i);

int main(void)
{
    int product_sum = 0, sum = 0, i = 1, two_digits, product;
    long number, num2;
    
    do
    {
        number= num2 = get_long("Number: ");
    }
    while (number < 0);
    
    for (; number > 0; i++)
    {
        if (i % 2== 0)
        {
            product = (number % 10) * 2;
            
    /***if product is two digits***/        
            if (product > 9)
            {                          
                product_sum += product % 10;
                product /= 10;
                product_sum += product%10;
            }
            else
                product_sum += product;
        }
        
        else
        {
            sum += number%10;
        }
        number /= 10;
    }
    
    /***actual length of number***/
    i--;                                            
    two_digits= (int) first_two_digits(num2, i);
    
    if ((sum + product_sum) % 10 != 0 || i < 13)
        printf("INVALID\n");
        
    else
    {
        if (i == 15 && (two_digits == 34 || two_digits == 37))
            printf("AMEX\n");
        
        else if (i == 13)
            printf("VISA\n");
            
    /***length is 16***/
        else
        {                                       
            if (two_digits < 56 && two_digits > 50)
                printf("MASTERCARD\n");
            else if ((two_digits /= 10) == 4)
                printf("VISA\n"); 
            else
                printf("INVALID\n");
        }
    }
        return 0;
}

long first_two_digits(long a, int i)
{
    int j;
    
    for(j = 1; j < (i - 1); j++)
        a /= 10;
        
    return a;    
}