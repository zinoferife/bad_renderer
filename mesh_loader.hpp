//
//  mesh_loader.hpp
//  gl_pro01
//
//  Created by ferife zino  on 09/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef mesh_loader_hpp
#define mesh_loader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>



#include <GL/glew.h>
#include <openGL/gl.h>
#include <glm/glm.hpp>


#include "mesh.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"


class Mesh_loader
{
private:
    std::ifstream m_file_to_parse;
    
    std::vector<glm::vec3> temp_vert;
    std::vector<glm::vec3> temp_normal;
    std::vector<glm::vec2> temp_uvs;
    std::vector<unsigned short> temp_index;
    
    
    std::vector<unsigned short> index_vert;
    std::vector<unsigned short> index_norm;
    std::vector<unsigned short> index_uv;
    
    
    
    //individal parsers to parse each segment of the obj file
    void parse_vert(std::string line);
    void parse_norm(std::string line);
    void parse_index(std::string line);
    void parse_uv(std::string line);
    
    void debug_normal();
    
    
    //the current mesh obj file
    bool has_normal;
    bool has_uv;
    bool draw_only_vert;
    
public:
    Mesh_loader(std::string& filename , Mesh& obj, bool only_vert);
    bool parse_obj();
};


#endif /* mesh_loader_hpp */
