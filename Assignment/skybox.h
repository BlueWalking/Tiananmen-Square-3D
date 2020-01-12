    float width = groundSize*2 *2;
    float height = groundSize*2 *2 / 2;
    float length = groundSize*2 *2;

    float xx = 0 - width/2;
    float yy = -0.1 ;
    float zz = 0 - length/2;

GLUquadricObj* skySphere;

//天空盒
void  createSkyBox()
{
    /** 计算天空盒左下角的位置 **/
    float x = xx;
    float y = yy;
    float z = zz;    //-250, 0, -250

    glEnable(GL_TEXTURE_2D);

    /** 开始绘制 */
    glPushMatrix();

    float groundSiz = groundSize*10;
    float num = groundSiz/30;
    glBindTexture(GL_TEXTURE_2D, texBrick);
    glBegin(GL_QUADS);
    glTexCoord2f(num, 0.0f);
    glVertex3f(groundSiz, 0, groundSiz);
    glTexCoord2f(num, 40.0f);
    glVertex3f(groundSiz, 0, -groundSiz);
    glTexCoord2f(0.0f, num);
    glVertex3f(-groundSiz, 0, -groundSiz);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-groundSiz, 0, groundSiz);
    glEnd();

    glPopMatrix();                 /** 绘制结束 */

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    skySphere = gluNewQuadric();//申请空间

    if(skyEnable == 1)
    {
        int texBeiJing;
        if(timer <= pi / 11*1)
            texBeiJing = texNight4;
        else if(timer <= pi / 11*2)
            texBeiJing = texNight3;
        else if(timer <= pi / 11*3)
            texBeiJing = texNight2;
        else if(timer <= pi / 11*4)
            texBeiJing = texNight1;
        else if(timer <= pi / 11*8)
            texBeiJing = texSky;
        else if(timer <= pi / 11*9)
            texBeiJing = texNight1;
        else if(timer <= pi / 11*10)
            texBeiJing = texNight2;
        else if(timer <= pi / 11*11)
            texBeiJing = texNight3;

        else if(timer <= pi + pi / 22*1)
            texBeiJing = texNight4;
        else if(timer <= pi + pi / 22*2)
            texBeiJing = texNight5;
        else if(timer <= pi + pi / 11*2)
            texBeiJing = texNight6;
        else if(timer <= pi + pi / 11*3)
            texBeiJing = texNight7;
        else if(timer <= pi + pi / 11*4)
            texBeiJing = texNight8;
        else if(timer <= pi + pi / 11*5)
            texBeiJing = texNight9;
        else if(timer <= pi + pi / 11*6)
            texBeiJing = texNight9;
        else if(timer <= pi + pi / 11*7)
            texBeiJing = texNight9;            ///加星星
        else if(timer <= pi + pi / 11*8)
            texBeiJing = texNight8;
        else if(timer <= pi + pi / 11*9)
            texBeiJing = texNight7;
        else if(timer <= pi + pi / 11*10)
            texBeiJing = texNight6;
        else if(timer <= pi + pi / 11*11)
            texBeiJing = texNight5;
        else if(timer <= pi + pi / 7*4)
            texBeiJing = texNight4;

        glBindTexture(GL_TEXTURE_2D, texBeiJing);
        gluQuadricTexture(skySphere, GL_TRUE);//纹理函数
    }

    //移动天空球的位置，使它跟着视角移动
    glTranslatef(xx+groundSize*2,yy,zz+groundSize*2);
    gluSphere(skySphere, groundSize*2, 80, 80); //二次曲面qobj

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

}
