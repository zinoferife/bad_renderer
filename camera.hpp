//
//  camera.hpp
//  gl_pro01
//
//  Created by ferife zino  on 04/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef camera_hpp
#define camera_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <openGL/gl.h>

class Camera
{
    glm::mat4 m_projection_matrix;
    glm::mat4 m_view_matrix;
    
    
    GLint m_shader_programID;
    std::string m_camera_view_shader_name;
    std::string m_camera_proj_shader_name;
public:

    Camera();
    Camera(glm::mat4 proj_mat , glm::mat4 view_mat);
    
    //matrix maagment
    void load_identity_view();
    void load_identity_proj();
    void set_proj_mat(glm::mat4& proj);
    void set_view_mat(glm::mat4& view);
    glm::mat4 get_view_mat();
    glm::mat4 get_proj_mat();
    
    //attaching to shader
    bool set_shader_programID(GLint shaderID);
    bool set_shader_view_name(std::string& name);
    bool set_shader_proj_name(std::string& name);
    bool update_cam_shader();
    
    //camera controls
    void yaw(GLfloat degrees);
    void roll(GLfloat degrees);
    void pitch(GLfloat degrees);
    void move(glm::vec3 move_by);
    
    
    
    ~Camera();

};



#endif /* camera_hpp */
