//��4 ͷ��2
void generatePeople()
{
    //ͷ
    glColor3f(red);
    constract(0,0,2, 2,2,-2);
    build();
    //����
    glColor3f(green);
    constract(0.6,-1.5,1.4, 0.8f,1.5f,-0.8f);
    build();
    //��1
    glColor3f(gold);
    constract(0.6,-2,1.4, 0.35,0.5,-0.8);
    build();
    //��2
    glColor3f(gold);
    constract(1.05,-2,1.4, 0.35,0.5,-0.8);
    build();
    //�첲1
    glColor3f(nbrown);
    constract(1.4,-0.8,1.15, 0.3,0.8,-0.3);
    build();
    //�첲2
    glColor3f(nbrown);
    constract(0.3,-0.8,1.15, 0.3,0.8,-0.3);
    build();
}

void initPeople()
{
    ///��ʼ��С������
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

//С���ƶ�����
void peopleMove(int i)
{
    glPushMatrix();

    ///�����ײ��
    float xxx[3] = {people[i].peopleX, people[i].peopleY, people[i].peopleZ};
    float yyy[3] = {-33, 0, 37-100};
    float zzz[3] = {66, 13, -37};

    //��������˱߽��λ�ã����³�ʼ��С��λ��
    if((people[i].peopleX >= groundSize || people[i].peopleX <= -groundSize) ||
       (people[i].peopleZ >= groundSize || people[i].peopleZ <= -groundSize))
    {
        people[i].peopleX = pow(-1,(rand()%2))*(rand()%100);  //-100~100
        people[i].peopleY = 2;
        people[i].peopleZ = pow(-1,(rand()%2))*(rand()%100);
        printf("%d: С���ܳ�ȥ����\n", i);
    }
    //�����û��ת���Ƕȣ����ոճ�ʼ���꣬�ͼӿ�����ת��ʱ��
    int rotateTime = 0;
    if(people[i].peopleAngle == 0){
        rotateTime = 30;
    }
    else{
        rotateTime = 70;
    }
    //ת��
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
//����ǳ�ʼ��λ����������ת��
///����ʱ�䣬������ͬ��С��
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
