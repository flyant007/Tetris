#ifndef COMMON_H
#define COMMON_H
/*************************************************************
 * 本文件用于存放整个程序的宏定义
 *************************************************************/
#include <GL/glut.h>

#define NUM_FIGURE 7 //形状的数量
#define NUM_FIGURE_BLOCK 4 //每个形状需要的方块数量
#define BLOCK_SIZE 19 //方块的边长：19像素
#define BLOCK_SPACING 1 //方块之间的距离：1像素
#define MAX_BLOCK_NUM 100 //游戏界面宽或高最大容纳的方块数
#define WINDOW_WIDTH  350//游戏界面宽度
#define WINDOW_HEIGHT 500//游戏界面高度
#define NUM_BLOCKS_X WINDOW_WIDTH/(BLOCK_SIZE + BLOCK_SPACING) //界面上横坐标可以容纳的方块数
#define NUM_BLOCKS_Y WINDOW_HEIGHT/(BLOCK_SIZE + BLOCK_SPACING) //界面上纵坐标可以容纳的方块数
#define USED 1 //用在游戏类的map二维数组中，表示该坐标位置显示方块
#define EMPTY 0 //用在游戏类的map二维数组中，表示该坐标位置不显示方块
//游戏运行状态
#define RUNNING 1
#define LOSE 0

//3维数组定义7种不同的形状
//第一维表示7种不同的形状
//第二维表示组成形状的4个方块
//第三维是每个方块坐标与形状坐标的偏移量
const int image[NUM_FIGURE][NUM_FIGURE_BLOCK][2] =
{
    {
        //O
        {0,0},{0,1},{1,1},{1,0}
    },
    {
        //I
        {0,-1},{0,0},{0,1},{0,2}
    },
    {
        //J
        {0,1},{-1,1},{-1,0},{-1,-1}
    },
    {
        //L
        {0,1},{1,1},{1,0},{1,-1}
    },
    {
        //S
        {-1,1},{-1,0},{0,0},{0,-1}
    },
    {
        //Z
        {0,1},{0,0},{-1,0},{-1,-1}
    },
    {
        //T
        {-1,0},{0,0},{1,0},{0,1}
    }

};

#endif // COMMON_H
