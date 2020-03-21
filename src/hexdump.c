#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "../include/conv.h"
#include "../include/parser.h"
#include "../include/w_error.h"
#include "../include/ansi_c.h"
#define VAL_BUFFER 1024

void w_error(char *msg)
{
    perror(msg);
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
        printf("%s\n",result.msg);
        exit(EXIT_FAILURE);
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
                        char *res;
                        if((res=(char*) malloc(sizeof(char) * VAL_BUFFER))==NULL)
                        {
                            printf("Could not allocate memory. Aborting!\n");
                            exit(EXIT_FAILURE);
                        }
                        int             temp,dt,i,j;
                        char            t,ptt;
                        unsigned long   c = result.val_conv.d_val;
                        int             m = c % 16;
                        char            *s_pt,*e_pt;
                        s_pt = e_pt = res;
                        memset(res, '\0', sizeof(char) * VAL_BUFFER);
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
                        printf(S"FATAL ERROR: Wrong parse result. Aborting!\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case CONV_DTOB:
                    ;
                    unsigned long val = result.val_conv.d_val; 
                    printf("%lu\n",val);
                    /* if(val == 0 || val == 1)
                       {
                       printf(S"%lu",val);
                       exit(EXIT_SUCCESS);
                       }*/
                    int i;
                    char            *st,*ptr;
                    unsigned long   p_val,c_val;;
                    double          c_bit = 1;
                    bool            first = true;
                    char            *arr;
                    if((st = (char*) malloc(sizeof(char) * VAL_BUFFER)) == NULL)
                    {
                        printf(S"Could not allocate memory. Aborting!\n");
                        exit(EXIT_FAILURE);
                    }
                    ptr=st;
                    memset(ptr,'0',sizeof(char)*VAL_BUFFER);
                    if((arr=malloc(sizeof(char) * sizeof(unsigned long))) == NULL)
                    {
                        printf(S"Could not allocate memory! Aborting!\n");
                        exit(EXIT_FAILURE);
                    }
                    int derp = 0;
                    p_val = c_val = 1;
                    while(val > 0)
                    {
                        while(val>=c_val)
                        {
                            p_val = c_val;
                            derp++;
                            c_bit++;
                            c_val = c_val * 2;
                        }
                        c_val = c_val - p_val;
                        c_bit--;
                        printf("c_val:%lu\n",c_val);
                        val = val - c_val;
                        for(i=0;i<c_bit-1;i++)
                        {
                            ptr++;
                        }
                        memset(ptr,'1',1);
                        if(first)
                        {
                            // printf("%f",c_bit);
                            memset(st,'0',c_bit-2);
                            first=false;
                            ptr++;
                            memset(ptr,'\0',1);
                        }
                        printf("val:%lu\n",val);
                        ptr=st;
                        p_val = c_bit = c_val = 1;
                    }
                    printf(S"%s",st);
                    break;
                case CONV_DTOA:
                    break;
            }
        }
    }

    return 0;
}
