//
//  shader.hpp
//  gl_pro01
//
//  Created by ferife zino  on 03/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <openGL/gl.h>
#include <iostream>
#include <exception>
#include <vector>


#include <fstream>


class Shader
{
    GLint m_programID;
    
public:
    Shader(const char * V_filename, const char * F_filename);
    GLint program_id();
    bool bind();
    bool unbind();
    
    
    ~Shader();
        
};






#endif /* shader_hpp */
