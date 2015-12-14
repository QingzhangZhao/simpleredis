#include"list.h"
typedef struct hashNode{
	void *key;


	void *value;
//0 - unkown
//1 - string
//2 - integer
//3 - list
//4 - hash
//5 - set 
	int type;
	
	struct hashNode *next;


}hashNode;



typedef struct hashTable{
   hashNode **table;
   
   int  size;

   //TODE
  // unsigned long sizemask;

   int  used;
}hashTable;


//create a new hashTable  
//order is used to ensure the size of the table need to create
hashTable *  new_Table(int order);

//free a hashTable
void freeTable(hashTable * table);

//
void addTable(hashTable *table,void  *key,void *value,int type);

hashNode * getTable(hashTable * table,void *key);

void removeTable(hashTable * table,void  *key);

int sizeTable(hashTable *table);

list *keysTable(hashTable *table);
