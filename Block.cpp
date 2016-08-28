#include "Common.h"
#include "Tetris.h"

//全局游戏类对象
extern Game tetrisGame;

//Block的构造函数
Block::Block()
{
    //默认位置居中，在顶部
    posX = NUM_BLOCKS_X / 2;
    posY = NUM_BLOCKS_Y - 1;
}

//Block的虚析构函数
Block::~Block() {}

//显示Block
void Block::Draw() const
{
    //获得Block的坐标
    int left = posX * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
    int right = left + BLOCK_SIZE;
    int bottom = posY * (BLOCK_SIZE + BLOCK_SPACING) - BLOCK_SPACING;
    int top = bottom + BLOCK_SIZE;

    //调用OpenGL库函数显示方块
    glBegin(GL_QUADS);
    glColor3d(1,1,1);
    glVertex3f(left, top, 0);
    glVertex3f(right, top, 0);
    glVertex3f(right, bottom, 0);
    glVertex3f(left, bottom, 0);
    glEnd();
}

//判断方块是否可以跟着形状旋转到指定位置
bool Block::CanRotate(const int figureX, const int figureY) const
{
    //方块位置与形状位置的位移
    int offsetX = posX - figureX;
    int offsetY = posY - figureY;
    
    //如果方块位置即为形状位置，则旋转形状不需要调整方块位置
    if(offsetX == 0 && offsetY == 0)
        return true;
    //向左选装90°的新位置
    int nextPosX = figureX - offsetY;
    int nextPosY = figureY + offsetX;

    //目标位置意境有方块，则返回false
    if(tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY)
        return false;

    //临时变量存储旋转过程中经过的所有位置
    int tmpX[3], tmpY[3];

    //分别对不同的情况的讯专经过的区域惊醒判断，只有这些区域都没有方块才可以旋转
    //tmpX[0]和tmpY[0]分别为旋转过程中左边及上边所达到的最远坐标
    tmpX[0] = figureX + offsetX - offsetY;
    tmpY[0] = figureY + offsetX + offsetY;

    if(abs(offsetX) > 1 || abs(offsetY) > 1)
    {
        //旋转的时I字形，且为离形状位置最远的方块
        //(tmpX[1], tmpY[1])与(tmpX[2], tmpY[2])为向左旋转过程中经过的区域
        tmpX[1] = (tmpX[0] + posX) / 2;
        tmpX[2] = (tmpX[0] + figureX - offsetY) / 2;
        tmpY[1] = (tmpY[0] + posY) / 2;
        tmpY[2] = (tmpY[0] + figureY +offsetX) / 2;

        //如果这两个坐标位置有方块则无法旋转
        if(tetrisGame.GetMap(tmpX[1], tmpY[1]) != EMPTY || tetrisGame.GetMap(tmpX[2], tmpY[2])
                != EMPTY)
            return false;
    }
    else if(abs(offsetX) == 1 || abs(offsetY) == 1)
    {
        //方块与形状位置45°相邻
        //(tmpX[1], tmpY[1])为向左旋转过程中讲过的区域
        tmpX[1] = (tmpX[0] + posX) / 2;
        tmpY[1] = (tmpY[0] + posY) / 2;

        //如果tmpX[1], tmpY[1]位置有方块则无法旋转
        if(tetrisGame.GetMap(tmpX[1], tmpY[1]) != EMPTY)
            return false;
    }
    else if(tetrisGame.GetMap(tmpX[0], tmpY[0]) != EMPTY)
        //方块与形状相邻
        return false;

    return true;

}

//旋转形状
bool Block::Rotate(const int figureX, const int figureY)
{
    //如果不可以移动，返回false
    if(!CanRotate(figureX, figureY))
        return false;

    //方块位置与形状位置的位移
    int offsetX = posX - figureX;
    int offsetY = posY - figureY;

    //向左选装90°的新位置,并旋转到该位置
    int nextPosX = figureX - offsetY;
    int nextPosY = figureY + offsetX;
    SetPosX(nextPosX);
    SetPosY(nextPosY);

    return true;
}

//判断方块是否可以移动到指定位置
bool Block::CanTranslate(const int offsetX, const int offsetY) const
{
    //获得目标位置
    int nextPosX = posX + offsetX;
    int nextPosY = posY + offsetY;

    //目标位置如果有方块，则返回false
    if(tetrisGame.GetMap(nextPosX, nextPosY) != EMPTY)
        return false;
    return true;
}

bool Block::Translate(const int offsetX, const int offsetY)
{
    //目标位置如果有方块，则返回false
    if(!CanTranslate(offsetX, offsetY))
        return false;

    //获得目标位置,并旋转到该位置
    int nextPosX = posX + offsetX;
    int nextPosY = posY + offsetY;
    SetPosX(nextPosX);
    SetPosY(nextPosY);
}
