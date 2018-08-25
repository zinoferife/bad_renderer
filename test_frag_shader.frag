#version 120

varying vec2 t_c;
//varying vec3 norm_var;
uniform sampler2D tex_sam;
uniform sampler2D tex_sam_two;

void main()
{
    vec4 col = vec4(1.0,1.0,0.0,1.0);
    vec3 lightpos = vec3(0.0,0.0,1.0);
    //float d = dot(lightpos, normalize(norm_var));
    gl_FragColor = mix(texture2D(tex_sam , t_c), col, 0.0);
}