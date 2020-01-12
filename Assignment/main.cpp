#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#define PI 3.14
#include "variable.h"
#include "texture.h"
#include "skybox.h"
#include "keyboard.h"
#include "construct.h"
#include "tiananmen.h"
#include "people.h"
#include "particle.h"
#include "draw.h"


/******窗口刷新函数******/
void reshape(int width, int height)
{
    if(height == 0)
        height = 1;
    winHeight = height;
    winWidth = width;
    float whRatio = (GLfloat)width/(GLfloat)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0f, whRatio, 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
}


void idle()
{
    Sleep(50);

    if(timer > pi)  //晚上的时候时间过得快一点
        timer += 0.008 * pi;
    else
        timer += 0.005 * pi;
    if(timer > pi*2)
        timer = 0;

    //小人移动时间
    for(int i = 0; i < peopleNum; i++)
    {
        people[i].peopleTime ++;
        if(people[i].peopleTime > 1000)
            people[i].peopleTime = 0;
    }

    glutPostRedisplay();
}

///设置材质
void setMaterial()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_intensity);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sunshine_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

/******初始化函数******/
void initial()
{
    srand(time(NULL));

    /** 初始化粒子 */
    initSnow();

    ///初始化小人
    initPeople();

    //光照模型
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

    /*********************************************对灯光进行初始化****************************************************/
    //太阳光--2
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);   //光源位置
    glLightfv(GL_LIGHT2, GL_DIFFUSE, sunshine_mat);

    //开启颜色跟踪，这样在开启了材质之后，也可以用glcolor设置颜色
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  //对环境光和漫反射进行颜色跟踪

    glEnable(GL_DEPTH_TEST); //打开深度测试

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);

}

void print()
{
    printf("[w]\t相机前移\n");
	printf("[s]\t相机后移\n");
	printf("[a]\t相机左移\n");
	printf("[d]\t相机右移\n");
	printf("[1]\t相机上移\n");
	printf("[2]\t相机下移\n\n");
	printf("[q]\t视角左转\n");
	printf("[e]\t视角右转\n");
    printf("[3]\t视角上转\n");
	printf("[4]\t视角下转\n\n");
	printf("[z]\t开关雪花效果\n\n");
	printf("[空格]\t回到原相机位置\n\n");
	printf("[鼠标左键]\t控制视线变换\n");
	printf("[鼠标右键]\t控制相机移动\n");
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(400, 0);
    glutCreateWindow("天安门广场");

    initial();
    print();

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(OnKeyboard);

    glutMouseFunc(mouse);
	glutMotionFunc(motion); //鼠标移动

    glutIdleFunc(idle);

    /*********设置纹理***********/

    texSky = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\成果1234.bmp");

    texTianAnMen = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\天安门无字画.bmp");
    texMao = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\mao.bmp");
    texZuoZi = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\左边字.bmp");
    texYouZi = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\右边字.bmp");
    texGuoHui = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\国徽.bmp");
    texWindow = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\窗户.bmp");

    texBrick = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\brick.bmp");
    texGrass = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\grass.bmp");
    texFlag = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\flag.bmp");

    texMoon = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\moon3.bmp");
    texSun = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\sun.bmp");

    texSnow = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\snow2.bmp");

    texNight1 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜1.bmp");
    texNight2 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜2.bmp");
    texNight3 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜3.bmp");
    texNight4 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜4.bmp");
    texNight5 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜5.bmp");
    texNight6 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜6.bmp");
    texNight7 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜7.bmp");
    texNight8 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜8.bmp");
    texNight9 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜9.bmp");
    texNight9Star = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\黑夜9加星星.bmp");

    //告示牌
    texHJS = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\hjs.bmp");
    texQSP = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\qsp.bmp");
    texDYC = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\dyc.bmp");
    texXHC = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\xhc.bmp");


    glutMainLoop();
    return 0;
}
