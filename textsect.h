
void fillSymTabLabel(char *label ,unsigned int lineno){
  ST *symtmp,*t1;

  if(label!=NULL){
      symtmp=(ST*)malloc(sizeof(ST));
      strcpy(symtmp->sname,label);
      symtmp->saddr=lineno;
      symtmp->type=slabel;
      symtmp->nxt=NULL;
      
      if(symHd==NULL){
	  symHd=symtmp;
	  symtmp->sid=0;
      }
      else{
	for(t1=symHd;t1->nxt!=NULL;t1=t1->nxt);
	t1->nxt=symtmp;
	symtmp->sid=t1->sid + 1;
      }
  }
}

void fillTII(char *symbol, unsigned int sid){
  TII * tiitemp, *t1;

  tiitemp = (TII*)malloc(sizeof(TII));
  strcpy(tiitemp->symb,symbol);
  tiitemp->addr = sid;
  tiitemp->nxt = NULL;

  if(tiiHd == NULL)
    tiiHd = tiitemp;
  else{
    for(t1=tiiHd; t1->nxt!=NULL; t1=t1->nxt);
    t1->nxt = tiitemp;
  }
}

void fillSymTabOperand(char *operand){
  ST *symtmp, *t1;
  for(symtmp=symHd; symtmp!=NULL; symtmp=symtmp->nxt){
    if(strcmp(symtmp->sname, operand)==0){
      symtmp->used=1;
      return;
    }
  }
  symtmp = (ST*)malloc(sizeof(ST));
  strcpy(symtmp->sname, operand);
  symtmp->nxt = NULL;
  
  if(symHd == NULL){
    symHd = symtmp;
    symtmp->sid = 0;
  }
  else{
    for(t1=symHd; t1->nxt!=NULL; t1=t1->nxt);
    t1->nxt = symtmp;
    symtmp->sid = t1->sid + 1;
  }
  symtmp->used = 1;
  if(symtmp->decl != 1)
    fillTII(operand, symtmp->sid);
}
/*
char* checkOperand(char *operand){
  int i;
  for(i=0;operand[i]!='\0';i++){
    str
  }
}
*/
int tokenTextLine(char *t,Dictionary *dh, unsigned int lineno){
  char label[80],mnemonic[6],operand1[80],operand2[80];
  int i;
  Dictionary *td;
  
  for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
  label[0] = mnemonic[0] = operand1[0] = operand2[0] = '\0';
  
  for(i=0; t[i]!='\n' && t[i]!=';'; i++){
    if(t[i]==':'){
      strncpy(label,t,i);
      label[i]='\0';
      fillSymTabLabel(label,lineno);
      t += i;
      t++;

      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]=='\n' || t[i]=='\0')
	break;
      
      for(i=0; t[i]!=' ' && t[i]!='\n' && t[i]!='\0' && t[i]!=';'; i++)
	mnemonic[i] = t[i];
      mnemonic[i] = '\0';
      t += i;
      t++;
      
      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]=='\n' || t[i]=='\0')
	break;
	  
      for(i=0; t[i]!=' ' && t[i]!=',' && t[i]!='\n' && t[i]!='\0' && t[i]!=';'; i++)
	operand1[i] = t[i];
      operand1[i] = '\0';
      if(t[i]==' ')
	for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      t += i;
      t++;
      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]==','){
	printf("\nError: More than one seperator used!!!");
	exit(1);
      }

      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]=='\n' || t[i]=='\0')
	break;

      for(i=0; t[i]!=' ' && t[i]!='\n' && t[i]!='\0' && t[i]!=';'; i++)
	operand2[i] = t[i];
      operand2[i] = '\0';
      t += i;
      break;
    }
    else if(t[i]==' ' || t[i]=='\0' || t[i]=='\n' || t[i]==EOF){
      strncpy(mnemonic,t,i);
      mnemonic[i]='\0';
      t += i;
      t++;

      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]=='\n' || t[i]=='\0')
	break;
      
      for(i=0; t[i]!=' ' && t[i]!=',' && t[i]!='\n' && t[i]!='\0' && t[i]!=';'; i++)
	operand1[i] = t[i];
      operand1[i] = '\0';
      if(t[i]==' ')
	for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      t += i;
      t++;
      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]==','){
	printf("\nError: More than one seperator used!!!");
	exit(1);
      }

      for(i=0; t[i]==' ' || t[i]=='\t'; i++,t++);
      if(t[i]=='\n' || t[i]=='\0')
	break;
      
      for(i=0; t[i]!=' ' && t[i]!='\n' && t[i]!='\0' && t[i]!=';'; i++)
	operand2[i] = t[i];
      operand2[i] = '\0';
      t += i;
      break;
    }
  }

  td = mnemonicSearch(dh,mnemonic);

  printf("\n%d",lineno);
  if(td!=NULL)
    printf("\t%c\t%s\t%s\t%hu\t%hu",td->status,label,mnemonic,td->opcode,td->no_of_operands);
  
  return 0;
}

