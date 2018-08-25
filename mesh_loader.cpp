//
//  mesh_loader.cpp
//  gl_pro01
//
//  Created by ferife zino  on 09/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "mesh_loader.hpp"

Mesh_loader::Mesh_loader(std::string& filename , Mesh& obj , bool only_vert)
: draw_only_vert(only_vert){
    m_file_to_parse.open(filename);
    if(!m_file_to_parse.is_open())
    {
        std::cout << "CANNOT OPEN OBJ FILE TO PARSE"  << std::endl;
        return;
    }
    parse_obj();
    
    debug_normal();
    if(!only_vert)
    {
    Vertex_buffer vert((unsigned char * ) temp_vert.data() , sizeof(glm::vec3) * temp_vert.size() , GL_FLOAT , 3);
    
    std::cout <<" Vertex count: "<<temp_vert.size() << std::endl;
    std::cout <<" Texture coords: " <<temp_uvs.size() << std::endl;
    std::cout <<"Normal count: " <<temp_normal.size() << std::endl;
    
    
     Vertex_buffer norml((unsigned char * ) temp_normal.data() , sizeof(glm::vec3) * temp_normal.size() , GL_FLOAT , 3);
     Index_buffer index((unsigned char * )temp_index.data() , (sizeof(unsigned short) * temp_index.size()), temp_index.size());
    
    
    
    obj.add_buffer(vert, 0);
    obj.add_buffer(norml, 1);
    obj.add_index_buf(index);
    
    if(has_uv)
    {
        Vertex_buffer uv_b((unsigned char * ) temp_uvs.data() , sizeof(glm::vec3) * temp_uvs.size() , GL_FLOAT , 2);
        obj.add_buffer(uv_b, 2);
    }
  
    }else
    {
        //arrange the vertex array coording to the index
        std::vector<glm::vec3> new_vert(temp_vert.size());
        for(int i = 0; i < temp_vert.size(); i++)
        {
            new_vert[i] = temp_vert[index_vert[i]];
        }
        temp_vert = new_vert;
        
        
        //load the data into the mesh
        Vertex_buffer vert((unsigned char * ) temp_vert.data() , sizeof(glm::vec3) * temp_vert.size() , GL_FLOAT , 3);
        
        std::cout <<" Vertex count: "<<temp_vert.size() << std::endl;
        std::cout <<" Texture coords: " <<temp_uvs.size() << std::endl;
        std::cout <<"Normal count: " <<temp_normal.size() << std::endl;
        
        
        Vertex_buffer norml((unsigned char * ) temp_normal.data() , sizeof(glm::vec3) * temp_normal.size() , GL_FLOAT , 3);
        Index_buffer index((unsigned char * )temp_index.data() , (sizeof(unsigned short) * temp_index.size()), temp_index.size());
        
        
        
        obj.add_buffer(vert, 0);
        obj.add_buffer(norml, 1);
        obj.add_index_buf(index);
        
        if(has_uv)
        {
            Vertex_buffer uv_b((unsigned char * ) temp_uvs.data() , sizeof(glm::vec3) * temp_uvs.size() , GL_FLOAT , 2);
            obj.add_buffer(uv_b, 2);
        }
    }
    
    //do not set up buffers allow the mesh do that
}



//all obj parsing happens here and the data is placed in the temp buffers
// the file is already open


void Mesh_loader::parse_vert(std::string line)
{
    std::istringstream s(line.substr(2));
    glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;
    temp_vert.push_back(v);
}



void Mesh_loader::parse_norm(std::string line)
{
    std::istringstream n(line.substr(3));
    glm::vec3 no;
    n >> no.x;
    n >> no.y;
    n >>  no.z;
    temp_normal.push_back(no);

}




