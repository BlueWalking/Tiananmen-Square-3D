double fang[8][3];             // ���峤�����8������

double triPrism[6][3];            //������ŵ�������

double fourPrism[8][3];     //��������̨������


//��һ��xyz�����½ǵĵ㣬�ڶ�����������ƫ������
//�����֣������ǰ����Һ���z��ƫ��Ӧ�Ǹ���
//�����������ǰ����z��ƫ��Ӧ������
void constract(double x, double y, double z, double x1, double y1, double z1)  //������  ��buildһ����
{
    fang[0][0] = x;
    fang[0][1] = y;
    fang[0][2] = z;        //  ��0����

    fang[1][0] = x;
    fang[1][1] = y;
    fang[1][2] = z + z1;     //  ��һ����

    fang[2][0] = x + x1;
    fang[2][1] = y;
    fang[2][2] = z + z1;     //  �ڶ�����

    fang[3][0] = x + x1;
    fang[3][1] = y;
    fang[3][2] = z;        //  ��������
    for (int i = 0; i<4; i++)   // for()ѭ�������������ĸ���
    {
        for (int j = 0; j<3; j++)
        {
            if (j == 1)
                fang[i + 4][j] = fang[i][j] + y1;
            else
                fang[i + 4][j] = fang[i][j];
        }
    }
}

void build() 	//��constractһ���ã���������
{
    glBegin(GL_POLYGON);
    //glColor3f(red);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
    glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
    glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
    glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
    glEnd();   //     �µ�

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
    glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
    glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
    glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
    glEnd();   //     ����

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
    glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
    glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
    glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
    glEnd();   //     ����

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
    glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
    glVertex3f(fang[2][0], fang[2][1], fang[2][2]);
    glVertex3f(fang[1][0], fang[1][1], fang[1][2]);
    glEnd();   //     ǰ��

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(fang[0][0], fang[0][1], fang[0][2]);
    glVertex3f(fang[3][0], fang[3][1], fang[3][2]);
    glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
    glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
    glEnd();   //     ����

    glBegin(GL_POLYGON);
    //glColor3f(red);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(fang[4][0], fang[4][1], fang[4][2]);
    glVertex3f(fang[7][0], fang[7][1], fang[7][2]);
    glVertex3f(fang[6][0], fang[6][1], fang[6][2]);
    glVertex3f(fang[5][0], fang[5][1], fang[5][2]);
    glEnd();   //     ����
}

/*****************************��������*******************************************/
//�����������ε�ǰһ����Ͷ�������꣬�Լ���������
void consTriPrism(double x, double y, double z, double x1, double y1, double z1, double length)
{
    triPrism[0][0] = x;
    triPrism[0][1] = y;
    triPrism[0][2] = z;     //��һ���㣬�����εױߵ�һ����

    triPrism[1][0] = x1;
    triPrism[1][1] = y1;
    triPrism[1][2] = z1;    //�ڶ����㣬������������Ǹ���

    int hemiZ = z - z1;
    int Z = 2 * hemiZ;

    triPrism[2][0] = x;
    triPrism[2][1] = y;
    triPrism[2][2] = z - Z; //�������㣬�����εױߵ�����һ����

    for(int i = 3; i < 6; i++)
    {
        triPrism[i][0] = triPrism[i - 3][0] + length;
        triPrism[i][1] = triPrism[i - 3][1];
        triPrism[i][2] = triPrism[i - 3][2];
    }
    //���˳��0���-����-ǰ  1���-����  2���-����-�� 3�Ҳ�-����-ǰ  4�Ҳ�-����  5�Ҳ�-����-��
}
//��������
void buileTriPrism()
{
    //������������
    glBegin(GL_TRIANGLES);
    glVertex3f(triPrism[0][0], triPrism[0][1], triPrism[0][2]);
    glVertex3f(triPrism[1][0], triPrism[1][1], triPrism[1][2]);
    glVertex3f(triPrism[2][0], triPrism[2][1], triPrism[2][2]);
    glEnd();

    //���Ҳ��������
    glBegin(GL_TRIANGLES);
    glVertex3f(triPrism[3][0], triPrism[3][1], triPrism[3][2]);
    glVertex3f(triPrism[4][0], triPrism[4][1], triPrism[4][2]);
    glVertex3f(triPrism[5][0], triPrism[5][1], triPrism[5][2]);
    glEnd();

    //��ǰ����ı���
    glBegin(GL_POLYGON);
	//glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(triPrism[0][0], triPrism[0][1], triPrism[0][2]);
	glVertex3f(triPrism[3][0], triPrism[3][1], triPrism[3][2]);
	glVertex3f(triPrism[4][0], triPrism[4][1], triPrism[4][2]);
	glVertex3f(triPrism[1][0], triPrism[1][1], triPrism[1][2]);
	glEnd();

    //��������ı���
    glBegin(GL_POLYGON);
	//glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(triPrism[2][0], triPrism[2][1], triPrism[4][2]);
	glVertex3f(triPrism[1][0], triPrism[1][1], triPrism[1][2]);
	glVertex3f(triPrism[4][0], triPrism[4][1], triPrism[4][2]);
	glVertex3f(triPrism[5][0], triPrism[5][1], triPrism[4][2]);
	glEnd();

    //���ײ���ı���
    glBegin(GL_POLYGON);
    //glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(triPrism[2][0], triPrism[2][1], triPrism[2][2]);
    glVertex3f(triPrism[0][0], triPrism[0][1], triPrism[0][2]);
    glVertex3f(triPrism[3][0], triPrism[3][1], triPrism[3][2]);
    glVertex3f(triPrism[5][0], triPrism[5][1], triPrism[5][2]);
    glEnd();
}

