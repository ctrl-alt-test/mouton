/* File generated with Shader Minifier 1.3.1
 * http://www.ctrl-alt-test.fr
 */
#ifndef POSTPROCESS_FRAG_INL_
# define POSTPROCESS_FRAG_INL_

const char *postprocess_frag =
 "#version 150\n"
 "out vec4 fragColor;"
 "uniform sampler2D prevPass;"
 "uniform float iTime;"
 "vec3 t(vec3 p)"
 "{"
   "uvec3 v=uvec3(p*1e5);"
   "v=(v>>8U^v.yzx)*1103515245U;"
   "v=(v>>8U^v.yzx)*1103515245U;"
   "v=(v>>8U^v.yzx)*1103515245U;"
   "return vec3(v)*(1./float(-1U))-.5;"
 "}"
 "float p(vec3 v)"
 "{"
   "vec3 p=floor(v+dot(v,vec3(.3333333))),d=v-p+dot(p,vec3(.1666667)),x=step(vec3(0.),d-d.yzx),y=x*(1.-x.zxy),i=1.-x.zxy*(1.-x),s=d-y+.1666667,z=d-i+.3333334,e=d-1.+.5000001;"
   "vec4 f,r;"
   "f.x=dot(d,d);"
   "f.y=dot(s,s);"
   "f.z=dot(z,z);"
   "f.w=dot(e,e);"
   "f=max(.6-f,0.);"
   "r.x=dot(t(p),d);"
   "r.y=dot(t(p+y),s);"
   "r.z=dot(t(p+i),z);"
   "r.w=dot(t(p+1.),e);"
   "f*=f;"
   "f*=f;"
   "r*=f;"
   "return dot(r,vec4(52.));"
 "}"
 "void main()"
 "{"
   "vec2 v=1./vec2(1280.,720.),x=gl_FragCoord.xy*v,d=(x*2.-1.)*v.x*.5;"
   "vec3 f;"
   "f.x=texture(prevPass,x+d).x;"
   "f.y=texture(prevPass,x).y;"
   "f.z=texture(prevPass,x-d).z;"
   "vec3 y=vec3(p(vec3(gl_FragCoord.xy*v.y*250.,iTime*5.)));"
   "float s=dot(f,vec3(.2126,.7152,.0722));"
   "f+=y*(1.-pow(s,.5))*.05;"
   "f*=smoothstep(0.,10.,iTime);"
   "f=mix(f,vec3(1.),smoothstep(158.,160.,iTime));"
   "fragColor=vec4(f,1.);"
 "}";

#endif // POSTPROCESS_FRAG_INL_
