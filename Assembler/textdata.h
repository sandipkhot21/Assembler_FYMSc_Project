int tokenDataLine(char *t,Dictionary *dh, unsigned int lineno){
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
