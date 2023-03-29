// Generated with Shader Minifier 1.3.5 (https://github.com/laurentlb/Shader_Minifier/)
#ifndef SHADERS_INL_
# define SHADERS_INL_
# define VAR_a_position "X"
# define VAR_animationAmp "m"
# define VAR_animationSpeed "s"
# define VAR_anvilPos "r"
# define VAR_blink "b"
# define VAR_camFocal "n"
# define VAR_camPos "c"
# define VAR_camTa "a"
# define VAR_excited "k"
# define VAR_eyeDir "d"
# define VAR_eyesSurprise "p"
# define VAR_fishEyeFactor "o"
# define VAR_flowerPos "x"
# define VAR_fragColor "f"
# define VAR_headRot "l"
# define VAR_iTime "t"
# define VAR_noseSize "w"
# define VAR_panelPos "z"
# define VAR_panelWarningPos "i"
# define VAR_sheepPos "y"
# define VAR_sunDir "e"
# define VAR_tex "L"

const char *mouton_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 v=vec2(1280,720);"
 "in vec3 m,s,y,x,z,i,r,e,c,a,d;"
 "in vec2 l,k;"
 "in float b,n,p,o,w;"
 "uniform float t;"
 "const float g=acos(-1.);"
 "float u=0.;"
 "vec2 h(vec2 i,vec2 y)"
 "{"
   "return i.x<y.x?"
     "i:"
     "y;"
 "}"
 "vec2 h(vec3 i,vec3 x,vec3 s,vec3 v)"
 "{"
   "vec3 y=v*i,c=abs(v)*s,m=-y-c,d=-y+c;"
   "float a=max(max(m.x,m.y),m.z),n=min(min(d.x,d.y),d.z);"
   "return a>n||n<0.?"
     "vec2(-1):"
     "vec2(a,n);"
 "}"
 "float h(vec3 v,vec3 i,float y)"
 "{"
   "float m=max(dot(v,normalize(i+v)),0.),d=2e4/(1.+y),x=30./(1.+y);"
   "return(pow(m,d)*(d+2.)+pow(m,x)*(x+2.)*2.)*.041;"
 "}"
 "vec3 h(vec3 v)"
 "{"
   "uvec3 y=uvec3((v+1e2)*1e4);"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "return vec3(y)*(1./float(-1U));"
 "}"
 "float C(vec3 v)"
 "{"
   "vec3 y=floor(v),m=fract(v);"
   "m=m*m*m*(m*(m*6.-15.)+10.);"
   "return mix(mix(mix(h(y+vec3(0)).x,h(y+vec3(1,0,0)).x,m.x),mix(h(y+vec3(0,1,0)).x,h(y+vec3(1,1,0)).x,m.x),m.y),mix(mix(h(y+vec3(0,0,1)).x,h(y+vec3(1,0,1)).x,m.x),mix(h(y+vec3(0,1,1)).x,h(y+vec3(1)).x,m.x),m.y),m.z)*2.-1.;"
 "}"
 "vec2 B(vec3 v)"
 "{"
   "v.xz-=r.xz;"
   "v.y-=-r.y;"
   "float y=v.y+smoothstep(1.,20.,length(v.xz));"
   "return y<.4?"
     "(y-=pow((C(v*.7+1.)*.5+C(v*1.7+1e2)*.3+C(v*2.7+1e2)*.1)*.5+.5,3.)*.45*(1.-exp((-t+150.)*4.))+.03,vec2(y,12)):"
     "vec2(9e7,0);"
 "}"
 "mat3 B(vec3 v,vec3 y)"
 "{"
   "vec3 x=normalize(y-v),m=normalize(cross(x,normalize(vec3(0,1,0))));"
   "return mat3(m,cross(m,x),x);"
 "}"
 "mat2 A(float v)"
 "{"
   "float y=cos(v),x=sin(v);"
   "return mat2(y,x,-x,y);"
 "}"
 "vec3 A(vec3 i,vec2 v,float y)"
 "{"
   "vec3 f=vec3(y*y);"
   "vec2 x=vec2(cos(t*.7+2.4),sin(t*.7+2.4)*.75);"
   "float m=smoothstep(.151,.15,length(v-x));"
   "vec2 d=A(t*2e-4)*v*2e2,s=floor(d);"
   "vec3 c=h(vec3(abs(s),abs(s.x)));"
   "float a=c.z*.06;"
   "f+=m*smoothstep(.13,.2701,length(v-x-vec2(.05))+.004*C(1e2*vec3(v-x,0)))*vec3(1,.9,.1)*smoothstep(.5,-1.,e.y);"
   "f+=smoothstep(a,a*.01,length(fract(d)-.5+(c.xy-.5)))*(1.-m);"
   "f+=exp(-length(v-x)*2.)*.1;"
   "return f;"
 "}"
 "float A(vec3 v,vec3 y)"
 "{"
   "vec3 m=abs(v)-y;"
   "return length(max(m,0.))+min(max(m.x,max(m.y,m.z)),0.);"
 "}"
 "vec2 D(vec3 v)"
 "{"
   "v-=r;"
   "v.xz=A(1.)*v.xz;"
   "float y=pow(clamp(v.y-1.,.004,1.),.5),f=A(v-vec3(0,1,0),vec3(1.5-y,1,2.5-y));"
   "if(f<10.)"
     "{"
       "f=min(f,A(v-vec3(0,3,0),vec3(2,1,3)));"
       "float m=length((v.yz-vec2(4.5,3))*vec2(1,.8))-2.;"
       "m=max(m,abs(v.x)-.5);"
       "m=max(m,v.y-3.5);"
       "f=min(f,m);"
       "vec2 i=vec2(f-.1,11);"
       "return i;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "vec2 E(vec3 v)"
 "{"
   "v-=z;"
   "float y=A(v-vec3(0,7.5,-5),vec3(.8,.8,.1))-.2;"
   "if(y<7.)"
     "{"
       "y=max(y,abs(v.z+5.)-.1);"
       "float m=A(v-vec3(0,4,-5.1),vec3(.11,4,.08));"
       "vec2 i=vec2(m,5);"
       "i=h(i,vec2(y,7));"
       "return i;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "float A(vec3 v,float x,float i,float y)"
 "{"
   "vec2 m=vec2(length(v.xz),v.y),d=vec2(y,x),t=vec2(y-i,2.*x),s=vec2(m.x-min(m.x,m.y<0.?"
     "i:"
     "y),abs(m.y)-x),c=m-d+t*clamp(dot(d-m,t)/dot(t,t),0.,1.);"
   "return(c.x<0.&&s.y<0.?"
     "-1.:"
     "1.)*sqrt(min(dot(s,s),dot(c,c)));"
 "}"
 "float B(vec3 v,vec3 x,vec3 m,float y)"
 "{"
   "vec3 i=v-x,t=m-x;"
   "return length(i-t*clamp(dot(i,t)/dot(t,t),0.,1.))-y;"
 "}"
 "float C(vec3 v,vec2 y)"
 "{"
   "return length(vec2(length(v.xy)-y.x,v.z))-y.y;"
 "}"
 "float D(vec3 v,vec3 y)"
 "{"
   "float m=length(v/y);"
   "return m*(m-1.)/length(v/(y*y));"
 "}"
 "vec2 F(vec3 v)"
 "{"
   "v-=x;"
   "vec3 m=v;"
   "m.x+=cos(.775+t)*3.1*.2;"
   "m.y-=2.8;"
   "m.zy=A(.7)*m.zy;"
   "float y=D(m-vec3(0,.3,0),vec3(1,.2+cos(m.x*150.)*sin(m.z*150.)*.05,1)*.25);"
   "if(y<5.)"
     "{"
       "vec2 i=vec2(y,8);"
       "vec3 f=m;"
       "const float s=g*.2;"
       "float d=atan(f.z,f.x),c=length(f.xz);"
       "d=mod(d-s/2.,s)-s/2.;"
       "f.xz=vec2(cos(d),sin(d))*c;"
       "float a=D(f-vec3(.5,.2+sin(f.x*2.)*.2,0),vec3(2,.1+sin(f.z*40.)*.02,.75)*.25);"
       "if(a<i.x)"
         "i=vec2(a,9);"
       "float n=max(length(v.xz+vec2(cos(v.y*.25+t)*v.y*.2+.02,-.1))-smoothstep(3.1,0.,v.y)*.05-.02,v.y-3.1);"
       "if(n<i.x)"
         "i=vec2(n,10);"
       "return i;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "float B(float v,float y,float x)"
 "{"
   "float m=clamp(.5+.5*(y-v)/x,0.,1.);"
   "return mix(y,v,m)-x*m*(1.-m);"
 "}"
 "float C(float v,float x,float y)"
 "{"
   "y*=1.4;"
   "float m=max(y-abs(v-x),0.);"
   "return max(v,x)+m*m*m/(6.*y*y);"
 "}"
 "vec2 G(vec3 v)"
 "{"
   "v-=y;"
   "float i=mod(t,1.);"
   "i=smoothstep(0.,1.,abs(i*2.-1.));"
   "v.y-=1.;"
   "v.z-=-2.;"
   "float d=t*s.x;"
   "vec3 x=vec3(cos(d*g),cos(d*g*2.)*.1,0)*.025*m.x;"
   "float f=length(v*vec3(1,1,.825)-vec3(0,1.5,2.55)-x)-2.;"
   "if(f<3.)"
     "{"
       "float a=pow(C((v-x+vec3(.05,0,0))*2.)*.5+.5,.75)*2.-1.;"
       "f=f+.05-a*.2;"
       "float c=mod(t*s.x,2.),z=smoothstep(0.,.5,c),n=smoothstep(.5,1.,c),e=smoothstep(1.,1.5,c),r=smoothstep(1.5,2.,c);"
       "vec4 k=vec4(n*(1.-n),r*(1.-r),z*(1.-z),e*(1.-e)),o=c*.5-vec4(n,r,z,e);"
       "o*=m.x;"
       "vec3 D=v;"
       "D.x-=.8;"
       "D.z-=2.+o.x;"
       "D.yz=A(k.x)*D.yz;"
       "float E=A(D-vec3(0),.7,.3,.2),G=A(D-vec3(0,-.8,0),.2,.35,.3);"
       "D=v;"
       "D.x+=1.;"
       "D.z-=2.+o.y;"
       "D.yz=A(k.y)*D.yz;"
       "E=min(E,A(D-vec3(0),.7,.3,.2));"
       "G=min(G,A(D-vec3(0,-.8,0),.2,.35,.3));"
       "D=v;"
       "D.x-=1.;"
       "D.z-=4.+o.z;"
       "D.yz=A(k.z)*D.yz;"
       "E=min(E,A(D-vec3(0),.7,.3,.2));"
       "G=min(G,A(D-vec3(0,-.8,0),.2,.35,.3));"
       "D=v;"
       "D.x+=1.;"
       "D.z-=4.+o.w;"
       "D.yz=A(k.w)*D.yz;"
       "E=min(E,A(D-vec3(0),.7,.3,.2));"
       "G=min(G,A(D-vec3(0,-.8,0),.2,.35,.3));"
       "vec3 I=v+vec3(0,-2,-1.2);"
       "I.xz=A((i*s.y-.5)*.25*m.y+l.x)*I.xz;"
       "I.zy=A(sin(t*s.y)*.25*m.y-l.y)*I.zy;"
       "float F=length(I-vec3(0,-1.3,-1.2))-1.;"
       "F=B(F,length(I-vec3(0))-.5,1.8);"
       "vec3 H=I;"
       "H*=vec3(.7,1,.7);"
       "float J=length(I-vec3(0,.35,-.1))-.55;"
       "J-=(cos(I.z*8.+I.y*4.5+I.x*4.)+cos(I.z*4.+I.y*6.5+I.x*8.))*.05;"
       "J=B(J,f,.1);"
       "H=I;"
       "H.yz=A(-.6)*H.yz;"
       "H.x=abs(v.x)-.8;"
       "H*=vec3(.3,1,.4);"
       "H-=vec3(0,-.05-pow(H.x,2.)*5.,-.1);"
       "float K=length(H)-.15;"
       "K=C(K,-length(H-vec3(0,-.1,0))+.12,.01);"
       "H.y*=.3;"
       "H.y-=-.11;"
       "float L=length(H)-.16;"
       "H=I;"
       "H.x=abs(I.x)-.4;"
       "float U=length(H*vec3(1,1,1.-p)-vec3(0,0,-1))-.3,M=abs(U)-.01;"
       "M=C(M,B(-abs(I.y+I.z*.025)+.25-smoothstep(.95,.96,b)*.3+cos(t)*.02,-I.z-1.-p*1.8,.2),.01);"
       "M=B(M,F,.02);"
       "F=min(F,M);"
       "H.x=abs(I.x)-.2;"
       "H.xz=A(-.45)*H.xz;"
       "F=C(F,-length(H-vec3(-.7,-1.2,-2.05))+.14*w,.1);"
       "F=B(F,C(H-vec3(-.7,-1.2,-1.94),vec2(.14*w,.05)),.05);"
       "float N=B(v-vec3(0,-.1,cos(v.y-.7)*.5),vec3(cos(t*s.z)*m.z,.2,5),vec3(0,2,4.9),.2);"
       "N-=(cos(v.z*8.+v.y*4.5+v.x*4.)+cos(v.z*4.+v.y*6.5+v.x*3.))*.02;"
       "N=B(f,N,.1);"
       "vec2 O=vec2(f,1);"
       "O=h(O,vec2(N,1));"
       "O=h(O,vec2(J,1));"
       "O.x=C(O.x,-L,.15);"
       "O=h(O,vec2(E,2));"
       "O=h(O,vec2(F,2));"
       "O=h(O,vec2(U,3));"
       "O=h(O,vec2(G,4));"
       "O=h(O,vec2(K,2));"
       "u=F;"
       "return O;"
     "}"
   "return vec2(f,1);"
 "}"
 "float D(vec3 v,vec2 m,float y)"
 "{"
   "return max(abs(v).z-m.y,C(C(v.x*.9+v.y*.5,-v.x*.9+v.y*.5,y),-v.y,y)-m.x*.5);"
 "}"
 "vec2 H(vec3 v)"
 "{"
   "v-=i;"
   "float y=D(v-vec3(0,7.5,-5),vec2(1.7,.1),.3);"
   "if(y<8.)"
     "{"
       "y=C(y,-D(v-vec3(0,7.5,-5.1),vec2(1.6,.1),.3),.001);"
       "float m=A(v-vec3(0,4,-5.1),vec3(.11,4,.08));"
       "vec3 f=v;"
       "f.y=abs(f.y-7.3)-.3;"
       "m=min(m,A(f-vec3(0,0,-5.05),vec3(.35,.1,.05)));"
       "vec2 x=vec2(m,5);"
       "x=h(x,vec2(y,6));"
       "return x;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "vec2 I(vec3 v)"
 "{"
   "vec2 y=vec2(v.y,0);"
   "y=h(y,G(v));"
   "y=h(y,F(v));"
   "y=h(y,E(v));"
   "y=h(y,H(v));"
   "y=h(y,D(v));"
   "y=h(y,B(v));"
   "return y;"
 "}"
 "float C(vec3 v,vec3 y,float i,float x)"
 "{"
   "float m=0.,f=1.;"
   "for(int d=1;d<=2;d++)"
     "{"
       "float t=float(d)/2*i,s=I(v+t*y).x;"
       "m+=(t-s)*f;"
       "f*=.95;"
     "}"
   "return max(0.,1.-x*1.5*m);"
 "}"
 "float E(vec3 v,vec3 m)"
 "{"
   "vec3 s=1./m;"
   "float d=9e7,f;"
   "vec2 c=h(v-y-vec3(0,3,-2),m,vec3(3,3,7),s);"
   "if(c.y>0.)"
     "{"
       "f=max(c.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "vec3 t=v+m*f;"
           "float n=h(vec2(t.y,0),G(t)).x;"
           "f+=n;"
           "if(f>c.y||abs(n)<.001)"
             "break;"
         "}"
       "if(f<c.y)"
         "d=f;"
     "}"
   "c=h(v-z-vec3(0,5,-5),m,vec3(1.5,5,1),s);"
   "if(c.y>0.)"
     "{"
       "f=max(c.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=E(v+m*f).x;"
           "f+=t;"
           "if(f>c.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<c.y)"
         "d=min(d,f);"
     "}"
   "c=h(v-i-vec3(0,5,-5),m,vec3(1.5,5,1),s);"
   "if(c.y>0.)"
     "{"
       "f=max(c.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=H(v+m*f).x;"
           "f+=t;"
           "if(f>c.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<c.y)"
         "d=min(d,f);"
     "}"
   "c=h(v-x-vec3(0,5,0),m,vec3(2,5,1),s);"
   "if(c.y>0.)"
     "{"
       "f=max(c.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=F(v+m*f).x;"
           "f+=t;"
           "if(f>c.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<c.y)"
         "d=min(d,f);"
     "}"
   "c=h(v-r-vec3(0,3,2),m,vec3(4,4,5),s);"
   "if(c.y>0.)"
     "{"
       "f=max(c.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=D(v+m*f).x;"
           "f+=t;"
           "if(f>c.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<c.y)"
         "d=min(d,f);"
     "}"
   "f=(-v.y-.4)*s.y;"
   "if(f>0.&&length((v+m*f).xz-r.xz)<10.)"
     "{"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=B(v+m*f).x;"
           "f+=t;"
           "if(f>c.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<1e2)"
         "d=min(d,f);"
     "}"
   "f=-v.y*s.y;"
   "if(f>0.)"
     "d=min(d,f);"
   "return d;"
 "}"
 "float F(vec3 v,vec3 y)"
 "{"
   "float f=1.,m=.08;"
   "for(int i=0;i<64;i++)"
     "{"
       "float s=I(v+y*m).x;"
       "f=min(f,30.*s/m);"
       "m+=s;"
       "if(f<1e-4||m>50.)"
         "break;"
     "}"
   "return clamp(f,0.,1.);"
 "}"
 "float D(vec2 v,float y,float x,float m)"
 "{"
   "v.x=abs(v.x);"
   "float s=(y-x)/m,f=sqrt(1.-s*s),i=dot(v,vec2(-s,f));"
   "return i<0.?"
     "length(v)-y:"
     "i>f*m?"
       "length(v-vec2(0,m))-x:"
       "dot(v,vec2(f,s))-y;"
 "}"
 "float E(vec2 v,float m,float y)"
 "{"
   "vec2 x=vec2(.81,-.59),f=vec2(-x.x,x.y);"
   "v.x=abs(v.x);"
   "v-=2.*max(dot(x,v),0.)*x;"
   "v-=2.*max(dot(f,v),0.)*f;"
   "v.x=abs(v.x);"
   "v.y-=m;"
   "vec2 s=y*vec2(-x.y,x)-vec2(0,1);"
   "float i=clamp(dot(v,s)/dot(s,s),0.,m);"
   "return length(v-s*i)*sign(v.y*s.x-v.x*s.y);"
 "}"
 "void main()"
 "{"
   "vec2 m=gl_FragCoord.xy/v,y=m*2.-1.;"
   "y.x*=v.x/v.y;"
   "vec3 s=c,l=B(s,a)*normalize(vec3(y,n-length(y)*o));"
   "float O=E(s,l);"
   "vec3 H=s+l*O;"
   "vec2 r=I(H),G=vec2(1e-4,0);"
   "vec3 w=normalize(vec3(r.x-I(H-G.xyy).x,r.x-I(H-G.yxy).x,r.x-I(H-G.yyx).x));"
   "float b=smoothstep(0.,.3,e.y)+.1,M=C(H,w,.15,1.);"
   "M*=C(H,w,1.,.1)*.5;"
   "float U=F(H,e),g=1.+dot(l,w);"
   "vec3 N=vec3(1,.8,.7)*max(dot(w,e),0.)*pow(vec3(U),vec3(1,1.2,1.5)),J=vec3(1,.8,.7)*.1*max(dot(w,-e),0.)*M,K=vec3(.5)*mix(C(H,l,.3,.75),C(H,e,.3,.75),.5),L=vec3(1)*max(dot(reflect(l,w),e),0.),P=vec3(0),Q=vec3(.4,.45,.5)*M,R=vec3(0),S=vec3(0);"
   "if(r.y==0.)"
     "S=vec3(3),K*=0.,L*=0.;"
   "else if(r.y==1.)"
     "S=vec3(.4),K*=g*.5+.5,R=vec3(.35),L=pow(L,vec3(4))*g*.25;"
   "else if(r.y==4.)"
     "S=vec3(.025),K*=0.,L=pow(L,vec3(80))*g*10.;"
   "else if(r.y==3.)"
     "{"
       "K*=.5;"
       "vec3 T=normalize(d+(C(vec3(t,t*.5,t*1.5))*2.-1.)*.01),V=cross(T,vec3(0,1,0)),W=cross(T,V);"
       "V=cross(W,T);"
       "vec3 X=w.z*T+w.x*V+w.y*W,Y=l.z*d+l.x*V+l.y*W;"
       "vec2 Z=Y.xy/Y.z*length(X.xy)/length(s-H)*.4;"
       "X.xy-=Z*smoothstep(.01,0.,dot(X,l));"
       "float _=.2+p*.5,j=length(X.xy),q=atan(X.x,X.y);"
       "vec3 at=mix(vec3(.5,.3,.1),vec3(0,.8,1),smoothstep(.16,.3,j)*.3+cos(q*15.)*.04);"
       "float ay=smoothstep(-.9,1.,C(vec3(j*10.,q*30.+cos(j*50.+C(vec3(q))*50.),0)));"
       "ay+=smoothstep(-.9,1.,C(vec3(j*10.,q*40.+cos(j*30.+C(vec3(q))*50.)*2.,0)));"
       "S=at*(ay*.5+.5)*smoothstep(.3,.29,j);"
       "S*=vec3(1,.8,.7)*pow(max(0.,dot(normalize(vec3(3,1,-1)),X)),8.)*3e2+.5;"
       "float ax=smoothstep(_,_+.02,j);"
       "S*=ax;"
       "S+=pow(L,vec3(800))*3;"
       "S=mix(S,vec3(.8),smoothstep(.29,.3,j));"
       "S=mix(at*.3,S,smoothstep(0.,.05,abs(j-.3)+.01));"
       "w=mix(normalize(w+(d+w)*4.),w,smoothstep(.3,.32,j));"
       "{"
         "vec3 am=reflect(l,w),av=normalize(vec3(1,1.5,-1)),ad=vec3(-av.x,av.y*.5,av.z);"
         "float ac=0.;"
         "ac+=h(am,av,0.);"
         "ac+=h(am,normalize(av+vec3(.2,0,0)),2.);"
         "ac+=h(am,normalize(av+vec3(.2,0,.2)),4.);"
         "ac+=h(am,ad,20.)*.1;"
         "ac+=h(am,normalize(ad+vec3(.1,0,.2)),80.)*.5;"
         "ac/=5.;"
         "P=(mix(mix(vec3(.3,.3,0),vec3(.1),smoothstep(-.7,.2,am.y)),vec3(.3,.65,1),smoothstep(0.,1.,am.y))+ac*vec3(1,.9,.8))*mix(.15,.2,ax)*sqrt(g)*2.5;"
       "}"
       "I(H);"
       "S*=smoothstep(0.,.015,u)*.4+.6;"
       "L*=0.;"
     "}"
   "else if(r.y==5.)"
     "S=vec3(.85,.95,1),K*=0.,L=pow(L,vec3(8))*g*2.;"
   "else if(r.y==6.)"
     "{"
       "vec3 X=H-i;"
       "K*=0.;"
       "L=pow(L,vec3(8))*g*20.;"
       "if(w.z>.5)"
         "{"
           "float j=D(X-vec3(0,7.5,-5),vec2(1.3,.2),.01);"
           "S=vec3(1.5,0,0);"
           "float V=smoothstep(.13,.1295,distance(X,vec3(0,7.1,-4.9)));"
           "V+=smoothstep(.005,0.,D(X.xy-vec2(0,7.34),.06,.14,1.));"
           "S=mix(S,vec3(2),smoothstep(.005,0.,j));"
           "S=mix(S,vec3(0),V);"
         "}"
       "else"
         " S=vec3(.85,.95,1);"
     "}"
   "else if(r.y==7.)"
     "{"
       "vec3 X=H-z;"
       "K*=0.;"
       "L=pow(L,vec3(8))*g*10.;"
       "if(w.z>.5)"
         "{"
           "S=vec3(0,0,1.5);"
           "X.y-=7.4;"
           "float j=A(X-vec3(0,.1,-5),vec3(.8,.8,1)),V=0.;"
           "X.xy=A(.8)*X.xy;"
           "V+=smoothstep(.01,0.,D(X.xy-vec2(-.04,-.6),.1,.05,1.));"
           "V+=smoothstep(.01,0.,D(X.xy-vec2(-.04,.5),.16,.135,.15));"
           "V*=smoothstep(0.,.01,D(X.xy-vec2(-.12,.56),.001,.02,.2));"
           "V*=smoothstep(0.,.01,D(X.xy-vec2(0,.56),.001,.02,.2));"
           "X.xy=A(-1.6)*X.xy;"
           "V+=smoothstep(.01,0.,D(X.xy-vec2(.04,-.6),.1,.05,1.));"
           "V+=smoothstep(.01,0.,D(X.xy-vec2(.04,.5),.16,.1,.15));"
           "S=mix(S,vec3(2),smoothstep(.01,0.,j));"
           "S=mix(S,vec3(0),V);"
         "}"
       "else"
         " S=vec3(1);"
     "}"
   "else if(r.y==8.)"
     "{"
       "vec3 X=H-x;"
       "X.x+=cos(.775+t)*3.1*.2;"
       "X.y-=2.8;"
       "X.zy=A(.75)*X.zy;"
       "S=mix(vec3(2,.75,0),vec3(2,2,0),smoothstep(0.,.45,length(X-vec3(0,.3,0))))*1.8;"
       "K=vec3(.01);"
       "L*=0.;"
     "}"
   "else if(r.y==10.)"
     "S=vec3(0,.05,0),L*=g;"
   "else if(r.y==9.)"
     "{"
       "vec3 X=H-x;"
       "X.x+=cos(.775+t)*3.1*.2;"
       "X.y-=2.8;"
       "X.zy=A(.75)*X.zy;"
       "S=mix(vec3(1)+.5,vec3(.75,.5,1),smoothstep(.5,1.1,length(X-vec3(0,.3,0))))*2.;"
       "K*=0.;"
       "L=pow(L,vec3(4))*g;"
     "}"
   "else if(r.y==11.)"
     "S=vec3(1),N*=vec3(.1)*g,Q*=vec3(.1)*g,J*=0.,K*=0.,L=pow(L,vec3(100))*g*2.;"
   "else if(r.y==12.)"
     "S=vec3(1,.01,.01)*.3,N*=vec3(3),Q*=g*g*vec3(2),K*=0.,L=vec3(1,.3,.3)*pow(L,vec3(500))*5.;"
   "else if(r.y==2.)"
     "S=vec3(1,.7,.5),Q*=vec3(1,.75,.75),K=pow(K,vec3(.5,2.5,5)+2.)*2.,L=pow(L,vec3(4))*g*.02;"
   "vec3 X=(S*(Q+N*.5+J*2.+K*2.)+P+L*U+R)*b;"
   "X=clamp(mix(X,A(l,m,b),smoothstep(90.,1e2,O)),0.,1.);"
   "if(r.y==0.)"
     "{"
       "vec2 j=m*2.-1.;"
       "float V=length(j)*.5;"
       "X=mix(X,mix(mix(vec3(1,.5,0),vec3(.8,.5,1),(cos(V*5.+t*5.)*.5+.5)*k.y),vec3(1),smoothstep(-V,V,cos(atan(j.x,j.y)*15.-t*3.-V*30.*k.y))),k.x);"
     "}"
   "vec2 V=vec2(abs(y.x*5.-.3)-1.5,y.y*5.-1.4);"
   "V=A(t*5.)*V;"
   "float j=1.4+.2*sin(t*20.);"
   "j*=smoothstep(.5,1.,k.x);"
   "float q=E(V,j,.5);"
   "vec3 T=mix(vec3(1,.6,0),vec3(1,.2,0),smoothstep(-.1,.6,E(V,j*.5,.5)))*1.3;"
   "X=mix(X,T,smoothstep(0.,-.01,q)*k.x);"
   "X=pow(pow(X,vec3(1./2.2)),vec3(1,1.05,1.1));"
   "float W=length(gl_FragCoord.xy/v.xx-vec2(.5,.3)),_=max(.137,smoothstep(157.,156.,t));"
   "X*=smoothstep(_,_-.005,W);"
   "float Y=W,Z=smoothstep(.135,.136,Y)*smoothstep(157.,158.,t);"
   "Y=fract(23.*pow(Y,.25));"
   "Y-=smoothstep(.95,.99,Y);"
   "vec3 at=mix(vec3(1,.6,0),vec3(1,0,0),pow(Y,1.));"
   "X=mix(X,at,Z);"
   "X*=smoothstep(0.,10.,t)*smoothstep(162.,161.,t);"
   "f=vec4(X/(1.+pow(length(m*2.-1.),4.)*.04),1);"
 "}";

