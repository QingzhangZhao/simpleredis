#include"sds.h"

#include<string.h>
#include<stdlib.h>
#include<stdio.h>

sds  * new_sds(void * value)
{
     sds * new_str = malloc(sizeof(sds));
	 new_str ->len =strlen(value);
	 new_str ->buf =malloc(sizeof(char)*strlen(value)+1);
      strcpy(new_str->buf,value);
	 return new_str;
}



sds * sds_append(sds *string , void *value)
{
   sds *   result_str = malloc(sizeof(sds));

   int len = (string->len)+strlen(value);

   result_str -> buf =malloc(sizeof(char)*len+1);

   memcpy(result_str->buf,string->buf,strlen(string->buf)+1);
   strcat(result_str->buf,value);
    
   result_str->len=len;
   free(string->buf);
   free(string);
   return result_str;
}



void sds_setrange(sds * string,int start,void *value)
{

   int len = string->len;
   int l = strlen(value);
   if (l>len-start)
	   string->len+=l-len+start;
	memcpy((string->buf)+start,value,strlen(value));
}


//sds_getrange()




//int main()
//{
  //     int  *a ="1234";
	//   int  *b="5678";
      // sds *string= new_sds(a);
       
	//   printf("str->len=%d,str->buf=%s\n",string->len,string->buf); 
    //  sds *string2=sds_append(string,b); 
       
	//   printf("str->len=%d,str->buf=%s\n",string2->len,string2->buf);
	//
	 // sds_setrange(string2,3,"000000");

	  // printf("str->len=%d,str->buf=%s\n",string2->len,string2->buf); 
//}
