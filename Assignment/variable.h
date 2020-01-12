/****************����ɫ�ĺ궨��******************/
# define  White  1.0 ,  1.0  ,  1.0   // ����ɫ�ĺ궨��
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
# define MiSe 255.0/255.0, 245.0/255.0, 255.0/255.0 ///ƫ����
# define Bisque 255/255.0, 228/255.0, 196/255.0     ///ƫ����
# define Tomato 255/255.0 ,99/255.0 ,71/255.0       ///��΢ƫ��
# define LightGrey 211/255.0, 211/255.0, 211/255.0 ///ǳ��ɫ
# define DarkGray 169/255.0,169/255.0,169/255.0 ///���ɫ
# define SandyBrown 244/255.0,164/255.0,96/255.0  ///ɳ��ɫ
# define Wheat 245/255.0,222/255.0,179/255.0 ///С��ɫ
# define Tan 210/255.0,180/255.0,140/255.0 ///ƫ�ػ�
# define BrulyWood 222/255.0,184/255.0,135/255.0 ///����ƫ�ػ�


/*********************�������*********************/
int winHeight = 0, winWidth = 0;
GLfloat timer = 0;
int sunRadius = 250; //̫���ư�Բ�ƶ�ʱ�İ뾶

int groundSize = 350;   //ǰ��500

int skyEnable = 1;  //Ĭ�϶������ͼ

///������Ӧ�ı���
GLfloat angle = 0;
GLfloat angle_UpDown = 0;
static float cx = 0.0f, cy = 15.0f, cz = 80.0f;//���λ��
static float lx = 0.0f, ly = 0.0f, lz = -20.0f;//���߷��򣬳�ʼ��Ϊ����Z�Ḻ����


///С�˽ṹ��
const int peopleNum = 50;
typedef struct people{
    int peopleTime;   //����С���ƶ���ʱ��
    float peopleAngle;
    float peopleX;
    float peopleY;
    float peopleZ;
}p;
p people[peopleNum];


/** ���ӽṹ */
typedef struct Particle
{
    float x,y,z;            //���ӵ�λ��
    unsigned int  r,g,b;    //���ӵ���ɫ
    float vx,vy,vz;         //���ӵ��ٶ�(x,y,z����)
    float ax,ay,az;         //������x��y��z�ϵļ��ٶ�
    float lifetime;         //��������ֵ
    float size;             //���ӳߴ�
    float dec;              //������ʧ���ٶ�
}s;
const int snowNum = 8000;
s snow[snowNum];
int snowEnable = 0;  //ѩ��Ч��Ĭ�Ϲر�
float sx,sy,sz,vx,vy,vz,ax,ay,az,size,lifetime,dec;
int r,g,b;
float snowHeight = 0;

/****************��������****************/
void setMaterial();


/****************��Դ&�������Զ���******************/
/* ���Դ */
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };//color
GLfloat purple[] = { 1.0, 0, 1.0, 1.0 };//color

/* ̫���⡪��ƽ�й� */
GLfloat light2_position[] = {0, 100, 0, 0};

GLfloat mat_specular[]={0.8,1.0,1.0,1.0};
GLfloat mat_shininess[]={5.0};
GLfloat mat_ambient[]={0.1,0.1,0.1,1};

GLfloat	no_mat[]= {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat	mat_diffuse1[]= {0.1f, 0.5f, 0.8f, 1.0f};
GLfloat	no_shininess[]= {0.0f};

GLfloat sunshine_mat[] = {sunshine, 1.0f};

GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };
/************************�������������������*************************/

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

