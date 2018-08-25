//
//  vertex_array.cpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "vertex_array.hpp"

void enable(Vertex_buffer & buf ,GLuint attrib_index, GLenum type , GLint components)
{
    glEnableVertexAttribArray(attrib_index);
    buf.bind();
    glVertexAttribPointer(attrib_index,components,type,GL_FALSE,0, NULL);
    
}


//strat of the vertex array class
Vertex_array::Vertex_array()
{
   
}

void Vertex_array::generate()
{
    glGenVertexArrays(1, &m_vertex_arrayID);
    glBindVertexArray(m_vertex_arrayID);
}


bool Vertex_array::add_buffer(Vertex_buffer& buffer, GLuint attrib_index)
{
    if(buffer.get_vertex_bufferID() == 0)
    {
        return false;
    }
    
    m_buffers.push_back(buffer);
    return true;
}

bool Vertex_array::setup_buffers()
{
    if(m_buffers.empty())
    {
        std::cout << "The array is empty" <<std::endl;
        return false;
    }
    for( GLuint i = 0; i < m_buffers.size(); i++)
    {
        enable(m_buffers[i], i, m_buffers[i].m_type, m_buffers[i].m_components);
    }
    m_index_buffer.bind();
    return true;
}


// world have to search through the array and find the buffer to remove
bool Vertex_array::remove_buffer(Vertex_buffer & buffer)
{
    return true;
}

GLuint Vertex_array::get_vertex_arrayID()
{
    return m_vertex_arrayID;
}

bool Vertex_array::bind()
{
    if(m_vertex_arrayID == 0)
    {
        return false;
    }
    
    glBindVertexArray(m_vertex_arrayID);
    return true;
}

bool Vertex_array::unbind()
{
    if(!glIsVertexArray(m_vertex_arrayID) || m_vertex_arrayID == 0)
    {
        return false;
    }
    glBindVertexArray(0);
    return true;
}


void Vertex_array::add_index_buf(Index_buffer &index)
{
    m_index_buffer = index;
}


Vertex_array::~Vertex_array()
{
    if(!m_buffers.empty())
    {
        for(int i = 0; i < m_buffers.size(); i++)
        {
            GLuint vbo = m_buffers[i].get_vertex_bufferID();
            glDeleteBuffers(1,&vbo);
        }
        m_buffers.clear();
    }
    glDeleteVertexArrays(1, &m_vertex_arrayID);
}






