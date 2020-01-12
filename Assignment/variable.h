/****************对颜色的宏定义******************/
# define  White  1.0 ,  1.0  ,  1.0   // 对颜色的宏定义
# define  green  0.0 ,  0.502,  0.0
# define  red    0.8 ,  0.0  ,  0.0
# define  gray   0.502, 0.502,0.502
# define  pi  3.14159265
# define  gold   1.0,215.0/255.0,0.0
# define  nbrown 128.0/255.0, 64.0/255.0, 64.0/255.0
# define  menba   139.0/255.0 ,69.0/255.0,19.0/255.0

# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0
# define orangeRed 255.0/255.0, 69.0/255.0, 0.0/255.0
# define ZhuZi 210.0/255.0, 50.0/255.0, 10.0/255.0
# define ZhuCeng 255.0/255.0, 50.0/255.0, 0.0/255.0
# define GuoHuiCeng 200.0/255.0, 50.0/255.0, 10.0/255.0
# define MiSe 255.0/255.0, 245.0/255.0, 255.0/255.0 ///偏纯白
# define Bisque 255/255.0, 228/255.0, 196/255.0     ///偏纯白
# define Tomato 255/255.0 ,99/255.0 ,71/255.0       ///稍微偏红
# define LightGrey 211/255.0, 211/255.0, 211/255.0 ///浅灰色
# define DarkGray 169/255.0,169/255.0,169/255.0 ///深灰色
# define SandyBrown 244/255.0,164/255.0,96/255.0  ///沙棕色
# define Wheat 245/255.0,222/255.0,179/255.0 ///小麦色
# define Tan 210/255.0,180/255.0,140/255.0 ///偏棕灰
# define BrulyWood 222/255.0,184/255.0,135/255.0 ///淡，偏棕灰


/*********************定义变量*********************/
int winHeight = 0, winWidth = 0;
GLfloat timer = 0;
int sunRadius = 250; //太阳绕半圆移动时的半径

int groundSize = 350;   //前后共500

int skyEnable = 1;  //默认对天空贴图

///键盘响应的变量
GLfloat angle = 0;
GLfloat angle_UpDown = 0;
static float cx = 0.0f, cy = 15.0f, cz = 80.0f;//相机位置
static float lx = 0.0f, ly = 0.0f, lz = -20.0f;//视线方向，初始设为沿着Z轴负方向


///小人结构体
const int peopleNum = 50;
typedef struct people{
    int peopleTime;   //控制小人移动的时间
    float peopleAngle;
    float peopleX;
    float peopleY;
    float peopleZ;
}p;
p people[peopleNum];


/** 粒子结构 */
typedef struct Particle
{
    float x,y,z;            //粒子的位置
    unsigned int  r,g,b;    //粒子的颜色
    float vx,vy,vz;         //粒子的速度(x,y,z方向)
    float ax,ay,az;         //粒子在x，y，z上的加速度
    float lifetime;         //粒子生命值
    float size;             //粒子尺寸
    float dec;              //粒子消失的速度
}s;
const int snowNum = 8000;
s snow[snowNum];
int snowEnable = 0;  //雪花效果默认关闭
float sx,sy,sz,vx,vy,vz,ax,ay,az,size,lifetime,dec;
int r,g,b;
float snowHeight = 0;

/****************函数声明****************/
void setMaterial();


/****************光源&材质属性定义******************/
/* 点光源 */
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };//color
GLfloat purple[] = { 1.0, 0, 1.0, 1.0 };//color

/* 太阳光——平行光 */
GLfloat light2_position[] = {0, 100, 0, 0};

GLfloat mat_specular[]={0.8,1.0,1.0,1.0};
GLfloat mat_shininess[]={5.0};
GLfloat mat_ambient[]={0.1,0.1,0.1,1};

GLfloat	no_mat[]= {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat	mat_diffuse1[]= {0.1f, 0.5f, 0.8f, 1.0f};
GLfloat	no_shininess[]= {0.0f};

GLfloat sunshine_mat[] = {sunshine, 1.0f};

GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };
/************************定义各个纹理对象的名称*************************/

GLuint texTianAnMen;
GLuint texMao;
GLuint texZuoZi;
GLuint texYouZi;
GLuint texGuoHui;
GLuint texWindow;

GLuint texSky;

GLuint texBrick;
GLuint texGrass;
GLuint texFlag;

GLuint texMoon;
GLuint texSun;

GLuint texSnow;

GLuint texHJS;
GLuint texQSP;
GLuint texDYC;
GLuint texXHC;

GLuint texNight1;
GLuint texNight2;
GLuint texNight3;
GLuint texNight4;
GLuint texNight5;
GLuint texNight6;
GLuint texNight7;
GLuint texNight8;
GLuint texNight9;
GLuint texNight9Star;

