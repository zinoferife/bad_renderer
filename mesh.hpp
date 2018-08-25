//
//  mesh.hpp
//  gl_pro01
//
//  Created by ferife zino  on 05/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef mesh_hpp
#define mesh_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"


class Mesh : public Vertex_array
{
private:
    glm::mat4 m_model_matrix;
    glm::mat3 m_normal_matrix;
    GLint m_shader_programID;
    std::string m_shader_matrix_name;
    std::string m_shader_normal_matrix_name;
    int m_number_of_vertex;
public:
    
    Mesh();
    
    
    void set_model_matrix(glm::mat4 matrix);
    void set_normal_matrix(glm::mat3 matrix);
    void set_noraml_matrix_name(std::string name);
    
    glm::mat4 get_model_matrix();
    int get_number_of_vertex();
    void set_number_of_vertex(int num);
    
    //shader stuff
    void set_shader_programID(GLint programID);
    GLint get_shader_programID();
    bool set_shader_matrix_name(std::string name);
    bool update_mesh_shader();
    
    
    //model controls
    void rotX(GLfloat degrees);
    void rotY(GLfloat degrees);
    void rotZ(GLfloat degrees);
    void translate(glm::vec3 move_by);
    
    
    void draw();
    void draw_elements();
    ~Mesh();
};




#endif /* mesh_hpp */
