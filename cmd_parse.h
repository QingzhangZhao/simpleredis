list * recv_parse(char *command);
 static char *commandtable[] ={
	 "set",      
	 "get",
	 "incr",
	 "decr",
	 "incrby",
	 "decrby",
	 "strlen",
	 "del",
	 "exists",
	 "randomkey",
	 "keys",
	 "type",
	 "append",
	 "mesetnx",
	 "setrange",
	 "getrange",
	 "lpush",
	 "rpush",
	 "lpop",
	 "rpop",
	 "llen",
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 };
char *  cmd_parse(hashTable *table,list *cmd_list_head);

