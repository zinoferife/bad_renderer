//
//  mesh.cpp
//  gl_pro01
//
//  Created by ferife zino  on 05/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "mesh.hpp"


Mesh::Mesh()
: m_shader_programID(-1), m_number_of_vertex(0)
{
    m_model_matrix = glm::mat4(1.0);
}

void Mesh::set_model_matrix(glm::mat4 matrix)
{
    m_model_matrix = matrix;
}

glm::mat4 Mesh::get_model_matrix()
{
    return m_model_matrix;
}

GLint Mesh::get_shader_programID()
{
    return m_shader_programID;
}

void Mesh::set_shader_programID(GLint programID)
{
    m_shader_programID = programID;
}

bool Mesh::set_shader_matrix_name(std::string name)
{
    if(name.empty())
    {
        return false;
    }
    m_shader_matrix_name = name;
    return true;
}

bool Mesh::update_mesh_shader()
{
    
    
    if(m_shader_matrix_name.empty() || m_shader_programID == -1)
    {
        std::cout << "COULD NOT LOAD MODEL MATRIX NO SHADER" << std::endl;
        return false;
    }
    GLint unifrom_loc = glGetUniformLocation(m_shader_programID, m_shader_matrix_name.c_str());
    GLint uniform_loc_normal = glGetUniformLocation(m_shader_programID , m_shader_normal_matrix_name.c_str());
    
    
    if(unifrom_loc == -1 || uniform_loc_normal == -1)
    {
        std::cout << "COULD NOT GET UNIFROM LOACTION" << std::endl;
        return false;
    }
    
    std::cout << "SETTING THE MODEL MATRIX AT " << unifrom_loc << std::endl;
    glUniformMatrix4fv(unifrom_loc, 1 , GL_FALSE , glm::value_ptr(m_model_matrix) );
    glUniformMatrix3fv(uniform_loc_normal, 1 , GL_FALSE , glm::value_ptr(m_normal_matrix) );
    return true;
}


void Mesh::rotX(GLfloat degrees)
{
    m_model_matrix = glm::rotate(m_model_matrix, degrees, glm::vec3(1.0,0.0,0.0));
}

void Mesh::rotY(GLfloat degrees)
{
    m_model_matrix = glm::rotate(m_model_matrix, degrees, glm::vec3(0.0,1.0,0.0));
}

void Mesh::rotZ(GLfloat degrees)
{
    m_model_matrix = glm::rotate(m_model_matrix, degrees, glm::vec3(0.0,0.0,1.0));
}

void Mesh::translate(glm::vec3 move_by)
{
    m_model_matrix = glm::translate(m_model_matrix, move_by);
}

void Mesh::set_number_of_vertex(int num)
{
    m_number_of_vertex = num;
}


int Mesh::get_number_of_vertex()
{
    return m_number_of_vertex;
}

void Mesh::draw()
{
    if(m_number_of_vertex == 0)
    {
        std::cout << "CANNOT DRAW EMPTY MESH" << std::endl;
    }
    glDrawArrays(GL_TRIANGLES, 0, m_number_of_vertex);
}

void Mesh::draw_elements()
{
    glDrawElements(GL_TRIANGLES, m_index_buffer.count(), GL_UNSIGNED_SHORT, NULL);

}

void Mesh::set_noraml_matrix_name(std::string name)
{
    m_shader_normal_matrix_name = name;
}

void Mesh::set_normal_matrix(glm::mat3 matrix)
{
    m_normal_matrix = matrix;
}

Mesh::~Mesh()
{
}




