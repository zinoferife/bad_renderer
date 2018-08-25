//
//  texture.hpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

#include <openGL/gl.h>
#include <SOIL.h>


class Texture
{
private:
    GLuint m_texID;
    int m_height;
    int m_width;
    
    unsigned char * m_image; // holds the image in memory
    
    //TODO : texture matrix and stuff
    
    GLint m_shader_programID;
    std::string m_shader_sampler_name;
    
    GLenum m_texture_unit;
public:
    Texture(const char * filename , GLenum tex_unit);
    bool bind();
    bool unbind();
    
    void set_shader_programID(GLint programID);
    GLint get_shader_programID();
    
    
    void set_shader_sampler_name(std::string name);
    std::string& get_shader_sampler_name();
    bool update_shader(GLuint tex_unit_num);
    
    void set_texture_unit(GLenum tex_unit);
    GLenum get_texture_unit();
    
    ~Texture();
    
    
};



#endif /* texture_hpp */
