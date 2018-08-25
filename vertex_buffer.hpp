//
//  vertex_buffer.hpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef vertex_buffer_hpp
#define vertex_buffer_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <OpenGL/gl.h>

//dosent store any data in the  memory
//just a handle on the buffer memory in the gpu


//written by zee

class Vertex_buffer
{
private:
    GLuint m_vertex_bufferID;
public:
    Vertex_buffer( unsigned char * buffer, size_t size, GLenum type , int components);
    GLuint get_vertex_bufferID() const;
    bool bind();
    bool unbind();
    
    
    //might set getters
    size_t m_size;
    int m_components;
    GLenum m_type;
    
    
    ~Vertex_buffer();
    
};


#endif /* vertex_buffer_hpp */
