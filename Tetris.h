#ifndef TETRIS_H
#define TETRIS_H
/****************************************************
 * 实现程序中所有类的定义
 *
 ***************************************************/

//游戏类
class Game
{
public:
    //构造函数和析构函数
    Game();
    virtual ~Game();

    //显示界面
    void Draw() const;

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

private:
    //界面行数和列数
    int num_row, num_col;

    //2D界面显示内容，数组中每个元素表示一个显示单元
    int map[MAX_BLOCK_NUM][MAX_BLOCK_NUM];

    //游戏状态，True表示游戏运行，False表示游戏失败
    bool status;
};

#endif // TETRIS_H
