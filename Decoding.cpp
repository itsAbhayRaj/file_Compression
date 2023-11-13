#include <iostream>
#include <string.h>
#include <malloc.h>
#include "compression.h"

using namespace std;


codeTable *codelist;

int n;
char *decodeBuffer(char buffer);
char *int2string(int n);
int match(char a[],char b[],int limit);
int fileError(FILE *fp);

int main(int argc, char** argv)
{
    FILE *fp,*outfile;
    char buffer;
    char *decoded;
    int i;

    if(argc<=2)
    {
        printf("***Huffman Decoding***\n");
        if(argc==2)
        {
            argv[2]=(char *)malloc(sizeof(char)*(strlen(argv[1])+strlen(decompressed_extension)+1));
            strcpy(argv[2],argv[1]);
            strcat(argv[2],decompressed_extension);
            argc++;
        }
        else	
            return 0;
    }
    if((fp=fopen(argv[1],"rb"))==NULL)
    {
        printf("[!]Input file cannot be opened.\n");
        return -1;
    }

    printf("\n[Reading File Header]");
    if(fread(&buffer,sizeof(unsigned char),1,fp)==0) return (fileError(fp));
        N=buffer;		
    if(N==0)
        n=256;
    else
        n=N;
    printf("\nDetected: %u different characters.",n);

    codelist=(codeTable *)malloc(sizeof(codeTable)*n);

    printf("\nReading character to Codeword Mapping Table");
    if(fread(codelist,sizeof(codeTable),n,fp)==0) return (fileError(fp));
    /*
    printf("\n");
    for(i=0;i<n;i++)
        printf("[%c|%s] ",symlist[i].x,symlist[i].code);
    */

    if(fread(&buffer,sizeof(char),1,fp)==0) return (fileError(fp));
        padding=buffer;		
    printf("\nDetected: %u bit padding.",padding);

    if((outfile=fopen(argv[2],"wb"))==NULL)
    {
        printf("[!]Output file cannot be opened.\n");
        fclose(fp);
        return -2;
    }

    printf("\n\n[Reading data]\nReplacing codewords with actual characters");
    while(fread(&buffer,sizeof(char),1,fp)!=0)	
    {
        decoded=decodeBuffer(buffer);	
        i=0;
        while(decoded[i++]!='\0');	
        //printf("%s",decoded);
        fwrite(decoded,sizeof(char),i-1,outfile);
    }
    fclose(fp);
    fclose(outfile);
    printf("\nEverything fine..\nOutput file %s written successfully.\n",argv[2]); 
    return 0;
}

char *decodeBuffer(char b)
{
    int i=0,j=0,t;
    static int k;
    static int buffer;	
    char *decoded=(char *)malloc(MAX*sizeof(char));
    

    t=(int)b;
    //printf("\nt=%sk=%d",int2string(t),k);
    t=t & 0x00FF;		
    //printf("\nt=%sk=%d",int2string(t),k);
    t=t<<8-k;
    //printf("\nt=%sk=%d",int2string(t),k);
    buffer=buffer | t;	
    k=k+8;		
    if(padding!=0)	
    {buffer=buffer<<padding;
    k=8-padding;	
    padding=0;}

    //printf("\nbuffer=%s, k=%d",int2string(buffer),k);

    while(i<n)
    {
        if(!match(codelist[i].code, int2string(buffer),k))
        {	
            decoded[j++]=codelist[i].x;	
            t=strlen(codelist[i].code);	
            buffer=buffer<<t;		
            k=k-t;				
            i=0;				 
            // printf("\nBuffer=%s,removed=%c,k=%d",int2string(buffer),decoded[j-1],k);
            if(k==0) break;
            continue;
        }
    i++;
    }

    decoded[j]='\0';
    return decoded;

}

int match(char a[],char b[],int limit)
{
    b[strlen(a)]='\0';
    b[limit]='\0';
    return strcmp(a,b);
}

char *int2string(int n)
{
    int i,k,andd,j;
    char *temp=(char *)malloc(16*sizeof(char));
    j=0;

    for(i=15;i>=0;i--)
    {
        andd=1<<i;
        k=n & andd;
        if(k==0) temp[j++]='0'; else temp[j++]='1';
    }
    temp[j]='\0';
    return temp;
}

int fileError(FILE *fp)
{
    printf("[!]File read Error.\n[ ]File is not compressed using huffman.\n");
    fclose(fp);
    return -3;
}
