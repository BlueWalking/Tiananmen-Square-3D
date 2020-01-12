/*******************************************天安门****************************************/
///快速画柱子
void drawPillar(float zhux, float zhuy, float zhuz, float radius, float height, GLUquadricObj * objCylinder){
    glPushMatrix();
    glColor3f(ZhuZi);
    glTranslated(zhux, zhuy, zhuz);
    glRotated(-90, 1, 0, 0);
    objCylinder = gluNewQuadric();
    mySolidCylinder(objCylinder, radius, radius, height, 32, 5);
    glPopMatrix();
}
///画窗户 参数：左下角坐标
void drawWindow(float wx, float wy, float wz)
{
    float wlen = 50/7;
    float wh = 6;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texWindow);
    for(int k = 0; k < 7; k++)
    {
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(wx+wlen*k+wlen, wy, wz+0.1);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(wx+wlen*k+wlen, wy+wh, wz+0.1);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(wx+wlen*k, wy+wh, wz+0.1);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(wx+wlen*k, wy, wz+0.1);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}
///画小旗： 参数：旗杆位置
void drawSmallFlag(float flx, float fly, float flz)
{
    //旗杆
    glPushMatrix();
    glColor3f(gray);
    glTranslated(flx, fly, flz);
    glRotated(-90, 1, 0, 0);    //随着时间移动，可以看到旗杆动了一下。。很迷
    GLUquadricObj *objCylinder = gluNewQuadric();
    mySolidCylinder(objCylinder, 0.2, 0.2, 9.0, 32, 5);
    glPopMatrix();

    float length = 4;
    float width = 2.5;
    //小国旗   13 ~ 22   4 - 2.6
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texFlag);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(flx+length, 19.5, 36);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(flx+length, 22, 36);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(flx, 22, 36);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(flx, 19.5, 36);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

///天安门
void drawTianAnMen()
{
    //高30  宽110  宽37
    glPushMatrix();
    glTranslatef(0,0,-100-5);
    ///底
    constract(-55, 0, 37, 110, 13, -37);
    //constract(-66, 0, 74, 132, 26, -74);
    glColor3f(red);
    build();

    ///主层
    constract(-25, 13, 29, 50, 6, -25);
    //constract(-36, 26, 57, 72, 20, -40);
    glColor3f(ZhuCeng);
    build();

    ///屋檐-棱台
    consFourPrism(-30,19,36, 30,19,2, -20,21,29, 20,21,4);
    glColor3f(menba);
    buildFourPrism();

    ///圆柱子
    GLUquadricObj *objCylinder11;
    GLUquadricObj *objCylinder22;
    GLUquadricObj *objCylinder33;
    GLUquadricObj *objCylinder44;
    GLUquadricObj *objCylinder55;
    GLUquadricObj *objCylinder66;
    GLUquadricObj *objCylinder77;
    GLUquadricObj *objCylinder88;
    GLUquadricObj *objCylinder99;
    GLUquadricObj *objCylinderAA;
    drawPillar(-27,13,32,0.8,6,objCylinder11);
    drawPillar(-21.5,13,32,0.8,6,objCylinder22);
    drawPillar(-16,13,32,0.8,6,objCylinder33);
    drawPillar(-10.5,13,32,0.8,6,objCylinder44);
    drawPillar(-5,13,32,0.8,6,objCylinder55);
    drawPillar(5,13,32,0.8,6,objCylinder66);
    drawPillar(10.5,13,32,0.8,6,objCylinder77);
    drawPillar(16,13,32,0.8,6,objCylinder88);
    drawPillar(21.5,13,32,0.8,6,objCylinder99);
    drawPillar(27,13,32,0.8,6,objCylinderAA);

    ///房顶1
    glColor3f(GuoHuiCeng);
    constract(-20,21,29, 40,4,-25);
    build();

    ///房顶2-三棱柱  -22 22    31 2
    consTriPrism(-22, 25+0.1, 31, -22, 30+0.1, 16.5, 44);
    //consTriPrism(-40, 46, 37, -40, 64, 37, 80);
    glColor3f(menba);
    buileTriPrism();

    ///画窗户
    drawWindow(-25,13,29);

    //setMaterial();
    ///画国徽
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texGuoHui);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1, 22, 29+0.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1, 24, 29+0.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1, 24, 29+0.1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1, 22, 29+0.1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    ///画小红旗
    drawSmallFlag(-54,13,36);
    drawSmallFlag(-47,13,36);
    drawSmallFlag(-40,13,36);   //左边三个旗子
    drawSmallFlag(54,13,36);
    drawSmallFlag(47,13,36);
    drawSmallFlag(40,13,36);   //右边三个旗子

    ///贴mzx
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texMao);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(3.2, 5.9, 37.1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(3.2, 13, 37.1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-2.8, 13, 37.1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-2.8, 5.9, 37.1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    ///贴字-左边
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texZuoZi);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-10, 5.7, 37.1); //右下
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-10, 11, 37.1);  //右上
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-50, 11, 37.1); //左上
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-50, 5.7, 37.1);    //左下
    glEnd();
    glDisable(GL_TEXTURE_2D);

    ///贴字-右边
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texYouZi);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(50, 5.7, 37.1); //右下
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(50, 11, 37.1);  //右上
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(10, 11, 37.1); //左上
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(10, 5.7, 37.1);    //左下
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

