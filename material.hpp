//
//  material.hpp
//  gl_pro01
//
//  Created by ferife zino  on 17/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef material_hpp
#define material_hpp

#include <stdio.h>
#include <string>



#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <OpenGL/gl.h>
#include <glm/glm.hpp>


class Material
{

private:
    
    GLint m_shaderID;
    
    
    glm::vec3 m_diffuse;
    glm::vec3 m_ambient;
    glm::vec3 m_specular;
    glm::vec3 m_emission;
    float m_shine;
    
    std::string m_diffuse_name;
    std::string m_ambient_name;
    std::string m_specular_name;
    std::string m_emission_name;
    std::string m_shine_name;
    
    bool is_zero(glm::vec3 value);
public:
    
    Material();
    
    bool set_diffuse_value(glm::vec3 value);
    bool set_ambient_value(glm::vec3 value);
    bool set_specular_value(glm::vec3 value);
    bool set_emission_value(glm::vec3 value);
    bool set_shine_value(float value);
    
    
    bool set_diffuse_name(std::string& name);
    bool set_ambient_name(std::string& name);
    bool set_specular_name(std::string& name);
    bool set_emission_name(std::string& name);
    bool set_shine_name(std::string& name);
    
    
    bool set_shaderID(GLint id);
    bool update_shader();

};




#endif /* material_hpp */
