/* File generated with Shader Minifier 1.3.1
 * http://www.ctrl-alt-test.fr
 */
#ifndef POSTPROCESS_FRAG_INL_
# define POSTPROCESS_FRAG_INL_

const char *postprocess_frag =
 "#version 150\n"
 "out vec4 fragColor;\n"
 "#define iResolution vec2(1280.,720.)\n"
 "uniform sampler2D prevPass;"
 "uniform float iTime;"
 "vec3 t(vec3 v)"
 "{"
   "uvec3 x=uvec3(v*1e5);"
   "x=(x>>8U^x.yzx)*1103515245U;"
   "x=(x>>8U^x.yzx)*1103515245U;"
   "x=(x>>8U^x.yzx)*1103515245U;"
   "return vec3(x)*(1./float(-1U))-.5;"
 "}"
 "float v(vec3 v)"
 "{"
   "vec3 x=floor(v+dot(v,vec3(.3333333))),d=v-x+dot(x,vec3(.1666667)),y=step(vec3(0.),d-d.yzx),i=y*(1.-y.zxy),z=1.-y.zxy*(1.-y),s=d-i+.1666667,p=d-z+.3333334,e=d-1.+.5000001;"
   "vec4 f,r;"
   "f.x=dot(d,d);"
   "f.y=dot(s,s);"
   "f.z=dot(p,p);"
   "f.w=dot(e,e);"
   "f=max(.6-f,0.);"
   "r.x=dot(t(x),d);"
   "r.y=dot(t(x+i),s);"
   "r.z=dot(t(x+z),p);"
   "r.w=dot(t(x+1.),e);"
   "f*=f;"
   "f*=f;"
   "r*=f;"
   "return dot(r,vec4(52.));"
 "}"
 "void main()"
 "{"
   "vec2 x=1./iResolution,d=gl_FragCoord.xy*x,y=(d*2.-1.)*x.x*.5;"
   "vec3 f;"
   "f.x=texture(prevPass,d+y).x;"
   "f.y=texture(prevPass,d).y;"
   "f.z=texture(prevPass,d-y).z;"
   "vec3 t=vec3(v(vec3(gl_FragCoord.xy*x.y*250.,iTime*5.)));"
   "float s=dot(f,vec3(.2126,.7152,.0722));"
   "f+=t*(1.-pow(s,.5))*.05;"
   "f*=smoothstep(0.,10.,iTime);"
   "f=mix(f,vec3(1.),smoothstep(158.,160.,iTime));"
   "fragColor=vec4(f,1.);"
 "}";

#endif // POSTPROCESS_FRAG_INL_