/*****************************人民英雄纪念碑*********************/
void drawHero()
{
    //底
    constract(-7, 0, 128, 14, 2, -14);
    glColor3f(gray);
    build();

    //碑
    constract(-3, 2, 118, 6, 25, -2);
    glColor3f(BrulyWood);
    build();
}

/******************************毛主席纪念堂*************************/
void drawRemember()
{
    //地面2
    constract(-20, 0, 186, 40, 1, -40);
    glColor3f(gray);
    build();

    //底座    底座是被中间块包着的
    constract(-16, 1, 168, 32, 12, -22);
    glColor3f(Wheat);
    build();

    //中
    constract(-18, 8, 170, 36, 2, -26);
    glColor3f(Tan);
    build();
}

/**************************人民大会堂*******************************/
void drawHall() //左边的
{
    glColor3f(Bisque);
    glColor3f(Wheat);
    ///右侧柱子
    constract(-115,0,175, 35,24,-15);
    build();

    ///左侧柱子
    constract(-115,0,290, 35,24,-15);
    build();

    glColor3f(SandyBrown);
    ///中心外
    constract(-115,0,275, 27,24,-100);
    build();

    ///中心内
    constract(-115,0,260, 30,28,-70);
    build();
}


/*******************************博物馆************************************/
void drawMuseum()   //右边的
{
    glColor3f(Bisque);
    glColor3f(DarkGray);
    ///正面柱子左
    constract(53,0,217, 8,22,-50);
    build();

    ///正面柱子右
    constract(53,0,297, 8,22,-50);
    build();

    ///左面柱子
    constract(61,0,175, 114,22,-8);
    build();

    ///右面柱子
    constract(61,0,297, 114,22,-8);
    build();

    ///后面柱子
    constract(175,0,297, 8,22,-130);
    build();

    ///中心
    glColor3f(SandyBrown);
    constract(68,0,282, 100,28,-100);
    build();
}

/******************************正阳门***************************/
void drawZhengYangMen()
{
    glColor3f(red);
    //底
	glBegin(GL_POLYGON);
	constract(-33, 0, 317, 66, 13, -37);
	glColor3f(red);
	build();

    //中
    glBegin(GL_POLYGON);
	constract(-18, 13, 308.5, 36, 10, -20);
	glColor3f(orangeRed);
	build();

	//房顶
	consTriPrism(-20, 23+0.1, 313.5, -20, 32+0.1, 298.5, 40);
	glColor3f(menba);
	buileTriPrism();
}

