#include <stdlib.h>
#include "Common.h"
#include <GL/glut.h>
//void background(void)
//{
//    glClearColor(0.0,0.0,0.0,0.0);//设置背景颜色为黑色
//}

//void myDisplay(void)
//{
//    glClear(GL_COLOR_BUFFER_BIT);//buffer设置为颜色可写

//    glBegin(GL_TRIANGLES);//开始画三角形
//    glShadeModel(GL_SMOOTH);//设置为光滑明暗模式

//    glColor3f(1.0,0.0,0.0);//设置第一个顶点为红色
//    glVertex2f(-1.0,-1.0);//设置第一个顶点的坐标为（-1.0，-1.0）

//    glColor3f(0.0,1.0,0.0);//设置第二个顶点为绿色
//    glVertex2f(0.0,-1.0);//设置第二个顶点的坐标为（0.0，-1.0）

//    glColor3f(0.0,0.0,1.0);//设置第三个顶点为蓝色
//    glVertex2f(-0.5,1.0);//设置第三个顶点的坐标为（-0.5，1.0）
//    glEnd();//三角形结束

//    glFlush();//强制OpenGL函数在有限时间内运行
//}

//void myReshape(GLsizei w,GLsizei h)
//{
//    glViewport(0,0,w,h);//设置视口

//    glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
//    glLoadIdentity();//将当前矩阵置换为单位阵

//    if(w <= h)
//        gluOrtho2D(-1.0,1.5,-1.5,1.5*(GLfloat)h/(GLfloat)w);//定义二维正视投影矩阵
//    else
//        gluOrtho2D(-1.0,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5);
//    glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW
//}

//int main(int argc,char ** argv)
//{
//    /*初始化*/
//    glutInit(&argc,argv);
////    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
////    glutInitWindowSize(400,400);
////    glutInitWindowPosition(200,200);

////    /*创建窗口*/
////    glutCreateWindow("Triangle");

////    /*绘制与显示*/
////    background();
////    glutReshapeFunc(myReshape);
////    glutDisplayFunc(myDisplay);

////    glutMainLoop();
//    return(0);
//}

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

    //进入主循环
    glutMainLoop();


}

