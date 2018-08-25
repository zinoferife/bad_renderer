//
//  main.cpp
//  gl_pro01
//
//  Created by ferife zino  on 28/05/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opengl/gl.h>
#include <SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include  "shader.hpp"
#include  "texture.hpp"
#include "vertex_array.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "mesh_loader.hpp"
#include "ting_obj_loader.hpp"
#include "light.hpp"
#include "material.hpp"
#include "screen_capture.hpp"


//.......................................... MODELS .............................................................

std::string mesh_filepath("/Users/ferifezino/Documents/opengl_projects/res/models/male_head.obj");
std::string other_filepath("/Users/ferifezino/Documents/opengl_projects/res/models/chalet.obj");
std::string z_filepath("/Users/ferifezino/Documents/opengl_projects/res/models/Zuccarello.obj");
std::string spider_filepath("/Users/ferifezino/Documents/opengl_projects/res/models/spider.obj");
std::string house_filepath("/Users/ferifezino/Documents/opengl_projects/res/models/house.obj");
std::string earth_filepath("/Users/ferifezino/Documents/opengl_projects/res/models/earth.obj");

//.................................................................................................................



float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

GLfloat tex_coords[] =
{
    0.0 , 0.0,
    1.0 , 0.0,
    0.5 , 1.0
};


GLfloat full_screen_vex_coords[] =
{
    -1.0f , 1.0f ,0.0f ,
    1.0f, 1.0f , 0.0f,
    -1.0f ,-1.0f, 0.0f,
    -1.0f, -1.0f ,0.0f,
    1.0f,1.0f,0.0f,
    1.0f , -1.0f , 0.0f
};

GLfloat full_screen_tex_coords[]
{
    0.0,1.0,
    1.0,0.0,
    0.0,0.0,
    0.0,0.0,
    1.0,0.0,
    1.0,1.0
};
glm::mat4 view = glm::lookAt(glm::vec3(0.0,0.0,5.0), glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,1.0,0.0));
glm::mat4 model_mat(1.0);
double ap = 680/480;
glm::mat4 proj = glm::perspective(45.0, ap , 1.0, 1000.0);
std::string prog_name("proj_matrix");
std::string view_name("view_matrix");

Camera cam(proj,view);


Mesh obj;
Mesh obj2;


void key_callback(GLFWwindow * window , int key, int scancode, int action , int mods)
{
    if( key == GLFW_KEY_W && action == GLFW_REPEAT )
    {
        cam.roll(0.05);
        cam.update_cam_shader();
    }if( key == GLFW_KEY_A && action == GLFW_REPEAT )
    {
        cam.pitch(0.05);
        cam.update_cam_shader();
    }if( key == GLFW_KEY_D && action == GLFW_REPEAT )
    {
        cam.yaw(0.05);
        cam.update_cam_shader();
    }if( key == GLFW_KEY_S && action == GLFW_REPEAT)
    {
        cam.move(glm::vec3(0.0,0.0,1.0));
        cam.update_cam_shader();
    }if( key == GLFW_KEY_X && action == GLFW_REPEAT)
    {
        cam.move(glm::vec3(0.0,0.0,-1.0));
        cam.update_cam_shader();
    }if( key == GLFW_KEY_U &&action == GLFW_REPEAT)
    {
        obj.rotX(0.05);
        obj.update_mesh_shader();
        
    }if( key == GLFW_KEY_H && action == GLFW_REPEAT)
    {
        obj.rotY(0.05);
        obj.update_mesh_shader();
        
    }if( key == GLFW_KEY_K && action == GLFW_REPEAT)
    {
        obj.rotZ(0.05);
        obj.update_mesh_shader();
    } if( key == GLFW_KEY_V && action == GLFW_REPEAT )
    {
        obj2.rotX(0.05);
        obj2.update_mesh_shader();
    }
    if (key == GLFW_KEY_R && action == GLFW_REPEAT)
    {
        cam.move(glm::vec3(0.0,1.0,0.0));
        cam.update_cam_shader();
    } if ((key == GLFW_KEY_T  && action == GLFW_REPEAT))
    {
        cam.move(glm::vec3(0.0,-1.0,0.0));
        cam.update_cam_shader();
    } if ((key == GLFW_KEY_G  && action == GLFW_REPEAT))
    {
        obj.translate(glm::vec3(0.0,-1.0,0.0));
        obj.update_mesh_shader();
    }if ((key == GLFW_KEY_B && action == GLFW_REPEAT))
    {
        obj.translate(glm::vec3(0.0,1.0,0.0));
        obj.update_mesh_shader();
    }
    
}



