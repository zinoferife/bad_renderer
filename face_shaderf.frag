/* 
  face_shaderf.frag
  gl_pro01

  Created by ferife zino  on 20/06/2018.
  Copyright © 2018 practice. All rights reserved.
*/

//vertex postion and normal in view space
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




uniform sampler2D tex_sam;
uniform sampler2D tex_sam_two;
uniform sampler2D tex_sam_three;



void main()
{
    
 // vec3 nn = texture2D(tex_sam_two , t_c).xyz;
    
    
  vec3 n = normalize(norm_var);
  vec3  v = normalize(-vert_pos);
  vec3 l = normalize((F_lightpos - vert_pos ));
  vec3 r = normalize(reflect( -l , n ));
    
    
    
    float diffuse_co = max(dot(n,l),0.0);
    float specular_co = pow(max(dot(v,r),0.0), F_mshine);
    
    vec4 tex_color = texture2D(tex_sam , t_c);
    vec4 tex_three_color = vec4(0.0);
    vec3 limit = vec3(-10.0);
    
    //for the earth render, too lasy to write another fragment file
    
    /*
    if(vert_pos.x  < limit.x || vert_pos.y < limit.y ||  vert_pos.z < limit.z )
        tex_three_color = vec4(0.0);
    else
        tex_three_color = texture2D(tex_sam_three , t_c);
     */
    
    
    vec3 tex_col = tex_color.xyz;
    
    vec3 e = F_memission;
    vec3 color = (F_lightambient * F_mambient) + (F_lightdiffuse * F_mdiffuse * diffuse_co ) + ( F_lightspecular * F_mspecular * specular_co );
    gl_FragColor = vec4( color , 1.0);
    
}