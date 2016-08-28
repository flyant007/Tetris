#include "Tetris.h"
#include "Common.h"
#include <stdio.h>
#include <time.h>

//全局游戏对象
extern Game tetrisGame;

//形状的构造函数，创建随机形状
Figure::Figure()
{
    //获得随机形状编号
    int numFigure = rand() % NUM_FIGURE;

    //创建形状
    New(numFigure);
}

//形状的构造函数，创建指定编号的形状
Figure::Figure(int numFigure)
{
    //创建形状
    New(numFigure);
}

//形状的析构函数
Figure::~Figure()
{
}

//显示形状，显示形状种的每个方块
void Figure::Draw() const
{
    int i;
    for(i = 0; i < NUM_FIGURE_BLOCK; ++i)
    {
        data[i].Draw();
    }
}

//创建新形状
void Figure::New(int numFigure)
{
    int i;

    //判断需要创建的形状是否支持
    if(numFigure >= 0 && numFigure < NUM_FIGURE)
    {
        //如果不是田子形，则可以旋转
        canRotate = (numFigure != 0);

        //创建的形状初始化状态为顶部居中
        posX = NUM_BLOCKS_X / 2;
        posY = NUM_BLOCKS_Y - 2;

        //判断是否有足够的空间创建该形状，如果没有则游戏结束
        if(tetrisGame.GetMap(posX, posY + 1) == 1 && tetrisGame.GetStatus())
        {
            tetrisGame.SetStatus(false);
            return;
        }

    }

    //分别设置组成形状的每个方块的位置
    for(i = 0; i < NUM_FIGURE_BLOCK; ++i)
    {
        data[i].SetPosX(posX + image[numFigure][i][0]);
        data[i].SetPosY(posY + image[numFigure][i][1]);
    }
}

//向左旋转形状
bool Figure::Rotate()
{
    int i;

    //判断是否可以旋转
    if(!canRotate)
        return false;

    //一次判断每个方块是否可以移动到旋转后的位置，有一个不可以则返回false
    for(i = 0; i < 4; ++i)
    {
       if(!data[i].CanRotate(posX, posY))
       {
           return false;
       }
    }

    //旋转形状
    for(i = 0; i < 4; ++i)
    {
        data[i].Rotate(posX, posY);
    }

    return true;
}

//移动形状
bool Figure::Translate(const int offsetX, const int offsetY)
{
    int i;

    //判断每个方块是否可以移动到指定的位置，有一个不可以则返回false
    for(i = 0; i < 4; ++i)
    {
       if(!data[i].CanTranslate(offsetX, offsetY))
       {
           return false;
       }
    }

    //分别移动每个形状
    for(i = 0; i < 4; ++i)
    {
        data[i].Translate(offsetX, offsetY);
    }

    //设置形状的新位置
    SetPosX(posX + offsetX);
    SetPosY(posY + offsetY);

    return true;
}
