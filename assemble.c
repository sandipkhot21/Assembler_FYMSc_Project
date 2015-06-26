#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dictionary.h"
#include"assembleDS.h"
#include"textsect.h"

int main(int argc,char *argv[]){
  int i,ch;
  unsigned int lineno=0;
  char buff[400],section[3][6]={".data",".bss",".text"};
  char sect[]="section";
  char *t1=NULL,t2[20];
  FILE *fp;
  Dictionary *dh=NULL;

  if(argc<2){
    printf("\nError : Please provide File Name to  COMPILE!!!\n");
    exit(1);
  }
  if(!(fp=fopen(argv[1],"r"))){
    printf("\nError : Unable to open file %s !!!\n",argv[1]);
    exit(1);
  }

  dh = readDictFile();

  while(fgets(buff,400,fp)){
    t1=buff;
    lineno++;

    for(i=0; t1[i]==' ' || t1[i]=='\t'; i++,t1++);
    if(t1[i]==';' || t1[i]=='\n')
      continue;
    for(i=0; t1[i]!=' ' && t1[i]!='\n' && t1[i]!=';' && t1[i]!='\t' && t1[i]!='\0'; i++)
      t2[i]=t1[i];
    t2[i]='\0';

    if(strcmp(sect,t2)==0){
      t1+=i;
      t1++;
      for(i=0; t1[i]==' ' || t1[i]=='\t'; i++,t1++);
      for(i=0; t1[i]!=' ' && t1[i]!='\n' && t1[i]!=';' && t1[i]!='\t'; i++)
	t2[i]=t1[i];
      t2[i]='\0';
      if(strcmp(t2,section[0])==0){
	ch=1;
	continue;
      }
      else if(strcmp(t2,section[1])==0){
	ch=2;
	continue;
      }
      else if(strcmp(t2,section[2])==0){
	ch=3;
	continue;
      }
    }
    switch(ch){
      case 1:

	break;

      case 2:

	break;

      case 3:
	tokenTextLine(t1,dh,lineno);
	break;

      default:
	printf("\nError: Unrecognized instruction format");
	exit(1);
    }
  }

  return 0;
}

