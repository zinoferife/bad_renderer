//
//  vertex_array.hpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef vertex_array_hpp
#define vertex_array_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <openGL/gl.h>
#include <vector>

#include "vertex_buffer.hpp"
#include "index_buffer.hpp"

class Vertex_array
{
private:
    std::vector<Vertex_buffer> m_buffers;
   
    const int m_max_buffer =16;
    
    GLuint m_vertex_arrayID;
public:
    Vertex_array();
    bool add_buffer(Vertex_buffer& buffer , GLuint attrib_index);
    void add_index_buf(Index_buffer& index);
    bool setup_buffers();
    bool remove_buffer(Vertex_buffer& buffer);
    
    void generate();
    
    bool bind();
    bool unbind();
    
    friend void enable(Vertex_buffer & buf ,GLuint attrib_index, GLenum type , GLint components);
    
    GLuint get_vertex_arrayID();
    
    //NOT SUPPOSED TO BE HERE BUT, YEAH BAD OOP
     Index_buffer m_index_buffer;
    
    
    
    ~Vertex_array();
    
    

};


#endif /* vertex_array_hpp */
