#include<Windows.h>
#include<tchar.h>
#include <iostream>
using namespace std;

#define mgSize  8
#define StackSize 100

typedef struct POSITION
{
    int x;
    int y;
    int di;
}Position,*PPosition;

typedef struct MOVEMENT
{
    int MoveX;
    int MoveY;
}MoveMent,*PMovement;

typedef struct POSITION_STACK
{
    Position PosStack[StackSize];
    int Top;
}PositionStack,*PPositionStack;

BOOL PushData(PositionStack &PositionStack, Position Position)
{
    if (PositionStack.Top == StackSize - 1)
    {
        return FALSE;
    }
    else
    {
        PositionStack.Top++;
        PositionStack.PosStack[PositionStack.Top].x = Position.x;
        PositionStack.PosStack[PositionStack.Top].y = Position.y;
        PositionStack.PosStack[PositionStack.Top].di = Position.di;
        return TRUE;
    }
}

Position PopData(PositionStack &PositionStack)
{
    if (PositionStack.Top == -1)
    {
    }
    else
    {
        Position v1 = PositionStack.PosStack[PositionStack.Top];
        PositionStack.Top--;
        return v1;
    }
}

bool FindmgPath(int (&mg)[mgSize + 2][mgSize + 2], PositionStack &PositionStack)
{
    MoveMent MoveMent[4] = { {-1,0},{1,0},{0,-1},{0,1} };   //四个方向 上下左右
    Position CurrentPos = { 1,1,-1 };                       //初始坐标
    mg[1][1] = -1;                                        //设置为-1，表示已到过该坐标
    int NextX, NextY;
    int xi, yi, di;                      //临时变量，用于保存当前坐标和下一坐标
    PushData(PositionStack, CurrentPos);
    while (PositionStack.Top != -1)
    {
        //获取当前栈顶的坐标
        CurrentPos = PopData(PositionStack);
        xi = CurrentPos.x;
        yi = CurrentPos.y;
        di = CurrentPos.di + 1;
        //按上下左右的顺序查看四个方向是否有通路
        while (di < 4)
        {
            //保存下一坐标
            NextX = xi + MoveMent[di].MoveX;
            NextY = yi + MoveMent[di].MoveY;
            //如果有通路
            if (mg[NextX][NextY] == 0)
            {
                //压栈，同时当前坐标指向该坐标
                PushData(PositionStack, CurrentPos);
                CurrentPos.x = NextX;
                CurrentPos.y = NextY;
                xi = NextX;
                yi = NextY;
                //该坐标已到达
                mg[xi][yi] = -1;
                //如果到达终点
                if (xi == mgSize && yi == mgSize)
                {
                    //输出路径
                    PushData(PositionStack, CurrentPos);
                    for (int i = 0; i < PositionStack.Top; i++)
                    {
                        printf("(%d,%d)->", PositionStack.PosStack[i].x, PositionStack.PosStack[i].y);
                    }
                    printf("(%d,%d)", PositionStack.PosStack[PositionStack.Top].x, PositionStack.PosStack[PositionStack.Top].y);
                    return TRUE;
                }
                else
                {
                    //如果没有到达终点，则继续重新从四个方向查找通路
                    di = 0;
                }
            }
            else
            {
                //如果当前方向不同，转向下一方向
                di++;
            }
        }
    }
}
int main()
{
    int mg[mgSize + 2][mgSize + 2] =
            {

                    { 1,1,1,1,1,1,1,1,1,1 },
                    { 1,0,1,0,1,1,1,1,1,1 },
                    { 1,0,0,0,0,0,0,1,1,1 },
                    { 1,1,0,1,1,1,0,1,1,1 },
                    { 1,1,0,0,0,1,0,1,1,1 },
                    { 1,1,1,1,0,1,1,1,1,1 },
                    { 1,0,0,0,0,1,1,1,1,1 },
                    { 1,0,1,0,1,0,0,0,1,1 },
                    { 1,1,1,0,0,0,1,0,0,1 },
                    { 1,1,1,1,1,1,1,1,1,1 },
            };
    PositionStack PositionStack;
    PositionStack.Top = -1;

    FindmgPath(mg, PositionStack);

}