void Mesh_loader::parse_index(std::string line)
{
    //issue !!
    std::istringstream s(line.substr(2));
    
    bool sim_flag = false;
    bool com_flag = false;
    
    //check how many indices is preset. if 1 : contains only vertex , if 2 , contains vertext and uv if 3 contains vertex, uv and normal;
    std::string l2;
    s >> l2;
    for(int i = 0; i < l2.size(); i++)
    {
        if(l2[i] == '/')
        {
            com_flag = true;
            break;
        }
    }
    if(!com_flag)
    {
        sim_flag = true;
    }
    s.seekg(std::ios::beg);
    
    
    
    if(com_flag)
    {
        std::string vertex1 , vertex2 , vertex3;
        
        s >> vertex1;
        s >> vertex2;
        s >> vertex3;
        
        std::istringstream stream1(vertex1);
        std::istringstream stream2(vertex2);
        std::istringstream stream3(vertex3);
       
        std::string tok1 , tok2 , tok3;
        unsigned short c[3];
        int j = 0;
        
        while (std::getline(stream1 , tok1 , '/'))
        {
            unsigned short i = (unsigned short)std::stoi(tok1);
            c[j] = --i;
            j++;
        }
        index_vert.push_back(c[0]);
        index_uv.push_back(c[1]);
        index_norm.push_back(c[2]);
        
        j = 0;
        while (std::getline(stream2 , tok2 , '/'))
        {
            unsigned short i = std::stoi(tok2);
            c[j] = --i;
            j++;
        }
        index_vert.push_back(c[0]);
        index_uv.push_back(c[1]);
        index_norm.push_back(c[2]);
        
        j = 0;
        while (std::getline(stream3 , tok3 , '/'))
        {
            unsigned short i = std::stoi(tok3);
            c[j] = --i;
            j++;
        }
        index_vert.push_back(c[0]);
        index_uv.push_back(c[1]);
        index_norm.push_back(c[2]);

    }
    if(sim_flag)
    {
        unsigned short a,b,c;
        s >> a; s >> b; s >> c;
        a--; b--; c--;
        temp_index.push_back(a);
        temp_index.push_back(b);
        temp_index.push_back(c);
    }

}

void Mesh_loader::parse_uv(std::string line)
{
    std::istringstream u(line.substr(3));
    glm::vec2 uv_;
    
    u >> uv_.x;
    u >> uv_.y;
    temp_uvs.push_back(uv_);
}


bool Mesh_loader::parse_obj()
{
    
     has_normal = false;
     has_uv = false;
    std::string line;
    while(std::getline(m_file_to_parse, line))
    {
        if (line.substr(0,2) == "v ")
        {
            parse_vert(line);
        }
        else if (line.substr(0,2) == "f ")
        {
            parse_index(line);
        }
        else if(line.substr(0,3) == "vn ")
        {
            has_normal = true;
            parse_norm(line);
        }
        else if(line.substr(0,3) == "vt ")
        {
            has_uv = true;
            parse_uv(line);
        }
        
        else if (line[0] == '#')
        {
            /* ignoring this line */
        }
        else
        {
            /* ignoring this line */
        }
        
    }
    
    if(!has_normal)
    {
        temp_normal.resize(temp_vert.size(), glm::vec3(0.0, 0.0, 0.0));
        for (int i = 0; i < temp_vert.size(); i+=3)
        {
            unsigned short ia = temp_index[i];
            unsigned short ib = temp_index[i+1];
            unsigned short ic = temp_index[i+2];
            glm::vec3 normal = glm::normalize(glm::cross(
                                                         glm::vec3(temp_vert[ib]) - glm::vec3(temp_vert[ia]),
                                                         glm::vec3(temp_vert[ic]) - glm::vec3(temp_vert[ia])));
            temp_normal[ia] = temp_normal[ib] = temp_normal[ic] = normal;
        }
        
    }
    
    if(!index_vert.empty())
    {
        std::vector<glm::vec3> _normal(temp_vert.size());
        std::vector<glm::vec2> _uvs(temp_vert.size());
        
        for(int i = 0; i < index_vert.size(); i++)
        {
            _normal[index_vert[i]] = temp_normal[index_norm[i]];
            _uvs[index_vert[i]] = temp_uvs[index_uv[i]];
        }
        
        temp_normal = _normal;
        temp_uvs = _uvs;
        temp_index = index_vert;
    }

    return true;
}


void Mesh_loader::debug_normal()
{
    std::vector<glm::vec3>::iterator iter;
    std::cout << std::endl;
    std::cout << "\t\t PRINTING NORMALS \t\t" << std::endl;
    for(iter = temp_normal.begin(); iter != temp_normal.end(); iter++)
    {
        
        std::cout << iter->x << iter->y << iter->z << "\n";
    }
    std::cout << std::endl;
}


