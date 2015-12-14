#include<stdio.h>
#include<string.h>

#include"hash.h"
#include"sds.h"
#include"call.h"
#include"cmd_parse.h"


//parrse recv_string to command struct
list * recv_parse(char *command)
{

	 char * token;
	//printf("%s",command);

     token = strtok(command," \n\0");
	 list * cmd_list_head;

	 cmd_list_head = cmd_list_init(token);
	 

	 while(token!=NULL)
	 {
	  token = strtok(NULL," \n\0");
	  if (token)
      cmd_list_append(cmd_list_head,token);
	 }


     listNode * current = (cmd_list_head->head);
       
	 while (current)
	 { 
		 current=current->next;
	 }
	 return cmd_list_head;
}

//parrse command and call
char *  cmd_parse(hashTable *table,list *cmd_list_head)
{
      char * cmd_name = (cmd_list_head ->head)->value;          
      
      int i;
	  for (i=0;i<43;i++)
	  {
		  if (strcmp(cmd_name,commandtable[i])==0)	  {
				break;
		  }
	  }
     printf("Runing command is %s\n",commandtable[i]);  
	 if (i==43)
	 {
		 return "Command Not Found!!";
	 }
     return  call(table,i,cmd_list_head);
}



