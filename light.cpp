//
//  light.cpp
//  gl_pro01
//
//  Created by ferife zino  on 14/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "light.hpp"


bool is_zero(glm::vec3 in)
{
    if(in.x == 0.0f && in.y == 0.0f && in.z == 0.0f)
    {
        return true;
    }else
        return false;
}


Light::Light()
: m_diffuse(0.0) , m_specular(0.0) , m_ambient(0.0), m_position(0.0),m_shaderID(0)
{
    
}

Light::Light(glm::vec3 postion , glm::vec3 diffuse, glm::vec3 spec , glm::vec3 abient)
{
    m_position = postion;
    m_diffuse = diffuse;
    m_ambient = abient;
    m_specular = spec;
}

bool Light::set_shaderID(GLuint shaderID)
{
    if(shaderID == 0)
    {
        return false;
    }
    
    m_shaderID = shaderID;
    return true;
}

bool Light::set_am_name(std::string name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_ambient_name = name;
    return true;
}

bool Light::set_diffuse_name(std::string name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_diffuse_name = name;
    return true;
}


bool Light::set_spec_name(std::string name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_spec_name = name;
    return true;
}


bool Light::set_am_value(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    m_ambient = value;
    return true;
}

bool Light::set_diffuse_value(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    
    m_diffuse = value;
    return true;
}

bool Light::set_spec_value(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    m_specular = value;
    return true;
}

bool Light::set_position_name(std::string name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_position_name = name;
    return true;
}


bool Light::set_position(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    
    m_position = value;
    return true;
}

bool Light::update_shader()
{
    if( m_diffuse_name.empty() && m_ambient_name.empty() && m_spec_name.empty() && m_position_name.empty())
    {
        return false;
    }
    
    if(m_shaderID == 0)
    {
        return false;
    }
    
    GLint unifrom_difuse , unifrom_spec , unifrom_position, unifrom_ambient;
    
    unifrom_difuse = glGetUniformLocation(m_shaderID , m_diffuse_name.c_str());
    unifrom_spec = glGetUniformLocation(m_shaderID , m_spec_name.c_str());
    unifrom_ambient = glGetUniformLocation(m_shaderID, m_ambient_name.c_str());
    unifrom_position = glGetUniformLocation(m_shaderID, m_position_name.c_str());
    
    if((unifrom_position == -1) || (unifrom_difuse == -1 ) || (unifrom_ambient == -1) || (unifrom_spec == -1))
    {
        std::cout << "Cannot get uniform location" <<std::endl;
        return false;
    }
    
    //set the values to the shader
    glUniform3fv(unifrom_position ,1, glm::value_ptr(m_position));
    glUniform3fv(unifrom_difuse ,1, glm::value_ptr(m_diffuse));
    glUniform3fv(unifrom_ambient ,1, glm::value_ptr(m_ambient));
    glUniform3fv(unifrom_spec ,1, glm::value_ptr(m_specular));
    return true;
}





