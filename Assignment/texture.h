/****************************����һ��λͼ��Ϊ�������ص���������**********************************************/
#define BMP_Header_Length 54    //ͼ���������ڴ���е�ƫ����
#define GL_BGR_EXT 0x80E0
//�ж�һ�����Ƿ���2�������η�
int power_of_two(int n)
{
	if( n <= 0 )
		return 0;
    return (n & (n-1)) == 0;
}

GLuint load_texture(const char* file_name)
{
    GLint width, height, total_bytes;
    GLubyte* pixels = 0;
    GLuint last_texture_ID=0, texture_ID = 0;

    // ���ļ������ʧ�ܣ�����
    FILE* pFile = fopen(file_name, "rb");
    if( pFile == 0 )
    {
        printf("Wrong!!!!\n");
        return 0;
    }

    // ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);

    // ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
    GLint line_bytes = width * 3;
    while( line_bytes % 4 != 0 )
        ++line_bytes;
    total_bytes = line_bytes * height;

    // �����������ֽ��������ڴ�
    pixels = (GLubyte*)malloc(total_bytes);
    if( pixels == 0 )
    {
        fclose(pFile);
        return 0;
    }

    // ��ȡ��������
    if( fread(pixels, total_bytes, 1, pFile) <= 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    // �Ծ;ɰ汾�ļ��ݣ����ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
    // ��ͼ���߳�����OpenGL�涨�����ֵ��Ҳ����
    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    if( !power_of_two(width) || !power_of_two(height) || width > max || height > max )
    {
        const GLint new_width = 256;
        const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������
        GLint new_line_bytes, new_total_bytes;
        GLubyte* new_pixels = 0;

        // ����ÿ����Ҫ���ֽ��������ֽ���
        new_line_bytes = new_width * 3;
        while( new_line_bytes % 4 != 0 )
            ++new_line_bytes;
        new_total_bytes = new_line_bytes * new_height;

        // �����ڴ�
        new_pixels = (GLubyte*)malloc(new_total_bytes);
        if( new_pixels == 0 )
        {
            free(pixels);
            fclose(pFile);
            return 0;
        }

        // ������������
        gluScaleImage(GL_RGB,
                      width, height, GL_UNSIGNED_BYTE, pixels,
                      new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

        // �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
        free(pixels);
        pixels = new_pixels;
        width = new_width;
        height = new_height;
    }


    // ����һ���µ�������
    glGenTextures(1, &texture_ID);
    if( texture_ID == 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    // ���µ������������������������
    // �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
    GLint lastTextureID = last_texture_ID;/**����ҿ������Ǹ�����û�м�**/
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);

    glBindTexture(GL_TEXTURE_2D, texture_ID);   //������

    //����4�����õ��������������ΰ���������ӳ�������
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //ָ��������ͼ����ʵĻ��ģʽ

    //������ Ŀ����������ϸ�ڲ�Σ������Ƕ�������Ϊ0����RGB���ݴ洢��ʽ����ά�������ؿ�ߣ�����߿��С
    //       �����������ݵĸ�ʽ�����ݱ�����ʽ�������������ͣ��ֽڣ����ڴ���ָ������ͼ���ָ�루����ͼ����ڲο��ַ��
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels); //Ϊ�������ָ��һ������

    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������

    free(pixels);
    return texture_ID;
}
