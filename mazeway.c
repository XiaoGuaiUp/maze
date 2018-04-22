#include <stdio.h>
#include <malloc.h>
#include "seqstack.h"
#define MAX_ROW 6
#define MAX_COL 6


//用一个二维数组来表示迷宫地图
typedef struct Maze{
    int map[MAX_ROW][MAX_COL];
} Maze;


//迷宫初始化
void MazeInit(Maze* maze){
    int map[MAX_ROW][MAX_COL]={
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,0,0},
        {0,1,0,1,1,0},
        {0,1,1,0,0,0},
        {0,0,1,0,0,0}
    };
    size_t i=0;
    for(;i<MAX_ROW;++i){
        size_t j=0;
        for(;j<MAX_COL;++j){
            maze->map[i][j]=map[i][j];
        }
    }
    return;
}

//迷宫地图打印
void MazePrintf(Maze* maze){
    size_t i=0;
    for(;i<MAX_ROW;++i){
        size_t j=0;
        for(;j<MAX_COL;++j){
            printf("%2d",maze->map[i][j]);
        }
        printf("\n");
    }
}

int CanStay(Maze* maze,Point pt){
    //1.若pt在地图外，排除
    if(pt.row<0||pt.row>=MAX_ROW||pt.col<0||pt.col>=MAX_COL){
        return 0;
    }
    //2.若pt在地图内，若其值为1，可落脚，其他值（0,2）排除
    int value=maze->map[pt.row][pt.col];
    if(value==1){
        return 1;
    }
    return 0;
}

void Mark(Maze* maze,Point cur){
    maze->map[cur.row][cur.col]=2;
}

//是否为出口
int IsExit(Maze* maze,Point cur,Point entry){
    //1.当前点是否为入口，若是一定不是出口
    if(cur.row==entry.row&&cur.col==entry.col){
        return 0;
    }
    //2.若点在地图的边界上，也说明是出口
    if(cur.row==0 || cur.row==MAX_ROW-1 || cur.col==0 || cur.col==MAX_COL-1){
        return 1;
    }
    return 0;
}

//递归函数
void _GetPath(Maze* maze,Point cur,Point entry){
    //1.判定当前点是否能走，是否可落脚
    if(!CanStay(maze,cur)){
        return;
    }
    //2.若能落脚，把当前位置做标记，例如：将原来的1改为2
    Mark(maze,cur);
    //3.若当前点为出口，说明就找到了
    if(IsExit(maze,cur,entry)){
        //说明找到了这条路
        printf("找到了一条路径\n");
        return;
    }
    //4.若不为出口，就按顺时针探测四个相邻的点，递归调用函数自身，递归时，更新cur
    //  每次递归时，点都是下一次要走的点，这个点是否能走，由递归做判断
    Point up=cur;
    up.row -=1;//当前点的上一个
    _GetPath(maze,up,entry);

    Point right=cur;
    right.col +=1;
    _GetPath(maze,right,entry);

    Point down=cur;
    down.row +=1;
    _GetPath(maze,down,entry);

    Point left=cur;
    left.col -=1;
    _GetPath(maze,left,entry);
}

//法一：使用递归方式
void GetPath(Maze* maze,Point entry){
    if(maze==NULL){
        return;
    }
    //使用下面的函数辅助我们完成递归
    _GetPath(maze,entry,entry);
}

//法二：使用非递归版本
#ifdef FOR_MAZE

