#include "Common.h"
#include "Tetris.h"

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
