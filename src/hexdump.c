#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/conv.h"
#include "../include/parser.h"
#include "../include/w_error.h"
#include "../include/ansi_c.h"
#define VAL_BUFFER 128

void w_error(char *msg)
{
    printf("%s",msg);
    exit(1);

}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("No command line arguments.");
        exit(EXIT_FAILURE);
    }
    struct parse_res result = parse_args(++argv,argc-1);
    
    if(result.state == FAILURE)
    {
        printf("%s",result.msg);
    }
    else if(result.state == SUCCESS)
    {
        if(result.file) //handle file hexdump
        {

        }
        else if(!result.file) //handle value hexdump
        {
            switch(result.val_conv.conv)
            {
                case CONV_HTOD:
                    break;
                case CONV_HTOB:
                    break;
                case CONV_HTOA:
                    break;
                case CONV_BTOH:
                    break;
                case CONV_BTOD:
                    break;
                case CONV_BTOA:
                    break;
                case CONV_DTOH:
                    if(!result.file)
                    {
                        //printf("%lu",result.val_conv.d_val);
                        char hex[] = {'A','B','C','D','E','F'};
                        char *res = (char*) malloc(sizeof(char) * VAL_BUFFER);
                        char *s_pt,*e_pt;
                        s_pt = e_pt =res;
                        memset(res, '\0', sizeof(char) * VAL_BUFFER);
                        int temp,dt,i,j;
                        char t,ptt;
                        unsigned long c = result.val_conv.d_val;
                        int m = c % 16;

                        do
                        {
                            temp = c%16;
                            if(temp > 9)
                            {
                                dt = temp - 10;
                                strncat(res,&hex[dt],1);
                            }
                            else
                            {
                                t = temp + '0';
                                strncat(res,&t,1);
                            }
                        } while((c = c/16) >= 1);
                        int len = strlen(s_pt);
                        for(i=0;i<len-1;i++)
                        {
                            e_pt++;
                        }
                        for(j=0;j<len/2;j++)
                        {
                            ptt = *s_pt;
                            *s_pt = *e_pt;
                            *e_pt = ptt;
                            e_pt--;
                            s_pt++;
                        }
                        printf(S"%s\n",res);

                    }
                    else 
                    {
                        w_error("FATAL ERROR: Wrong parse result. Aborting!");
                    }
                    break;
                case CONV_DTOB:
                    break;
                case CONV_DTOA:
                    break;
            }
        }
    }

    return 0;
}