void GetPathByLoop(Maze*maze,Point entry)
{
    //1.创建一个栈，用老保存走过的路径
    SeqStack stack;
    SeqStackInit(&stack);
    //2.判断入口点是否合法，
    if(!CanStay(maze,entry))
    {
        return;
    }
    //3.能落脚，标记点，入栈这个点的值
    Mark(maze,entry);
    SeqStackPush(&stack,entry);
    //4.进入循环，不断获取当前栈顶元素
    while(1)
    {
        Point cur;
        int ret=SeqStackTop(&stack,&cur);
        if(ret==0)
        {
            //说明栈为空了
            return ;
        }
        //5.判断当前点是否能落脚，能的话，就标记，栈顶元素一定能落脚，不用再判断
        //判断此点是否是出口，是的话，直接返回
        if(IsExit(maze,cur,entry))
        {
            printf("找到一条路径\n");
        }
        //此时证明此点不是出口
        //6.按照四个方向遍历
        Point up=cur;
        up.row -=1;
        if(CanStay(maze,up))
        {
            Mark(maze,up);
            SeqStackPush(&stack,up);
            continue;
        }

        Point right=cur;
        right.col +=1;
        if(CanStay(maze,right))
        {
            Mark(maze,right);
            SeqStackPush(&stack,right);
            continue;
        }

        Point down =cur;
        down.row +=1;
        if(CanStay(maze,down))
        {
            Mark(maze,down);
            SeqStackPush(&stack,down);
            continue;
        }

        Point left=cur;
        left.col -=1;
        if(CanStay(maze,left))
        {
            Mark(maze,left);
            SeqStackPush(&stack,left);
            continue;
        }
        //7.四个方向都找完了，就要原路返回了，出栈，也就是回溯
        SeqStackPop(&stack);
    }
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//迷宫有多条路径，寻找最短路径
//////////////////////////////////////////////////////////////////////////////////////////////

//初始化
void MazeInitShortPath(Maze* maze)
{
    int map[MAX_ROW][MAX_COL]={
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,0,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0}
    };
    size_t i=0;
    for(;i<MAX_ROW;++i)
    {
        size_t j=0;
        for(;j<MAX_COL;++j)
        {
            maze->map[i][j]=map[i][j];
        }
    }
    return;
}

//法一：以下为求最短路径的递归版本

void SeqSTackAssgin(SeqStack* from,SeqStack* to)//赋值函数
{
   //要保证to中的内存能够容纳from
   //1.释放to中的内存
   SeqStackDestroy(to);
   //2.根据from元素个数给to重新申请内存
   to->size=from->size;
   to->capacity=from->capacity;
   to->data=(SeqStackType*)malloc(to->capacity*sizeof(SeqStackType));
   //3.
   size_t i=0;
   for(;i<from->size;++i)
   {
       to->data[i]=from->data[i];
   }
   return ;
}

void _GetShortPath(Maze* maze,Point cur,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    //1.判断当前点是否能落脚
    if(!CanStay(maze,cur)){
        return;
    } 
    //2.能落脚的话，要标记，入栈到cur_path
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //3.判断是否是出口
    // a)是出口的话，找到了一条路径，对比cur_path和short_path的size大小
    if(IsExit(maze,cur,entry))
    {
        printf("找到了一条路径\n");
        if(cur_path->size<short_path->size||short_path->size==0)
        {
            printf("找到了一条较短的路径\n");
            SeqSTackAssgin(cur_path,short_path);//赋值函数
        }
        //此时替代完毕后，也要回溯去找其他路径
       //b)如果当前的路径没有short_path的短，就找其他路径，出栈回溯
       //在回溯之前，要把cur_path栈顶元素出栈
       SeqStackPop(cur_path);
       return;
    }
    Point up=cur;
    up.row -=1;
    _GetShortPath(maze,up,entry,cur_path,short_path);

    Point right=cur;
    right.col +=1;
    _GetShortPath(maze,right,entry,cur_path,short_path);

    Point down =cur;
    down.row +=1;
    _GetShortPath(maze,down,entry,cur_path,short_path);

    Point left =cur;
    left.col -=1;
    _GetShortPath(maze,left,entry,cur_path,short_path);

    //5.四个方向找完了，再进行出栈
    SeqStackPop(cur_path);
}

void GetShortPath(Maze* maze,Point entry)
{
    //保存当前路径和最短路径的栈
    SeqStack cur_path;
    SeqStack short_path;

    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);

    _GetShortPath(maze,entry,entry,&cur_path,&short_path);

    //打印栈中的内容
    SeqStackDebugPrint(&short_path,"最短路径是：");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//复杂迷宫，可能带环的迷宫，求带环迷宫的最短路径
////////////////////////////////////////////////////////////////////////////////////////////////////

