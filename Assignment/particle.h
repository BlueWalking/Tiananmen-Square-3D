/****************************���ӵĴ���************************************/
void drawPeople();

///��ѩ����ֵ�ĺ���
void setSnow(int i)
{
    snow[i].r = r;
    snow[i].g = g;
    snow[i].b = b;

    snow[i].x = sx;
    snow[i].y = sy;
    snow[i].z = sz;

    snow[i].vx = vx;
    snow[i].vy = vy;
    snow[i].vz = vz;

    snow[i].ax = ax;
    snow[i].ay = ay;
    snow[i].az = az;

    snow[i].lifetime = lifetime;

    snow[i].dec = dec;

    snow[i].size = size;
}

int getSnow(int index,GLint &r,GLint &g,GLint &b, //���ӵ���ɫ
            GLfloat &x,GLfloat &y,GLfloat &z,     //λ��
            GLfloat &vx,GLfloat &vy,GLfloat &vz,  //�ٶ�
            GLfloat &ax,GLfloat &ay,GLfloat &az,  //���ٶ�
            GLfloat &size,                        //��С
            GLfloat &lifetime,                    //����ʱ��
            GLfloat &dec                          //��ʧ�ٶ�
           )
{
    if (index>=0 && index<snowNum)
    {
        r=snow[index].r;
        g=snow[index].g;
        b=snow[index].b;
        sx=snow[index].x;
        sy=snow[index].y;
        sz=snow[index].z;
        vx=snow[index].vx;
        vy=snow[index].vy;
        vz=snow[index].vz;
        ax=snow[index].ax;
        ay=snow[index].ay;
        az=snow[index].az;
        lifetime=snow[index].lifetime;
        size=snow[index].size;
        dec=snow[index].dec;
        return true;
    }
    return false;
}

/** ��ʼ��ѩ������ */
void initSnow()
{
    for (int i=0; i < snowNum; i++)
    {
        ///��ʼ����ɫ����ɫ��
        r = 255;
        g = 255;
        b = 255;

        ///��ʼ������
        sx = pow(-1, (rand()%2))*(rand() % groundSize);
        sy = 200;
        sz = pow(-1, (rand()%2))*(rand() % groundSize);

        ///��ʼ���ٶ�
        vx = pow(-1, (rand()%2)) * 0.01 * (rand()%100); //���Ҿ������ƶ�
        vy = 0.004 * (rand()%2800); //0.002~5.6
        vz = pow(-1, (rand()%2)) * 0.01 * (rand()%100);

        ///��ʼ�����ٶ�
        ax = 0;
        ay = 0.05f;
        az = 0;

        ///��ʼ����������
        lifetime = 100;

        ///��ʧ�ٶ�
        dec = 0.09 * (rand()%50);   //0.05~2.5

        ///��ʼ����С
        size = 0.3f;   //0.03

        setSnow(i);
    }
}

/** �������� */
void updateSnow(int i)
{
    /** ����λ�� */
    sx += (vx * 5);
    sz -= (vz * 5);
    sy -= vy;

    /** �����ٶ� */
    vy += ay;

    /** ��������ʱ�� */
    lifetime -= dec;

    /** ���������ʧ���������� */
    if (sy <= 0 || lifetime <= 0)
    {
        ///��ʼ������
        sx = pow(-1, (rand()%2))*(rand() % 100);
        sy = 100;
        //sz = pow(-1, (rand()%2))*(rand() % groundSize);
        sz = (rand() % groundSize);

        ///��ʼ���ٶ�
        vx = pow(-1, (rand()%2)) * 0.01 * (rand()%100); //���Ҿ������ƶ�
        vy = 0.002 * (rand()%2800);
        vz = 0.01 * (rand()%100);   //Ŀǰ����ֻ��ǰ

        ///��ʧ�ٶ�
        dec = 0.1 * (rand()%50);    //0.1~5

        ///��ʼ����������
        lifetime = 100;
    }
    ///���²���
    setSnow(i);
}


///** �������� */
void drawParticle()
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);    /**< ���û�����ӻ�ð�͸��Ч�� */
    glEnable(GL_BLEND);

    /** ������ */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texSnow);

    for(int i = 0; i < snowNum; ++i)
    {
        /** ������ӵ��������� */
        getSnow(i,r,g,b,sx,sy,sz,vx,vy,vz,ax,ay,az,size,lifetime,dec);
        glPushMatrix();
        glColor4ub(r,g,b,255);
        glNormal3f(0.0f,0.0f,1.0f);   //���巨�߷���

        glTranslatef(sx,sy,sz);    //�ƶ����µ�λ��
        glTranslatef(0, snowHeight, 0); //�ƶ����ʱ��ͬʱ�ƶ�ѩ��λ��

        /** �������� */
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(cx-size,cy-size,cz);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(cx-size,cy+size,cz);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(cx+size,cy+size,cz);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(cx+size,cy-size,cz);
        glEnd();

        /** ������������ */
        updateSnow(i);

        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

}
