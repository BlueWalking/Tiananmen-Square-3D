void drawRoad();
void drawRoad2(float , float , float );
void drawTianAnMen();
void drawFlag();
void drawTree();
void drawParterre();
void drawBillboard(float, float, GLuint);
void drawSun();

///设置移动光源的位置和颜色变化
void changeLight()
{
    light2_position[0] = sunRadius * cos(timer);
    light2_position[1] = sunRadius * sin(timer);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    //前pi/2，从暗到亮 rgb加   后pi/2，从亮到暗  rgb减

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


/******显示函数******/
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ///移动改变光源
    changeLight();

    //天空盒贴图  中心位置
    createSkyBox();

    /** 绘制粒子 */
    if(snowEnable == 1)
        drawParticle();

    ///绘制小人
    drawPeople();

    /**天安门**/
    drawTianAnMen();

    /**长安街**/
    drawRoad();

    ///画两条竖的马路
    drawRoad2(-40 - 30,0,37-30);
    drawRoad2(30 + 20,0 ,37-30);

    ///正阳门前的马路
    glPushMatrix();
    glTranslatef(0,0,groundSize+60);
    drawRoad();
    drawTree();
    glPopMatrix();

    /**旗杆**/
    drawFlag();

    /**人民英雄纪念碑**/
    glPushMatrix();
    glTranslatef(0 ,0 ,-5);
    drawHero();
    glPopMatrix();

    /**毛主席纪念堂**/
    glPushMatrix();
    glTranslatef(0 ,0 ,15);
    drawRemember();
    glPopMatrix();

    ///博物馆
    glPushMatrix();
    glTranslatef(20+15+15 ,0 ,-90);
    drawMuseum();
    glPopMatrix();

    ///人民大会堂
    glPushMatrix();
    glTranslatef(-15 ,0 ,-90);
    drawHall();
    glPopMatrix();

    ///正阳门
    drawZhengYangMen();

    ///树
    drawTree();

    ///花坛
    drawParterre();

    ///告示栏
    drawBillboard(10, 235, texHJS);
    drawBillboard(2, 230, texDYC);
    drawBillboard(-6, 225, texQSP);
    drawBillboard(-14, 220, texXHC);

    /**太阳**/
    drawSun();

    glutSwapBuffers();
}


