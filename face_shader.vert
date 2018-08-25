/* 
  face_shader.vert
  gl_pro01

  Created by ferife zino  on 20/06/2018.
  Copyright © 2018 practice. All rights reserved.
*/
#version 120


attribute vec3 vp;
attribute vec3 norm;
attribute vec2 tc;

varying vec3 vert_pos;
varying vec2 t_c;
varying vec3 norm_var;


//light varying
varying vec3 F_lightpos;
varying vec3 F_lightdiffuse;
varying vec3 F_lightspecular;
varying vec3 F_lightambient;

//material varying
varying vec3 F_mdiffuse;
varying vec3 F_mambient;
varying vec3 F_mspecular;
varying vec3 F_memission;
varying float F_mshine;


uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

//light unifrom
uniform vec3 lpos;
uniform vec3 ldiffuse;
uniform vec3 lspec;
uniform vec3 lambient;



//material unifrom
uniform vec3 mdiffuse;
uniform vec3 mambient;
uniform vec3 mspecular;
uniform vec3 memission;
uniform float mshine;

void main()
{
    vec4 pos = view_matrix * model_matrix * vec4(vp, 1.0);
    F_lightpos = (view_matrix * vec4(lpos, 1.0)).xyz;
  
    F_lightambient = lambient;
    F_lightdiffuse = ldiffuse;
    F_lightspecular = lspec;
    
    F_mdiffuse = mdiffuse;
    F_mambient = mambient;
    F_mspecular = mspecular;
    F_memission = memission;
    F_mshine = mshine;
     
    vert_pos = pos.xyz;
    t_c = tc;
    norm_var = normal_matrix * norm;
    gl_Position = proj_matrix *  pos;
}
