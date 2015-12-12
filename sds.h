
typedef struct sdshdr {
	int len;

	//ToDO
//	int free;
	
	
	char *buf;


}sds;



sds  * new_sds(void * value);

sds * sds_append(sds * string, void *value);

void sds_setrange(sds * string,int start,void *value);
//int sdscpy();