/*****************************************长安街**************************************/
void drawRoad()
{
    //上白条
    glPushMatrix();
    glTranslatef(0,0.1,0);

    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(-groundSize, 0, 37-85);
    glVertex3f(-groundSize, 0, 37-90);
    glVertex3f(groundSize, 0, 37-90);
    glVertex3f(groundSize, 0, 37-85);
    glEnd();
    //公路
    glColor3f(gray);
    glBegin(GL_QUADS);
    glVertex3f(-groundSize, 0, 37-35);
    glVertex3f(-groundSize, 0, 37-85);
    glVertex3f(groundSize, 0, 37-85);
    glVertex3f(groundSize, 0, 37-35);
    glEnd();
    //下白条
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

/***********************************两条马路***************************************/
//参数：马路左上角的坐标！！！注意不是左下角了
void drawRoad2(float rx, float ry, float rz)
{
    float chang = groundSize;
    float kuan = 20;
    float baiKuan = 1;
    float zhongKuan = 3;
    float zhongChang = 9;
    glPushMatrix();
    glTranslatef(0,0.1,0);

    //左白条
    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(rx+baiKuan, 0, rz+chang);
    glVertex3f(rx+baiKuan, 0, rz);
    glVertex3f(rx, 0, rz);
    glVertex3f(rx, 0, rz+chang);
    glEnd();

    //公路
    glColor3f(gray);
    glBegin(GL_QUADS);
    glVertex3f(rx+kuan-baiKuan, 0, rz+chang);
    glVertex3f(rx+kuan-baiKuan, 0, rz);
    glVertex3f(rx+baiKuan, 0, rz);
    glVertex3f(rx+baiKuan, 0, rz+chang);
    glEnd();

    //右白条
    glColor3f(White);
    glBegin(GL_QUADS);
    glVertex3f(rx+kuan, 0, rz+chang);
    glVertex3f(rx+kuan, 0, rz);
    glVertex3f(rx+kuan-baiKuan, 0, rz);
    glVertex3f(rx+kuan-baiKuan, 0, rz+chang);
    glEnd();

    //中心条
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


/*****************************************国旗****************************************/
void drawFlag()
{
    glPushMatrix();
    glTranslatef(0,0.1,0);

    ///草地
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

    ///基座
    float jizuoSize = 10;
    float bias = 10;
    float jiGao = 3;
    glColor3f(LightGrey);
    constract(grassx+bias, 0, grassz-bias, jizuoSize,jiGao,-jizuoSize);
    build();    //主块

    float xiaoL = 4;
    float xiaoW = 2;
    float xiaoH = 1.3;
    float xiaoBias = jizuoSize/2-xiaoL/2;
    constract(grassx+bias+xiaoBias, 0, grassz-bias+xiaoW, xiaoL, xiaoH, -xiaoW);
    build();    //下面的小块
    constract(grassx+bias+xiaoBias, 0, grassz-bias+xiaoW-jizuoSize-xiaoW, xiaoL, xiaoH, -xiaoW);
    build();    //上面的小块
    constract(grassx+bias-xiaoW, 0, grassz-bias-xiaoBias, xiaoW, xiaoH, -xiaoL);
    build();    //左面的小块
    constract(grassx+bias-xiaoW+jizuoSize+xiaoW, 0, grassz-bias-xiaoBias, xiaoW, xiaoH, -xiaoL);
    build();    //右面的小块

    ///围栏
    float zhuziGao = 3;
    float zhuziSize = 1;
    float jizuoChang = 8;
    float jizuoGao = 1;
    float zhalanGao = 1;
    float zhalanSize = 0.5;
    glColor3f(White);
    //栏柱子
    constract(grassx+grassSize-zhuziSize,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();    //右下角
    //栏基座
    constract(grassx+grassSize-jizuoChang,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();    //右下角
    //栅栏
    for(int i = 1; i < jizuoChang/zhalanSize-3; i+=2){
        constract(grassx+grassSize-jizuoChang+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }  //右下角

    //左下角
    constract(grassx,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }

    //左上角
    glPushMatrix();
    glTranslatef(0, 0, -grassSize-zhuziSize);
    constract(grassx+grassSize-zhuziSize,0,grassz+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();    //右下角
    constract(grassx,0,grassz+zhuziSize,jizuoChang,jizuoGao,-zhuziSize);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx+i*zhalanSize,jizuoGao,grassz+zhuziSize-zhalanSize/2,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }
    glPopMatrix();

    //右上角
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


    //左边的左下角
    constract(grassx-zhuziSize,0,grassz,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx-zhuziSize,0,grassz,zhuziSize,jizuoGao,-jizuoChang);
    build();
    for(int i = 3; i < jizuoChang/zhalanSize; i+=2){
        constract(grassx-zhuziSize+zhalanSize/2,jizuoGao,grassz-i*zhalanSize,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }

    //上边的左上角
    constract(grassx-zhuziSize,0,grassz-grassSize+zhuziSize,zhuziSize,zhuziGao,-zhuziSize);
    build();
    constract(grassx-zhuziSize,0,grassz-grassSize+zhuziSize+jizuoChang,zhuziSize,jizuoGao,-jizuoChang);
    build();
    for(int i = 1; i <= jizuoChang/zhalanSize+3; i+=2){
        constract(grassx-zhuziSize+zhalanSize/2,jizuoGao,grassz-grassSize+zhuziSize+jizuoChang-i*zhalanSize,zhalanSize,zhalanGao,-zhalanSize);
        build();
    }

    //下边的右下角
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

    //上边的右上角
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

    ///旗杆
    float flagz = grassz-grassSize/2;
    glPushMatrix();
    glColor3f(gray);
    glTranslated(0, jiGao, flagz);
    glRotated(-90, 1, 0, 0);    //随着时间移动，可以看到旗杆动了一下。。很迷
    GLUquadricObj *objCylinder = gluNewQuadric();
    mySolidCylinder(objCylinder, 0.5, 0.5, 30.0, 32, 5);
    glPopMatrix();

    ///国旗   3:2
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

/************************************画树**************************************/
void generateTree()
{
    float x=0,y=2.1,z=1,x1=1.7,y1=2.1,z1=1.7;
    //根
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
    //第一层
    glColor3f(green);
    constract(x,y+4*y1,z,x1,y1,-z1);
    build();
    //第二层
    constract(x,y+3*y1,z+z1,x1,y1,-z1);
    build();
    constract(x,y+3*y1,z-z1,x1,y1,-z1);
    build();
    constract(x-x1,y+3*y1,z,x1,y1,-z1);
    build();
    constract(x+x1,y+3*y1,z,x1,y1,-z1);
    build();
    //第三层
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
///在路两边生成两排树
void drawTree()
{
    //马路上白条的树
    for(int i = -groundSize; i < groundSize; i += 40){
        glPushMatrix();
        glTranslatef(i, 0, 37-87.5);
        generateTree();
        glPopMatrix();
    }
    //马路下白条的树
    for(int i = -groundSize; i < groundSize; i += 40){
        glPushMatrix();
        glTranslatef(i, 0, 37-32.5);
        generateTree();
        glPopMatrix();
    }
}


/***********************************画花坛*******************************************/
void generateParterre(float x, float z) //pa 'ter
{
    float gao = 0.5;  //高
    float chang = 20;   //总长
    float kuan = 10;    //总宽
    float hengKuan = 1;     //横条的那个宽
    float shuKuan = 1; //竖条的宽
    float shuChang = chang - 2*hengKuan;
    float zuoshang[2] = {x, z};  //左上角点坐标  -25 65
    float zuoxia[2] = {zuoshang[0], zuoshang[1]+chang};

    glPushMatrix();
    glTranslatef(0,0.1,0);

    //下方的短条
    glColor3f(nbrown);
    constract(zuoxia[0], 0, zuoxia[1], kuan, gao, -hengKuan);
    build();

    //左侧的长条
    glColor3f(nbrown);
    constract(zuoxia[0], 0, zuoxia[1]-hengKuan, shuKuan, gao, -shuChang);
    build();

    //上方的短条
    glColor3f(nbrown);
    constract(zuoshang[0], 0, zuoshang[1]+hengKuan, kuan, gao, -hengKuan);
    build();

    //右侧的长条
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
///宽10 对称点坐标-15和15 间隔70画一个
void drawParterre()
{
    generateParterre(-40, 65);
    generateParterre(30, 65);
    generateParterre(-40, 135);
    generateParterre(30, 135);
    generateParterre(-40, 205);
    generateParterre(30, 205);
}

/************************************告示牌*************************************/
void drawBillboard(float x, float z, GLuint tex)
{
    float chang = 10;    //板子的长度
    float kuan = 2;     //板子的宽度
    float banjing = 0.2;     //柱子的圆心半径
    float gao = 10;     //柱子的高

    //参数的坐标是左边柱子的圆心坐标
    float pillar1[2] = {x, z};
    float pillar2[2] = {x+chang+2*banjing, z};

    //左柱子
    glPushMatrix();
    glColor3f(gray);
    glTranslated(pillar1[0], 0, pillar1[1]);
    glRotated(-90, 1, 0, 0);
    GLUquadricObj *objCylinder1 = gluNewQuadric();
    mySolidCylinder(objCylinder1, banjing, banjing, gao, 32, 5);
    glPopMatrix();

    //右柱子
    glPushMatrix();
    glColor3f(gray);
    glTranslated(pillar2[0], 0, pillar2[1]);
    glRotated(-90, 1, 0, 0);
    GLUquadricObj *objCylinder2 = gluNewQuadric();
    mySolidCylinder(objCylinder2, banjing, banjing, gao, 32, 5);
    glPopMatrix();

    //告示栏
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

    //小人
    glPushMatrix();
    glTranslated(pillar1[0]-3, 2, pillar1[1]+1);
    generatePeople();
    glPopMatrix();

}


/***************************************日月**************************************/
GLUquadricObj* qobj;//二次曲面声明类型
void drawSun()
{
    glPushMatrix();
    glColor3f(gold);

    qobj = gluNewQuadric();//申请空间

    glEnable(GL_TEXTURE_2D);
    if(timer <= pi) //白天
    {
        glTranslatef(sunRadius * cos(timer), sunRadius * sin(timer), 0);
        glBindTexture(GL_TEXTURE_2D, texSun);
    }
    else    //晚上
    {
        glTranslatef(sunRadius * cos(timer-pi), sunRadius * sin(timer-pi), 0);
        glBindTexture(GL_TEXTURE_2D, texMoon);
    }

    gluQuadricTexture(qobj, GL_TRUE);//纹理函数
    gluSphere(qobj, 5.0, 20, 20); //二次曲面qobj

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}


