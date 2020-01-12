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


/******����ˢ�º���******/
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

    if(timer > pi)  //���ϵ�ʱ��ʱ����ÿ�һ��
        timer += 0.008 * pi;
    else
        timer += 0.005 * pi;
    if(timer > pi*2)
        timer = 0;

    //С���ƶ�ʱ��
    for(int i = 0; i < peopleNum; i++)
    {
        people[i].peopleTime ++;
        if(people[i].peopleTime > 1000)
            people[i].peopleTime = 0;
    }

    glutPostRedisplay();
}

///���ò���
void setMaterial()
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_intensity);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sunshine_mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
	glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

/******��ʼ������******/
void initial()
{
    srand(time(NULL));

    /** ��ʼ������ */
    initSnow();

    ///��ʼ��С��
    initPeople();

    //����ģ��
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

    /*********************************************�Եƹ���г�ʼ��****************************************************/
    //̫����--2
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);   //��Դλ��
    glLightfv(GL_LIGHT2, GL_DIFFUSE, sunshine_mat);

    //������ɫ���٣������ڿ����˲���֮��Ҳ������glcolor������ɫ
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  //�Ի�����������������ɫ����

    glEnable(GL_DEPTH_TEST); //����Ȳ���

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);

}

void print()
{
    printf("[w]\t���ǰ��\n");
	printf("[s]\t�������\n");
	printf("[a]\t�������\n");
	printf("[d]\t�������\n");
	printf("[1]\t�������\n");
	printf("[2]\t�������\n\n");
	printf("[q]\t�ӽ���ת\n");
	printf("[e]\t�ӽ���ת\n");
    printf("[3]\t�ӽ���ת\n");
	printf("[4]\t�ӽ���ת\n\n");
	printf("[z]\t����ѩ��Ч��\n\n");
	printf("[�ո�]\t�ص�ԭ���λ��\n\n");
	printf("[������]\t�������߱任\n");
	printf("[����Ҽ�]\t��������ƶ�\n");
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(400, 0);
    glutCreateWindow("�찲�Ź㳡");

    initial();
    print();

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(OnKeyboard);

    glutMouseFunc(mouse);
	glutMotionFunc(motion); //����ƶ�

    glutIdleFunc(idle);

    /*********��������***********/

    texSky = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\�ɹ�1234.bmp");

    texTianAnMen = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\�찲�����ֻ�.bmp");
    texMao = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\mao.bmp");
    texZuoZi = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\�����.bmp");
    texYouZi = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\�ұ���.bmp");
    texGuoHui = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\����.bmp");
    texWindow = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\����.bmp");

    texBrick = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\brick.bmp");
    texGrass = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\grass.bmp");
    texFlag = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\flag.bmp");

    texMoon = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\moon3.bmp");
    texSun = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\sun.bmp");

    texSnow = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\snow2.bmp");

    texNight1 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ1.bmp");
    texNight2 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ2.bmp");
    texNight3 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ3.bmp");
    texNight4 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ4.bmp");
    texNight5 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ5.bmp");
    texNight6 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ6.bmp");
    texNight7 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ7.bmp");
    texNight8 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ8.bmp");
    texNight9 = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ9.bmp");
    texNight9Star = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\��ҹ9������.bmp");

    //��ʾ��
    texHJS = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\hjs.bmp");
    texQSP = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\qsp.bmp");
    texDYC = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\dyc.bmp");
    texXHC = load_texture("C:\\Users\\user\\Desktop\\Assignment\\bmp\\xhc.bmp");


    glutMainLoop();
    return 0;
}
