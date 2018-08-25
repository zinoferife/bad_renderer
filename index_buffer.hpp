//
//  index_buffer.hpp
//  gl_pro01
//
//  Created by ferife zino  on 09/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef index_buffer_hpp
#define index_buffer_hpp

#include <stdio.h>
#include <GL/glew.h>
#include <iostream>
#include <openGL/gl.h>


class Index_buffer
{
private:
    GLuint m_indexID;
    unsigned int m_size;
    unsigned int m_count;
    
    
public:
    Index_buffer(unsigned char * data, unsigned int byte_size , unsigned int count);
    Index_buffer();
    bool bind();
    bool unbind();
    
    
    unsigned int count();
    
};








#endif /* index_buffer_hpp */
