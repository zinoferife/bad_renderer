//
//  ting_obj_loader.hpp
//  gl_pro01
//
//  Created by ferife zino  on 10/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef ting_obj_loader_hpp
#define ting_obj_loader_hpp

#include <stdio.h>
#include <tiny_obj_loader.h>
#include <vector>


#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "mesh.hpp"

class Tiny_obj_loader
{
private:

    //tiny obj objects
    tinyobj::attrib_t attib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    
    //temp buffers for processing
    std::vector<glm::vec3> temp_vert;
    std::vector<glm::vec3> temp_norm;
    std::vector<glm::vec2> temp_uv;
    
    //check if it has normal or uv
    bool has_normal;
    bool has_uv;
    
    
    std::string m_erro_str;
    std::string m_filename;
    void parse_obj();
    void debug_normal();
    bool make_normals();
public:
    Tiny_obj_loader(std::string& filename , Mesh& obj);
    
    

};



#endif /* ting_obj_loader_hpp */
