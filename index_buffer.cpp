//
//  index_buffer.cpp
//  gl_pro01
//
//  Created by ferife zino  on 09/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "index_buffer.hpp"
Index_buffer::Index_buffer()
: m_indexID(0), m_size(0) , m_count(0)
{
    //
}


Index_buffer::Index_buffer(unsigned char * data , unsigned int byte_size , unsigned int count)
: m_indexID(0) , m_size(byte_size) , m_count(count)
{
    glGenBuffers(1, &m_indexID);
    if(m_indexID == 0)
    {
        std::cout << "Cannot genrate buffer" << std::endl;
        return;
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , m_size , data , GL_STATIC_DRAW);
}


unsigned int Index_buffer::count()
{
    return m_count;
}


bool Index_buffer::bind()
{
    if(m_indexID == 0)
    {
        return  false;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , m_indexID);
    return true;
}

bool Index_buffer::unbind()
{
    if( m_indexID == 0)
    {
        return  false;
    }
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);
    return true;
}

