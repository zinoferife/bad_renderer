//
//  vertex_buffer.cpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "vertex_buffer.hpp"


Vertex_buffer::Vertex_buffer(unsigned char * buffer , size_t size, GLenum type , int components)
: m_vertex_bufferID(0), m_type(type) , m_size(size), m_components(components)
{
    glGenBuffers(1,&m_vertex_bufferID);
    
    if(m_vertex_bufferID == 0)
    {
        std::cout << "invalid buffer object created" << std::endl;
        //throw error
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_bufferID);
    glBufferData(GL_ARRAY_BUFFER, size, buffer , GL_STATIC_DRAW);
}

bool Vertex_buffer::bind()
{
    if(m_vertex_bufferID == 0)
    {
        std::cout << "NOT BINDING" << std::endl;
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_bufferID);
    return true;
}

GLuint Vertex_buffer::get_vertex_bufferID() const
{
    return m_vertex_bufferID;
}


bool Vertex_buffer::unbind()
{
    if(m_vertex_bufferID == 0)
    {
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

Vertex_buffer::~Vertex_buffer()
{
   //glDeleteBuffers(1, &m_vertex_bufferID);
}