void MazeInitShortPathWithCycle(Maze* maze)
{
    int map[MAX_ROW][MAX_COL]={
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,1,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,0,0}
    };
    size_t i=0;
    for(;i<MAX_ROW;++i)
    {
        size_t j=0;
        for(;j<MAX_COL;++j)
        {
            maze->map[i][j]=map[i][j];
        }
    }
    return;
}

//递归版本

int CanStayWithCycle(Maze* maze,Point cur,Point pre)
{
    //1.当前点是否在地图
    if(cur.row<0||cur.row>=MAX_ROW||cur.col<0||cur.col>=MAX_COL)
    {
        return 0;
    }
    int cur_value=maze->map[cur.row][cur.col];
    if(cur_value==0)
    {
        return 0;
    }
    if(cur_value==1)
    {
        return 1;
    }
    int pre_value=maze->map[pre.row][pre.col];
    if(cur_value>pre_value+1)
    {
        return 1;
    }
    return 0;
}

void MarkWithCycle(Maze* maze,Point cur,Point pre)
{
    if(pre.row==-1&&pre.col==-1)
    {
        maze->map[cur.row][cur.col]=2;
    }
    int pre_value=maze->map[pre.row][pre.col];
    maze->map[cur.row][cur.col]=pre_value+1;
}

void _GetShortPathWithCycle(Maze* maze,Point cur,Point pre,Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    //1.判断当前点落脚否？
    if(!CanStayWithCycle(maze,cur,pre))
    {
        return;
    }
    //2.标记当前点
    MarkWithCycle(maze,cur,pre);
    SeqStackPush(cur_path,cur);
    //3.判断是不是出口
    if(IsExit(maze,cur,entry))
    {
        //a)是出口的，比较路径长短
        printf("找到了一条路径\n");
        if(cur_path->size<short_path->size||short_path->size==0)
        {
            printf("找到了一条较短的路径\n");
            SeqSTackAssgin(cur_path,short_path);
        }
        //进行回溯，无论当前路径是否是比较短的，都要回溯
        SeqStackPop(cur_path);
        return;
    }
    //4.不是出口的话，按照四个方向走
    Point up=cur;
    up.row -=1;
    _GetShortPathWithCycle(maze,up,cur,entry,cur_path,short_path);

    Point right =cur;
    right.col +=1;
    _GetShortPathWithCycle(maze,right,cur,entry,cur_path,short_path);

    Point down=cur;
    down.row +=1;
    _GetShortPathWithCycle(maze,down,cur,entry,cur_path,short_path);

    Point left =cur;
    left.col -=1;
    _GetShortPathWithCycle(maze,left,cur,entry,cur_path,short_path);

}

void GetShortPathWithCycle(Maze* maze,Point entry)
{
    SeqStack cur_path;
    SeqStack short_path;
    
    SeqStackInit(&cur_path);
    SeqStackInit(&short_path);

    Point pre={-1,-1};
    _GetShortPathWithCycle(maze,entry,pre,entry,&cur_path,&short_path);
    SeqStackDebugPrint(&short_path,"最短路径是：");
}

#endif
void Test1()
{
    printf("================== 测试递归版本 ============\n");
    Maze maze;
    MazeInit(&maze);
    MazePrintf(&maze);
    Point entry={0,1};
    GetPath(&maze,entry);
    MazePrintf(&maze);
}

void Test2()
{
    printf("================== 测试非递归版本 ============\n");
    Maze maze;
    MazeInit(&maze);
    MazePrintf(&maze);
    Point entry={0,1};
    GetPathByLoop(&maze,entry);
    MazePrintf(&maze);

}

void Test3()
{
    printf("================== 测试找最短路径的递归版本 ============\n");
    Maze maze;
    MazeInitShortPath(&maze);
    MazePrintf(&maze);
    Point entry={0,1};
    GetShortPath(&maze,entry);
    MazePrintf(&maze);

}

void Test4()
{
    printf("================== 测试找带环迷宫的最短路径的递归版本 ============\n");
    Maze maze;
    MazeInitShortPathWithCycle(&maze);
    MazePrintf(&maze);
    Point entry={0,1};
    GetShortPathWithCycle(&maze,entry);
    MazePrintf(&maze);

}
void main()
{
    Test1();        
    Test2();
    Test3();
    Test4();
}
