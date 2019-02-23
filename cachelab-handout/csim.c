#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include<fcntl.h>
unsigned arg_number[3];
char* arg_str=NULL;
void* mem;
int miss;
int eviction;
int hit;
int vflag;
typedef struct _stack{ 
   unsigned data;
   int valid;
   struct _stack* next;
}stack;
typedef struct _cache{
    unsigned tag;
    stack stk;
    unsigned offset;
}cache;
void help(){
    printf("./csim -s <s> -E <E> -b <b> -t <tracefile>\n");
}
int argv_parser(int argc,char* argv[]){
    int i=2;
    int j=0;
    
    if(argc==9){
    while(i!=8){
       arg_number[j++]=atoi(argv[i]);
       i=i+2;
    }
    arg_str=argv[i];
    }
    else if(argc==10){
        if(argc==10&&!strcmp(argv[1],"-v"))
            vflag=1;
        else if(argc==10&&!strcmp(argv[1],"-h"))
            help();
        i=3;
        while(i!=9){
        arg_number[j++]=atoi(argv[i]);
        i=i+2;
        }
        arg_str=argv[i];
    }
    else if(argc==11){
        vflag=1;
        help();
        i=4;
        while(i!=10){
        arg_number[j++]=atoi(argv[i]);
        i=i+2;
        }
        arg_str=argv[i];
    }
    else{
        printf("syntax error,input should be:\n");
        printf("./csim -s <s> -E <E> -b <b> -t <tracefile>\n");
        exit(0);
    }
    return 0;
}

int get_stack_size(stack* start){
    int count=0;
    while(start->next!=NULL){
      start=start->next;
      count++;
    }
    return count;
}
//use stack to simulate LRU
void lru_add(stack* start,unsigned E,unsigned long tag){
    stack* pre=start;
    stack* curr=pre->next;
    stack*p=NULL;
    //delete existed tag in sets and put them on top of stack
    while(curr!=NULL){
        if(curr->data==tag){
            pre->next=curr->next;
            free(curr);
            curr=pre->next;
        }
        else{
            pre=curr;
            curr=curr->next;
        }
    }
    int sz=get_stack_size(start);
    if(sz==E){ //eviction from bottom of stack and put data on top of stack
        p=start->next;
        start->next=start->next->next;
        free(p);
        pre=start;
        p=start->next;
        while(p!=NULL){
            pre=p;
            p=p->next;
        }
        pre->next=(stack*)malloc(sizeof(stack));
        pre->next->data=tag;
        pre->next->valid=1;
        pre->next->next=NULL;
    }
    else{//put data on top of stack
        pre=start;
        p=start->next;
        while(p!=NULL){
            pre=p;
            p=p->next;
        }
        pre->next=(stack*)malloc(sizeof(stack));
        pre->next->data=tag;
        pre->next->valid=1;
        pre->next->next=NULL;
    }

}
//store is implemented in cache until it's changed,so you need to load them in cache first
int load_store(stack*p,cache* mycache,unsigned sz,unsigned long set,unsigned long tag,unsigned E){
    for(int i=0;i<sz;i++){
        if(p->next!=NULL&&p->next->data==tag){
            lru_add(&mycache[set].stk,E,tag);
            if(vflag==1)
             printf("hit\n");
             hit++;
             return 0;
            }
        p=p->next;
    }
    if(sz==E){
        lru_add(&mycache[set].stk,E,tag);
        if(vflag==1){
        printf("miss ");
        printf("eviction\n");
        }
        miss++;
        eviction++;
    }
    else{ 
        lru_add(&mycache[set].stk,E,tag);
        if(vflag==1)
        printf("miss\n");
        miss++;
    }
    return 0;
}
//modify means load a data from DRAM and then store it.
int modify(stack*p,cache* mycache,unsigned sz,unsigned long set,unsigned long tag,unsigned E){
    //flag ensures ones you hit first,it direct stores.
    int flag=0;
    //load
    for(int i=0;i<sz;i++){
        if(p->next!=NULL&&p->next->data==tag){
            flag=1;
            lru_add(&mycache[set].stk,E,tag);
            if(vflag==1)
            printf("hit ");
            hit++;
            break;//once we've updated LRU stack,must skip loop
            }
        p=p->next;
    }
    if(sz==E&&flag==0){
        lru_add(&mycache[set].stk,E,tag);
        if(vflag==1){
        printf("miss ");
        printf("eviction "); 
        }
        miss++;
        eviction++;   
    }
    else if(flag==0) { 
        lru_add(&mycache[set].stk,E,tag);
        if(vflag==1)
        printf("miss ");
        miss++;
    }
    if(vflag==1)
    printf("hit\n");//store
    hit++;
    return 0;
}

