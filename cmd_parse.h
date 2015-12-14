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
	 "hdel",
	 "hlen",
	 "hexists",
	 "hget",
	 "hset",
	 "hincrby",
	 "hincrbyfloat",
	 "hkeys",
	 "hvals",
	 "hmset",
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 };
char *  cmd_parse(hashTable *table,list *cmd_list_head);

