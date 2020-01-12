float jiao1 = 0;
float jiao2 = 0;

/******键盘响应操作变换******/
//旋转相机，绕y轴旋转
void orient_LeftRight(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);
    jiao1 = ang;    //鼠标键盘角度匹配
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
}

//旋转相机，上下转动，绕x轴旋转
void orient_UpDown(float ang)
{
    ly = 5 * sin(ang);
    jiao2 = ang;    //鼠标键盘角度匹配
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
}

//前后移动相机
void move_Front_Back(int direction)
{
    cx = cx + direction*(lx)*1.5;
    cz = cz + direction*(lz)*1.5; //lz为负，即向前
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);
    //同时移动相机和所看的点坐标，只用修改x和z，视线参数不用修改，

    xx += direction*(lx)*1.5;
    zz += direction*(lz)*1.5;
}

//左右移动相机
void move_Left_Right(int direction)
{
    cx = cx + direction*(lz)*1.5;
    cz = cz - direction*(lx)*1.5; //如果视角旋转了，比如向左边旋转了，那么lx为负。则向左移动的话，x减少，z增大
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

    xx += direction*(lz)*1.5;
    zz -= direction*(lx)*1.5;
}

//上下移动相机
void move_High_Low(int direction)
{
    if(cy >= 50)
        cy = cy + direction * 1.4;
    else
      cy = cy + direction * 0.6;
    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

    snowHeight = snowHeight - direction * 0.6;  //调整雪花的位置
}


//按空格键回到原位置，复位所有的变量
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


/******键盘响应函数******/
void OnKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'q':
        angle -= 0.03f;
        orient_LeftRight(angle);
        break;
    case 'e':               //q,e键调用相机旋转
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
        break;              //wasd调整相机前后左右移动
    case '1':
        move_High_Low(1);
        break;
    case '2':
        move_High_Low(-1);
        break;              //1,2键上下移动相机
    case '3':
        if(angle_UpDown <= PI / 2)
            angle_UpDown += 0.20f;
        orient_UpDown(angle_UpDown);
        break;
    case '4':
        if(angle_UpDown >= - PI / 2)
            angle_UpDown -= 0.20f;
        orient_UpDown(angle_UpDown);
        break;              //3,4键上下移动视角。
    case 'z':
        snowEnable = !snowEnable;
        break;              //开关雪花效果
    case 32:    //空格键，回到原位置
        reInit();
        break;
    case 'm':   //是否开启天空贴图
        skyEnable = !skyEnable;
    default:
        break;
    }
}

///鼠标控制视角
GLfloat oldx;//当左键按下时记录鼠标坐标
GLfloat oldy;
GLfloat oldx2;//当右键按下时记录鼠标坐标
GLfloat oldy2;

int left = 1;   //left=1时左键有效。等于0时右键有效
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) //检测到左键
    {
        if (state == GLUT_DOWN) //左键按下
        {
            oldx = x;//当左键按下时记录鼠标坐标
            oldy = y;
            left = 1;
        }
    }
    if (button == GLUT_RIGHT_BUTTON)    //检测到右键
    {
        if (state == GLUT_DOWN) //右键按下
        {
            oldx2 = x;//当左键按下时记录鼠标坐标
            oldy2 = y;
            left = 0;
        }
    }
}

void motion(int x, int y)   //x和y是当前坐标位置
{
    //鼠标平行向右移动，x减
    //鼠标向上：y和z均加  向下：y和z均减
    ///左键  相机视角移动
    if(left == 1)
    {
        ///deltax：向右是减  向左是加
        ///deltay：向后是负的 向前是正的
        GLint deltax = -(oldx - x);
        GLint deltay = (oldy - y);    ///鼠标在不停的移动，它反应的是上一时刻和这一时刻的差值

        oldx = x;//记录此时的鼠标坐标，更新鼠标坐标
        oldy = y;//若是没有这两句语句，滑动是旋转会变得不可控

        jiao1 += deltax * 0.01;
        lx = sin(jiao1);
        lz = -cos(jiao1);

        jiao2 += deltay * 0.01;
        ly = sin(jiao2);

        //让键盘控制的角度跟着变化
        angle_UpDown = jiao2;
        angle = jiao1;
    }
    ///右键：相机和人眼的位置移动
    if(left == 0)
    {
        GLint deltax2 = -(oldx2 - x);
        GLint deltay2 = -(oldy2 - y);
        oldx2 = x;
        oldy2 = y;

        ///相机平行左右移动
        cx += deltax2*0.12;
        //lx -= deltax*0.05;

        ///相机平行前后移动
        cz += deltay2*0.12;
    }

    glLoadIdentity();
    gluLookAt(cx, cy, cz, cx + lx, cy + ly, cz + lz, 0.0f, 1.0f, 0.0f);

}





