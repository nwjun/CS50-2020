#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    FILE *fpin, *fpout ;
    BYTE buffer[512];
    char filename[8];
    int num = 0, byte;
    bool jpeg = false;
    
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./%s image\n", argv[0]);
        return(1);
    }
    
    if((fpin = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Can't open %s", argv[1]);
        return 1;
    }
    
    while((byte = fread(buffer, sizeof(BYTE), 512, fpin)) > 0 )
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if(jpeg == false)
            {
                sprintf(filename, "%03i.jpg", num);
            
                if((fpout = fopen(filename, "w")) == NULL)
                {
                    fprintf(stderr, "Can't open %s", filename);
                    return 1;
                }
                
                fwrite(buffer, sizeof(BYTE), byte, fpout);
                
                jpeg = true;
            }
            
            else
            {
                fclose(fpout);
                num ++;
                
                sprintf(filename, "%03i.jpg", num);
            
                if((fpout = fopen(filename, "w")) == NULL)
                {
                    fprintf(stderr, "Can't open %s", filename);
                    return 1;
                }
                
                fwrite(buffer, sizeof(BYTE), byte, fpout);
            }    
        }
        
        else
        {
            if(jpeg == true)
            {
                fwrite(buffer, sizeof(BYTE), byte, fpout);
            }
        }
    }
    fclose(fpin);

    return 0;
}
