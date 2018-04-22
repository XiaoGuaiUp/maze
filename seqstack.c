#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "seqstack.h"


//初始化
void SeqStackInit(SeqStack* stack)
{
    stack->size=0;
    stack->capacity = 1000;
    stack->data=(SeqStackType*)malloc(stack->capacity*sizeof(SeqStack));
}
//销毁
void SeqStackDestroy(SeqStack* stack)
{
    free(stack->data);
    stack->size=0;
    stack->capacity=0;
}
//扩容
void SeqStackReSize(SeqStack* stack)
{
    if(stack)
    {
        return;
    }
    if(stack->size<stack->capacity)
    {
        return;
    }
    //这个容量的大小需要自定义
    stack->capacity=stack->capacity*2+1; //这里加1是为了防止capacity为0时的情况
        SeqStackType* new_ptr=(SeqStackType*)malloc(stack->capacity*sizeof(SeqStackType));
    //将原来的搬运到现在扩容后的顺序栈里
    //遍历
    size_t i=0;
    for(;i<stack->size;++i)
    {
        new_ptr[i]=stack->data[i];
    }
    free(stack->data);
    stack->data=new_ptr;
    return;
}
//入栈（尾插）
void SeqStackPush(SeqStack* stack,SeqStackType value)
{
    if(stack==NULL)
    {//非法输入
        return;
    }
    if(stack->size>=stack->capacity)
    {//此时就需要扩容了
        SeqStackReSize(stack);
    }
    //尾删
    stack->data[stack->size++]=value;
    return;
}
//出栈（尾删）
void SeqStackPop(SeqStack* stack)
{
    if(stack==NULL)
    {
        return;
    }
    if(stack->size==0)
    {//空栈
        return;
    }
    --stack->size;
    return;
}
//取栈顶元素
//返回两个信息：（1）执行成功失败（2）栈顶元素的值
int SeqStackTop(SeqStack* stack,SeqStackType* value)
{
    if(stack==NULL && value==NULL)
    {
        return 0;
    }
    if(stack->size==0)
    {
        return 0;
    }
    *value=stack->data[stack->size-1];//取栈顶元素
    return 1;
}


void SeqStackDebugPrint(SeqStack* stack,const char* msg)
{
    printf("[ %s ]\n",msg);
    size_t i=0;
    for(;i<stack->size;++i)
    {
        printf("( %d,%d )\n",stack->data[i].row,stack->data[i].col);
    }
    printf("\n");
}
