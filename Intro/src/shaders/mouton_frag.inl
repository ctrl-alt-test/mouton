/* File generated with Shader Minifier 1.2
 * http://www.ctrl-alt-test.fr
 */
#ifndef MOUTON_FRAG_INL_
# define MOUTON_FRAG_INL_

const char *mouton_frag =
 "#version 150\n"
 "out vec4 fragColor;"
 "const vec2 v=vec2(1280.,720.);"
 "in vec3 animationAmp,animationSpeed;"
 "in vec2 headRot;"
 "in vec3 sheepPos,panelPos,flowerPos,panelWarningPos,anvilPos,sunDir,camPos,camTa;"
 "in float camFocal,blink;"
 "in vec3 eyeDir;"
 "in float eyesSurprise,excited,fishEyeFactor,noseSize;"
 "uniform float iTime;"
 "const float y=3.141592653589,m=0.,s=1.,x=2.,f=3.,a=4.,z=5.,l=6.,c=7.,p=8.,e=9.,i=10.,r=11.,d=12.;"
 "vec2 n(vec2 v,vec2 y)"
 "{"
   "return v.x<y.x?v:y;"
 "}"
 "vec2 h(vec2 v,float f)"
 "{"
   "float y=atan(v.y,v.x),s=length(v);"
   "y=mod(y-f/2.,f)-f/2.;"
   "return vec2(cos(y),sin(y))*s;"
 "}"
 "vec2 h(in vec3 v,in vec3 x,vec3 y,vec3 m)"
 "{"
   "vec3 z=m*v,s=abs(m)*y,i=-z-s,f=-z+s;"
   "float d=max(max(i.x,i.y),i.z),e=min(min(f.x,f.y),f.z);"
   "if(d>e||e<0.)"
     "return vec2(-1.);"
   "return vec2(d,e);"
 "}"
 "float h(float v)"
 "{"
   "return fract(sin(v)*43758.5453123);"
 "}"
 "vec3 n(vec3 v)"
 "{"
   "uvec3 i=uvec3(v*1e5);"
   "const uint y=1103515245U;"
   "i=(i>>8U^i.yzx)*y;"
   "i=(i>>8U^i.yzx)*y;"
   "i=(i>>8U^i.yzx)*y;"
   "return vec3(i)*(1./float(-1U));"
 "}"
 "vec3 h(vec3 v,vec2 m,float y)"
 "{"
   "vec3 f=vec3(1.);"
   "float i=max(dot(v,sunDir),0.);"
   "f+=vec3(1.,.7,.3)*pow(i,1.);"
   "f+=vec3(1.,.5,.1)*pow(i,52.);"
   "f=vec3(1.)*y*y;"
   "vec2 x=vec2(cos(iTime*.7+2.3),sin(iTime*.7+2.3)*.75);"
   "float r=smoothstep(.201,.2,length(m-x));"
   "r*=smoothstep(.2,.201,length(m-x-vec2(.1,.025)));"
   "r+=smoothstep(2.,0.,length(m-x))*.02;"
   "r*=smoothstep(.5,0.,sunDir.y);"
   "vec2 z=m*200.,s=fract(z)-.5,d=floor(z);"
   "vec3 a=n(vec3(abs(d),abs(d.x)));"
   "float l=a.z*.1;"
   "r+=smoothstep(l,l*.01,length(s+(a.xy-.5)))*(cos(iTime*3.*a.y+a.z*3.14)*.5+.5)*2.;"
   "f+=r*smoothstep(.5,-1.,sunDir.y);"
   "return f;"
 "}"
 "float t(float v)"
 "{"
   "return fract(v*17.*fract(v*.3183099));"
 "}"
 "float w(in vec3 v)"
 "{"
   "vec3 m=floor(v),s=fract(v),y=s*s*s*(s*(s*6.-15.)+10.);"
   "float i=m.x+317.*m.y+157.*m.z,x=t(i),f=t(i+1.),a=t(i+317.),z=t(i+318.),l=t(i+157.),e=t(i+158.),p=t(i+474.),k=t(i+475.),d=x,c=f-x,r=a-x,n=l-x,u=x-f-a+z,b=x-a-l+p,T=x-f-l+e,h=-x+f+a-z+l-e-p+k;"
   "return-1.+2.*(d+c*y.x+r*y.y+n*y.z+u*y.x*y.y+b*y.y*y.z+T*y.z*y.x+h*y.x*y.y*y.z);"
 "}"
 "vec2 u(vec3 v)"
 "{"
   "v.xz-=anvilPos.xz;"
   "v.y-=-anvilPos.y;"
   "float y=v.y+smoothstep(1.,20.,length(v.xz));"
   "if(y<.4)"
     "return vec2(y-(w(v*3.5)*.5+.5)*.3,d);"
   "else"
     " return vec2(9999.,m);"
 "}"
 "mat3 t(vec3 v,vec3 y)"
 "{"
   "const vec3 i=vec3(0.,1.,0.);"
   "vec3 x=normalize(y-v),s=normalize(cross(x,normalize(i)));"
   "return mat3(s,cross(s,x),x);"
 "}"
 "mat2 g(float v)"
 "{"
   "float y=cos(v),x=sin(v);"
   "return mat2(y,x,-x,y);"
 "}"
 "float g(vec3 v,vec3 y)"
 "{"
   "vec3 i=abs(v)-y;"
   "return length(max(i,0.))+min(max(i.x,max(i.y,i.z)),0.);"
 "}"
 "vec2 b(vec3 v)"
 "{"
   "v-=anvilPos;"
   "float y=pow(clamp(v.y-1.,0.,1.),.5),f=g(v-vec3(0.,1.,0.),vec3(1.5-y,1.,2.5-y));"
   "if(f<10.)"
     "{"
       "f=min(f,g(v-vec3(0.,3.,0.),vec3(2.,1.,3.)));"
       "float i=length((v.yz-vec2(4.5,3.))*vec2(1.,.8))-2.;"
       "i=max(i,abs(v.x)-.5);"
       "i=max(i,v.y-3.5);"
       "f=min(f,i);"
       "vec2 x=vec2(f-.1,r);"
       "return x;"
     "}"
   "else"
     " return vec2(9999999.,m);"
 "}"
 "float b(vec3 v,float y,float x,float i)"
 "{"
   "vec2 s=vec2(length(v.xz),v.y),f=vec2(i,y),z=vec2(i-x,2.*y),d=vec2(s.x-min(s.x,s.y<0.?x:i),abs(s.y)-y),m=s-f+z*clamp(dot(f-s,z)/dot(z,z),0.,1.);"
   "float r=m.x<0.&&d.y<0.?-1.:1.;"
   "return r*sqrt(min(dot(d,d),dot(m,m)));"
 "}"
 "float g(in vec3 v,in vec2 m,in float y,in float x)"
 "{"
   "v.x=abs(v.x);"
   "float i=m.y*v.x>m.x*v.y?dot(v.xy,m):length(v.xy);"
   "return sqrt(dot(v,v)+y*y-2.*y*i)-x;"
 "}"
 "float n(vec3 v,vec3 x,vec3 m,float y)"
 "{"
   "vec3 i=v-x,s=m-x;"
   "float z=clamp(dot(i,s)/dot(s,s),0.,1.);"
   "return length(i-s*z)-y;"
 "}"
 "float b(vec3 v,vec2 y)"
 "{"
   "vec2 i=vec2(length(v.xy)-y.x,v.z);"
   "return length(i)-y.y;"
 "}"
 "float u(vec3 v,vec3 y)"
 "{"
   "float i=length(v/y),s=length(v/(y*y));"
   "return i*(i-1.)/s;"
 "}"
 "vec2 o(vec3 v)"
 "{"
   "v-=flowerPos;"
   "vec3 f=v;"
   "f.x+=cos(.775+iTime)*3.1*.2;"
   "f.y-=2.8;"
   "f.zy=g(.75)*f.zy;"
   "float x=u(f-vec3(0.,.3,0.),vec3(1.,.2+cos(f.x*150.)*sin(f.z*150.)*.05,1.)*.25);"
   "if(x<5.)"
     "{"
       "vec2 s=vec2(x,p);"
       "vec3 r=f;"
       "r.xz=h(r.xz,y*.2);"
       "float z=u(r-vec3(.5,.2+sin(r.x*2.)*.15,0.),vec3(2.,.1+sin(r.z*50.)*.02,.75)*.25);"
       "if(z<s.x)"
         "s=vec2(z,e);"
       "float d=max(length(v.xz+vec2(cos(v.y*.25+iTime)*v.y*.2,-.075))-smoothstep(3.1,0.,v.y)*.1-.02,v.y-3.1);"
       "if(d<s.x)"
         "s=vec2(d,i);"
       "return s;"
     "}"
   "return vec2(999999.,m);"
 "}"
 "float b(float v,float i,float y)"
 "{"
   "float x=clamp(.5+.5*(i-v)/y,0.,1.);"
   "return mix(i,v,x)-y*x*(1.-x);"
 "}"
 "float g(float v,float x,float y)"
 "{"
   "y*=1.4;"
   "float i=max(y-abs(v-x),0.);"
   "return max(v,x)+i*i*i/(6.*y*y);"
 "}"
 "vec2 P(vec3 v)"
 "{"
   "v-=panelPos;"
   "float i=g(v-vec3(0.,7.5,-5.),vec3(1.,1.,.1));"
   "if(i<7.)"
     "{"
       "i=g(i,-g(v-vec3(0.,7.5,-5.1),vec3(.9,.9,.1)),.001);"
       "float f=g(v-vec3(0.,4.,-5.1),vec3(.1,4.,.1));"
       "vec3 y=v;"
       "y.y=abs(y.y-7.3)-.3;"
       "f=min(f,g(y-vec3(0.,0.,-5.05),vec3(.35,.1,.05)));"
       "vec2 x=vec2(f,z);"
       "x=n(x,vec2(i,c));"
       "return x;"
     "}"
   "else"
     " return vec2(999999.,m);"
 "}"
 "vec2 T(vec3 v)"
 "{"
   "v-=sheepPos;"
   "float i=mod(iTime,1.);"
   "i=smoothstep(0.,1.,abs(i*2.-1.));"
   "v.y-=1.;"
   "v.z-=-2.;"
   "float z=iTime*animationSpeed.x;"
   "vec3 m=vec3(cos(z*y),cos(z*y*2.)*.1,0.)*.025*animationAmp.x;"
   "float r=length(v*vec3(1.,1.,.825)-vec3(0.,1.5,2.55)-m)-2.;"
   "if(r<3.)"
     "{"
       "float e=pow(w((v-m-.1)*2.)*.5+.5,.75)*2.-1.;"
       "r=r+.05-e*.2;"
       "float l=mod(iTime*animationSpeed.x,2.);"
       "vec4 d=vec4(0.),c=vec4(0.);"
       "float p=smoothstep(0.,.5,l),k=smoothstep(.5,1.,l),t=smoothstep(1.,1.5,l),S=smoothstep(1.5,2.,l);"
       "d.z=p*(1.-p);"
       "d.x=k*(1.-k);"
       "d.w=t*(1.-t);"
       "d.y=S*(1.-S);"
       "c+=l*.5;"
       "c.x-=k;"
       "c.z-=p;"
       "c.y-=S;"
       "c.w-=t;"
       "c*=animationAmp.x;"
       "vec3 u=v;"
       "u.x-=.8;"
       "u.z-=2.+c.x;"
       "u.yz=g(d.x)*u.yz;"
       "float h=b(u-vec3(0.,0.,0.),.7,.3,.2),T=b(u-vec3(0.,-.8,0.),.2,.35,.3);"
       "u=v;"
       "u.x+=1.;"
       "u.z-=2.+c.y;"
       "u.yz=g(d.y)*u.yz;"
       "h=min(h,b(u-vec3(0.,0.,0.),.7,.3,.2));"
       "T=min(T,b(u-vec3(0.,-.8,0.),.2,.35,.3));"
       "u=v;"
       "u.x-=1.;"
       "u.z-=4.+c.z;"
       "u.yz=g(d.z)*u.yz;"
       "h=min(h,b(u-vec3(0.,0.,0.),.7,.3,.2));"
       "T=min(T,b(u-vec3(0.,-.8,0.),.2,.35,.3));"
       "u=v;"
       "u.x+=1.;"
       "u.z-=4.+c.w;"
       "u.yz=g(d.w)*u.yz;"
       "h=min(h,b(u-vec3(0.,0.,0.),.7,.3,.2));"
       "T=min(T,b(u-vec3(0.,-.8,0.),.2,.35,.3));"
       "vec3 o=v+vec3(0.,-2.,-1.2);"
       "o.xz=g((i*animationSpeed.y-.5)*.25*animationAmp.y+headRot.x)*o.xz;"
       "o.zy=g(sin(iTime*animationSpeed.y)*.25*animationAmp.y-headRot.y)*o.zy;"
       "float P=length(o-vec3(0.,-1.3,-1.2))-1.;"
       "P=b(P,length(o-vec3(0.,0.,0.))-.5,1.8);"
       "vec3 D=o;"
       "D.yz=g(-.6)*D.yz;"
       "D.x=abs(v.x)-.8;"
       "D*=vec3(.3,1.,.4);"
       "D-=vec3(0.,-.05-pow(D.x,2.)*5.,-.1);"
       "float A=length(D)-.15;"
       "A=g(A,-(length(D-vec3(0.,-.1,0.))-.12),.01);"
       "D=o;"
       "D.x=abs(o.x)-.4;"
       "float U=length(D*vec3(1.,1.,1.-eyesSurprise)-vec3(0.,0.,-1.))-.3;"
       "D.x=abs(o.x)-.2;"
       "D.xz=g(-.45)*D.xz;"
       "float F=b(D-vec3(-.7,-1.2,-2.),vec2(.15*noseSize,.05));"
       "D=v;"
       "D*=vec3(.7,1.,.7);"
       "float W=length(D-vec3(0.,2.4,.7))-.4;"
       "W=b(W,n(v-vec3(0.,0.,cos(v.y-.7)*.5),vec3(cos(iTime*animationSpeed.z)*animationAmp.z,.2,5.),vec3(0.,2.,4.9),.2),.2);"
       "W-=(pow(w(v*2.)*.5+.5,.75)*2.-1.)*.1;"
       "vec2 R=vec2(r,s);"
       "R=n(R,vec2(W,s));"
       "R=n(R,vec2(h,x));"
       "R=n(R,vec2(P,x));"
       "R=n(R,vec2(U,f));"
       "R=n(R,vec2(F,x));"
       "R=n(R,vec2(T,a));"
       "R=n(R,vec2(A,x));"
       "return R;"
     "}"
   "else"
     " return vec2(r,s);"
 "}"
 "float P(vec3 v,vec2 y,float x)"
 "{"
   "vec3 i=abs(v);"
   "return max(i.z-y.y,g(g(v.x*.866025+v.y*.5,-v.x*.866025+v.y*.5,x),-v.y,x)-y.x*.5);"
 "}"
 "vec2 k(vec3 v)"
 "{"
   "v-=panelWarningPos;"
   "float i=P(v-vec3(0.,7.5,-5.),vec2(1.7,.1),.3);"
   "if(i<8.)"
     "{"
       "i=g(i,-P(v-vec3(0.,7.5,-5.1),vec2(1.6,.1),.3),.001);"
       "float f=g(v-vec3(0.,4.,-5.1),vec3(.1,4.,.1));"
       "vec3 y=v;"
       "y.y=abs(y.y-7.3)-.3;"
       "f=min(f,g(y-vec3(0.,0.,-5.05),vec3(.35,.1,.05)));"
       "vec2 x=vec2(f,z);"
       "x=n(x,vec2(i,l));"
       "return x;"
     "}"
   "else"
     " return vec2(999999.,m);"
 "}"
 "vec2 S(vec3 v)"
 "{"
   "vec2 i=vec2(v.y,m);"
   "i=n(i,T(v));"
   "i=n(i,o(v));"
   "i=n(i,P(v));"
   "i=n(i,k(v));"
   "i=n(i,b(v));"
   "i=n(i,u(v));"
   "return i;"
 "}"
 "float P(in vec3 v,in vec3 y,float i,float x)"
 "{"
   "float f=0.,s=1.;"
   "const int m=2;"
   "for(int r=1;r<=m;r++)"
     "{"
       "float z=float(r)/m*i,l=S(v+z*y).x;"
       "f+=(z-l)*s;"
       "s*=.95;"
     "}"
   "return max(0.,1.-x*1.5*f);"
 "}"
 "float P(vec3 v,vec3 y)"
 "{"
   "vec3 i=1./y;"
   "float x=9999.;"
   "vec2 f=h(v-sheepPos-vec3(0.,3.,-2.),y,vec3(3.,3.,7.),i);"
   "if(f.y>0.)"
     "{"
       "float s=max(f.x,0.);"
       "for(int r=0;r<128;r++)"
         "{"
           "vec3 d=v+y*s;"
           "float z=n(vec2(d.y,m),T(d)).x;"
           "s+=z;"
           "if(s>f.y)"
             "break;"
           "if(abs(z)<.001)"
             "break;"
         "}"
       "if(s<f.y)"
         "x=s;"
     "}"
   "{"
     "vec2 d=h(v-panelPos-vec3(0.,5.,-5.),y,vec3(1.5,5.,1.),i);"
     "if(d.y>0.)"
       "{"
         "float s=max(d.x,0.);"
         "for(int r=0;r<128;r++)"
           "{"
             "float z=P(v+y*s).x;"
             "s+=z;"
             "if(s>d.y)"
               "break;"
             "if(abs(z)<.001)"
               "break;"
           "}"
         "if(s<d.y)"
           "x=min(x,s);"
       "}"
   "}"
   "{"
     "vec2 d=h(v-panelWarningPos-vec3(0.,5.,-5.),y,vec3(1.5,5.,1.),i);"
     "if(d.y>0.)"
       "{"
         "float s=max(d.x,0.);"
         "for(int r=0;r<128;r++)"
           "{"
             "float z=k(v+y*s).x;"
             "s+=z;"
             "if(s>d.y)"
               "break;"
             "if(abs(z)<.001)"
               "break;"
           "}"
         "if(s<d.y)"
           "x=min(x,s);"
       "}"
   "}"
   "{"
     "vec2 d=h(v-flowerPos-vec3(0.,5.,0.),y,vec3(2.,5.,1.),i);"
     "if(d.y>0.)"
       "{"
         "float s=max(d.x,0.);"
         "for(int r=0;r<128;r++)"
           "{"
             "float z=o(v+y*s).x;"
             "s+=z;"
             "if(s>d.y)"
               "break;"
             "if(abs(z)<.001)"
               "break;"
           "}"
         "if(s<d.y)"
           "x=min(x,s);"
       "}"
   "}"
   "{"
     "vec2 d=h(v-anvilPos-vec3(0.,3.,2.),y,vec3(2.2,3.,5.2),i);"
     "if(d.y>0.)"
       "{"
         "float s=max(d.x,0.);"
         "for(int r=0;r<128;r++)"
           "{"
             "float z=b(v+y*s).x;"
             "s+=z;"
             "if(s>d.y)"
               "break;"
             "if(abs(z)<.001)"
               "break;"
           "}"
         "if(s<d.y)"
           "x=min(x,s);"
       "}"
   "}"
   "{"
     "float s=-(v.y+.4)*i.y;"
     "if(s>0.&&length((v+y*s).xz-anvilPos.xz)<10.)"
       "{"
         "float r=-s;"
         "for(int z=0;z<128;z++)"
           "{"
             "vec3 d=v+y*r;"
             "float l=min(d.y,u(d).x);"
             "r+=l;"
             "if(r>100.)"
               "break;"
             "if(abs(l)<.001)"
               "break;"
           "}"
         "if(r<100.)"
           "x=min(x,r);"
       "}"
   "}"
   "{"
     "float s=-v.y*i.y;"
     "if(s>0.)"
       "x=min(x,s);"
   "}"
   "return x;"
 "}"
 "float S(vec3 v,vec3 y,vec2 m)"
 "{"
   "float i=m.x;"
   "for(int f=0;f<128;f++)"
     "{"
       "float x=S(v+y*i).x;"
       "i+=x;"
       "if(i>m.y)"
         "break;"
       "if(abs(x)<.001)"
         "break;"
     "}"
   "return i;"
 "}"
 "vec3 D(vec3 v)"
 "{"
   "vec2 y=vec2(1e-4,0.);"
   "float m=S(v).x;"
   "vec3 i;"
   "i.x=m-S(v-y.xyy).x;"
   "i.y=m-S(v-y.yxy).x;"
   "i.z=m-S(v-y.yyx).x;"
   "return normalize(i);"
 "}"
 "float D(vec3 v,vec3 y,float x,float i)"
 "{"
   "float f=1.,s=x;"
   "for(int r=0;r<64;r++)"
     "{"
       "float m=S(v+y*s).x;"
       "f=min(f,30.*m/s);"
       "s+=m;"
       "if(f<1e-4||s>i)"
         "break;"
     "}"
   "return clamp(f,0.,1.);"
 "}"
 "float S(vec2 v,float i,float x,float y)"
 "{"
   "v.x=abs(v.x);"
   "float s=(i-x)/y,f=sqrt(1.-s*s),d=dot(v,vec2(-s,f));"
   "if(d<0.)"
     "return length(v)-i;"
   "if(d>f*y)"
     "return length(v-vec2(0.,y))-x;"
   "return dot(v,vec2(f,s))-i;"
 "}"
 "vec3 D(vec3 v,vec3 y,vec3 n,vec3 u,vec2 R)"
 "{"
   "vec2 b=S(n);"
   "float k=smoothstep(0.,.3,sunDir.y)+.1,T=P(n,u,.15,1.);"
   "T*=P(n,u,1.,.1)*.5;"
   "float o=D(n,sunDir,.08,50.),t=clamp(1.+dot(y,u),0.,1.);"
   "vec3 W=vec3(1.,.8,.7)*max(dot(u,sunDir),0.)*pow(vec3(o),vec3(1.,1.5,2.)),A=vec3(1.,.8,.7)*.1*max(dot(u,-sunDir),0.)*T,w=vec3(.5)*P(n,y,.3,.5),U=vec3(1.)*max(dot(reflect(y,u),sunDir),0.),F=vec3(.4,.45,.5)*T,C=vec3(0.),q=vec3(0.);"
   "if(b.y==m)"
     "q=vec3(3.),w=vec3(0.),U=vec3(0.);"
   "else"
     " if(b.y==s)"
       "q=vec3(.4),w*=vec3(1.)*(t*.5+.5),C=vec3(.35),U=pow(U,vec3(4.))*t*.5;"
     "else"
       " if(b.y==a)"
         "q=vec3(.025),w=vec3(0.),U=vec3(0.);"
       "else"
         " if(b.y==f)"
           "{"
             "w*=.7;"
             "q=vec3(1.);"
             "float E=dot(u,normalize(vec3(0.,0.,1.))),Z=dot(u,eyeDir);"
             "q*=smoothstep(-.953,-.952,Z-eyesSurprise/2.);"
             "if(E>0.||blink>.95)"
               "b.y=x;"
             "U=pow(U,vec3(80.))*t;"
           "}"
         "else"
           " if(b.y==z)"
             "q=vec3(1.),w=vec3(0.),U=pow(U,vec3(8.))*t*2.;"
           "else"
             " if(b.y==l)"
               "{"
                 "vec3 E=n-panelWarningPos;"
                 "w=vec3(0.);"
                 "U=pow(U,vec3(8.))*t*2.;"
                 "if(u.z>.5)"
                   "{"
                     "q=vec3(1.5,0.,0.);"
                     "float Z=P(E-vec3(0.,7.5,-5.),vec2(1.3,.2),.01),Y=smoothstep(.15,.1495,distance(E,vec3(0.,7.1,-4.9)));"
                     "Y+=smoothstep(.005,0.,S(E.xy-vec2(0.,7.4),.06,.12,1.));"
                     "q=mix(q,vec3(1.5),smoothstep(.005,0.,Z));"
                     "q=mix(q,vec3(0.),Y);"
                   "}"
                 "else"
                   " q=vec3(1.);"
               "}"
             "else"
               " if(b.y==c)"
                 "{"
                   "vec3 E=n-panelPos;"
                   "w=vec3(0.);"
                   "U=pow(U,vec3(8.))*t*2.;"
                   "if(u.z>.5)"
                     "{"
                       "q=vec3(0.,0.,1.5);"
                       "E.y-=7.4;"
                       "float Z=g(E-vec3(0.,.1,-5.),vec3(.8,.8,1)),Y=0.;"
                       "E.xy=g(.8)*E.xy;"
                       "float X=.04;"
                       "Y+=smoothstep(.01,0.,S(E.xy-vec2(-X,-.6),.1,.05,1.));"
                       "Y+=smoothstep(.01,0.,S(E.xy-vec2(-X,.5),.16,.135,.15));"
                       "Y*=smoothstep(0.,.01,S(E.xy-vec2(-X-.08,.56),.001,.02,.2));"
                       "Y*=smoothstep(0.,.01,S(E.xy-vec2(-X+.04,.56),.001,.02,.2));"
                       "E.xy=g(-1.6)*E.xy;"
                       "Y+=smoothstep(.01,0.,S(E.xy-vec2(X,-.6),.1,.05,1.));"
                       "Y+=smoothstep(.01,0.,S(E.xy-vec2(X,.5),.16,.1,.15));"
                       "q=mix(q,vec3(1.5),smoothstep(.01,0.,Z));"
                       "q=mix(q,vec3(0.),Y);"
                     "}"
                   "else"
                     " q=vec3(1.);"
                 "}"
               "else"
                 " if(b.y==p)"
                   "{"
                     "vec3 E=n-flowerPos;"
                     "E.x+=cos(.775+iTime)*3.1*.2;"
                     "E.y-=2.8;"
                     "E.zy=g(.75)*E.zy;"
                     "q=mix(vec3(2.,.75,0.),vec3(2.,2.,0.),smoothstep(0.,.45,length(E-vec3(0.,.3,0.))))*2.;"
                     "w=vec3(.01);"
                     "U=vec3(0.);"
                   "}"
                 "else"
                   " if(b.y==i)"
                     "q=vec3(0.,.1,0.),w*=vec3(1.),U*=vec3(1.)*t;"
                   "else"
                     " if(b.y==e)"
                       "{"
                         "vec3 E=n-flowerPos;"
                         "E.x+=cos(.775+iTime)*3.1*.2;"
                         "E.y-=2.8;"
                         "E.zy=g(.75)*E.zy;"
                         "q=mix(vec3(1.,1.,1.)+.5,vec3(.75,.5,1.),smoothstep(.6,1.,length(E-vec3(0.,.3,0.))))*2.;"
                         "w*=0.;"
                         "U=pow(U,vec3(4.))*t;"
                       "}"
                     "else"
                       " if(b.y==r)"
                         "q=vec3(1.),W*=vec3(.25)*t,F*=vec3(.25)*t,A*=vec3(.25)*t,w=vec3(0.),U=pow(U,vec3(8.))*t*2.;"
                       "else"
                         " if(b.y==d)"
                           "{"
                             "q=vec3(1.,.01,.01);"
                             "float E=t*t;"
                             "W*=vec3(1.)*E;"
                             "F*=vec3(1.)*E;"
                             "A*=vec3(1.)*E;"
                             "w=vec3(0.);"
                             "U=pow(U,vec3(32.))*500.;"
                           "}"
   "if(b.y==x)"
     "q=vec3(1.,.7,.5),w=pow(w,vec3(.5,2.5,8.)+2.)*2.,U=pow(U,vec3(4.))*t*.02;"
   "vec3 E=(q*(F+W*.5+A*2.+w*2.+U*o)+C)*k;"
   "float Z=length(n-v);"
   "E=mix(E,h(y,R,k),smoothstep(90.,100.,Z));"
   "if(b.y==m)"
     "{"
       "float Y=cos(atan(R.x,R.y)*15.+iTime),X=length(R)*.3;"
       "E=mix(E,mix(vec3(1.,.5,0),vec3(1.,1.,1.),smoothstep(-X,X,Y)),excited);"
     "}"
   "return clamp(E,0.,1.);"
 "}"
 "float D(in vec2 v,in float x,in float y)"
 "{"
   "const vec2 i=vec2(.809016994375,-.587785252292),s=vec2(-i.x,i.y);"
   "v.x=abs(v.x);"
   "v-=2.*max(dot(i,v),0.)*i;"
   "v-=2.*max(dot(s,v),0.)*s;"
   "v.x=abs(v.x);"
   "v.y-=x;"
   "vec2 f=y*vec2(-i.y,i.x)-vec2(0,1);"
   "float z=clamp(dot(v,f)/dot(f,f),0.,x);"
   "return length(v-f*z)*sign(v.y*f.x-v.x*f.y);"
 "}"
 "void main()"
 "{"
   "vec2 y=vec2(1.)/v,s=gl_FragCoord.xy*y,i=s*2.-1.;"
   "i.x*=v.x*y.y;"
   "vec3 x=camPos,f=camTa,z=t(x,f)*normalize(vec3(i,camFocal-length(i)*fishEyeFactor));"
   "float r=P(x,z);"
   "vec3 d=x+z*r,U=D(d),u=D(x,z,d,U,i);"
   "{"
     "vec2 E=i*5.;"
     "E.x=abs(E.x)-1.5;"
     "E.y-=1.4;"
     "E=g(iTime*5.)*E;"
     "u=mix(u,mix(vec3(1.,.8,.1),vec3(1.),smoothstep(-.1,.5,i.y)),smoothstep(0.,-.01,D(E,1.7,.5))*excited);"
   "}"
   "u*=smoothstep(0.,10.,iTime);"
   "u=mix(u,vec3(1.),smoothstep(163.,165.,iTime));"
   "u/=1.+pow(length(i),3.)*.1;"
   "fragColor=vec4(pow(u,vec3(1./2.2)),1.);"
 "}";

#endif // MOUTON_FRAG_INL_
