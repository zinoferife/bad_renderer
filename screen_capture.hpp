//
//  screen_capture.hpp
//  gl_pro01
//
//  Created by ferife zino  on 01/07/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef screen_capture_hpp
#define screen_capture_hpp

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <SOIL.h>

#include <iostream>
#include <string>

class Screen_capture
{
    
    std::string capture_file;
    int m_width;
    int m_height;
public:
    Screen_capture();
    Screen_capture(std::string file, int width , int  height);
    
    bool capture();
    bool set_capture_file(std::string file);
};


#endif /* screen_capture_hpp */

