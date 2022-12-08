/* File generated with Shader Minifier 1.3.1
 * http://www.ctrl-alt-test.fr
 */
#ifndef FXAA_FRAG_INL_
# define FXAA_FRAG_INL_

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 fragColor;"
 "uniform sampler2D prevPass;"
 "vec3 d(vec4 m,sampler2D z,vec2 d)"
 "{"
   "vec3 y=textureLod(z,m.zw,0.).xyz,v=textureLod(z,m.zw+vec2(1,0)*d.xy,0.).xyz,t=textureLod(z,m.zw+vec2(0,1)*d.xy,0.).xyz,a=textureLod(z,m.zw+vec2(1,1)*d.xy,0.).xyz,s=textureLod(z,m.xy,0.).xyz,x=vec3(.299,.587,.114);"
   "float w=dot(y,x),r=dot(v,x),p=dot(t,x),e=dot(a,x),o=dot(s,x),c=min(o,min(min(w,r),min(p,e))),u=max(o,max(max(w,r),max(p,e)));"
   "vec2 f;"
   "f.x=-(w+r-p-e);"
   "f.y=w+p-r-e;"
   "float n=1./(min(abs(f.x),abs(f.y))+1./128.);"
   "f=min(vec2(8.,8.),max(vec2(-8.,-8.),f*n))*d.xy;"
   "vec3 g=.5*(textureLod(z,m.xy+f*(1./3.-.5),0.).xyz+textureLod(z,m.xy+f*(2./3.-.5),0.).xyz),i=g*.5+.25*(textureLod(z,m.xy+f*-.5,0.).xyz+textureLod(z,m.xy+f*.5,0.).xyz);"
   "float L=dot(i,x);"
   "if(L<c||L>u)"
     "return g;"
   "return i;"
 "}"
 "void main()"
 "{"
   "vec2 x=1./vec2(1280.,720.),z=gl_FragCoord.xy*x;"
   "vec4 y=vec4(z,z-x*.5);"
   "vec3 w=d(y,prevPass,x);"
   "fragColor=vec4(w,1.);"
 "}";

#endif // FXAA_FRAG_INL_
