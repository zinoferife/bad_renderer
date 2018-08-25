//
//  screen_capture.cpp
//  gl_pro01
//
//  Created by ferife zino  on 01/07/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "screen_capture.hpp"


Screen_capture::Screen_capture()
{

}

Screen_capture::Screen_capture(std::string file , int width , int  height)
{
    capture_file = file;
    m_width = width;
    m_height = height;
    
    capture();
}


bool Screen_capture::capture()
{
    if(capture_file.empty() || ( m_height == 0 ) || ( m_width == 0 ) )
    {
        return false;
    }
    
    int ret = SOIL_save_screenshot(capture_file.c_str(), SOIL_SAVE_TYPE_BMP, 0, 0, m_width, m_height);
    if(!ret)
        return false;
    
    return true;
}
