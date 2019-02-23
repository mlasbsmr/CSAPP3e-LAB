#include<stdio.h>
int func4(unsigned x,unsigned y,unsigned z){
__asm__(
".L0:\n\t"
"sub    $0x8,%rsp\n\t"
"mov    %edx,%eax\n\t"
"sub    %esi,%eax\n\t"
"mov    %eax,%ecx\n\t"
"shr    $0x1f,%ecx\n\t"
"add    %ecx,%eax\n\t"
"sar    %eax\n\t"
"lea    (%rax,%rsi,1),%ecx\n\t"
"cmp    %edi,%ecx\n\t"
"jle    .L1\n\t"
"lea    -0x1(%rcx),%edx\n\t"
"callq  .L0\n\t"
"add    %eax,%eax\n\t"
"jmp    .L2\n\t"
".L1:\n\t"
"mov    $0x0,%eax\n\t"
"cmp    %edi,%ecx\n\t"
"jge    .L2\n\t"
"lea    0x1(%rcx),%esi\n\t"
"callq  .L0\n\t"
"lea    0x1(%rax,%rax,1),%eax\n\t"
".L2:\n\t"
"add    $0x8,%rsp\n\t"
"retq\n\t"
);
}

void main(){
    for(unsigned i=0;i<=0xe;i++){
        if(func4(i,0,0xe)==0)
            printf("%d\t",i);
    }
	printf("\n");
}