void drawRoad();
void drawRoad2(float , float , float );
void drawTianAnMen();
void drawFlag();
void drawTree();
void drawParterre();
void drawBillboard(float, float, GLuint);
void drawSun();

///�����ƶ���Դ��λ�ú���ɫ�仯
void changeLight()
{
    light2_position[0] = sunRadius * cos(timer);
    light2_position[1] = sunRadius * sin(timer);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    //ǰpi/2���Ӱ����� rgb��   ��pi/2����������  rgb��

    float rr;
    float gg;
    float bb;
    float change_light[4] = {rr,gg,bb,1.0f};
    if(timer <= pi)
    {
        //sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0
        rr = sunshine_mat[0] - cos(timer);
        gg = sunshine_mat[1] - cos(timer);
        bb = sunshine_mat[2] - cos(timer);
        change_light[0] = rr;
        change_light[1] = gg;
        change_light[2] = bb;
    }
    glLightfv(GL_LIGHT2, GL_DIFFUSE, change_light);
}


/******��ʾ����******/
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ///�ƶ��ı��Դ
    changeLight();

    //��պ���ͼ  ����λ��
    createSkyBox();

    /** �������� */
    if(snowEnable == 1)
        drawParticle();

    ///����С��
    drawPeople();

    /**�찲��**/
    drawTianAnMen();

    /**������**/
    drawRoad();

    ///������������·
    drawRoad2(-40 - 30,0,37-30);
    drawRoad2(30 + 20,0 ,37-30);

    ///������ǰ����·
    glPushMatrix();
    glTranslatef(0,0,groundSize+60);
    drawRoad();
    drawTree();
    glPopMatrix();

    /**���**/
    drawFlag();

    /**����Ӣ�ۼ��**/
    glPushMatrix();
    glTranslatef(0 ,0 ,-5);
    drawHero();
    glPopMatrix();

    /**ë��ϯ������**/
    glPushMatrix();
    glTranslatef(0 ,0 ,15);
    drawRemember();
    glPopMatrix();

    ///�����
    glPushMatrix();
    glTranslatef(20+15+15 ,0 ,-90);
    drawMuseum();
    glPopMatrix();

    ///��������
    glPushMatrix();
    glTranslatef(-15 ,0 ,-90);
    drawHall();
    glPopMatrix();

    ///������
    drawZhengYangMen();

    ///��
    drawTree();

    ///��̳
    drawParterre();

    ///��ʾ��
    drawBillboard(10, 235, texHJS);
    drawBillboard(2, 230, texDYC);
    drawBillboard(-6, 225, texQSP);
    drawBillboard(-14, 220, texXHC);

    /**̫��**/
    drawSun();

    glutSwapBuffers();
}


/*****************************************������**************************************/
void drawRoad()
{
    //�ϰ���
    glPushMatrix();
    glTranslatef(0,0.1,0);

    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(-groundSize, 0, 37-85);
    glVertex3f(-groundSize, 0, 37-90);
    glVertex3f(groundSize, 0, 37-90);
    glVertex3f(groundSize, 0, 37-85);
    glEnd();
    //��·
    glColor3f(gray);
    glBegin(GL_QUADS);
    glVertex3f(-groundSize, 0, 37-35);
    glVertex3f(-groundSize, 0, 37-85);
    glVertex3f(groundSize, 0, 37-85);
    glVertex3f(groundSize, 0, 37-35);
    glEnd();
    //�°���
    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(-groundSize, 0, 37-30);
    glVertex3f(-groundSize, 0, 37-35);
    glVertex3f(groundSize, 0, 37-35);
    glVertex3f(groundSize, 0, 37-30);
    glEnd();

    glColor3f(White);
    for(int x = -groundSize; x <= groundSize-12; x += 24)
    {
        glBegin(GL_QUADS);
        glVertex3f(x, 0.1, 37-58);
        glVertex3f(x, 0.1, 37-62);
        glVertex3f(x+12, 0.1, 37-62);
        glVertex3f(x+12, 0.1, 37-58);
        glEnd();
    }

    glPopMatrix();
}

