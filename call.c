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
			return "(error) ERR wrong number of arguments for 'lpush' command";
		node=(node->next)->next;
        char * value =malloc(sizeof(char)*strlen(node->value));	
        strcpy(value,node->value);

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
			return "(error) ERR wrong number of arguments for 'rpush' command";
		
		node=(node->next)->next;
		char * value =malloc(sizeof(char)*strlen(node->value));
	    strcpy(value,node->value);

		hashNode * hnode =getTable(table,key);
		if (hnode)
			if (hnode->type ==3)
			{
			   cmd_list_append((list *)(hnode->value),value);
			   printf("append value =%s\n",value);
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
			if (((list *)(hnode->value))->head)
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
				return "(data nill)";
		else
		   return "(key nil)";
	}

	//bug?
    //command is "rpop"
    else if (i==19)
	{
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'rpop' command";
	    hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(hnode->value))->tail)
			    if (hnode->type ==3)
			{
				printf("tail exists!\n");
		        char * str =  malloc(sizeof(char )*50);
				memset(str,0,sizeof(char)*50);
				strcpy(str,cmd_list_rget((list *)(hnode->value))); 
				cmd_list_rpop((list *)(hnode->value));
				return str;
			}
			    else 
		           return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(rpop data nill)";
		else
		   return "(key nil)";
		



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

	//cmomand is "hdel"
	else if (i==21)
	{
       if(len!=3)
	      return "(error) ERR wrong number of arguments for 'hdel' command";
	    hashNode *hnode =getTable(table,key);
	  if (hnode)
		  if(hnode->type==4)
	  {
       	 node=(node->next)->next;
		 char * t_key  = node->value;

	    hashTable   *t = ((getTable(table,key))->value);
		hashNode * f_node = getTable(t,t_key);

		if (f_node)
		{
			removeTable(t,t_key);
			return "(integer) 1";

		}
		else 
			return "(integer) 0";

	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(integer) 0";

	}

	//cmomand is "hlen"
	else if (i==22)
	{
       if(len!=2)
	      return "(error) ERR wrong number of arguments for 'hlen' command";
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==4)
	  {
	    hashTable   *t = ((getTable(table,key))->value);
		int n =t->used;
		char * str = malloc(sizeof(char)*10);
		sprintf(str,"%d",n);
		return str;
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";



	}

  	//cmomand is "hexists"
	else if (i==23)
	{
      if(len!=3)
	      return "(error) ERR wrong number of arguments for 'hexists' command";
	    hashNode *hnode =getTable(table,key);
	  if (hnode)
		  if(hnode->type==4)
	  {
       	 node=(node->next)->next;
		 char * t_key  = node->value;

	    hashTable   *t = ((getTable(table,key))->value);
		hashNode * f_node = getTable(t,t_key);

		if (f_node)
		{
			return "(integer) 1";

		}
		else 
			return "(integer) 0";

	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(integer) 0";

	}

	//cmomand is "hget"
	else if (i==24)
	{
 
		if(len!=3)
	      return "(error) ERR wrong number of arguments for 'hget' command";
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==4)
	  {
       	 node=(node->next)->next;
		 char * t_key  = node->value;


	    hashTable   *t = ((getTable(table,key))->value);
		hashNode * f_node = getTable(t,t_key);

		if (f_node)
		{
			sds * value = f_node->value;
			return value->buf;

		}
		else 
			return "(nil)";

	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";


	}

	//cmomand is "hset"
	else if (i==25)
	{
         if(len!=4)
			return "(error) ERR wrong number of arguments for 'hset' command";
		 node=(node->next)->next;
		 char * filed  = node->value;
		 node = (node->next);
		 char *value = node->value;
		 int i;
		 int flag=2;
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
	   hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==4)
	   {
	     hashTable   *t = ((getTable(table,key))->value);
		 hashNode * f_node = getTable(t,filed);
		 if (f_node)
		 {
           sds *t_value = new_sds(value); 
		   sds * t_filed=new_sds(filed);
			sds * value = f_node->value;
			removeTable(t,filed);
			addTable(t,t_filed,t_value,flag);
			return "change it!!(integer) 1";
		 }
		 else
		 {
            sds *t_value = new_sds(value); 	
		    sds * t_filed=new_sds(filed);
		    addTable(t,t_filed,t_value,flag);
			return "(integer) 1";
		 }
	   }
	     else
		   return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
        else
		{
		  sds* t_key= new_sds(key);
          sds *t_value = new_sds(value); 
		
		
		  sds * t_filed=new_sds(filed);
		
          hashTable * t = new_Table(3);
	      addTable(t,t_filed,t_value,flag);
		  addTable(table,t_key,t,4);   
		 return "(integer) 1";
		}

	}
	//cmomand is "hincrby"
	else if (i==26)
	{

        if (len!=4)
			return "(error) ERR wrong number of arguments for 'incrby' command";	
		node=(node->next)->next;
		char * filed  = node->value;
		node = (node->next);
		char *value = node->value;

        hashNode *hnode =getTable(table,key);
	    if (hnode)
		  if(hnode->type==4)
	  { 
	    hashTable   *t = ( (getTable(table,key))->value);
		hashNode * f_node = getTable(t,filed);
		if (f_node)
		{	
			if (f_node->type==2)
			{

			    sds * t_value = f_node->value;
                int n = atoi(t_value->buf);
			    printf("n=%d\n",n);
			    int add = atoi (value);
			    n=n+add;
			    char * str = malloc(sizeof(char)*50);
		        sprintf(str,"%d",n);
                ((sds *)(f_node->value))->len=strlen(str);
			    free(((sds *)(node->value))->buf);
			    ((sds *)(f_node->value))->buf=str;
			    return str;  
			}
			else
				return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";

		}
		else 
			return "(nil)";
	  }
		  else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";
	}




	//cmomand is "hincrbyfloat"
	else if (i==27)
	{
        if (len!=4)
			return "(error) ERR wrong number of arguments for 'incrbyfloat' command";	
		node=(node->next)->next;
		char * filed  = node->value;
		node = (node->next);
		char *value = node->value;

        hashNode *hnode =getTable(table,key);
	    if (hnode)
		  if(hnode->type==4)
	  { 
	    hashTable   *t = ( (getTable(table,key))->value);
		hashNode * f_node = getTable(t,filed);
		if (f_node)
		{	
			if (f_node->type==2||f_node->type==1)
			{

			    sds * t_value = f_node->value;

			    char* p1;
				char *p2;
				float f1,f2;
				f1 = strtof (t_value->buf, &p1);
			    f2 = strtof(value,&p2);
			    float result = f1+f2;
				char * str = malloc(sizeof(char)*50);
		        
				sprintf(str,"%f",result);
                
				((sds *)(f_node->value))->len=strlen(str);
			    
				free(((sds *)(node->value))->buf);
			   
				((sds *)(f_node->value))->buf=str;
			    
				f_node->type=1;

				return str;  
			}
			else
				return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
		}
		else 
			return "(nil)";
	  }
		  else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";
	}


	//cmomand is "hkeys"
	else if (i==28)
	{
        if (len!=2)
			return "(error) ERR wrong number of arguments for 'hkeys' command"; 
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==4)
	  {
		list * keys =keysTable(hnode->value);
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
		else 
			return "(nil)";
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";

	}


	//cmomand is "hvals"
	else if (i==29)
	{
	   if(len!=2)
	      return "(error) ERR wrong number of arguments for 'hvals' command";
           hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==4)
	  {
		list * keys =keysTable(hnode->value);
		if (keys)
		{
            char *str = malloc(sizeof(char)*200);
			memset(str,0,sizeof(char)*200);
			listNode * p = keys->head;
			for (p;p;p=p->next)
			{
			
	            hashTable   *t = ((getTable(table,key))->value);
		        hashNode * f_node = getTable(t,p->value);
			    sds * value = f_node->value;
				strcat(str,value->buf);
				strcat(str,"\n");
		   }
			return str;
		}
		else 
		    return "(empty list or set)";
	  }
		  else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";
	}


	//cmomand is "hmset"
	else if (i==30)
	{
		return "not support yet!";
	}

	//cmomand is "sadd"
	else if (i==31)
	{
	    if(len!=3)
			return "(error) ERR wrong number of arguments for 'hset' command";
		 node=(node->next)->next;
		 char * member  = node->value;
	   hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==5)
	   {
	     hashTable   *t = ((getTable(table,key))->value);
		 hashNode * f_node = getTable(t,member);
		 if (f_node)
		 {
		   return "member already exists!";
		 }
		 else
		 {
            sds *t_member = new_sds(member); 	
		    addTable(t,t_member,t_member,5);
			return "(integer) 1";
		 }
	   }
		  else
		   return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
        else
		{
          sds *t_member = new_sds(member); 
          sds * t_key =new_sds(key); 
		  hashTable * set = new_Table(3);
		  addTable(set,t_member,NULL,5);
		  addTable(table,t_key,set,5);   
		 return "set init ok!";
		}
	}
	//cmomand is "smove"
	else if (i==32)
	{
      if(len!=4)
	      return "(error) ERR wrong number of arguments for 'smove' command";
	  
	  hashNode *hnode =getTable(table,key);
	  
	  if (hnode)
		  if(hnode->type==5)
	  {
       	 node=(node->next)->next;
		 char * dst  = node->value;
		 node=node->next;
         char * member = node->value;
	    
		hashTable   *t = ((getTable(table,key))->value);
		hashNode * f_node = getTable(t,member);

		//src exists
		if (f_node)
		{

		 //dst exists
          if (getTable(table,dst))
		  {
			  if((getTable(table,dst)->type)==5)
			  {
			   hashTable   *dst_t = ((getTable(table,dst))->value);
			  
			 //add member to dst
			   sds *t_member = new_sds(member); 	
		       addTable(dst_t,t_member,t_member,5); 
			 //remove member in src
			   removeTable(t,member);
			   return "move OK!";
			  }
			  else
				  return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	     }
		 //dst not exist 
		 //init it and do command
		  else 
		  {
                   sds *t_member = new_sds(member); 
                  sds * t_key =new_sds(dst); 
		          
				  hashTable * set = new_Table(3);
				  //add member to dst 
		          addTable(set,t_member,NULL,5);
		          addTable(table,t_key,set,5);   
				  //remove member in src
            	  removeTable(t,member);
			      return "move OK!";
		  }
		}
		else
			return "(integer) 0";
		} else
	 	   return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else 
		return "(integer) 0";

	
	}






	//cmomand is "scard"
	else if (i==33)
	{
       if(len!=2)
	      return "(error) ERR wrong number of arguments for 'hlen' command";
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==5)
	  {
	    hashTable   *t = ((getTable(table,key))->value);
		int n =t->used;
		char * str = malloc(sizeof(char)*10);
		sprintf(str,"%d",n);
		return str;
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";
	}

	//cmomand is "spop"
	else if (i==34)
	{
     if (len!=2)
			return "(error) ERR wrong number of arguments for 'spop' command"; 
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==5)
	  {
		list * keys =keysTable(hnode->value);
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
            char *str = malloc(sizeof(char)*strlen(s));
			strcpy(str,s);
			removeTable(hnode->value,str);
			return str;
		}
		else 
			return "(nil)";
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";


	}


	//cmomand is "sdiff"
	else if (i==35)
	{
		if (len!=3)
			return "(error) ERR wrong number of arguments for 'sunion' command"; 
		//get the  smallest scard of s1 and s2 
		node=(node->next)->next;
		char * key_2 = node->value;
	    hashNode *hnode =getTable(table,key);
		hashNode *node_2 = getTable(table,key_2);
	   if (hnode)
		  if(hnode->type==5)
		  {
	        list * keys =keysTable(hnode->value);
			  if (keys)
		{
            char *str = malloc(sizeof(char)*200);
			memset(str,0,sizeof(char)*200);
			listNode * p = keys->head;
			for (p;p;p=p->next)
			{

	  		    hashTable   *t_2 = (node_2->value);
				hashNode * f_node = getTable(t_2,p->value);
				if (f_node);
				else
				{
					strcat(str,p->value);
					strcat(str,"\n");
				}
			}
		      return str;
		}
			  else
			  return "(null)";
		  }	 else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(null)";

	}

	//cmomand is "srandmember"
	else if (i==36)
	{
        if (len!=2)
			return "(error) ERR wrong number of arguments for 'srandmember' command"; 
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==5)
	  {
		list * keys =keysTable(hnode->value);
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
		else 
			return "(nil)";
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";

	}

	//cmomand is "srem"
	else if (i==37)
	{

      if(len!=3)
	      return "(error) ERR wrong number of arguments for 'srem' command";
	  hashNode *hnode =getTable(table,key);
	  if (hnode)
		  if(hnode->type==5)
	  {
       	 node=(node->next)->next;
		 char * t_member = node->value;

	    hashTable   *t = ((getTable(table,key))->value);
		hashNode * f_node = getTable(t,t_member);

		if (f_node)
		{
			removeTable(t,t_member);
			return "(integer) 1";

		}
		else 
			return "(integer) 0";

	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(integer) 0";
	}


	//cmomand is "sinter"
	else if (i==38)
	{
		if (len!=3)
			return "(error) ERR wrong number of arguments for 'sunion' command"; 
		//get the  smallest scard of s1 and s2 
        int s1,s2;
		node=(node->next)->next;
		char * key_2 = node->value;
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==5)
		  {
			  hashTable   *t = (hnode->value);

			   s1 =t->used; 
		  }else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(null)";

	    hashNode *hnode_2=getTable(table,key_2);
		if (hnode)
		  if(hnode->type==5)
		  {
			  hashTable   *t = (hnode_2->value);
			  s2 =t->used; 
		  }else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(null)"; 
		// ismember the smallest to another if is add
          if (s1<=s2)
		  {
			  list * keys =keysTable(hnode->value);
			  if (keys)
		{
            char *str = malloc(sizeof(char)*200);
			memset(str,0,sizeof(char)*200);
			listNode * p = keys->head;
			for (p;p;p=p->next)
			{

	  		    hashTable   *t_2 = (hnode_2->value);
				hashNode * f_node = getTable(t_2,p->value);
				if (f_node)
				{
					strcat(str,p->value);
					strcat(str,"\n");
				}
			}
			return str;
		}
		else 
			return "null";
		  }
		  else
		  {
			  list * keys =keysTable(hnode_2->value);
			  if (keys)
		{
            char *str = malloc(sizeof(char)*200);
			memset(str,0,sizeof(char)*200);
			listNode * p = keys->head;
			for (p;p;p=p->next)
			{

	  		    hashTable   *t_1 = (hnode->value);
				hashNode * f_node = getTable(t_1,p->value);
				if (f_node)
				{
					strcat(str,p->value);
					strcat(str,"\n");
				}
			}
			return str;
		}
		else 
			return "null";
		  }
	}

	//cmomand is "sscan"
	else if (i==39)
	{
		return "sorry,not support this command yet!";
	}


	//cmomand is "sunion"
	else if (i==40)
	{
        if (len!=3)
			return "(error) ERR wrong number of arguments for 'sunion' command"; 
	    hashNode *hnode =getTable(table,key);
        node=(node->next)->next;
		char * s2 = node->value;
		hashNode *node_2 = getTable(table,s2);
	   if (hnode)
		  if(hnode->type==5)
		  {
			  list * keys =keysTable(hnode->value); 
	   //s1 exists and has members
	     if(keys)
		 {
			 //s2 exists
			 if(node_2)
				 if(node_2->type==5)
				 {
					 list * keys_2 =keysTable(node_2->value);
				 //s1 exists and has members adn s2 also
					 if(keys_2)
					 {

						 hashTable * set = new_Table(3);
						 listNode * p = keys->head;
						 for (p;p;p=p->next)
						{
						 sds *t_member = new_sds(p->value); 
						 addTable(set,t_member,NULL,5);

						}
						  p = keys_2->head;
						 for (p;p;p=p->next)
						{
						 sds *t_member = new_sds(p->value); 
						 addTable(set,t_member,NULL,5);
						}
							 list * keys_3 =keysTable(set);
							 {
								 char *str = malloc(sizeof(char)*200);
								 memset(str,0,sizeof(char)*200);
								 listNode * p = keys_3->head;
								 for (p;p;p=p->next)
								 {
									 strcat(str,p->value);
									 strcat(str,"\n");
								 }
							 
							 freeTable(set);
							 return str;
							 }
					 }
					 //s1 exists and has members but s2 null
					 else
					 {
						 list * keys =keysTable(node_2->value);
						 if (keys)
						 {
							 char *str = malloc(sizeof(char)*200);
							 memset(str,0,sizeof(char)*200);
							 listNode * p = keys->head;
							 for (p;p;p=p->next)
							 {
								 strcat(str,p->value);
								 strcat(str,"\n");
							 }
							 return str;
						 }
						 else 
							 return "(nil)";
					 }
				}else
						return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
			 //s1 exists and has members but s2 not exists
			 else
			 {
				 list * keys =keysTable(hnode->value);
				 if (keys)
				 {
				 char *str = malloc(sizeof(char)*200);
				 memset(str,0,sizeof(char)*200);
				 listNode * p = keys->head;
				 for (p;p;p=p->next)
				 {
					 strcat(str,p->value);
					 strcat(str,"\n");
				 }
				 return str; 
				 }
				 else 
				 return "(nil)";
			 }
		 }
	   //s1 = null
	     else
		 {
			 list * keys =keysTable(node_2->value);
			 if (keys)
			 {
				 char *str = malloc(sizeof(char)*200);
				 memset(str,0,sizeof(char)*200);
				 listNode * p = keys->head;
				 for (p;p;p=p->next)
				 {
					 strcat(str,p->value);
					 strcat(str,"\n");
				 }
				 return str; 
			 }
			 else 
				 return "(nil)";
		 }
		  }
		  else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  
	   // s1 = not exists  
	   else
	   {
		   list * keys =keysTable(node_2->value);
			 if (keys)
			 {
				 char *str = malloc(sizeof(char)*200);
				 memset(str,0,sizeof(char)*200);
				 listNode * p = keys->head;
				 for (p;p;p=p->next)
				 {
					 strcat(str,p->value);
					 strcat(str,"\n");
				 }
				 return str; 
			 }
			 else 
				 return "(nil)";
	   }
	}


	//cmomand is "sismember"
	else if (i==41)
	{

      if(len!=3)
	      return "(error) ERR wrong number of arguments for 'sismember' command";
	  hashNode *hnode =getTable(table,key);
	  if (hnode)
		  if(hnode->type==5)
	  {
       	 node=(node->next)->next;
		 char * t_member = node->value;

	    hashTable   *t = ((getTable(table,key))->value);
		hashNode * f_node = getTable(t,t_member);

		if (f_node)
		{
			return "(integer) 1";

		}
		else 
			return "(integer) 0";

	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(integer) 0";
	}
	//cmomand is "smembers"
	else if (i==42)
	{
        if (len!=2)
			return "(error) ERR wrong number of arguments for 'smembers' command"; 
	    hashNode *hnode =getTable(table,key);
	   if (hnode)
		  if(hnode->type==5)
	  {
		list * keys =keysTable(hnode->value);
		if (keys)
		{
            char *str = malloc(sizeof(char)*200);
			memset(str,0,sizeof(char)*200);
			listNode * p = keys->head;
			for (p;p;p=p->next)
			{
				strcat(str,p->value);
				strcat(str,"\n");
			}
		    return str; 
		}
		else 
			return "(nil)";
	  }
	      else
		      return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
	  else
		  return "(nil)";
	}

	//command is "lpushx"
    else if (i==43)
	{
		if (len!=3)
			return "(error) ERR wrong number of arguments for 'lpushx' command";
		node=(node->next)->next;
        char * value =malloc(sizeof(char)*strlen(node->value));	
        strcpy(value,node->value);

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
			  return "(null)";

	}
    //command is "rpushx"
	else if (i==44)
	{
        if (len!=3)
		
			return "(error) ERR wrong number of arguments for 'rpushx' command";
		node=(node->next)->next;
		char * value =malloc(sizeof(char)*strlen(node->value));
	    strcpy(value,node->value);

		hashNode * hnode =getTable(table,key);
		if (hnode)
			if (hnode->type ==3)
			{
			   cmd_list_append((list *)(hnode->value),value);
			   printf("append value =%s\n",value);
		       return "rpush OK!";
            hashTable * t = new_Table(3);
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
		else 
		    return "(null)";
	}
    //command is "lrange"
	else if (i==45)
	{
		if (len!=4)
			return "(error) ERR wrong number of arguments for 'lrange' command";
       	node=(node->next)->next;
		int i;
		char * value = node->value;
        int start = atoi(value);
		node = node->next;
		char * value_2 = node->value;
		int stop = atoi(value_2);

		hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(hnode->value))->head)
			    if (hnode->type ==3)
			{
		        char * str =  malloc(sizeof(char )*50);
				memset(str,0,sizeof(char)*50);
				for (i=start;i<stop;i++)
				{
					if(cmd_list_lindex((list *)(hnode->value),i))
				{
					strcat(str,cmd_list_lindex((list *)(hnode->value),i));
				    strcat(str,"\n");
				}else
					return str;
				}
				return str;
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(data nill)";
		else
		   return "(key nil)";
	}
	//command is "lrem"
	else if (i==46)
	{
		return "sorry for not support this command";
		if (len!=4)
			return "(error) ERR wrong number of arguments for 'lrem' command";
		node=(node->next)->next;
		char * count = node->value;
        int c = atoi(count);
		node = node->next;
		char * value = node->value;
	
	    if (c>0)
		{

		}
		else if (c<0)
		{

		}
		else if (c==0)	
		{

		}
	
	}
	//command is "lset"
	else if (i==47)
	{

		if(len!=4)
			return "(error) ERR wrong number of arguments for 'lset' command";
       	node=(node->next)->next;
		char * value = node->value;
		node = node->next;
		char * v = node->value;
		char * v_ =malloc(sizeof(char)*strlen(node->value));
		strcpy(v_,v);
		int count = atoi(value);
         hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(hnode->value))->head)
			    if (hnode->type ==3)
			{
		        char * str =  malloc(sizeof(char )*50);
				memset(str,0,sizeof(char)*50);
				if(cmd_list_lindex((list *)(hnode->value),count))
				{
					cmd_list_lset(((list *)(hnode->value)),count,v_);
				    return "lset OK!";
				}else
					return "(null)";
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(data nill)";
		else
		   return "(key nil)";


		return "not support yet!";
	}
	//command is "lindex"
	else if (i==48)
	{
		if(len!=3)
			return "(error) ERR wrong number of arguments for 'lindex' command";
       	node=(node->next)->next;
		char * value = node->value;
		int count = atoi(value);
          hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(hnode->value))->head)
			    if (hnode->type ==3)
			{
		        char * str =  malloc(sizeof(char )*50);
				memset(str,0,sizeof(char)*50);
				if(cmd_list_lindex((list *)(hnode->value),count))
				{strcpy(str,cmd_list_lindex((list *)(hnode->value),count));
				    return str;
				}else
					return "(null)";
			}
			else 
		       return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(data nill)";
		else
		   return "(key nil)";



	}
	//command is "ltrim"
	else if (i==49)
	{
	return "sorry,not support yet!";
	}
	//command is "linsert"
	else if (i==50)
	{	
		return "sorry,not support yet!";
		if(len!=5)
			return "(error) ERR wrong number of arguments for 'linsert' command";

	}

	//command is "rpoplpush"
	else if (i==51)
	{
    	if (len!=3)
			return "(error) ERR wrong number of arguments for 'rpoplpush' command";
	    hashNode *hnode = getTable(table,key);
		
		node=(node->next)->next;
		char * value =malloc(sizeof(char)*strlen(node->value));
	    strcpy(value,node->value);
		char * str =  malloc(sizeof(char )*50);
     	if (hnode)
			if (((list *)(hnode->value))->tail)
			    if (hnode->type ==3)
			{
				memset(str,0,sizeof(char)*50);
				strcpy(str,cmd_list_rget((list *)(hnode->value))); 
				
				cmd_list_rpop((list *)(hnode->value));
			    
				
				hashNode * hnode_2 =getTable(table,value);
				if (hnode_2)
					if (hnode_2->type ==3)
					{
						cmd_list_lpush((list *)(hnode_2->value),str);
						return str;
					}
					else
						return "(error) WRONGTYPE Operation against a key holding the wrong kind of value";
				else 
				{
					list * l = cmd_list_init(str);
					sds* t_key= new_sds(value);
					addTable(table,t_key,l,3);   
					return "init OK!";
				}
			}
			    else 
		           return "(error) WRONGTYPE Operation against a key holding the wrong kind of value"; 
			else
				return "(rpoprpush data nill)";
		else
		   return "(key nil)";
	}

	//command is "blpop"
	else if (i==52)
	{

		return "sorry for not support yet";

			//
		if (len!=2)
			return "(error) ERR wrong number of arguments for 'blpop' command";
	    hashNode *hnode = getTable(table,key);
     	if (hnode)
			if (((list *)(hnode->value))->head)
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
			{
				while (1)
				{
					if (hnode)
						if (((list *)(hnode->value))->head)
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
							continue;
					else 
						continue;
				}
			}
		else
		{
			while (1)
				{
					if (hnode)
						if (((list *)(hnode->value))->head)
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
							continue;
					else 
						continue;
				}
		}
	}

	//command is "brpop"
	
	else if (i==53)
	{
	return " sorry,not support yet!";

	}

	//command is "brpoplpush"
	else if (i==54)
	{
	return "sorry,not support yet!";

	}
}