void prepare_light(Light& light , Shader& shade)
{
    shade.bind();
    light.set_shaderID(shade.program_id());
    
    std::string diffuse_name("ldiffuse");
    std::string specular_name("lspec");
    std::string ambient_name("lambient");
    std::string pos_name("lpos");
    
    
    light.set_am_name(ambient_name);
    light.set_diffuse_name(diffuse_name);
    light.set_spec_name(specular_name);
    light.set_position_name(pos_name);
    
    
    glm::vec3 diffuse(0.85, 0.85, 0.85 );
    glm::vec3 ambient(1.0,1.0,1.0);
    glm::vec3 specular(0.75, 0.75,0.75);
    glm::vec3 position(10000.0f,10000.0f,10000.0f);
    
    
    light.set_am_value(ambient);
    light.set_diffuse_value(diffuse);
    light.set_spec_value(specular);
    light.set_position(position);
    
    if(!light.update_shader())
    {
        std::cout << "CANNOT SET UP THE LIGHT SHADER" << std::endl;
    }
    shade.unbind();
    
}

void prepare_material(Material& material , Shader& shader)
{

    shader.bind();
    material.set_shaderID(shader.program_id());
    
    std::string mdiffuse_name("mdiffuse");
    std::string mspecular_name("mspecular");
    std::string mambient_name("mambient");
    std::string memission_name("memission");
    std::string mshine_name("mshine");
    
    material.set_diffuse_name(mdiffuse_name);
    material.set_specular_name(mspecular_name);
    material.set_ambient_name(mambient_name);
    material.set_emission_name(memission_name);
    material.set_shine_name(mshine_name);
    
    glm::vec3 diffuse(0.75164, 0.60648, 0.22648);
    glm::vec3 specular(0.6282,0.555802,0.366065);
    glm::vec3 ambient(0.24725, 0.1995 , 0.0745);
    glm::vec3 emission(0.0);
    float shine = 128.2f;
    
    
    material.set_diffuse_value(diffuse);
    material.set_specular_value(specular);
    material.set_ambient_value(ambient);
    material.set_emission_value(emission);
    material.set_shine_value(shine);
    
    if(!material.update_shader())
    {
        std::cout << "CANNOT SET UP MATERIAL SHADER" << std::endl;
    }
    shader.unbind();

}



