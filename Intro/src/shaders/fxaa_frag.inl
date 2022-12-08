/* File generated with Shader Minifier 1.2
 * http://www.ctrl-alt-test.fr
 */
#ifndef FXAA_FRAG_INL_
# define FXAA_FRAG_INL_

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 fragColor;\n"
 "#define iResolution vec2(1280.,720.)\n"
 "uniform sampler2D prevPass;"
 "vec3 d(vec4 m,sampler2D v,vec2 d)"
 "{"
   "vec3 y=textureLod(v,m.zw,0.).xyz,z=textureLod(v,m.zw+vec2(1,0)*d.xy,0.).xyz,t=textureLod(v,m.zw+vec2(0,1)*d.xy,0.).xyz,a=textureLod(v,m.zw+vec2(1,1)*d.xy,0.).xyz,s=textureLod(v,m.xy,0.).xyz,x=vec3(.299,.587,.114);"
   "float w=dot(y,x),r=dot(z,x),n=dot(t,x),p=dot(a,x),e=dot(s,x),o=min(e,min(min(w,r),min(n,p))),c=max(e,max(max(w,r),max(n,p)));"
   "vec2 f;"
   "f.x=-(w+r-(n+p));"
   "f.y=w+n-(r+p);"
   "float i=1./(min(abs(f.x),abs(f.y))+1./128.);"
   "f=min(vec2(8.,8.),max(vec2(-8.,-8.),f*i))*d.xy;"
   "vec3 g=.5*(textureLod(v,m.xy+f*(1./3.-.5),0.).xyz+textureLod(v,m.xy+f*(2./3.-.5),0.).xyz),u=g*.5+.25*(textureLod(v,m.xy+f*-.5,0.).xyz+textureLod(v,m.xy+f*.5,0.).xyz);"
   "float l=dot(u,x);"
   "if(l<o||l>c)"
     "return g;"
   "return u;"
 "}"
 "void main()"
 "{"
   "vec2 x=1./iResolution,v=gl_FragCoord.xy*x;"
   "vec4 y=vec4(v,v-x*.5);"
   "vec3 z=d(y,prevPass,x);"
   "fragColor=vec4(z,1.);"
 "}";

#endif // FXAA_FRAG_INL_
