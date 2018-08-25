#version 120

attribute vec3 vp;
//attribute vec3 norm;
attribute vec2 tc;

varying vec2 t_c;
//varying vec3 norm_var;

uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

void main()
{
    vec4 pos = proj_matrix * view_matrix * model_matrix * vec4( vp , 1.0 );
    t_c = tc;
    //norm_var = norm;
    gl_Position = pos;
}
