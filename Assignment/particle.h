/****************************粒子的处理************************************/
void drawPeople();

///给雪花赋值的函数
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

int getSnow(int index,GLint &r,GLint &g,GLint &b, //粒子的颜色
            GLfloat &x,GLfloat &y,GLfloat &z,     //位置
            GLfloat &vx,GLfloat &vy,GLfloat &vz,  //速度
            GLfloat &ax,GLfloat &ay,GLfloat &az,  //加速度
            GLfloat &size,                        //大小
            GLfloat &lifetime,                    //生命时间
            GLfloat &dec                          //消失速度
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

/** 初始化雪花粒子 */
void initSnow()
{
    for (int i=0; i < snowNum; i++)
    {
        ///初始化颜色（白色）
        r = 255;
        g = 255;
        b = 255;

        ///初始化坐标
        sx = pow(-1, (rand()%2))*(rand() % groundSize);
        sy = 200;
        sz = pow(-1, (rand()%2))*(rand() % groundSize);

        ///初始化速度
        vx = pow(-1, (rand()%2)) * 0.01 * (rand()%100); //左右均可以移动
        vy = 0.004 * (rand()%2800); //0.002~5.6
        vz = pow(-1, (rand()%2)) * 0.01 * (rand()%100);

        ///初始化加速度
        ax = 0;
        ay = 0.05f;
        az = 0;

        ///初始化生命周期
        lifetime = 100;

        ///消失速度
        dec = 0.09 * (rand()%50);   //0.05~2.5

        ///初始化大小
        size = 0.3f;   //0.03

        setSnow(i);
    }
}

/** 更新粒子 */
void updateSnow(int i)
{
    /** 更新位置 */
    sx += (vx * 5);
    sz -= (vz * 5);
    sy -= vy;

    /** 更新速度 */
    vy += ay;

    /** 更新生存时间 */
    lifetime -= dec;

    /** 如果粒子消失或生命结束 */
    if (sy <= 0 || lifetime <= 0)
    {
        ///初始化坐标
        sx = pow(-1, (rand()%2))*(rand() % 100);
        sy = 100;
        //sz = pow(-1, (rand()%2))*(rand() % groundSize);
        sz = (rand() % groundSize);

        ///初始化速度
        vx = pow(-1, (rand()%2)) * 0.01 * (rand()%100); //左右均可以移动
        vy = 0.002 * (rand()%2800);
        vz = 0.01 * (rand()%100);   //目前设置只向前

        ///消失速度
        dec = 0.1 * (rand()%50);    //0.1~5

        ///初始化生命周期
        lifetime = 100;
    }
    ///跟新参数
    setSnow(i);
}


///** 绘制粒子 */
void drawParticle()
{
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);    /**< 设置混合因子获得半透明效果 */
    glEnable(GL_BLEND);

    /** 绑定纹理 */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texSnow);

    for(int i = 0; i < snowNum; ++i)
    {
        /** 获得粒子的所有属性 */
        getSnow(i,r,g,b,sx,sy,sz,vx,vy,vz,ax,ay,az,size,lifetime,dec);
        glPushMatrix();
        glColor4ub(r,g,b,255);
        glNormal3f(0.0f,0.0f,1.0f);   //定义法线方向

        glTranslatef(sx,sy,sz);    //移动到新的位置
        glTranslatef(0, snowHeight, 0); //移动相机时，同时移动雪花位置

        /** 画出粒子 */
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

        /** 更新粒子属性 */
        updateSnow(i);

        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

}
