#pragma once


#define FOR_MAZE
#ifdef FOR_MAZE
typedef struct Point{
    int row;
    int col;
} Point;
typedef Point SeqStackType;
#else
typedef char SeqStackType;
#endif

typedef struct SeqStack
{
    SeqStackType* data;//动态扩容-> 动态内存管理
    size_t size;   //栈中的元素个数
    size_t capacity; //data指向的内存中，最多能容纳的元素，相当于Max_size
} SeqStack;

//初始化
void SeqStackInit(SeqStack* stack);
//销毁
void SeqStackDestroy(SeqStack* stack);
//入栈（尾插）
void SeqStackPush(SeqStack* stack,SeqStackType value);
//出栈（尾删）
void SeqStackPop(SeqStack* stack);
//取栈顶元素
int SeqStackTop(SeqStack* stack,SeqStackType* value);//输出型参数
//扩容
void SeqStackReSize(SeqStack* stack);

void SeqStackDebugPrint(SeqStack* stack,const char* msg);
