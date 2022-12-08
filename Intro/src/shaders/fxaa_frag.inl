/* File generated with Shader Minifier 1.3.1
 * http://www.ctrl-alt-test.fr
 */
#ifndef FXAA_FRAG_INL_
# define FXAA_FRAG_INL_

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 fragColor;"
 "const vec2 y=vec2(1280.,720.);"
 "uniform sampler2D prevPass;"
 "vec3 d(vec4 y,sampler2D v,vec2 d)"
 "{"
   "vec3 z=textureLod(v,y.zw,0.).xyz,m=textureLod(v,y.zw+vec2(1,0)*d.xy,0.).xyz,t=textureLod(v,y.zw+vec2(0,1)*d.xy,0.).xyz,a=textureLod(v,y.zw+vec2(1,1)*d.xy,0.).xyz,s=textureLod(v,y.xy,0.).xyz,x=vec3(.299,.587,.114);"
   "float w=dot(z,x),r=dot(m,x),p=dot(t,x),e=dot(a,x),o=dot(s,x),c=min(o,min(min(w,r),min(p,e))),u=max(o,max(max(w,r),max(p,e)));"
   "vec2 f;"
   "f.x=-(w+r-p-e);"
   "f.y=w+p-r-e;"
   "float n=1./(min(abs(f.x),abs(f.y))+1./128.);"
   "f=min(vec2(8.,8.),max(vec2(-8.,-8.),f*n))*d.xy;"
   "vec3 g=.5*(textureLod(v,y.xy+f*(1./3.-.5),0.).xyz+textureLod(v,y.xy+f*(2./3.-.5),0.).xyz),i=g*.5+.25*(textureLod(v,y.xy+f*-.5,0.).xyz+textureLod(v,y.xy+f*.5,0.).xyz);"
   "float L=dot(i,x);"
   "if(L<c||L>u)"
     "return g;"
   "return i;"
 "}"
 "void main()"
 "{"
   "vec2 x=1./y,v=gl_FragCoord.xy*x;"
   "vec4 z=vec4(v,v-x*.5);"
   "vec3 w=d(z,prevPass,x);"
   "fragColor=vec4(w,1.);"
 "}";

#endif // FXAA_FRAG_INL_
