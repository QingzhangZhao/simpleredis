#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"hash.h"
#include"sds.h"
#include"call.h"
//if call run sucess return 1
//else return 0
char * call(hashTable *table,int i,list *cmd_list_head)
{
	listNode * node=(cmd_list_head->head);
	
	char * key;
	int len = cmd_list_head->len;
	
	//printf("len=%d\n",len);
	if (len>=2){
        key = (node->next)->value;
	}
	//command is "set"
	if (i==0)
	{
        if(len!=3)
			return "(error) ERR wrong number of arguments for 'set' command";
		 node=(node->next)->next;
		 char * value = node->value;
		 int i;int flag=2;
		 for (i=0;i<strlen(value);i++)
		 {
			 if ((value[i])>='0'&&(value[i])<='9')
				 continue;
			 else
			 {
				 flag=1;
				 break;
		     }
		 }
		printf("flag=%d\n",flag);
		sds* t_key= new_sds(key);
		sds* t_value = new_sds(value);
		// memcpy(t_key,key,strlen(key));
		//memcpy(t_value,value,strlen(value));
		 addTable(table,t_key,t_value,flag);   
		
		 return "OK!";
	}

	//command is "get"
	else if (i==1)
	{ 
		if(len!=2)
	      return "(error) ERR wrong number of arguments for 'get' command";
	    hashNode *node =getTable(table,key);
	  if (node)
		  if(node->type==1||node->type==2)
	  {
	    sds  *value =(getTable(table,key))->value;
		printf("get value = %s\n",value->buf);
	    return value->buf;
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";
	
	}
	//command is "incr"
	else if (i==2)			
	{
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'incr' command";
		hashNode *node = getTable(table,key);
		if(node->type==2)
		{
			int n = atoi(((sds *)(node->value))->buf);
			printf("n=%d\n",n);
			n=n+1;

			char * str = malloc(sizeof(((sds *)(node->value))->buf)+1);
		    sprintf(str,"%d",n);
			
			if (strlen(str)>(((sds *)(node->value))->len))
			{
                ((sds *)(node->value))->len+=1;
			    free(((sds *)(node->value))->buf);
				((sds *)(node->value))->buf=str;
			}
			else 
			{
			    free(((sds *)(node->value))->buf);
				((sds *)(node->value))->buf=str;
			}
				return str;  
		}
		else 
			return "(error) ERR value is not an integer or out of range";

	}
	//command is "decr"
	else if (i==3)
	{
        if (len!=2)
			return "(error) ERR wrong number of arguments for 'decr' command";
		hashNode *node = getTable(table,key);
		if(node->type==2)
		{
			int n = atoi(((sds *)(node->value))->buf);
			printf("n=%d\n",n);
			n=n-1;

			char * str = malloc(sizeof(((sds *)(node->value))->buf)+1);
		    sprintf(str,"%d",n);
			
			if (strlen(str)>(((sds *)(node->value))->len))
			{
                ((sds *)(node->value))->len+=1;
			    free(((sds *)(node->value))->buf);
				((sds *)(node->value))->buf=str;
			}
			else 
			{
			    free(((sds *)(node->value))->buf);
				((sds *)(node->value))->buf=str;
			}
				return str;  
		}
		else 
			return "(error) ERR value is not an integer or out of range";
	}
	//command is "incrby"
	else if (i==4)
	{
       	node=(node->next)->next;
		char * value = node->value;

        if (len!=3)
			return "(error) ERR wrong number of arguments for 'incrby' command";
		hashNode *node = getTable(table,key);
		if(node->type==2)
		{
			int n = atoi(((sds *)(node->value))->buf);
			printf("n=%d\n",n);
			int add = atoi (value);
			
			n=n+add;

			char * str = malloc(sizeof(((sds *)(node->value))->buf)+sizeof(value));
		    sprintf(str,"%d",n);
            ((sds *)(node->value))->len=strlen(str);
			free(((sds *)(node->value))->buf);
			((sds *)(node->value))->buf=str;
			return str;  
		}
		else 
			return "(error) ERR value is not an integer or out of range";

	}
	//command is "decrby"
	else if (i==5)
	{

     	node=(node->next)->next;
		char * value = node->value;

        if (len!=3)
			return "(error) ERR wrong number of arguments for 'incrby' command";
		hashNode *node = getTable(table,key);
		if(node->type==2)
		{
			int n = atoi(((sds *)(node->value))->buf);
			printf("n=%d\n",n);
			int minus= atoi (value);
			
			n=n-minus;

			char * str = malloc(sizeof(((sds *)(node->value))->buf)+sizeof(value));
		    sprintf(str,"%d",n);
            ((sds *)(node->value))->len=strlen(str);
			free(((sds *)(node->value))->buf);
			((sds *)(node->value))->buf=str;
			return str;  
		}
		else 
			return "(error) ERR value is not an integer or out of range";
	}
	//command is "strlen"
	else if (i==6)
	{
		if(len!=2)
			return "(error) ERR wrong number of arguments for 'strlen' command";
		
		hashNode *node = getTable(table,key);
		if (node)
		{
			int n =((sds *)(node->value))->len;
			char * str = malloc(sizeof(char *) *  (((sds *)(node->value))->len));
		    sprintf(str,"%d",n);
			printf("strlen = n",n);

			return str;
		}
		else
			return "0";
	}
	//command is "del"
	else if (i==7)
	{
	 if (len!=2)
		 return "(error) ERR wrong number of arguments for 'del' command"; 
	 hashNode *node=getTable(table,key);
	 if(node)
	 {
		 removeTable(table,key);
	  
		 return  "(integer) 1";
	 }
	 else
		 return "(integer) 0";
	}
    //command is "exists"
	else if  (i==8)
	{
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'exists' command";
		hashNode *node = getTable(table,key);
		if(node)
			return "(integer) 1";
		else 
			return "(integer) 0";
	}
	//command is "randomkey"
	else if (i==9)
	{
		list * keys =keysTable(table);
		if (keys)
		{
			srand((int)time(NULL));
			int r=((rand())%(keys->len));
			listNode *p = keys->head;
            int j;
			 for (j=0;j<r;j++)
			 {
				 p=p->next;
			 }
            char * s = p->value;
			return s;
		}
	}
	//command is "keys"
	else if (i==10)
	{
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'keys' command"; 
		list * keys =keysTable(table);
		if (keys)
		{
            char *str = malloc(sizeof(char)*200);
			memset(str,0,sizeof(char)*200);
			listNode * p = keys->head;
			for (p;p;p=p->next)
			{
				printf("keys = %s\n",p->value);
				strcat(str,p->value);
				strcat(str,"\n");
			}
		    return str; 
		}
	}
	//command is "type"
	else if (i==11)
	{
		if(len!=2)
			return "(error) ERR wrong number of arguments for 'keys' command";
        hashNode *node =getTable(table,key);
		if(node)
		{
			int t = node->type;
			switch(t)
			{
				case 0:
					return "unknown";
				case 1:
				case 2:
					return "string";
				case 3:
					return "list";
				case 4:
					return "hash";
				case 5:
					return "set";
				default:
					return "Error!";
			}
		}else
			return "none";

	}
	//command is "append"
    else if (i==12)
	{
		if (len!=3)
				return "(error) ERR wrong number of arguments for 'append' command";
        node=(node->next)->next;
		char * value = node->value;
		hashNode * hnode =getTable(table,key);
		if (hnode)
		{
		    (hnode->value) =sds_append((sds *)(hnode->value),value);
			return "OK!";
		}
		else
		{
		 int i;int flag=2;
		 for (i=0;i<strlen(value);i++)
		 {
			 if ((value[i])>='0'&&(value[i])<='9')
				 continue;
			 else
			 {
				 flag=1;
				 break;
		     }
		 }
		printf("flag=%d\n",flag);
		sds* t_key= new_sds(key);
		sds* t_value = new_sds(value);
		addTable(table,t_key,t_value,flag);   
		return "OK!";
		}
	}


	//command is "msetnx"
	else if (i==13)
	{
		return "Unsupport command now!";
		//if(len<3||(len-1)%2!=0)
		//	return "";

	}
	//command is "setrange"
	else if (i==14)
	{
		if (len!=4)
			return "(error) ERR wrong number of arguments for 'setrange' command";
        node=(node->next)->next;
		char * value = node->value;
		node =node->next;
		char *s =node->value;
		hashNode * hnode =getTable(table,key);
		if (hnode)
		{
         sds_setrange((sds *)(hnode->value),atoi(s),value);
		 return "OK!";
		}
	}
	//command is "getrange"
    else if (i==15)
	{ 
		return "now support yet!";
	}

	//command is "lpush"
	else if (i==16)
	{
		if (len!=3)
			return "(error) ERR wrong number of arguments for 'setrange' command";
		node=(node->next)->next;
		char * value = node->value;
	
		hashNode * hnode =getTable(table,key);
		if (hnode)
			if (hnode->type ==3)
			{
			   cmd_list_lpush((list *)(hnode->value),value);
		       return "OK!";
			}
			else
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
		  else 
		{
			list * l = cmd_list_init(value);
		    sds* t_key= new_sds(key);
		    addTable(table,t_key,l,3);   
		    return "init OK!";
		}

	}
	//command is "rpush"
	else if (i==17)
	{
        if (len!=3)
			return "(error) ERR wrong number of arguments for 'setrange' command";
		node=(node->next)->next;
		char * value =malloc(sizeof(char)*strlen(node->value));
	      strcpy(value,node->value);
		hashNode * hnode =getTable(table,key);
		if (hnode)
			if (hnode->type ==3)
			{
			   cmd_list_append((list *)(hnode->value),value);
			   printf("append value =%s\n",(((list *)(hnode->value))->head)->value);
		       return "rpush OK!";
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
		else 
		{
			list * l = cmd_list_init(value);
		    sds* t_key= new_sds(key);
		    addTable(table,t_key,l,3);   
		    return "init OK!";
		}
	}
    //command is "lpop"
	else if (i==18)
	{
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'lpop' command";
	    hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(node->value))->head)
			    if (hnode->type ==3)
			{
		        char * str =  malloc(sizeof(char )*50);
				memset(str,0,sizeof(char)*50);
				strcpy(str,cmd_list_lget((list *)(hnode->value))); 
				cmd_list_lpop((list *)(hnode->value));
				return str;
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(nill)";
		else
		   return "(nil)";
	}
    //command is "rpop"
    else if (i==19)
	{
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'rpop' command";
	    hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(node->value))->head)
			    if (hnode->type ==3)
			{
		        char * str =  malloc(sizeof(char )*50);
				memset(str,0,sizeof(char)*50);
				strcpy(str,cmd_list_rget((list *)(hnode->value))); 
				cmd_list_rpop((list *)(hnode->value));
				return str;
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(nill)";
		else
		   return "(nil)";
		



	}
	//command is "llen"
	else if (i==20)
	{
		if(len!=2)
			return "(error) ERR wrong number of arguments for 'llen' command";	
		hashNode * hnode =getTable(table,key);
		if (hnode)
		    if (hnode->type==3)
		{ 
			int l = cmd_list_llen((list *)(hnode->value));
            char *a=malloc(sizeof(char)*3);
			sprintf(a,"%d",l);
			return a;

		}
		   else
			   return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
		else 
			return "(integer) 0";

	}
	//command is "getbit"
	
	//command is "setbit"
	
	//command is "bitcount"
	
}













































































































































































































































