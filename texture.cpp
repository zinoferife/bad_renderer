//
//  texture.cpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "texture.hpp"


Texture::Texture(const char * filename , GLenum tex_unit)
:m_shader_programID(-1) , m_texture_unit(tex_unit)
{
    glActiveTexture(m_texture_unit);
    glGenTextures(1, &m_texID);
    glBindTexture(GL_TEXTURE_2D, m_texID);
    
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    
    m_image = SOIL_load_image(filename, &m_width, &m_height, 0, SOIL_LOAD_RGB);
    if(!m_image)
    {
        std::cout << "Cannot open image file" << std::endl;
        return;
    }
    
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, m_image);
    
    
}

bool Texture::bind()
{
    if(m_texID == -1)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        return false;
    }
    
    glBindTexture(GL_TEXTURE_2D, m_texID);
    return true;
}

bool Texture::unbind()
{
    if(m_texID == -1)
    {
        return false;
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

void Texture::set_shader_programID(GLint programID)
{
    m_shader_programID = programID;
}

GLint Texture::get_shader_programID()
{
    return m_shader_programID;
}

void Texture::set_shader_sampler_name(std::string name)
{
    m_shader_sampler_name = name;
}

std::string& Texture::get_shader_sampler_name()
{
    return m_shader_sampler_name;
}

bool Texture::update_shader(GLuint tex_unit_num)
{
    if(m_shader_programID == -1 || m_shader_sampler_name.empty())
    {
        return false;
    }
    GLint unifrom_loc = glGetUniformLocation(m_shader_programID,m_shader_sampler_name.c_str());
    if(unifrom_loc == -1)
    {
        std::cout <<"CANNOT GET TEXTURE SAMPLER UNIFROM" <<std::endl;
        return false;
    }
    
    glUniform1i(unifrom_loc, tex_unit_num);
    return true;
}

void Texture::set_texture_unit(GLenum tex_unit)
{
    m_texture_unit = tex_unit;
}

GLenum Texture::get_texture_unit()
{
    return m_texture_unit;
}



Texture::~Texture()
{
    free(m_image);
}






