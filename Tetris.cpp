#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "Common.h"
#include "Tetris.h"

using namespace std;

//-----------------初始化变量---------------
//随机创建一个形状
Figure tetrisFigure(rand() % NUM_FIGURE);

//创建游戏类对象
Game tetrisGame;

//-----------------OpenGL使用的回调函数---------------

//键盘输入处理函数
void HandleKeyPress(unsigned char key, int x, int y);

//显示处理函数
void Display(void);

//更新处理函数
void Update(int value);

//键盘处理函数
//参数：key：按键的ASCII码， 剩下的时按键时候相对于窗口左上角的鼠标坐标
void HandleKeyPress(unsigned char key, int x, int y)
{
    //a:形状向左移动
    //s:形状向下移动
    //d:形状向右移动
    //w:形状向左旋转90°
    if(tetrisGame.GetStatus())
    {
        switch (key)
        {
        case 'a':
            tetrisFigure.Translate(-1, 0);
            glutPostRedisplay();
            break;
        case 's':
            tetrisFigure.Translate(0, -1);
            glutPostRedisplay();
            break;
        case 'd':
            tetrisFigure.Translate(1, 0);
            glutPostRedisplay();
            break;
        case 'w':
            tetrisFigure.Rotate();
            glutPostRedisplay();
            break;
        default:
            break;
        }
    }
    else
    {
        //如果游戏已经失败
        //n：开始新的游戏
        switch (key)
        {
        case 'n':
            tetrisGame.New();
            glutPostRedisplay();
            break;
        default:
            break;
        }
    }

}

//显示函数
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    //如果游戏没有结束，显示当前的形状
    if(tetrisGame.GetStatus())
        tetrisFigure.Draw();

    //显示游戏界面
    tetrisGame.Draw();
    glutSwapBuffers();
}

//更新函数
void Update(int value)
{
    //如果游戏没有结束
    if(tetrisGame.GetStatus())
    {
        //向下移动形状
        int moveSuccess = tetrisFigure.Translate(0, -1);

        //如果移动失败，表示当前形状已经无法下一，更新游戏状态并创建新的形状
        if(!moveSuccess)
        {
            tetrisGame.Update(tetrisFigure);
            tetrisFigure.New(rand() % NUM_FIGURE);
        }
    }

    //刷新显示
    glutPostRedisplay();

    //设置每0.5s刷新一次
    glutTimerFunc(500, Update, 0);
}

int main(int argc, char *argv[])
{
    //初始化
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );

    //设置游戏界面大小，多出来的范围用来显示边界
    glutInitWindowSize(WINDOW_WIDTH+100, WINDOW_HEIGHT+100);

    //设置游戏界面的位置
    glutInitWindowPosition(50, 50);

    //创建游戏界面
    glutCreateWindow("Tetris");

    //初始化界面背景色
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //设置游戏图像显示区域
    gluOrtho2D(-50, (GLdouble)WINDOW_WIDTH + 50, -50, (GLdouble)WINDOW_HEIGHT + 50);
    srand(time(NULL));

    //注册显示和键盘处理函数
    glutDisplayFunc(Display);
    glutKeyboardFunc(HandleKeyPress);

    //设置Timer和更新函数
    glutTimerFunc(500, Update, 0);

    //进入主循环
    glutMainLoop();


}

