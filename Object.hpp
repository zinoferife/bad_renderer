//
//  Object.hpp
//  gl_pro01
//
//  Created by ferife zino  on 25/08/2018.
//  Copyright © 2018 practice. All rights reserved.
//

#ifndef Object_hpp
#define Object_hpp

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "mesh.hpp"



class Object : public Mesh
{
public:
    Object();
    void draw();


private:
        
    
};



#endif /* Object_hpp */
