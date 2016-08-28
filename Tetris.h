#ifndef TETRIS_H
#define TETRIS_H
/****************************************************
 * 实现程序中所有类的定义
 *
 ***************************************************/
#include "Common.h"
#include <GL/glut.h>
#include <string>

class Block
{
public:

    //构造函数
    Block();

    //虚析构函数
    virtual ~Block();

    //画出方块本身
    void Draw() const;

    //形状旋转时，方块随之移动到指定的位置，参数为该方块所处形状的中心位置
    bool Rotate(const int figureX, const int figureY);

    //方块移动指定的偏移
    //输入参数：目标位置和当前位置之间的偏移
    bool Translate(const int offsetX, const int offsetY);

    //判断方块是否可以跟着形状旋转到指定位置
    //参数为该方块所属的形状的位置
    bool CanRotate(const int figureX, const int figureY) const;

    //判断方块是否可以移动到指定的偏移
    //输入参数：目标位置和当前位置之间的偏移
    bool CanTranslate(const int offsetX, const int offsetY) const;

    //返回方块的位置
    int GetPosX() const {return posX;}
    int GetPosY() const {return posY;}

    //设置方块的位置
    void SetPosX(const int x) {posX = x;}
    void SetPosY(const int y) {posY = y;}

    //重载赋值操作符
    Block & operator = (Block & other)
    {
        if(this != &other)
        {
            SetPosX(other.GetPosX());
            SetPosY(other.GetPosY());
        }
        return *this;
    }

private:
    //方块的位置
    int posX, posY;

};

//形状类，每个形状由4个方块组成
class Figure
{
public:
    //构造函数
    Figure();
    Figure(int numFigure);

    //虚析构函数
    virtual ~Figure();

    //创建新形状
    void New(int numFigure);

    //显示形状
    void Draw() const;

    //向左90°旋转形状
    bool Rotate();

    //移动形状
    bool Translate(const int offsetX, const int offsetY);

    //返回形状的位置
    int GetPosX() const {return posX;}
    int GetPosY() const {return posY;}

    //设置形状的位置
    void SetPosX(const int x) {posX = x;}
    void SetPosY(const int y) {posY = y;}

    //组成形状的方块列表
    Block data[NUM_FIGURE_BLOCK];
private:
    //形状的位置
    int posX, posY;

    //是否可以变形
    bool canRotate;
};

//游戏类
class Game
{
public:
    //构造函数和析构函数
    Game();
    virtual ~Game();

    //显示界面
    void Draw();

    //更新游戏界面状态
    void Update(const Figure &figure);

    //判断行是否已经填满
    bool RowIsFull(const int row) const;

    //清空行
    void ClearRow(const int row);

    //创建新游戏
    void New();

    //获得游戏界面中指定坐标区域的方块是否显示
    int GetMap(const int x, const int y) const;

    //获得游戏运行状态：RUNNING或LOSE
    bool GetStatus() const {return status;}

    //设置游戏运行状态
    void SetStatus(const bool newstatus) {status = newstatus;}

    //设置游戏刷新实时间，控制游戏速度
    void SetSpeed(const int value) {speed = value;}

    //获得游戏刷新实时间，控制游戏速度
    int GetSpeed() {return speed;}

    //显示得分
    std::string ShowScore();


private:
    //界面行数和列数
    int num_row, num_col;

    //2D界面显示内容，数组中每个元素表示一个显示单元
    int map[MAX_BLOCK_NUM][MAX_BLOCK_NUM];

    //游戏状态，True表示游戏运行，False表示游戏失败
    bool status;

    //设置游戏刷新实时间，控制游戏速度
    int speed;

    //计分
    int score;


};



#endif // TETRIS_H
