/* File generated with Shader Minifier 1.2
 * http://www.ctrl-alt-test.fr
 */
#ifndef FXAA_FRAG_INL_
# define FXAA_FRAG_INL_

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 fragColor;\n"
 "#define iResolution vec2(1280.,720.)\n"
 "uniform sampler2D prevPass;\n"
 "#define FXAA_SPAN_MAX 8.0\n"
 "#define FXAA_REDUCE_MUL (1.0/FXAA_SPAN_MAX)\n"
 "#define FXAA_REDUCE_MIN (1.0/128.0)\n"
 "#define FXAA_SUBPIX_SHIFT (1.0/8.0)\n"
 "vec3 d(vec4 m,sampler2D v,vec2 F)"
 "{"
   "vec3 y=textureLod(v,m.zw,0.).xyz,z=textureLod(v,m.zw+vec2(1,0)*F.xy,0.).xyz,t=textureLod(v,m.zw+vec2(0,1)*F.xy,0.).xyz,X=textureLod(v,m.zw+vec2(1,1)*F.xy,0.).xyz,a=textureLod(v,m.xy,0.).xyz,x=vec3(.299,.587,.114);"
   "float d=dot(y,x),w=dot(z,x),s=dot(t,x),r=dot(X,x),n=dot(a,x),p=min(n,min(min(d,w),min(s,r))),L=max(n,max(max(d,w),max(s,r)));"
   "vec2 f;"
   "f.x=-(d+w-(s+r));"
   "f.y=d+s-(w+r);"
   "float i=max((d+w+s+r)*(.25*FXAA_REDUCE_MUL),FXAA_REDUCE_MIN),N=1./(min(abs(f.x),abs(f.y))+i);"
   "f=min(vec2(FXAA_SPAN_MAX,FXAA_SPAN_MAX),max(vec2(-FXAA_SPAN_MAX,-FXAA_SPAN_MAX),f*N))*F.xy;"
   "vec3 g=.5*(textureLod(v,m.xy+f*(1./3.-.5),0.).xyz+textureLod(v,m.xy+f*(2./3.-.5),0.).xyz),e=g*.5+.25*(textureLod(v,m.xy+f*-.5,0.).xyz+textureLod(v,m.xy+f*.5,0.).xyz);"
   "float A=dot(e,x);"
   "if(A<p||A>L)"
     "return g;"
   "return e;"
 "}"
 "void main()"
 "{"
   "vec2 x=1./iResolution,v=gl_FragCoord.xy*x;"
   "vec4 y=vec4(v,v-x*(.5+FXAA_SUBPIX_SHIFT));"
   "vec3 z=d(y,prevPass,x);"
   "fragColor=vec4(z,1.);"
 "}";

#endif // FXAA_FRAG_INL_