const char *mouton_vert =
 "#version 150\n"
 "in vec4 X;"
 "out vec3 m,s,y,x,z,i,r,e,c,a,d;"
 "out vec2 l,k;"
 "out float b,n,p,o,w;"
 "uniform float t;"
 "void main()"
 "{"
   "gl_Position=X;"
   "float v=t;"
   "y=vec3(0);"
   "z=vec3(9e7);"
   "x=vec3(9e7);"
   "i=vec3(9e7);"
   "r=vec3(9e7);"
   "n=2.;"
   "b=max(fract(t*.333),fract(t*.123+.1));"
   "k=vec2(0);"
   "e=normalize(vec3(3.5,1,-1));"
   "s=vec3(1);"
   "o=0.;"
   "l=vec2(0);"
   "w=1.;"
   "p=0.;"
   "if(v<10.)"
     "m=vec3(1,.2,1),s=vec3(1,1,.5),d=vec3(0,.45,1),l.y=.25,n=4.,c=vec3(0,2.5,-3.7),a=vec3(0,3,0);"
   "else if(v<20.)"
     "m=vec3(1,.2,.25),s=vec3(1,1,2),d=vec3(0,.5,1),l.y=.25,n=4.,c=vec3(5,.5,0),a=vec3(0,.5,1);"
   "else if(v<30.)"
     "{"
       "float f=v-20.;"
       "m=vec3(1,.2,.25);"
       "s=vec3(1,1,2);"
       "d=vec3(0,.5,1);"
       "l.y=.25;"
       "c=vec3(5.+f*.5,2,f*.5);"
       "a=vec3(0,2,0);"
     "}"
   "else if(v<50.)"
     "{"
       "float f=v-30.;"
       "m=vec3(1,.2,.25);"
       "s=vec3(1,1,2);"
       "d=vec3(0,.5,1);"
       "l.y=.25;"
       "float S=f*.35+.3;"
       "e=normalize(vec3(cos(S),sin(S),-.3));"
       "n=1.5;"
       "c=vec3(22,2,f*.6-10.);"
       "a=vec3(0,2,f*.6-10.);"
     "}"
   "else if(v<55.)"
     "{"
       "float f=v-50.,L=smoothstep(2.,2.5,f);"
       "l.y=mix(.25,0.,L);"
       "m=vec3(1.-L,.2*(1.-L),1);"
       "s=vec3(1,1,.5);"
       "d=vec3(L*.3,.3-L*.3,1);"
       "p=smoothstep(4.6,4.8,f)*.2;"
       "n=4.;"
       "c=vec3(0,3,-4);"
       "a=vec3(0,3,0);"
       "if(f>3.)"
         "b=max(fract(t*.333),fract(t*.333+.08));"
     "}"
   "else if(v<58.)"
     "{"
       "float f=v-55.;"
       "z=vec3(-5,0,-8);"
       "y=vec3(9e7);"
       "d=vec3(.3,0,1);"
       "p=.2;"
       "float S=smoothstep(0.,.5,f);"
       "n=mix(4.,3.,S);"
       "c=vec3(0,3,-4);"
       "a=mix(vec3(0,3,0),vec3(-5,5,-9),S);"
     "}"
   "else if(v<65.)"
     "{"
       "float f=v-58.;"
       "k.x=smoothstep(0.,.5,f);"
       "m=vec3(0);"
       "b=0.;"
       "d=vec3(.3,0,1);"
       "c=mix(vec3(0,3,-4),vec3(0,2,-6),k.x);"
       "a=vec3(0,3,0);"
       "n=mix(4.,3.,k.x)+smoothstep(0.,7.,f)*.5;"
     "}"
   "else if(v<70.)"
     "{"
       "float f=v-65.;"
       "d=vec3(0,0,1);"
       "y=vec3(0,0,-f*3.-2.);"
       "z=vec3(-5,0,-8);"
       "m=vec3(1,1,.5);"
       "s=vec3(3,1.5,8)*1.5;"
       "c=vec3(16,5,9);"
       "a=vec3(3,5,-2.-f);"
       "n=3.;"
     "}"
   "else if(v<80.)"
     "{"
       "float f=v-70.;"
       "m=vec3(1);"
       "s=vec3(3,1.5,8);"
       "float S=mod(f,8.);"
       "d=vec3(smoothstep(.5,1.,S)*smoothstep(2.8,2.5,S)-smoothstep(4.,4.5,S)*smoothstep(5.8,5.5,S)+cos(t)*.2,cos(t*.5)*.1+.1,1);"
       "o=.3;"
       "n=2.5;"
       "c=vec3(2.75,1,-5.25);"
       "a=vec3(0,2.3,0);"
       "float L=mod(f,2.);"
       "w+=smoothstep(.5,.6,L)*smoothstep(.7,.6,L)*.3;"
       "L=mod(f+.3,3.);"
       "w+=smoothstep(.5,.6,L)*smoothstep(.7,.6,L)*.3;"
     "}"
   "else if(v<85.)"
     "{"
       "float f=v-80.,L=smoothstep(1.,3.,f);"
       "m=vec3(0,1.-L*.5,1);"
       "s=vec3(3,1.5,6);"
       "d=vec3(L*.5,.3-L*.45,1);"
       "n=4.;"
       "c=vec3(0,3,-4);"
       "a=vec3(0,3,0);"
       "if(f>3.)"
         "b=max(fract(t*.333),fract(t*.333+.08));"
     "}"
   "else if(v<89.)"
     "{"
       "float f=v-85.;"
       "i=vec3(-5,0,-8);"
       "d=vec3(.5,-.15,1);"
       "m=vec3(0,.5,1);"
       "s=vec3(3,1.5,6);"
       "float S=smoothstep(0.,1.,f);"
       "n=mix(4.,3.,S);"
       "c=vec3(0,3,-4);"
       "a=mix(vec3(0,3,0),vec3(-5,5,-9),S);"
     "}"
   "else if(v<97.)"
     "{"
       "float f=v-89.;"
       "y=vec3(0,0,-11);"
       "i=vec3(-5,0,-8);"
       "d=normalize(mix(vec3(1,-.5,1),vec3(0,.5,1),smoothstep(2.8,3.2,f)));"
       "d=mix(d,vec3(1,-.5,1),smoothstep(6.5,7.,f));"
       "l.y=smoothstep(3.,3.5,f)*.6;"
       "l.x=smoothstep(3.,3.5,f)*smoothstep(8.,6.,f)*.25*sin(f*3.);"
       "m=vec3(1,.2,.5);"
       "s=vec3(0,.2,1);"
       "c=vec3(-3,4.8,-30);"
       "a=vec3(-3,4,0);"
       "n=3.5;"
     "}"
   "else if(v<107.)"
     "{"
       "float f=v-98.,L=smoothstep(6.,9.,f);"
       "y=vec3(0,0,f*.25-11.);"
       "i=vec3(-2,0,-8);"
       "d=vec3(-.5,.25-L,1);"
       "l.y=.5-L;"
       "m=vec3(1,.2,.5);"
       "s=vec3(-1,1,1)*.5;"
       "c=vec3(18,5,-5);"
       "a=vec3(-5,5,-6);"
       "n=3.;"
     "}"
   "else if(v<109.)"
     "{"
       "float f=v-107.;"
       "m=vec3(0);"
       "s=vec3(0);"
       "i=vec3(0,0,-8);"
       "a=mod(f,2.)<1.?"
         "(c=vec3(0,2,-8),vec3(0,3,0)):"
         "(c=vec3(0,5.5,2),vec3(0,5.75,0));"
       "d=vec3(0,-.1,1);"
       "n=3.+f*.1;"
     "}"
   "else if(v<116.)"
     "{"
       "float f=v-109.,L=sin(min(f,5.));"
       "m=vec3(0);"
       "s=vec3(0);"
       "d=normalize(vec3(L*.7,0,1));"
       "d=mix(d,vec3(-.3,.2,1),smoothstep(5.2,5.4,f));"
       "l.x=L*.25;"
       "p=smoothstep(6.,6.2,f)*.2;"
       "y=vec3(0,(smoothstep(6.,6.2,f)-smoothstep(6.2,6.4,f))*.4,0);"
       "n=3.5;"
       "c=vec3(0,2,-8);"
       "a=vec3(0,3,0);"
     "}"
   "else if(v<125.)"
     "{"
       "float f=v-116.;"
       "y=vec3(9e7);"
       "i=vec3(-2,0,-8);"
       "x=vec3(5,0,-20);"
       "float L=smoothstep(.5,1.5,f);"
       "n=mix(3.5,5.,L);"
       "c=vec3(0,5.5,2);"
       "a=mix(vec3(-.5,5.75,0),vec3(5,2,-20),L);"
       "k.x=L*.3;"
     "}"
   "else if(v<137.)"
     "{"
       "float f=v-125.;"
       "m=vec3(.1);"
       "s=vec3(.2);"
       "n=2.8+f*.15;"
       "int S=int(f);"
       "if(S%4==1)"
         "i=vec3(0,0,-8),c=vec3(2.5,2,-1),a=vec3(1,5.25,-8),n=2.8+pow(f*.3,1.2);"
       "else if(S%4==3)"
         "x=vec3(4,0,-8),c=vec3(0,5.5,2),a=vec3(4,3,-8),k.x=.3+.2/12.,k.y=f/12.;"
       "else"
         " c=vec3(0,2.4,-8),a=vec3(0,3,0);"
       "float L=smoothstep(.3,.7,fract(f));"
       "if(S%4==0)"
         "L=1.-L;"
       "l.x=-L*.1;"
       "d=normalize(mix(vec3(.1,-.25,1),vec3(-.2,.2,1),L));"
       "d+=vec3(cos(f*10.),cos(f*5.),1)*.01;"
     "}"
   "else if(v<140.)"
     "{"
       "float f=v-137.;"
       "m=vec3(0,.1,0);"
       "s=vec3(0,.5,0);"
       "c=vec3(0,2.4,-8);"
       "a=vec3(0,3,0);"
       "l.x=-.1;"
       "l.y=sin(f*2.)*.1;"
       "p=smoothstep(0.,3.,f)*.1;"
       "d=vec3(-.2,.2,1);"
       "n=3.2-f*.15;"
       "k.x=.1;"
       "k.y=5.;"
     "}"
   "else if(v<150.)"
     "{"
       "float f=v-140.;"
       "d=vec3(0,0,1);"
       "y=vec3(0,0,-f*2.-2.);"
       "x=vec3(0,-.5,-30);"
       "m=vec3(1,1,.5);"
       "s=vec3(3,1.5,8);"
       "c=vec3(-2,3.5,mix(-10.,-33.,smoothstep(0.,10.,f)));"
       "a=vec3(2,2,-3.-f*2.);"
       "n=3.;"
     "}"
   "else if(v<155.)"
     "{"
       "float f=v-150.;"
       "d=vec3(0,0,1);"
       "y=vec3(0,(1.-smoothstep(.3,.25,f))*-4.8,-22.-f*2.);"
       "x=vec3(2,0,-30);"
       "m=vec3(1,1,.5);"
       "s=vec3(3,1.5,8);"
       "c=vec3(-20,6,-13)+vec3(cos(f*72.),cos(f*64.),sin(f*48.))*3.*smoothstep(.3,.31,f)*smoothstep(.7,.1,f);"
       "a=vec3(3,2,-23);"
       "n=mix(4.,4.2,smoothstep(0.,5.,f));"
       "r=vec3(0,smoothstep(.3,.2,f)*13.,-22);"
     "}"
   "else"
     "{"
       "float f=v-155.;"
       "d=vec3(0,0,1);"
       "y=vec3(9e7);"
       "i=vec3(-1,0,-8);"
       "x=vec3(1,0,-25);"
       "a=vec3(2,3.6,-18);"
       "c=vec3(5,5,2);"
       "n=2.5+smoothstep(1.5,2.,f)*4.2;"
       "r=vec3(7,0,-20);"
     "}"
   "d=normalize(d);"
 "}";

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 S=vec2(1280,720);"
 "uniform sampler2D L;"
 "void main()"
 "{"
   "vec2 v=1./S,y=gl_FragCoord.xy*v;"
   "vec4 m=vec4(y,y-v*.5);"
   "vec3 x=vec3(.299,.587,.114);"
   "float d=dot(textureLod(L,m.zw,0.).xyz,x),s=dot(textureLod(L,m.zw+vec2(1,0)*v.xy,0.).xyz,x),c=dot(textureLod(L,m.zw+vec2(0,1)*v.xy,0.).xyz,x),a=dot(textureLod(L,m.zw+vec2(1)*v.xy,0.).xyz,x),t=dot(textureLod(L,m.xy,0.).xyz,x);"
   "vec2 i=vec2(-d-s+c+a,d+c-s-a);"
   "float n=1./(min(abs(i.x),abs(i.y))+1./128.);"
   "i=min(vec2(8),max(vec2(-8),i*n))*v.xy;"
   "vec3 X=.5*(textureLod(L,m.xy+i*(1./3.-.5),0.).xyz+textureLod(L,m.xy+i*(2./3.-.5),0.).xyz),r=X*.5+.25*(textureLod(L,m.xy+i*-.5,0.).xyz+textureLod(L,m.xy+i*.5,0.).xyz);"
   "float l=dot(r,x);"
   "f=l<min(t,min(min(d,s),min(c,a)))||l>max(t,max(max(d,s),max(c,a)))?"
     "vec4(X,1):"
     "vec4(r,1);"
 "}";

#endif // SHADERS_INL_
