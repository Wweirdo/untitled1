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
    MoveMent MoveMent[4] = { {-1,0},{1,0},{0,-1},{0,1} };   //�ĸ����� ��������
    Position CurrentPos = { 1,1,-1 };                       //��ʼ����
    mg[1][1] = -1;                                        //����Ϊ-1����ʾ�ѵ���������
    int NextX, NextY;
    int xi, yi, di;                      //��ʱ���������ڱ��浱ǰ�������һ����
    PushData(PositionStack, CurrentPos);
    while (PositionStack.Top != -1)
    {
        //��ȡ��ǰջ��������
        CurrentPos = PopData(PositionStack);
        xi = CurrentPos.x;
        yi = CurrentPos.y;
        di = CurrentPos.di + 1;
        //���������ҵ�˳��鿴�ĸ������Ƿ���ͨ·
        while (di < 4)
        {
            //������һ����
            NextX = xi + MoveMent[di].MoveX;
            NextY = yi + MoveMent[di].MoveY;
            //�����ͨ·
            if (mg[NextX][NextY] == 0)
            {
                //ѹջ��ͬʱ��ǰ����ָ�������
                PushData(PositionStack, CurrentPos);
                CurrentPos.x = NextX;
                CurrentPos.y = NextY;
                xi = NextX;
                yi = NextY;
                //�������ѵ���
                mg[xi][yi] = -1;
                //��������յ�
                if (xi == mgSize && yi == mgSize)
                {
                    //���·��
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
                    //���û�е����յ㣬��������´��ĸ��������ͨ·
                    di = 0;
                }
            }
            else
            {
                //�����ǰ����ͬ��ת����һ����
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
