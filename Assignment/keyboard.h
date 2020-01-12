float jiao1 = 0;
float jiao2 = 0;

/******������Ӧ�����任******/
//��ת�������y����ת
void orient_LeftRight(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);
    jiao1 = ang;    //�����̽Ƕ�ƥ��
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
}

//��ת���������ת������x����ת
void orient_UpDown(float ang)
{
    ly = 5 * sin(ang);
    jiao2 = ang;    //�����̽Ƕ�ƥ��
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
}

//ǰ���ƶ����
void move_Front_Back(int direction)
{
    cx = cx + direction*(lx)*1.5;
    cz = cz + direction*(lz)*1.5; //lzΪ��������ǰ
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
    //ͬʱ�ƶ�����������ĵ����ֻ꣬���޸�x��z�����߲��������޸ģ�

    xx += direction*(lx)*1.5;
    zz += direction*(lz)*1.5;
}

//�����ƶ����
void move_Left_Right(int direction)
{
    cx = cx + direction*(lz)*1.5;
    cz = cz - direction*(lx)*1.5; //����ӽ���ת�ˣ������������ת�ˣ���ôlxΪ�����������ƶ��Ļ���x���٣�z����
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

    xx += direction*(lz)*1.5;
    zz -= direction*(lx)*1.5;
}

//�����ƶ����
void move_High_Low(int direction)
{
    if(cy >= 50)
        cy = cy + direction * 1.4;
    else
      cy = cy + direction * 0.6;
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

    snowHeight = snowHeight - direction * 0.6;  //����ѩ����λ��
}


//���ո���ص�ԭλ�ã���λ���еı���
void reInit()
{
    cx = 0;
    cy = 15;
    cz = 80;
    lx = 0;
    ly = 0;
    lz = -20;
    jiao1 = 0;
    jiao2 = 0;
    angle = 0;
    angle_UpDown = 0;
    xx = 0 - width/2;
    zz = 0 - length/2;
    snowHeight = 0;

    glLoadIdentity();

    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

}


/******������Ӧ����******/
void OnKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'q':
        angle -= 0.03f;
        orient_LeftRight(angle);
        break;
    case 'e':               //q,e�����������ת
        angle += 0.03f;
        orient_LeftRight(angle);
        break;
    case 'w':
        move_Front_Back(1);
        break;
    case 's':
        move_Front_Back(-1);
        break;
    case 'a':
        move_Left_Right(1);
        break;
    case 'd':
        move_Left_Right(-1);
        break;              //wasd�������ǰ�������ƶ�
    case '1':
        move_High_Low(1);
        break;
    case '2':
        move_High_Low(-1);
        break;              //1,2�������ƶ����
    case '3':
        if(angle_UpDown <= PI / 2)
            angle_UpDown += 0.20f;
        orient_UpDown(angle_UpDown);
        break;
    case '4':
        if(angle_UpDown >= - PI / 2)
            angle_UpDown -= 0.20f;
        orient_UpDown(angle_UpDown);
        break;              //3,4�������ƶ��ӽǡ�
    case 'z':
        snowEnable = !snowEnable;
        break;              //����ѩ��Ч��
    case 32:    //�ո�����ص�ԭλ��
        reInit();
        break;
    case 'm':   //�Ƿ��������ͼ
        skyEnable = !skyEnable;
    default:
        break;
    }
}

///�������ӽ�
GLfloat oldx;//���������ʱ��¼�������
GLfloat oldy;
GLfloat oldx2;//���Ҽ�����ʱ��¼�������
GLfloat oldy2;

int left = 1;   //left=1ʱ�����Ч������0ʱ�Ҽ���Ч
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) //��⵽���
    {
        if (state == GLUT_DOWN) //�������
        {
            oldx = x;//���������ʱ��¼�������
            oldy = y;
            left = 1;
        }
    }
    if (button == GLUT_RIGHT_BUTTON)    //��⵽�Ҽ�
    {
        if (state == GLUT_DOWN) //�Ҽ�����
        {
            oldx2 = x;//���������ʱ��¼�������
            oldy2 = y;
            left = 0;
        }
    }
}

void motion(int x, int y)   //x��y�ǵ�ǰ����λ��
{
    //���ƽ�������ƶ���x��
    //������ϣ�y��z����  ���£�y��z����
    ///���  ����ӽ��ƶ�
    if(left == 1)
    {
        ///deltax�������Ǽ�  �����Ǽ�
        ///deltay������Ǹ��� ��ǰ������
        GLint deltax = -(oldx - x);
        GLint deltay = (oldy - y);    ///����ڲ�ͣ���ƶ�������Ӧ������һʱ�̺���һʱ�̵Ĳ�ֵ

        oldx = x;//��¼��ʱ��������꣬�����������
        oldy = y;//����û����������䣬��������ת���ò��ɿ�

        jiao1 += deltax * 0.01;
        lx = sin(jiao1);
        lz = -cos(jiao1);

        jiao2 += deltay * 0.01;
        ly = sin(jiao2);

        //�ü��̿��ƵĽǶȸ��ű仯
        angle_UpDown = jiao2;
        angle = jiao1;
    }
    ///�Ҽ�����������۵�λ���ƶ�
    if(left == 0)
    {
        GLint deltax2 = -(oldx2 - x);
        GLint deltay2 = -(oldy2 - y);
        oldx2 = x;
        oldy2 = y;

        ///���ƽ�������ƶ�
        cx += deltax2*0.12;
        //lx -= deltax*0.05;

        ///���ƽ��ǰ���ƶ�
        cz += deltay2*0.12;
    }

    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

}





