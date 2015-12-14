#include"list.h"
#include<stdlib.h>
#include<stdio.h>

//init the cmd_list
//not well
list *  cmd_list_init(char *value)
{
	listNode *chead=(listNode *)malloc(sizeof(listNode));
    list *c_listhead=(list *)malloc(sizeof(list));
	
	
	chead->value = value;
	chead->prev =NULL;
	chead->next =NULL;
    
	c_listhead->head=chead;
	c_listhead->tail=chead;
	c_listhead->len=1;
	
	return c_listhead;
}

//add to the cmd_list
void cmd_list_append(list*head,char  *value)
{
	listNode *cmd_node=(listNode *)malloc(sizeof(listNode));

	cmd_node->value=value;
	cmd_node->next=NULL;
	cmd_node->prev=(head->tail);
    
	if (head->tail)	
	{
		(head->tail)->next=cmd_node;
	     head->tail=cmd_node;
    }
	else
	{
	   head->tail=cmd_node;
	   head->head=cmd_node;
	}
    head->len+=1;
}


void cmd_list_lpush(list *head,char *value)
{
	listNode *new_node=(listNode *)malloc(sizeof(listNode));
	new_node->value = value;
	new_node->prev=NULL;
	new_node->next = (head->head);
     if (head->head)   
	 {
		 (head->head)->prev = new_node;
         (head->head)=new_node;	
	 }
	 else
	 {
		 head->head=new_node;
		 head->tail=new_node;
	 }
		 head->len+=1;  
}

int cmd_list_llen(list *head)
{
	return head->len;
}

void * cmd_list_lget(list *head)
{
	if (head->head)
	    return (head->head)->value;
	else
		return "(nill)";
}

void * cmd_list_rget(list *head)
{
	if (head->tail)
    	return (head->tail)->value;
	else 
		return "(nill)";
}

void  cmd_list_lpop(list *head)
{
	if (head->len>=1)
	{
	 listNode * p = head->head;
     (head->head)=(head->head)->next;
	 if (head->head)
	     (head->head)->prev=NULL;
	 else
		 head->tail=NULL;
	 free (p);
	 head->len-=1;
	}
	else
		 return;

}

void  cmd_list_rpop(list *head)
{
	if(head->len>=1)
	{
     listNode * p = head->tail;
     (head->tail)=(head->tail)->prev;
	 if(head->tail)
	     ((head->tail)->next)=NULL;
	 else
		 (head->head)=NULL;
	 free (p);
	 head->len-=1;
	}
	else 
		 return;
}