unsigned indicater(cache* mycache,unsigned long address,char* operation,
                   unsigned s,unsigned b,unsigned E){
        unsigned long tmask=(-1)<<(s+b);
        unsigned long smask=((-1)<<(b))^tmask;
        unsigned long tag=(address&tmask)>>(s+b);
        unsigned long set=(address&smask)>>b;
        int sz=get_stack_size(&mycache[set].stk);
        stack* p=&mycache[set].stk;
        /*
        if(strcmp(operation,"I"))
        printf("set:%ld tag:%ld size:%d\n",set,tag,sz);
        */
        switch (operation[0])
        {
            case 'L':
            case 'S':
                load_store(p,mycache,sz,set,tag,E);
                break;
            case 'M':
                modify(p,mycache,sz,set,tag,E);
                break;
            default:
                break;
        }
        //sz=get_stack_size(&mycache[set].stk);
       // printf("size changed to:%d\n",sz);
        
}
void buf_parser(char* buf,char*operation,unsigned long* address,int* size){
    char sz[2];
    char addr[64];
    int i,j=0;
    int x=strchr(buf,',')-buf;
    if(buf[0]==' '){
        operation[0]=buf[1];
        operation[1]='\0';
        for(i=3;i<x;i++)
            addr[j++]=buf[i];
        addr[j]='\0';
        sz[0]=buf[x+1];
        sz[1]='\0';
    }
    else{
        operation[0]=buf[0];
        operation[1]='\0';
        for(i=3;i<x;i++)
            addr[j++]=buf[i];
        addr[j]='\0';
        sz[0]=buf[x+1];
        sz[1]='\0';
    }

    *address=strtol(addr,NULL,16);//tracefile use base16
    *size=atoi(sz);//it's okay to use atoi because size is less than 8 bytes
}

void init_cache(cache* mycache,unsigned S){
    int i=0;
    for(;i<S;i++){
        mycache[i].stk.valid=0;
        mycache[i].stk.next=NULL;
        mycache[i].stk.data=-1;
    }
}
void free_cache(cache* mycache,unsigned S);
void printSummary(int hit,int miss,int eviction){
    printf("hits:%d misses:%d evictions:%d\n",hit,miss,eviction);
}
/*void pt(stack* p){
    while(p->next!=NULL){
        printf("%d ",p->next->data);
        p=p->next;
    }
    printf("\n");
}*/
int main(int argc,char*argv[])
{   argv_parser(argc,argv);
    FILE* fp;
    char operation[2];
    unsigned long address;
    int size;
    char buf[128];
    unsigned set_bit_count=arg_number[0];
    unsigned E=arg_number[1];
    unsigned offset_bit_count=arg_number[2];
    unsigned S=1<<set_bit_count;
    cache mycache[S];
    init_cache(mycache,S);
    fp=fopen(arg_str, "r");
    if(fp==NULL){
        printf("cannnot open file\n");
        exit(0);
    }
    while (fgets(buf, sizeof(buf), fp) != NULL){
        buf_parser(buf,operation,&address,&size);
        if(vflag==1&&strcmp(operation,"I"))
            printf("%s %lx %d ",operation,address,size);
        indicater(mycache,address,operation,set_bit_count,offset_bit_count,E);
    }
    fclose(fp);
    printSummary(hit,miss,eviction);
    
   /*stack stk={-1,-1,NULL};
   int i;
   while(1){
       scanf("%d",&i);
       lru_add(&stk,2,i);
       pt(&stk);
   }*/
    return 0;
}
