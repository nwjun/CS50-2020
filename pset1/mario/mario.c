#include <stdio.h>
#include <cs50.h>

void print_hashes(int level);
int get_height(string prompt);

int main(void){
    
	int height, level=1, i;
    
    height=get_height("Height (1-8): ");

	do{
		for(i=0; i<(height-level); i++)
			printf(" ");
		print_hashes(level);
		printf("  ");
		print_hashes(level);
		putchar('\n');
	}while(level++<height);

	return 0;
}

void print_hashes(int level){
	int j=0;

	while(j++<level)
		printf("#");
}

int get_height(string prompt)
{
    int n;
    
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n>8);
    
    return n;
}