int main(int argc, const char * argv[]) {
    
        if (!glfwInit()) {
            fprintf(stderr, "ERROR: could not start GLFW3\n");
            return 1;
        }
    
        GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
        if (!window) {
            fprintf(stderr, "ERROR: could not open window with GLFW3\n");
            glfwTerminate();
            return 1;
        }
        glfwMakeContextCurrent(window);
    
        glewExperimental = GL_TRUE;
        glewInit();
        
    
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);
        printf("Renderer: %s\n", renderer);
        printf("OpenGL version supported %s\n", version);
    
    
    
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    
    
    glfwSetKeyCallback(window, key_callback);
    
    //...................................................TEXTURES..............................................................
    
    
    Texture tex("/Users/ferifezino/Documents/opengl_projects/res/images/chalet.jpg", GL_TEXTURE0);
    Texture tex_two("/Users/ferifezino/Documents/opengl_projects/res/images/4096_normal.jpg", GL_TEXTURE1);
    Texture tex_three("/Users/ferifezino/Documents/opengl_projects/res/images/4096_night_lights.jpg", GL_TEXTURE2);
    
    //.................................................................................................................
    
    
    //.........................................SHADERS........................................................................
    
    
    Shader male_head_shader("/Users/ferifezino/documents/opengl_projects/gl_pro01/gl_pro01/face_shader.vert","/Users/ferifezino/documents/opengl_projects/gl_pro01/gl_pro01/face_shaderf.frag");
    
    Shader shade("/Users/ferifezino/documents/opengl_projects/gl_pro01/gl_pro01/test_vert_shader.vert","/Users/ferifezino/documents/opengl_projects/gl_pro01/gl_pro01/test_frag_shader.frag");
    
    
    //........................................................................................................................
    
    
    
    Vertex_buffer v_buf((unsigned char *)points , 9 * sizeof(float), GL_FLOAT , 3);
    Vertex_buffer tex_buf((unsigned char *)tex_coords, 6 * sizeof(float), GL_FLOAT, 2);
    Vertex_buffer ful_v_buf((unsigned char *)full_screen_vex_coords , 18 * sizeof(float), GL_FLOAT, 3);
    Vertex_buffer ful_t_buf((unsigned char *)full_screen_tex_coords, 12 * sizeof(float), GL_FLOAT , 2);
    
    
    Mesh array; //array is bound in the constructor
    array.generate();
    array.add_buffer(ful_v_buf, 0);
    array.add_buffer(ful_t_buf,1);
    array.setup_buffers();
    array.set_number_of_vertex(6);
    array.unbind();
    
    
    obj.generate();
    Tiny_obj_loader load(mesh_filepath , obj);
    obj.setup_buffers();
    

    Mesh obj2;
    obj2.generate();
    Tiny_obj_loader load2(z_filepath, obj2);
    obj2.setup_buffers();
    
    
    
    
    std::string te_s("tex_sam");
    std::string te_s_two("tex_sam_two");
    std::string te_s_three("tex_sam_three");
    Material mat;
    Light light;
    
    prepare_light(light, male_head_shader);
    prepare_material(mat, male_head_shader);

    male_head_shader.bind();
    
    tex.set_shader_programID(male_head_shader.program_id());
    tex.set_shader_sampler_name(te_s);
    tex.update_shader(0);
    
    
    tex_two.set_shader_programID(male_head_shader.program_id());
    tex_two.set_shader_sampler_name(te_s_two);
    tex_two.update_shader(1);
    
    
    tex_three.set_shader_programID(male_head_shader.program_id());
    tex_three.set_shader_sampler_name(te_s_three);
    tex_three.update_shader(2);
    
    
    cam.set_shader_programID(male_head_shader.program_id());
    cam.set_shader_proj_name(prog_name);
    cam.set_shader_view_name(view_name);
    cam.update_cam_shader();
    
    
    std::string matrix_name("model_matrix");
    std::string normal_matrix_name("normal_matrix");
    
    
    std::string capture_file("/Users/ferifezino/Documents/opengl_projects/res/images/capture_chalet.bmp");
    
    glm::mat4 model_m(1.0);
    //model_m = glm::scale(model_m, glm::vec3(0.05));
    //model_m = glm::translate(model_m, glm::vec3(0,0,-100));
    obj.set_shader_programID(male_head_shader.program_id());
    obj.set_shader_matrix_name(matrix_name);
    obj.set_noraml_matrix_name(normal_matrix_name);
    obj.set_model_matrix(model_m);
    
    obj2.set_shader_programID(male_head_shader.program_id());
    obj2.set_shader_matrix_name(matrix_name);
    obj2.set_noraml_matrix_name(normal_matrix_name);
    obj2.set_model_matrix(model_m);
    
    
    while(!glfwWindowShouldClose(window)) {
        
        
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);
     
     
        obj.bind();
        glm::mat3 n = glm::mat3(cam.get_view_mat());
        glm::mat3 m = glm::mat3(obj.get_model_matrix());
        glm::mat3 k = n * m;
        n = glm::transpose(glm::inverse(k));
        obj.set_normal_matrix(k);
        obj.update_mesh_shader();
        obj.setup_buffers();
        obj.draw();
        obj.unbind();
        
        obj2.bind();
        glm::mat3 n2 = glm::mat3(cam.get_view_mat());
        glm::mat3 m2 = glm::mat3(obj.get_model_matrix());
        glm::mat3 k2 = n2 * m2;
        n2 = glm::transpose(glm::inverse(k2));
        obj2.set_normal_matrix(k2);
        obj2.update_mesh_shader();
        obj2.setup_buffers();
        obj2.draw();
        obj2.unbind();
        
        
        
        
        if(glGetError() == GL_NO_ERROR)
        {
            std::cout << "GL RUNS WITH NO ERROR" <<  std::endl;
        }
        glfwPollEvents();
        
        glfwSwapBuffers(window);
    }
    
    
   // Screen_capture(capture_file, 640, 480);
    
    
    male_head_shader.unbind();
    tex.unbind();
    obj.unbind();
    
        glfwTerminate();
        return 0;

}
