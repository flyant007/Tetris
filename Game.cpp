#include "Common.h"
#include "Tetris.h"

void Game::Draw() const
{
    //设置游戏界面大小，多出来的范围用来显示边界
    glutInitWindowSize(WINDOW_WIDTH+100, WINDOW_HEIGHT+100);

    //设置游戏界面的位置
    glutInitWindowPosition(50, 50);

    //创建游戏界面
    glutCreateWindow("Tetris");

    //初始化界面背景色
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //设置游戏图像显示区域
    gluOrtho2D(-50, (GLdouble)WINDOW_WIDTH+50, -50,(GLdouble)WINDOW_HEIGHT+50);

    //-----------------画图流程---------------
    //几何数据的输入，其参数表示其下所接收的数据时何种类型，GL_LINE_LOOP表示回执封闭曲线
    glBegin(GL_LINE_LOOP);

    //设置绘制的几何图形的颜色
    glColor3f(0.5, 0.2, 0.1);

    //为绘制的几何图像设置需要的坐标点
    glVertex3f(0, 0, 0);
    glVertex3f(WINDOW_WIDTH-100/2, 0, 0);
    glVertex3f(WINDOW_WIDTH-100/2, WINDOW_HEIGHT, 0);
    glVertex3f(0, WINDOW_HEIGHT,0);

    //结束绘图
    glEnd();

}
