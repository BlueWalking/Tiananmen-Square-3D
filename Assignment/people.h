//高4 头宽2
void generatePeople()
{
    //头
    glColor3f(red);
    constract(0,0,2, 2,2,-2);
    build();
    //身子
    glColor3f(green);
    constract(0.6,-1.5,1.4, 0.8f,1.5f,-0.8f);
    build();
    //脚1
    glColor3f(gold);
    constract(0.6,-2,1.4, 0.35,0.5,-0.8);
    build();
    //脚2
    glColor3f(gold);
    constract(1.05,-2,1.4, 0.35,0.5,-0.8);
    build();
    //胳膊1
    glColor3f(nbrown);
    constract(1.4,-0.8,1.15, 0.3,0.8,-0.3);
    build();
    //胳膊2
    glColor3f(nbrown);
    constract(0.3,-0.8,1.15, 0.3,0.8,-0.3);
    build();
}

void initPeople()
{
    ///初始化小人坐标
    int px, pz, d1, d2;
    for(int i = 0; i < peopleNum; i++)
    {
        px = rand()%100;
        pz = rand()%100;
        d1 = rand()%2;
        d2 = rand()%2;
        people[i].peopleTime = 0;
        people[i].peopleAngle = 0;
        people[i].peopleX = pow(-1,d1)*px;  //-100~100
        people[i].peopleY = 2;
        people[i].peopleZ = pow(-1,d2)*pz;  //-100~100
    }
}

//小人移动函数
void peopleMove(int i)
{
    glPushMatrix();

    ///检测碰撞的
    float xxx[3] = {people[i].peopleX, people[i].peopleY, people[i].peopleZ};
    float yyy[3] = {-33, 0, 37-100};
    float zzz[3] = {66, 13, -37};

    //如果超过了边界的位置，重新初始化小人位置
    if((people[i].peopleX >= groundSize || people[i].peopleX <= -groundSize) ||
       (people[i].peopleZ >= groundSize || people[i].peopleZ <= -groundSize))
    {
        people[i].peopleX = pow(-1,(rand()%2))*(rand()%100);  //-100~100
        people[i].peopleY = 2;
        people[i].peopleZ = pow(-1,(rand()%2))*(rand()%100);
        printf("%d: 小人跑出去啦！\n", i);
    }
    //如果还没有转过角度，即刚刚初始化完，就加快它的转向时间
    int rotateTime = 0;
    if(people[i].peopleAngle == 0){
        rotateTime = 30;
    }
    else{
        rotateTime = 70;
    }
    //转向
    if(people[i].peopleTime % rotateTime == 0)
    {
        float jiaodu= rand()%90;
        people[i].peopleAngle = jiaodu;
    }
    else{
        people[i].peopleX += 1 * sin(people[i].peopleAngle);
        people[i].peopleZ += 1 * cos(people[i].peopleAngle);
    }
    glTranslated(people[i].peopleX, people[i].peopleY, people[i].peopleZ);
    generatePeople();
    glPopMatrix();
}
//如果是初始化位置让他尽快转向
///按照时间，画出不同的小人
void drawPeople()
{
    if(timer == 0)
        initPeople();
    if(timer >= pi/5 && timer < pi){
        for(int i = 0; i < peopleNum/4; i++)
            peopleMove(i);
    }
    if(timer >= pi/5*2 && timer < pi/5*4){
        for(int i = 0; i < peopleNum; i++)
            peopleMove(i);
    }

}