/***********************************������·***************************************/
//��������·���Ͻǵ����꣡����ע�ⲻ�����½���
void drawRoad2(float rx, float ry, float rz)
{
    float chang = groundSize;
    float kuan = 20;
    float baiKuan = 1;
    float zhongKuan = 3;
    float zhongChang = 9;
    glPushMatrix();
    glTranslatef(0,0.1,0);

    //�����
    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(rx+baiKuan, 0, rz+chang);
    glVertex3f(rx+baiKuan, 0, rz);
    glVertex3f(rx, 0, rz);
    glVertex3f(rx, 0, rz+chang);
    glEnd();

    //��·
    glColor3f(gray);
    glBegin(GL_QUADS);
    glVertex3f(rx+kuan-baiKuan, 0, rz+chang);
    glVertex3f(rx+kuan-baiKuan, 0, rz);
    glVertex3f(rx+baiKuan, 0, rz);
    glVertex3f(rx+baiKuan, 0, rz+chang);
    glEnd();

    //�Ұ���
    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(rx+kuan, 0, rz+chang);
    glVertex3f(rx+kuan, 0, rz);
    glVertex3f(rx+kuan-baiKuan, 0, rz);
    glVertex3f(rx+kuan-baiKuan, 0, rz+chang);
    glEnd();

    //������
    float bias = kuan/2-zhongKuan;
    glColor3f(White);
    for(int k = rz; k <= chang; k += 15)
    {
        glBegin(GL_QUADS);
        glVertex3f(rx+bias+baiKuan, 0.1, k+zhongChang);
        glVertex3f(rx+bias+baiKuan, 0.1, k);
        glVertex3f(rx+bias+zhongKuan+baiKuan, 0.1, k);
        glVertex3f(rx+bias+zhongKuan+baiKuan, 0.1, k+zhongChang);
        glEnd();
    }

    glPopMatrix();
}


