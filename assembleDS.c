typedef struct symtab{
  unsigned short int sid;
  char sname[32];
  unsigned int saddr;
  void *sval;
  enum name{slabel,sbyte,sword,sdouble,squad}type;
  char decl, used;
  unsigned short int len;
  struct symtab *nxt;
}ST;

typedef struct littab{
  unsigned short int lid;
  int val;
  unsigned int laddr;
}LT;

typedef struct errtab{
  unsigned short int eid;
  char *estr;
  struct errtab *nxt;
}ET;

typedef struct tabincinst{
  char *symb;
  unsigned int addr
  struct symtab *nxt;
}TII;


ST *symHd=NULL;
LT *lytHd=NULL;
ET *errHd=NULL;
TII *tiiHd=NULL;

char REGISTER[8][] = {"EAX","EBX","ECX","EDX","ESI","EDI","ESP","EBP"};
