#include<stdio.h>
#include<stdlib.h>

typedef struct dictionary{
  char status;
  unsigned short int opcode;
  unsigned short int no_of_operands;
  struct dictionary *nxt;
}Dictionary;

Dictionary *createDictionary(Dictionary *dict, char mnemonic[6], unsigned short int opcode, unsigned short int no_of_operands){
  Dictionary *tmph, *tmp;
  char c;
  int i, j;

  if(!dict)
    tmph = (Dictionary*)malloc(sizeof(Dictionary)*26);
  else
    tmph = dict;

  tmp = tmph;
  for(i=0; mnemonic[i]!='\0'; i++){
    if(mnemonic[i+1] == '\0'){
      tmp[mnemonic[i]-97].status = '1';
      tmp[mnemonic[i]-97].opcode = opcode;
      tmp[mnemonic[i]-97].no_of_operands = no_of_operands;
    }
    else{
      if(!tmp[mnemonic[i]-97].nxt)
	tmp[mnemonic[i]-97].nxt = (Dictionary*)malloc(sizeof(Dictionary)*26);
      tmp = tmp[mnemonic[i]-97].nxt;
    }
  }
  return tmph;
}

Dictionary *readDictFile(){
  FILE *fp;
  char buff[80], mnemonic[6];
  unsigned short int opcode, no_of_operands;
  Dictionary *dict=NULL;

  if(!(fp = fopen("testdict.txt","r"))){
    printf("\nError Opening the Mnemonics list file!!!");
    exit(1);
  }
  while(fgets(buff,80,fp) != NULL){
    sscanf(buff,"%s%hu%hu", mnemonic, &opcode, &no_of_operands);
    dict = createDictionary(dict,mnemonic,opcode,no_of_operands);
  }

  return dict;
}

void dispContent(Dictionary *hd){
  int i;
  for(i=0;i<26;i++)
    if(hd[i].nxt!=NULL || hd[i].status == '1'){
      printf("%c",i+97);
      if(hd[i].status != '1')
	dispContent(hd[i].nxt);
    }
  printf("\n");
}

Dictionary *mnemonicSearch(Dictionary *hd,char *mnemonic){
  if(*mnemonic>=97 && *mnemonic<=122){
    if(hd[*mnemonic-97].status=='1' && *(mnemonic+1)=='\0')
      return &(hd[*mnemonic-97]);
    else{
      if(hd[*mnemonic-97].nxt==NULL || *(mnemonic+1)=='\0')
	return NULL;
      else
	return mnemonicSearch(hd[*mnemonic-97].nxt,mnemonic+1);
    }
  }
  else
    return NULL;
}


int main(){
  Dictionary *head;
  char str[10];
  head = readDictFile();
  dispContent(head);
  /*  while(1){
    scanf("%s",str);
  if(mnemonicSearch(head,&str[0]))
    printf("\n1");
  else
    printf("\n0");
    }*/
  return 0;
}
