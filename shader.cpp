//
//  shader.cpp
//  gl_pro01
//
//  Created by ferife zino  on 03/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "shader.hpp"




Shader::Shader(const char * V_filename, const char * F_filename)
: m_programID(-1) {
    std::ifstream in_file(V_filename, std::ios::in);
    if(!in_file.is_open())
    {
        std::cout << "Cannot open  vertex file" << std::endl;
    }
    long s, e;
    s = in_file.tellg();
    in_file.seekg(0,std::ios::end);
    e = in_file.tellg();
    
    long sz = e - s;
    in_file.seekg(0,std::ios::beg);
    
    char * str_buf = new char[sz+1];
    if(!str_buf)
    {
        std::cout << "NO MEM FOR STR_BUF" << std::endl;
        throw std::bad_alloc();
    }
    
    in_file.read(str_buf, sz);
    str_buf[sz] = '\0';
 
    std::fstream f_file(F_filename);
    if(!f_file)
    {
        std::cout << "Cannot open fragment file" << std::endl;
    }
    
    long l,m;
    m = f_file.tellg();
    f_file.seekg(0,std::ios::end);
    l = f_file.tellg();
    
    f_file.seekg(0,std::ios::beg);
    long sz_2 = l - m;
    
    char * str_buf2 = new char[sz_2 + 1];
    if(!str_buf2)
    {
        std::cout << "NO MEM FOR STR BUF 2" <<std::endl;
        throw  std::bad_alloc();
    }
    f_file.read(str_buf2, sz_2);
    
    str_buf2[sz_2] = '\0';
    
    in_file.close();
    f_file.close();
    
    GLint v_id , f_id;
    
    v_id =  glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_id, 1 , &str_buf, NULL);
    glCompileShader(v_id);
    
    GLint r = GL_FALSE;
    GLint info_length;
    glGetShaderiv(v_id, GL_COMPILE_STATUS, &r);  //check for complile errors;
    glGetShaderiv(v_id, GL_INFO_LOG_LENGTH , &info_length);
    
    if(!r)
    {
        std::cout << "DEBUG : VERTEX" <<std::endl;
        std::vector<char> log(info_length + 1);
        glGetShaderInfoLog(v_id, info_length, NULL , log.data() );
        std::cout << (char *)log.data() << std::endl;
    }
    f_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_id, 1, &str_buf2 , NULL);
    glCompileShader(f_id);
    
    //check for complie error
    
    r = GL_FALSE;
    info_length = 0;
    
    glGetShaderiv(f_id, GL_COMPILE_STATUS, &r);
    glGetShaderiv(f_id, GL_INFO_LOG_LENGTH, &info_length);
    
    if(!r)
    {
        std::cout << "DEBUG : FRAGMENT" <<std::endl;
        std::vector<char> log_f(info_length + 1);
        glGetShaderInfoLog(f_id, info_length , NULL , log_f.data());
        std::cout << (char * )log_f.data() << std::endl;
    }
    
    m_programID = glCreateProgram();
    if(m_programID == -1)
    {
        std::cout << "Cannot create shader program" <<std::endl;
        //throw error, shader object is in valid
    }
    
    //everything complied well
    
    glAttachShader(m_programID , v_id);
    glAttachShader(m_programID , f_id);
    
    glLinkProgram(m_programID);
    
    //check for link errors
    r = GL_FALSE;
    info_length = 0;

    glGetProgramiv(m_programID, GL_LINK_STATUS, &r);
    glGetProgramiv(m_programID , GL_INFO_LOG_LENGTH , &info_length);
    
    
    if(!r)
    {
        std::vector<char> log_p(info_length + 1);
        glGetProgramInfoLog(m_programID, info_length, NULL , log_p.data());
        
        std::cout << log_p.data() << std::endl;
    }
    
    

    //everything links well
    //detach shaders and delete shaders
    
    delete [] str_buf;
    delete [] str_buf2;
    
    glDetachShader(m_programID,v_id);
    glDetachShader(m_programID, f_id);
    
    glDeleteShader(v_id);
    glDeleteShader(f_id);
}

bool  Shader::bind()
{
    if(m_programID == -1)
    {
        return  false;
    }
    glUseProgram(m_programID);
    return true;
}


bool Shader::unbind()
{
    if(m_programID == -1)
    {
        return  false;
    }
    
    glUseProgram(0);
    return true;
}

Shader::~Shader()
{
    if(m_programID == -1)
        return;
    
    glDeleteProgram(m_programID);
}

GLint Shader::program_id()
{
    return m_programID;
}


