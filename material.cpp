//
//  material.cpp
//  gl_pro01
//
//  Created by ferife zino  on 17/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "material.hpp"

bool Material::is_zero(glm::vec3 in)
{
    if(in.x == 0.0f && in.y == 0.0f && in.z == 0.0f)
    {
        return true;
    }else
        return false;
}

Material::Material()
:m_shine(0){};

bool Material::set_diffuse_name(std::string &name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_diffuse_name = name;
    return true;
}

bool Material::set_ambient_name(std::string &name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_ambient_name = name;
    return true;
}

bool Material::set_specular_name(std::string &name)
{
    if(name.empty())
    {
        return false;
    }
    m_specular_name = name;
    return true;
}

bool Material::set_emission_name(std::string &name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_emission_name = name;
    return true;
}

bool Material::set_shine_name(std::string &name)
{
    if(name.empty())
    {
        return false;
    }
    
    m_shine_name = name;
    return true;
}



bool Material::set_diffuse_value(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    m_diffuse = value;
    return true;
}

bool Material::set_ambient_value(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    m_ambient = value;
    return true;
}

bool Material::set_specular_value(glm::vec3 value)
{
    if(is_zero(value))
    {
        return false;
    }
    m_specular = value;
    return true;
}

bool Material::set_emission_value(glm::vec3 value)
{
    m_emission = value;
    return true;
}


bool Material::set_shine_value(float value)
{
    if( value == 0.0f)
    {
        return false;
    }
    m_shine = value;
    return true;
}


bool Material::set_shaderID(GLint id)
{
    if(id == 0)
    {
        return false;
    }
    m_shaderID  = id;
    return true;
}

bool Material::update_shader()
{
 if(m_diffuse_name.empty() || m_ambient_name.empty() || m_specular_name.empty() || m_emission_name.empty() || m_shine_name.empty())
 {
     std::cout << "ONE OF THE SHADER NAME IS INVALID" << std::endl;
     return false;
 }
    GLint uniform_diff, uniform_spec , uniform_ambi, uniform_shine , uniform_emi;
    
    uniform_diff = glGetUniformLocation(m_shaderID, m_diffuse_name.c_str());
    uniform_spec = glGetUniformLocation(m_shaderID, m_specular_name.c_str());
    uniform_ambi = glGetUniformLocation(m_shaderID, m_ambient_name.c_str());
    uniform_emi = glGetUniformLocation(m_shaderID, m_emission_name.c_str());
    uniform_shine = glGetUniformLocation(m_shaderID, m_shine_name.c_str());
    
    if((uniform_diff == -1) ||  ( uniform_spec == -1) || (uniform_shine == -1) || (uniform_emi== -1) || (uniform_ambi == -1) )
    {
        return false;
    }
    glUniform3fv(uniform_diff, 1, glm::value_ptr(m_diffuse));
    glUniform3fv(uniform_ambi, 1, glm::value_ptr(m_ambient));
    glUniform3fv(uniform_spec, 1, glm::value_ptr(m_specular));
    glUniform3fv(uniform_emi, 1, glm::value_ptr(m_emission));
    glUniform1fv(uniform_shine, 1, &m_shine );
    
    return true;
}