/*****************************������̨****************************************/
void consFourPrism(double x1, double y1, double z1, double x2, double y2, double z2,
                  double x3, double y3, double z3, double x4, double y4, double z4)
{
    fourPrism[0][0] = x1;
    fourPrism[0][1] = y1;
    fourPrism[0][2] = z1;     //��0���㣬�������ǰ��

    fourPrism[2][0] = x2;
    fourPrism[2][1] = y2;
    fourPrism[2][2] = z2;      //��2���㣬������Һ�

    fourPrism[4][0] = x3;
    fourPrism[4][1] = y3;
    fourPrism[4][2] = z3;     //��4���㣬ƽ̨����ǰ��

    fourPrism[6][0] = x4;
    fourPrism[6][1] = y4;
    fourPrism[6][2] = z4;      //��6���㣬ƽ̨���Һ�

    ///�Ӽ�
    fourPrism[1][0] = x1;
    fourPrism[1][1] = y1;
    fourPrism[1][2] = z2;     //��1���㣬�������ǰ��

    fourPrism[3][0] = x2;
    fourPrism[3][1] = y1;
    fourPrism[3][2] = z1;      //��2���㣬������Һ�

    fourPrism[5][0] = x3;
    fourPrism[5][1] = y3;
    fourPrism[5][2] = z4;     //��5���㣬ƽ̨����ǰ��

    fourPrism[7][0] = x4;
    fourPrism[7][1] = y3;
    fourPrism[7][2] = z3;      //��7���㣬ƽ̨���Һ�
}
void buildFourPrism()
{
    glBegin(GL_POLYGON);
    //glColor3f(red);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(fourPrism[0][0], fourPrism[0][1], fourPrism[0][2]);
    glVertex3f(fourPrism[1][0], fourPrism[1][1], fourPrism[1][2]);
    glVertex3f(fourPrism[2][0], fourPrism[2][1], fourPrism[2][2]);
    glVertex3f(fourPrism[3][0], fourPrism[3][1], fourPrism[3][2]);
    glEnd();   //     �µ�

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(fourPrism[1][0], fourPrism[1][1], fourPrism[1][2]);
    glVertex3f(fourPrism[0][0], fourPrism[0][1], fourPrism[0][2]);
    glVertex3f(fourPrism[4][0], fourPrism[4][1], fourPrism[4][2]);
    glVertex3f(fourPrism[5][0], fourPrism[5][1], fourPrism[5][2]);
    glEnd();   //     ����

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(fourPrism[7][0], fourPrism[7][1], fourPrism[7][2]);
    glVertex3f(fourPrism[6][0], fourPrism[6][1], fourPrism[6][2]);
    glVertex3f(fourPrism[2][0], fourPrism[2][1], fourPrism[2][2]);
    glVertex3f(fourPrism[3][0], fourPrism[3][1], fourPrism[3][2]);
    glEnd();   //     ����

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(fourPrism[5][0], fourPrism[5][1], fourPrism[5][2]);
    glVertex3f(fourPrism[6][0], fourPrism[6][1], fourPrism[6][2]);
    glVertex3f(fourPrism[2][0], fourPrism[2][1], fourPrism[2][2]);
    glVertex3f(fourPrism[1][0], fourPrism[1][1], fourPrism[1][2]);
    glEnd();   //     ����

    glBegin(GL_POLYGON);
    //glColor3f(green);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(fourPrism[0][0], fourPrism[0][1], fourPrism[0][2]);
    glVertex3f(fourPrism[3][0], fourPrism[3][1], fourPrism[3][2]);
    glVertex3f(fourPrism[7][0], fourPrism[7][1], fourPrism[7][2]);
    glVertex3f(fourPrism[4][0], fourPrism[4][1], fourPrism[4][2]);
    glEnd();   //     ǰ��

    glBegin(GL_POLYGON);
    //glColor3f(red);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(fourPrism[4][0], fourPrism[4][1], fourPrism[4][2]);
    glVertex3f(fourPrism[7][0], fourPrism[7][1], fourPrism[7][2]);
    glVertex3f(fourPrism[6][0], fourPrism[6][1], fourPrism[6][2]);
    glVertex3f(fourPrism[5][0], fourPrism[5][1], fourPrism[5][2]);
    glEnd();   //     ����
}


/**************************************��Բ����*********************************************/
//�ȵ����������ٷⶥ
GLvoid DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
    GLfloat vertex[4];

    const GLfloat delta_angle = 2.0*M_PI/num_segments;
    glBegin(GL_TRIANGLE_FAN);

    vertex[0] = cx;
    vertex[1] = cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);

    //draw the vertex on the contour of the circle
    for(int i = 0; i < num_segments ; i++)
    {
        vertex[0] = cos(delta_angle*i) * r + cx;
        vertex[1] = sin(delta_angle*i) * r + cy;
        vertex[2] = cz;
        vertex[3] = 1.0;
        glVertex4fv(vertex);
    }

    vertex[0] = 1.0 * r + cx;
    vertex[1] = 0.0 * r + cy;
    vertex[2] = cz;
    vertex[3] = 1.0;
    glVertex4fv(vertex);
    glEnd();
}

void mySolidCylinder( GLUquadric*   quad,
                      GLdouble base,    //radius
                      GLdouble top,     //radius
                      GLdouble height,
                      GLint slices,
                      GLint stacks )
{
    gluCylinder(quad, base, top, height, slices, stacks);
    //top
    DrawCircleArea(0.0, 0.0, height, top, slices);
    //base
    DrawCircleArea(0.0, 0.0, 0.0, base, slices);
}

