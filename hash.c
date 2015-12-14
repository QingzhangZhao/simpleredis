#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

#include"hash.h"
#include"sds.h"
//murmurhash2 
uint32_t ngx_murmur_hash2(char *data, size_t len)
{
    uint32_t  h, k;

    h = 0 ^ len;

    while (len >= 4) {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= 0x5bd1e995;
        k ^= k >> 24;
        k *= 0x5bd1e995;

        h *= 0x5bd1e995;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
    case 3:
        h ^= data[2] << 16;
    case 2:
        h ^= data[1] << 8;
    case 1:
        h ^= data[0];
        h *= 0x5bd1e995;
    }

    h ^= h >> 13;
    h *= 0x5bd1e995;
    h ^= h >> 15;

    return h;
}

//prime_array
static int prime_array[] = {
    17,             /* 0 */
    37,             /* 1 */
    79,             /* 2 */
    163,            /* 3 */
    331,            /* 4 */
    673,            /* 5 */
    1361,           /* 6 */
    2729,           /* 7 */
    5471,           /* 8 */
    10949,          /* 9 */
    21911,          /* 10 */
    43853,          /* 11 */
    87719,          /* 12 */
    175447,         /* 13 */
    350899,         /* 14 */
    701819,         /* 15 */
    1403641,        /* 16 */
    2807303,        /* 17 */
    5614657,        /* 18 */
    11229331,       /* 19 */
    22458671,       /* 20 */
    44917381,       /* 21 */
    89834777,       /* 22 */
    179669557,      /* 23 */
    359339171,      /* 24 */
    718678369,      /* 25 */
    1437356741,     /* 26 */
    2147483647      /* 27 (largest signed int prime) */
};               



hashTable * new_Table(int order)
{
	hashTable *Table;
	
	int size = prime_array[order];


	Table = malloc(sizeof(hashTable));

	Table->table=malloc(sizeof(hashNode)*size);

	Table->size=size;
    
	
	Table->used=0;
    
	int i;
	for (i=0;i<size;i++)
	{
		(Table->table)[i]=NULL;
	}
	return Table;
}

void freeTable(hashTable *table)
{
	int i;
	int size=table->size;
	hashNode *p,*q;
	for(i=0;i<size;i++)
	{

		for(p=(table->table)[i];p;p=q){
		          q=p->next;
				  free(p);
		}

	}
	free(table);
}

void addTable(hashTable *table,void * key,void  *value,int type)
{     
        int i =ngx_murmur_hash2(((sds *)key)->buf,strlen(((sds *)key)->buf))%(table->size);
		printf("#key =%s len =%d set i = %d\n",((sds *)key)->buf,strlen(key),i);
		
		hashNode *node,*new_node,*prev;

		for (node=(table->table)[i];node;node=node->next)
		{
			if(strcmp(((sds *)(node->key))->buf,((sds *)key)->buf)==0)
				return;
		}
		if(node==NULL)
		{
			new_node=malloc(sizeof(hashNode));
			new_node->key=key;
			new_node->value=value;
			new_node->next=NULL;
			new_node->type=type;
		}
		if((table->table)[i]==NULL){
			(table->table)[i]=new_node;
			printf("add OK!\n");
			table->used+=1;
			return;
		}
		prev=(table->table)[i];	
		for (node=(table->table)[i];node;node=node->next)
		{
			prev=node;
		}
		prev->next=new_node;
		table->used+=1;
}
hashNode *  getTable(hashTable *table,void *key)
{   
	hashNode *node;
	int i = ngx_murmur_hash2(key,strlen(key))%(table->size);

	for (node= (table->table)[i]; node; node = node->next)
	        if (strcmp(((sds *)node->key)->buf,key)==0)
				break;
    return node? node: NULL;

}

void removeTable(hashTable *table,void *key)
{
	int i = ngx_murmur_hash2(key,strlen(key))%(table->size);
	hashNode *node;
	node = (table->table)[i];
	if (node==NULL)
		return;
	else if(strcmp(((sds *)(node->key))->buf,key)==0);
	{   
		printf("del OK!");
		free(node);
		(table->table)[i]=NULL;
		table->used -=1;
		return;
	}
	//bugs
}


list * keysTable(hashTable *table)
{
	list * keys=NULL;
    int i;
	int first = 1;
	hashNode *node;
	for (i=0;i<(table->size);i++)
	{
	   if(((table->table)[i])!=NULL)
		{
			node = (table->table)[i];
			for (node;node;node=node->next)
			{
				if (first==1)
		        {
			      keys =  cmd_list_init(((sds *)(node->key))->buf);
		           first =0;
		          }
                 else
	           cmd_list_append(keys,((sds *)(node->key))->buf);

			}
		}
	}
		 return keys;
	//with bugs 
}

int   sizeTable(hashTable *table)
{
	return table->size;

}






//simple test
//int main()
//{
//	hashTable *table = new_Table(3);
//	printf("size=%d\n",table->size);
  // 
//	char *a = "a";
  //      int i =ngx_murmur_hash2(a,table->size)%(table->size);
   // char *b ="a";

     //   int j =ngx_murmur_hash2(b,table->size)%(table->size);
     // printf("set i =%d\n",i);
     // printf("set j =%d\n",j);



//}
