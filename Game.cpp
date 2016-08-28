#include "Common.h"
#include "Tetris.h"
#include <stdio.h>
#include <string>
#include <sstream>

//全局对象，当前正在下落的形状对象
extern Figure tetrisFigure;

//游戏类构造函数
Game::Game()
{
    //获得界面中宽和高各可以容纳多少方块
    num_col = (WINDOW_WIDTH) / (BLOCK_SIZE + BLOCK_SPACING);
    num_row = (WINDOW_HEIGHT) / (BLOCK_SIZE + BLOCK_SPACING);

    //设置默认刷新速度
    speed = 500;

    //初始分数为0
    score = 0;

    //设置失败标志位
    status = true;
}

//析构函数
Game::~Game()
{

}

//显示得分
std::string Game::ShowScore()
{
    std::stringstream ss;
    std::string str;
    ss << score;
    ss >> str;
    return str;
}

//显示游戏界面
void Game::Draw()
{
    int i, j;

    //-----------------画图流程,显示边界---------------
    //几何数据的输入，其参数表示其下所接收的数据时何种类型，GL_LINE_LOOP表示回执封闭曲线
    glBegin(GL_LINE_LOOP);

    //设置绘制的几何图形的颜色
    glColor3f(0.5, 0.2, 0.1);

    //为绘制的几何图像设置需要的坐标点
    glVertex3f(0, 0, 0);
    glVertex3f(WINDOW_WIDTH-BLOCK_SIZE/2, 0, 0);
    glVertex3f(WINDOW_WIDTH-BLOCK_SIZE/2, WINDOW_HEIGHT, 0);
    glVertex3f(0, WINDOW_HEIGHT,0);

    //结束绘图
    glEnd();

    //-----------------显示游戏---------------
    //如果没有失败，游戏继续
    if(status)
    {
        Block block = Block();

        //扫描map数组，根据内容显示所有需要显示的方块
        for(i = 0; i < num_row; ++i)
        {for(j = 0; j < num_col; ++j)
            {
                if(map[i][j])
                {
                    //该坐标位置需要显示方块
                    block.SetPosX(j);
                    block.SetPosY(i);
                    block.Draw();
                }
            }
        }
    }
    else
    {
        //游戏失败结束，显示GAME OVER + 得分
//        char string[] = "GAME OVER";
        std::string  end_str = "GAME OVER" + ShowScore();
        int len;

        glRasterPos2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

        //获取游戏结束后字符串长度
//        len = (int) strlen(string);
        len = end_str.size();

        //依次显示每个字母
        for(i = 0; i < len; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, end_str[i]);
        }
    }

}

//创建新游戏
void Game::New()
{
    //初始化界面中的每一个方块区域：初始化map数组
    int i, j;
    for(i = 0; i < num_row; ++i)
    {
        for(j = 0; j < num_col; ++j)
        {
            map[i][j] = EMPTY;
        }
    }

    //创建第一个形状
    tetrisFigure.New(rand() % NUM_FIGURE);

    //设置默认刷新速度
    speed = 500;

    //初始分数为0
    score = 0;

    //设置失败标志位
    status = true;
}

//更新游戏界面状态
void Game::Update(const Figure &figure)
{
    int i, num;

    //根据形状设置对应位置方块标志，每个形状由四个方块组成
    for(i = 0; i < NUM_FIGURE_BLOCK; ++i)
    {
        map[figure.data[i].GetPosY()][figure.data[i].GetPosX()] =USED;
    }

    //如果存在满行，则消除该行
    //获得最新形状的Y坐标
    num = figure.GetPosY();

    //从num位置开始判断是否已经满行,如果满行，则消除该行
    for(i = num + 2; i >= num - 2; --i)
    {
        if(RowIsFull(i))
        {
            ClearRow(i);
        }
    }
}

//清除行，该行方块消失，其他{return score;}行自动向下移动，并将分数+10
void Game::ClearRow(const int row)
{
    int i, j;

    //输入无效，返回
    if(row < 0 || row >= num_row)
        return;

    //扫面map，将没一行都向下移动
    for(i = row; i < num_row - 2; ++i)
        for(j = 0; j < num_col; ++j)
            map[i][j] = map[i+1][j];

    //将最上面一行内容清空
    for(j = 0; j < num_col; ++j)
        map[num_row - 1][j] = 0;

    //将分数+10
    score += 10;
}

//判断是否已经满行
bool Game::RowIsFull(const int row) const
{
    int i;

    //如果输入无效则返回false
    if(row < 0 || row >= num_row)
        return false;

    //扫面map种的指定数据查看是否为空
    for(i = 0; i < num_col; ++i)
        if(map[row][i] == EMPTY)
            return false;

    return true;
}

//获得游戏界面中指定坐标区域种的方块是否显示
int Game::GetMap(const int x, const int y) const
{
    if((x < 0) || (y < 0) || (x >= num_col) || (y >= num_row))
        return -1;
    else
        return map[y][x];
}
