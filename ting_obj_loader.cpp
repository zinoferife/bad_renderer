//
//  ting_obj_loader.cpp
//  gl_pro01
//
//  Created by ferife zino  on 10/06/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#include "ting_obj_loader.hpp"


Tiny_obj_loader::Tiny_obj_loader(std::string& filename , Mesh &obj)
: has_normal(false) , has_uv(false)
{
    bool ret = tinyobj::LoadObj(&attib, &shapes, &materials, &m_erro_str, filename.c_str());
 
    if(!ret)
    {
        std::cout << "CANNOT LOAD INTO TINY OBJ"  << m_erro_str <<std::endl;
        return;
    }
    parse_obj();
    //remaining the index;
    //debug_normal();
    
    Vertex_buffer vert_buf((unsigned char*)temp_vert.data(),sizeof(glm::vec3) * temp_vert.size() ,GL_FLOAT, 3);
    obj.add_buffer(vert_buf, 0);
    
    if(has_normal)
    {
        Vertex_buffer norm_buf((unsigned char*)temp_norm.data(), sizeof(glm::vec3) * temp_norm.size(), GL_FLOAT ,3);
        obj.add_buffer(norm_buf, 1);
    }else
    {
        std::cout << "MAKING NORMALS" << std::endl;
        make_normals();
        Vertex_buffer norm_buf((unsigned char*)temp_norm.data(), sizeof(glm::vec3) * temp_norm.size(), GL_FLOAT ,3);
        obj.add_buffer(norm_buf, 1);
    }
    
    if(has_uv)
    {
        Vertex_buffer tex_buf((unsigned char *)temp_uv.data(), sizeof(glm::vec2) * temp_uv.size(), GL_FLOAT ,2);
        obj.add_buffer(tex_buf, 2);
    }
    
    obj.set_number_of_vertex(temp_vert.size());
}


bool Tiny_obj_loader::make_normals()
{
    if(temp_vert.empty())
    {
        return false;
    }
    temp_norm.resize(temp_vert.size());
    glm::vec3 vertex1, vertex2 , vertex3;
    for(int i = 0; i < temp_vert.size(); i+= 3)
    {
        vertex1 =  temp_vert[i];
        vertex2 = temp_vert[i+1];
        vertex3 = temp_vert[i+2];
     
        glm::vec3 a = vertex1 - vertex2;
        glm::vec3 b = vertex1 - vertex3;
        
        glm::vec3 normal = glm::cross(a, b);
        temp_norm[i] = temp_norm[i+1] = temp_norm[i+2] = normal;
    }
    return true;
}


void Tiny_obj_loader::debug_normal()
{
    std::vector<glm::vec3>::iterator iter;
    std::cout << std::endl;
    std::cout << "\t\t PRINTING NORMALS \t\t" << std::endl;
    for(iter = temp_norm.begin(); iter != temp_norm.end(); iter++)
    {
       
        glm::vec3 n = glm::normalize(*iter);
        std::cout << n.x <<" "<< n.y <<" "<< n.z << "\n";
    }
    std::cout << std::endl;
}

void Tiny_obj_loader::parse_obj()
{
    
    glm::vec3 vert;
    glm::vec3 norm;
    glm::vec2 tex;
    
    
    for(size_t i = 0; i < shapes.size(); i++)
    {
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[i].mesh.num_face_vertices[f];
            for(int j = 0; j < fv; j++)
            {
                tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + j];
                
                vert.x = attib.vertices[3*idx.vertex_index + 0];
                vert.y = attib.vertices[3*idx.vertex_index + 1];
                vert.z = attib.vertices[3*idx.vertex_index + 2];
                
                if(idx.normal_index >= 0)
                {
                    norm.x = attib.normals[3* idx.normal_index +0];
                    norm.y = attib.normals[3* idx.normal_index +1];
                    norm.z = attib.normals[3* idx.normal_index +2];
                    has_normal = true;
                    
                    temp_norm.push_back(norm);
                }
                
                if(idx.texcoord_index >= 0)
                {
                    tex.x = attib.texcoords[2* idx.texcoord_index +0];
                    //flip the y tex coords, to align with opengl
                    tex.y = 1.0f - attib.texcoords[2* idx.texcoord_index +1];
                    temp_uv.push_back(tex);
                    has_uv = true;
                }
                
                
                temp_vert.push_back(vert);
            }
            
            index_offset += fv;
        }
    }
}