//
//  light.hpp
//  gl_pro01
//
//  Created by ferife zino  on 14/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef light_hpp
#define light_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



class Light
{
private:
    //shader light values
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    glm::vec3 m_ambient;

    
    glm::vec3 m_position;
    
    //shader names and ID
    std::string m_position_name;
    std::string m_diffuse_name;
    std::string m_spec_name;
    std::string m_ambient_name;
    GLuint m_shaderID;
    
    
public:
    Light();
    Light(glm::vec3 postion , glm::vec3 diffuse, glm::vec3 spec , glm::vec3 abient);
    
    
    //set shader name and values
    bool set_shaderID( GLuint shaderID );
    
    
    bool set_diffuse_value( glm::vec3 value );
    bool set_diffuse_name( std::string name );
    bool set_spec_value( glm::vec3 value );
    bool set_spec_name( std::string name );
    bool set_am_value( glm::vec3 value );
    bool set_am_name( std::string name );
    bool set_position_name( std::string name );
    bool set_position( glm::vec3 value );
    

    bool update_shader();
    
    
};






#endif /* light_hpp */
