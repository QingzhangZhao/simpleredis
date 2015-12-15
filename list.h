typedef struct listNode{

	//the previos listnode
	struct listNode *prev;

	//the next listnode
	struct listNode *next;

	//the value 
	void *value;
}listNode;


typedef struct list{
      
	listNode *head;

	listNode *tail;

	int len;
}list;

//create the first listnode
list * cmd_list_init(char *value);

void cmd_list_append(list *head,char *value);


void cmd_list_lpush(list *head,char *value);




void * cmd_list_lget(list *head);

void * cmd_list_rget(list *head);

void cmd_list_rpop(list *head);

void cmd_list_lpop(list *head);

int  cmd_list_llen(list *head);

void * cmd_list_lindex(list *head,int count);

void * cmd_list_lset(list *head,int count,void *value);











