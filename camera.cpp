//
//  camera.cpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "camera.hpp"



Camera::Camera() : m_projection_matrix(0) , m_view_matrix(0), m_shader_programID(0)
{

}

Camera::Camera(glm::mat4 proj_mat , glm::mat4 view_mat)
{
    /*
    load_identity_proj();
    load_identity_view();
    */
    
    m_view_matrix = view_mat;
    m_projection_matrix = proj_mat;
}


void Camera::load_identity_view()
{
    m_view_matrix = glm::mat4(1.0);
}

void Camera::load_identity_proj()
{
    m_projection_matrix = glm::mat4(1.0);
}


void Camera::set_proj_mat(glm::mat4 &proj)
{
    m_projection_matrix = proj;
}

void Camera::set_view_mat(glm::mat4 &view)
{
    m_view_matrix = view;
}

glm::mat4 Camera::get_proj_mat()
{
    return m_projection_matrix;
}


glm::mat4 Camera::get_view_mat()
{
    return m_view_matrix;
}


bool Camera::set_shader_programID(GLint shaderID)
{
    if(shaderID <= 0)
    {
        return false;
    }
    
    m_shader_programID = shaderID;
    return true;
}


bool Camera::set_shader_proj_name(std::string &name)
{
    if(name.empty())
    {
        return  false;
    }
    m_camera_proj_shader_name = name;
    return true;
}


bool Camera::set_shader_view_name(std::string &name)
{
    if(name.empty())
    {
        return false;
    }
    m_camera_view_shader_name = name;
    return true;
}

bool Camera::update_cam_shader()
{
    if(m_shader_programID <= 0)
    {
        return false;
    }
    if(m_camera_view_shader_name.empty())
    {
        return false;
    }
    if(m_camera_proj_shader_name.empty())
    {
        return false;
    }
    GLint uniform_loc_view, uniform_loc_proj;
    
    uniform_loc_proj = glGetUniformLocation(m_shader_programID,m_camera_proj_shader_name.c_str());
    uniform_loc_view = glGetUniformLocation(m_shader_programID, m_camera_view_shader_name.c_str());
    
    std::cout << "Setting proj matrix to uniform location" << uniform_loc_proj << std::endl;
    std::cout << "Setting view matrix to unifrom location" << uniform_loc_view << std::endl;
    
    glUniformMatrix4fv(uniform_loc_proj, 1, GL_FALSE, glm::value_ptr(m_projection_matrix));
    glUniformMatrix4fv(uniform_loc_view, 1,GL_FALSE, glm::value_ptr(m_view_matrix));
    
    return true;
}


void Camera::yaw(GLfloat degrees)
{
    m_view_matrix = glm::rotate(m_view_matrix, degrees, glm::vec3(0.0,0.0,1.0));
  
}

void Camera::roll(GLfloat degrees)
{
    m_view_matrix = glm::rotate(m_view_matrix, degrees, glm::vec3(1.0,0.0,0.0));
  
}

void Camera::pitch(GLfloat degrees)
{
    m_view_matrix = glm::rotate(m_view_matrix, degrees, glm::vec3(0.0,1.0,0.0));

}

void Camera::move(glm::vec3 move_by)
{
    m_view_matrix = glm::translate(m_view_matrix, move_by);
}

Camera::~Camera()
{
    //
}