/*****************************************����****************************************/
void drawFlag()
{
    glPushMatrix();
    glTranslatef(0,0.1,0);

    ///�ݵ�
    //-11 37 11 15
    float grassSize = 30;
    float grassx = -15;
    float grassz = 50;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texGrass);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(grassx+grassSize, 0, grassz);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(grassx+grassSize, 0, grassz-grassSize);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(grassx, 0, grassz-grassSize);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(grassx, 0, grassz);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    ///����
    float jizuoSize = 10;
    float bias = 10;
    float jiGao = 3;
    glColor3f(LightGrey);
    constract(grassx+bias, 0, grassz-bias, jizuoSize,jiGao,-jizuoSize);
    build();    //����

    float xiaoL = 4;
    float xiaoW = 2;
    float xiaoH = 1.3;
    float xiaoBias = jizuoSize/2-xiaoL/2;
    constract(grassx+bias+xiaoBias, 0, grassz-bias+xiaoW, xiaoL, xiaoH, -xiaoW);
    build();    //�����С��
    constract(grassx+bias+xiaoBias, 0, grassz-bias+xiaoW-jizuoSize-xiaoW, xiaoL, xiaoH, -xiaoW);
    build();    //�����С��
    constract(grassx+bias-xiaoW, 0, grassz-bias-xiaoBias, xiaoW, xiaoH, -xiaoL);
    build();    //�����С��
    constract(grassx+bias-xiaoW+jizuoSize+xiaoW, 0, grassz-bias-xiaoBias, xiaoW, xiaoH, -xiaoL);
    build();    //�����С��

    ///Χ��
    float zhuziGao = 3;
    float zhuziSize = 1;
    float jizuoChang = 8;
    float jizuoGao = 1;
    float zhalanGao = 1;
    float zhalanSize = 0.5;
    glColor3f(White);
    //������
    constract(grassx+grassSize-zhuziSize,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();    //���½�
    //������
    constract(grassx+grassSize-jizuoChang,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();    //���½�
    //դ��
    for(int i = 1; i < jizuoChang/zhalanSize-3; i+=2){
        constract(grassx+grassSize-jizuoChang+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }  //���½�

    //���½�
    constract(grassx,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }

    //���Ͻ�
    glPushMatrix();
    glTranslatef(0, 0, -grassSize-zhuziSize);
    constract(grassx+grassSize-zhuziSize,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();    //���½�
    constract(grassx,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }
    glPopMatrix();

    //���Ͻ�
    glPushMatrix();
    glTranslatef(0, 0, -grassSize-zhuziSize);
    constract(grassx,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx+grassSize-jizuoChang,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();
    for(int i = 1; i < jizuoChang/zhalanSize-3; i+=2){
        constract(grassx+grassSize-jizuoChang+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }
    glPopMatrix();


    //��ߵ����½�
    constract(grassx-zhuziSize,0,grassz,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx-zhuziSize,0,grassz,zhuziSize,jizuoGao,-jizuoChang);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx-zhuziSize+zhalanSize/2,jizuoGao,grassz-i*zhalanSize,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }

    //�ϱߵ����Ͻ�
    constract(grassx-zhuziSize,0,grassz-grassSize+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx-zhuziSize,0,grassz-grassSize+zhuziSize+jizuoChang,zhuziSize,jizuoGao,-jizuoChang);
    build();
    for(int i = 1; i <= jizuoChang/zhalanSize+3; i+=2){
        constract(grassx-zhuziSize+zhalanSize/2,jizuoGao,grassz-grassSize+zhuziSize+jizuoChang-i*zhalanSize,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }

    //�±ߵ����½�
    glPushMatrix();
    glTranslatef(grassSize+zhuziSize, 0, 0);
    constract(grassx-zhuziSize,0,grassz,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx-zhuziSize,0,grassz,zhuziSize,jizuoGao,-jizuoChang);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx-zhuziSize+zhalanSize/2,jizuoGao,grassz-i*zhalanSize,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }
    glPopMatrix();

    //�ϱߵ����Ͻ�
    glPushMatrix();
    glTranslatef(grassSize+zhuziSize, 0, 0);
    constract(grassx-zhuziSize,0,grassz-grassSize+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx-zhuziSize,0,grassz-grassSize+zhuziSize+jizuoChang,zhuziSize,jizuoGao,-jizuoChang);
    build();
    for(int i = 1; i <= jizuoChang/zhalanSize+3; i+=2){
        constract(grassx-zhuziSize+zhalanSize/2,jizuoGao,grassz-grassSize+zhuziSize+jizuoChang-i*zhalanSize,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }
    glPopMatrix();

    ///���
    float flagz = grassz-grassSize/2;
    glPushMatrix();
    glColor3f(gray);
    glTranslated(0, jiGao, flagz);
    glRotated(-90, 1, 0, 0);    //����ʱ���ƶ������Կ�����˶���һ�¡�������
    GLUquadricObj *objCylinder = gluNewQuadric();
    mySolidCylinder(objCylinder, 0.5, 0.5, 30.0, 32, 5);
    glPopMatrix();

    ///����   3:2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texFlag);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(8, 25+jiGao, flagz);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(8, 30+jiGao, flagz);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(0, 30+jiGao, flagz);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 25+jiGao, flagz);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/************************************����**************************************/
void generateTree()
{
    float x=0,y=2.1,z=1,x1=1.7,y1=2.1,z1=1.7;
    //��
    glColor3f(nbrown);
    constract(x,0,z,x1,y1,-z1);
    build();
    constract(x,y+0,z,x1,y1,-z1);
    build();
    constract(x,y+y1,z,x1,y1,-z1);
    build();
    constract(x,y+2*y1,z,x1,y1,-z1);
    build();
    constract(x,y+3*y1,z,x1,y1,-z1);
    build();
    //��һ��
    glColor3f(green);
    constract(x,y+4*y1,z,x1,y1,-z1);
    build();
    //�ڶ���
    constract(x,y+3*y1,z+z1,x1,y1,-z1);
    build();
    constract(x,y+3*y1,z-z1,x1,y1,-z1);
    build();
    constract(x-x1,y+3*y1,z,x1,y1,-z1);
    build();
    constract(x+x1,y+3*y1,z,x1,y1,-z1);
    build();
    //������
    constract(x,y+2*y1,z+z1,x1,y1,-z1);
    build();
    constract(x,y+2*y1,z+2*z1,x1,y1,-z1);
    build();
    constract(x,y+2*y1,z-z1,x1,y1,-z1);
    build();
    constract(x,y+2*y1,z-2*z1,x1,y1,-z1);
    build();
    constract(x-x1,y+2*y1,z,x1,y1,-z1);
    build();
    constract(x-2*x1,y+2*y1,z,x1,y1,-z1);
    build();
    constract(x+x1,y+2*y1,z,x1,y1,-z1);
    build();
    constract(x+2*x1,y+2*y1,z,x1,y1,-z1);
    build();
}
///��·��������������
void drawTree()
{
    //��·�ϰ�������
    for(int i = -groundSize; i < groundSize; i += 40){
        glPushMatrix();
        glTranslatef(i, 0, 37-87.5);
        generateTree();
        glPopMatrix();
    }
    //��·�°�������
    for(int i = -groundSize; i < groundSize; i += 40){
        glPushMatrix();
        glTranslatef(i, 0, 37-32.5);
        generateTree();
        glPopMatrix();
    }
}


/***********************************����̳*******************************************/
void generateParterre(float x, float z) //pa 'ter
{
    float gao = 0.5;  //��
    float chang = 20;   //�ܳ�
    float kuan = 10;    //�ܿ�
    float hengKuan = 1;     //�������Ǹ���
    float shuKuan = 1; //�����Ŀ�
    float shuChang = chang - 2*hengKuan;
    float zuoshang[2] = {x, z};  //���Ͻǵ�����  -25 65
    float zuoxia[2] = {zuoshang[0], zuoshang[1]+chang};

    glPushMatrix();
    glTranslatef(0,0.1,0);

    //�·��Ķ���
    glColor3f(nbrown);
    constract(zuoxia[0], 0, zuoxia[1], kuan, gao, -hengKuan);
    build();

    //���ĳ���
    glColor3f(nbrown);
    constract(zuoxia[0], 0, zuoxia[1]-hengKuan, shuKuan, gao, -shuChang);
    build();

    //�Ϸ��Ķ���
    glColor3f(nbrown);
    constract(zuoshang[0], 0, zuoshang[1]+hengKuan, kuan, gao, -hengKuan);
    build();

    //�Ҳ�ĳ���
    glColor3f(nbrown);
    constract(zuoxia[0]+kuan-shuKuan, 0, zuoxia[1]-hengKuan, shuKuan, gao, -shuChang);
    build();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texGrass);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(zuoshang[0]+kuan-shuKuan, 0, zuoshang[1]+hengKuan+shuChang);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(zuoshang[0]+kuan-shuKuan, 0, zuoshang[1]+hengKuan);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(zuoxia[0]+shuKuan, 0, zuoxia[1]-hengKuan-shuChang);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(zuoxia[0]+shuKuan, 0, zuoxia[1]-hengKuan);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
///��10 �ԳƵ�����-15��15 ���70��һ��
void drawParterre()
{
    generateParterre(-40, 65);
    generateParterre(30, 65);
    generateParterre(-40, 135);
    generateParterre(30, 135);
    generateParterre(-40, 205);
    generateParterre(30, 205);
}

/************************************��ʾ��*************************************/
void drawBillboard(float x, float z, GLuint tex)
{
    float chang = 10;    //���ӵĳ���
    float kuan = 2;     //���ӵĿ��
    float banjing = 0.2;     //���ӵ�Բ�İ뾶
    float gao = 10;     //���ӵĸ�

    //������������������ӵ�Բ������
    float pillar1[2] = {x, z};
    float pillar2[2] = {x+chang+2*banjing, z};

    //������
    glPushMatrix();
    glColor3f(gray);
    glTranslated(pillar1[0], 0, pillar1[1]);
    glRotated(-90, 1, 0, 0);
    GLUquadricObj *objCylinder1 = gluNewQuadric();
    mySolidCylinder(objCylinder1, banjing, banjing, gao, 32, 5);
    glPopMatrix();

    //������
    glPushMatrix();
    glColor3f(gray);
    glTranslated(pillar2[0], 0, pillar2[1]);
    glRotated(-90, 1, 0, 0);
    GLUquadricObj *objCylinder2 = gluNewQuadric();
    mySolidCylinder(objCylinder2, banjing, banjing, gao, 32, 5);
    glPopMatrix();

    //��ʾ��
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(pillar2[0]-banjing, 3, pillar1[1]);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(pillar2[0]-banjing, gao-1, pillar1[1]);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(pillar1[0]+banjing, gao-1, pillar1[1]);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(pillar1[0]+banjing, 3, pillar1[1]);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //С��
    glPushMatrix();
    glTranslated(pillar1[0]-3, 2, pillar1[1]+1);
    generatePeople();
    glPopMatrix();

}


/***************************************����**************************************/
GLUquadricObj* qobj;//����������������
void drawSun()
{
    glPushMatrix();
    glColor3f(gold);

    qobj = gluNewQuadric();//����ռ�

    glEnable(GL_TEXTURE_2D);
    if(timer <= pi) //����
    {
        glTranslatef(sunRadius * cos(timer), sunRadius * sin(timer), 0);
        glBindTexture(GL_TEXTURE_2D, texSun);
    }
    else    //����
    {
        glTranslatef(sunRadius * cos(timer-pi), sunRadius * sin(timer-pi), 0);
        glBindTexture(GL_TEXTURE_2D, texMoon);
    }

    gluQuadricTexture(qobj, GL_TRUE);//������
    gluSphere(qobj, 5.0, 20, 20); //��������qobj

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


