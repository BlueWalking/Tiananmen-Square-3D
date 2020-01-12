/****************************载入一副位图作为纹理，返回的是纹理编号**********************************************/
#define BMP_Header_Length 54    //图像数据在内存块中的偏移量
#define GL_BGR_EXT 0x80E0
//判断一个数是否是2的整数次方
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

    // 打开文件，如果失败，返回
    FILE* pFile = fopen(file_name, "rb");
    if( pFile == 0 )
    {
        printf("Wrong!!!!\n");
        return 0;
    }

    // 读取文件中图象的宽度和高度
    fseek(pFile, 0x0012, SEEK_SET);
    fread(&width, 4, 1, pFile);
    fread(&height, 4, 1, pFile);
    fseek(pFile, BMP_Header_Length, SEEK_SET);

    // 计算每行像素所占字节数，并根据此数据计算总像素字节数
    GLint line_bytes = width * 3;
    while( line_bytes % 4 != 0 )
        ++line_bytes;
    total_bytes = line_bytes * height;

    // 根据总像素字节数分配内存
    pixels = (GLubyte*)malloc(total_bytes);
    if( pixels == 0 )
    {
        fclose(pFile);
        return 0;
    }

    // 读取像素数据
    if( fread(pixels, total_bytes, 1, pFile) <= 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    // 对就旧版本的兼容，如果图象的宽度和高度不是的整数次方，则需要进行缩放
    // 若图像宽高超过了OpenGL规定的最大值，也缩放
    GLint max;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
    if( !power_of_two(width) || !power_of_two(height) || width > max || height > max )
    {
        const GLint new_width = 256;
        const GLint new_height = 256; // 规定缩放后新的大小为边长的正方形
        GLint new_line_bytes, new_total_bytes;
        GLubyte* new_pixels = 0;

        // 计算每行需要的字节数和总字节数
        new_line_bytes = new_width * 3;
        while( new_line_bytes % 4 != 0 )
            ++new_line_bytes;
        new_total_bytes = new_line_bytes * new_height;

        // 分配内存
        new_pixels = (GLubyte*)malloc(new_total_bytes);
        if( new_pixels == 0 )
        {
            free(pixels);
            fclose(pFile);
            return 0;
        }

        // 进行像素缩放
        gluScaleImage(GL_RGB,
                      width, height, GL_UNSIGNED_BYTE, pixels,
                      new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

        // 释放原来的像素数据，把pixels指向新的像素数据，并重新设置width和height
        free(pixels);
        pixels = new_pixels;
        width = new_width;
        height = new_height;
    }


    // 分配一个新的纹理编号
    glGenTextures(1, &texture_ID);
    if( texture_ID == 0 )
    {
        free(pixels);
        fclose(pFile);
        return 0;
    }

    // 绑定新的纹理，载入纹理并设置纹理参数
    // 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
    GLint lastTextureID = last_texture_ID;/**这个我看教室那个代码没有加**/
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);

    glBindTexture(GL_TEXTURE_2D, texture_ID);   //绑定纹理

    //设置4个常用的纹理参数。。如何把纹理像素映射成像素
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //指定纹理贴图与材质的混合模式

    //参数： 目标纹理，多重细节层次（不考虑多重纹理为0），RGB数据存储格式，二维纹理像素宽高，纹理边框大小
    //       纹理像素数据的格式，数据保存形式（像素数据类型，字节），内存中指向纹理图像的指针（纹理图像的内参快地址）
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                 GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels); //为纹理对象指定一个纹理

    glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定

    free(pixels);
    return texture_ID;
}
