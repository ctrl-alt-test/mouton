// Generated with Shader Minifier 1.3.3 (https://github.com/laurentlb/Shader_Minifier/)
#ifndef SHADERS_INL_
# define SHADERS_INL_
# define VAR_a_position "O"
# define VAR_animationAmp "m"
# define VAR_animationSpeed "s"
# define VAR_anvilPos "i"
# define VAR_blink "b"
# define VAR_camFocal "o"
# define VAR_camPos "c"
# define VAR_camTa "a"
# define VAR_excited "e"
# define VAR_eyeDir "d"
# define VAR_eyesSurprise "p"
# define VAR_fishEyeFactor "u"
# define VAR_flowerPos "x"
# define VAR_fragColor "f"
# define VAR_headRot "l"
# define VAR_iTime "t"
# define VAR_noseSize "k"
# define VAR_panelPos "z"
# define VAR_panelWarningPos "n"
# define VAR_sheepPos "y"
# define VAR_sunDir "r"
# define VAR_tex "K"

const char *mouton_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 v=vec2(1280,720);"
 "in vec3 m,s,y,x,z,n,i,r,c,a,d;"
 "in vec2 l,e;"
 "in float b,o,p,u,k;"
 "uniform float t;"
 "const float U=acos(-1.);"
 "float w=0.;"
 "vec2 h(vec2 i,vec2 x)"
 "{"
   "return i.x<x.x?"
     "i:"
     "x;"
 "}"
 "vec2 g(vec2 v,float i)"
 "{"
   "float y=atan(v.y,v.x),s=length(v);"
   "y=mod(y-i/2.,i)-i/2.;"
   "return vec2(cos(y),sin(y))*s;"
 "}"
 "vec2 g(vec3 i,vec3 v,vec3 s,vec3 m)"
 "{"
   "vec3 y=m*i,x=abs(m)*s,c=-y-x,d=-y+x;"
   "float a=max(max(c.x,c.y),c.z),f=min(min(d.x,d.y),d.z);"
   "return a>f||f<0.?"
     "vec2(-1):"
     "vec2(a,f);"
 "}"
 "float B(float v,float y)"
 "{"
   "return pow(v,y)*(y+2.)/(8.*U);"
 "}"
 "float B(vec3 v,vec3 i,float y)"
 "{"
   "vec3 x=normalize(i+v);"
   "float m=clamp(dot(v,x),0.,1.);"
   "return B(m,30./(1.+y))*2.+B(m,2e4/(1.+y));"
 "}"
 "vec3 g(vec3 v,vec3 i,vec3 y)"
 "{"
   "float m=0.;"
   "m+=B(v,normalize(i+vec3(0)),0.);"
   "m+=B(v,normalize(i+vec3(.2,0,0)),2.);"
   "m+=B(v,normalize(i+vec3(.2,0,.2)),4.);"
   "m+=B(v,y,20.)*.1;"
   "m+=B(v,normalize(y+vec3(.1,0,.2)),80.)*.5;"
   "m/=5.;"
   "vec3 f=mix(mix(vec3(.3,.3,0),vec3(.1),smoothstep(-.7,.2,v.y)),vec3(.3,.65,1),smoothstep(0.,1.,v.y));"
   "f+=m*vec3(1,.9,.8);"
   "return f;"
 "}"
 "vec3 B(vec3 v)"
 "{"
   "uvec3 y=uvec3(v*1e5);"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "return vec3(y)*(1./float(-1U));"
 "}"
 "float g(float v)"
 "{"
   "return fract(v*17.*fract(v*.3183099));"
 "}"
 "float h(vec3 v)"
 "{"
   "vec3 m=floor(v),s=fract(v),y=s*s*s*(s*(s*6.-15.)+10.);"
   "float x=m.x+317.*m.y+157.*m.z,c=g(x),d=g(x+1.),a=g(x+317.),z=g(x+318.),f=g(x+157.),o=g(x+158.),t=g(x+474.),n=g(x+475.);"
   "return-1.+2.*(c+(d-c)*y.x+(a-c)*y.y+(f-c)*y.z+(c-d-a+z)*y.x*y.y+(c-a-f+t)*y.y*y.z+(c-d-f+o)*y.z*y.x+(-c+d+a-z+f-o-t+n)*y.x*y.y*y.z);"
 "}"
 "vec2 A(vec3 v)"
 "{"
   "v.xz-=i.xz;"
   "v.y-=-i.y;"
   "float y=v.y+smoothstep(1.,20.,length(v.xz));"
   "return y<.4?"
     "(y-=pow((h(v*.7+1.)*.5+h(v*1.7+1e2)*.3+h(v*2.7+1e2)*.1)*.5+.5,3.)*.45*(1.-exp(-(t-150.)*4.))+.03,vec2(y,12)):"
     "vec2(9e7,0);"
 "}"
 "mat3 A(vec3 v,vec3 y)"
 "{"
   "const vec3 x=vec3(0,1,0);"
   "vec3 c=normalize(y-v),s=normalize(cross(c,normalize(x)));"
   "return mat3(s,cross(s,c),c);"
 "}"
 "mat2 C(float v)"
 "{"
   "float y=cos(v),s=sin(v);"
   "return mat2(y,s,-s,y);"
 "}"
 "vec3 A(vec3 i,vec2 v,float y)"
 "{"
   "vec3 f=vec3(y*y);"
   "vec2 x=vec2(cos(t*.7+2.4),sin(t*.7+2.4)*.75);"
   "float m=smoothstep(.151,.15,length(v-x)),s=m*smoothstep(.13,.2701,length(v-x-vec2(.05))+.004*h(1e2*vec3(v-x,0)));"
   "vec2 c=C(t*2e-4)*v*2e2,a=fract(c)-.5,d=floor(c);"
   "vec3 n=B(vec3(abs(d),abs(d.x)));"
   "float z=n.z*.06;"
   "f+=vec3(1,.9,.1)*s*smoothstep(.5,-1.,r.y);"
   "f+=smoothstep(z,z*.01,length(n.xy-.5+a))*(1.-m);"
   "f+=exp(-length(v-x)*2.)*.1;"
   "return f;"
 "}"
 "float C(vec3 v,vec3 y)"
 "{"
   "vec3 s=abs(v)-y;"
   "return length(max(s,0.))+min(max(s.x,max(s.y,s.z)),0.);"
 "}"
 "vec2 D(vec3 v)"
 "{"
   "v-=i;"
   "v.xz=C(1.)*v.xz;"
   "float y=pow(clamp(v.y-1.,.004,1.),.5),f=C(v-vec3(0,1,0),vec3(1.5-y,1,2.5-y));"
   "if(f<10.)"
     "{"
       "f=min(f,C(v-vec3(0,3,0),vec3(2,1,3)));"
       "float c=length((v.yz-vec2(4.5,3))*vec2(1,.8))-2.;"
       "c=max(c,abs(v.x)-.5);"
       "c=max(c,v.y-3.5);"
       "f=min(f,c);"
       "vec2 x=vec2(f-.1,11);"
       "return x;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "vec2 E(vec3 v)"
 "{"
   "v-=z;"
   "float y=C(v-vec3(0,7.5,-5),vec3(.8,.8,.1))-.2;"
   "if(y<7.)"
     "{"
       "y=max(y,abs(v.z+5.)-.1);"
       "float c=C(v-vec3(0,4,-5.1),vec3(.11,4,.08));"
       "vec2 f=vec2(c,5);"
       "f=h(f,vec2(y,7));"
       "return f;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "float A(vec3 v,float y,float i,float x)"
 "{"
   "vec2 m=vec2(length(v.xz),v.y),c=vec2(x,y),s=vec2(x-i,2.*y),d=vec2(m.x-min(m.x,m.y<0.?"
     "i:"
     "x),abs(m.y)-y),f=m-c+s*clamp(dot(c-m,s)/dot(s,s),0.,1.);"
   "return(f.x<0.&&d.y<0.?"
     "-1.:"
     "1.)*sqrt(min(dot(d,d),dot(f,f)));"
 "}"
 "float B(vec3 v,vec3 x,vec3 m,float y)"
 "{"
   "vec3 c=v-x,s=m-x;"
   "float i=clamp(dot(c,s)/dot(s,s),0.,1.);"
   "return length(c-s*i)-y;"
 "}"
 "float D(vec3 v,vec2 y)"
 "{"
   "vec2 x=vec2(length(v.xy)-y.x,v.z);"
   "return length(x)-y.y;"
 "}"
 "float E(vec3 v,vec3 y)"
 "{"
   "float c=length(v/y),s=length(v/(y*y));"
   "return c*(c-1.)/s;"
 "}"
 "vec2 F(vec3 v)"
 "{"
   "v-=x;"
   "vec3 m=v;"
   "m.x+=cos(.775+t)*3.1*.2;"
   "m.y-=2.8;"
   "m.zy=C(.7)*m.zy;"
   "float y=E(m-vec3(0,.3,0),vec3(1,.2+cos(m.x*150.)*sin(m.z*150.)*.05,1)*.25);"
   "if(y<5.)"
     "{"
       "vec2 i=vec2(y,8);"
       "vec3 f=m;"
       "f.xz=g(f.xz,U*.2);"
       "float c=E(f-vec3(.5,.2+sin(f.x*2.)*.2,0),vec3(2,.1+sin(f.z*40.)*.02,.75)*.25);"
       "if(c<i.x)"
         "i=vec2(c,9);"
       "float s=max(length(v.xz+vec2(cos(v.y*.25+t)*v.y*.2+.02,-.1))-smoothstep(3.1,0.,v.y)*.05-.02,v.y-3.1);"
       "if(s<i.x)"
         "i=vec2(s,10);"
       "return i;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "float C(float v,float y,float x)"
 "{"
   "float s=clamp(.5+.5*(y-v)/x,0.,1.);"
   "return mix(y,v,s)-x*s*(1.-s);"
 "}"
 "float D(float v,float y,float x)"
 "{"
   "x*=1.4;"
   "float s=max(x-abs(v-y),0.);"
   "return max(v,y)+s*s*s/(6.*x*x);"
 "}"
 "vec2 G(vec3 v)"
 "{"
   "v-=y;"
   "float f=mod(t,1.);"
   "f=smoothstep(0.,1.,abs(f*2.-1.));"
   "v.y-=1.;"
   "v.z-=-2.;"
   "float c=t*s.x;"
   "vec3 x=vec3(cos(c*U),cos(c*U*2.)*.1,0)*.025*m.x;"
   "float i=length(v*vec3(1,1,.825)-vec3(0,1.5,2.55)-x)-2.;"
   "if(i<3.)"
     "{"
       "float a=pow(h((v-x-vec3(.05,0,0))*2.)*.5+.5,.75)*2.-1.;"
       "i=i+.05-a*.2;"
       "float n=mod(t*s.x,2.),z=smoothstep(0.,.5,n),d=smoothstep(.5,1.,n),o=smoothstep(1.,1.5,n),r=smoothstep(1.5,2.,n);"
       "vec4 e=vec4(d*(1.-d),r*(1.-r),z*(1.-z),o*(1.-o)),u=n*.5-vec4(d,r,z,o);"
       "u*=m.x;"
       "vec3 I=v;"
       "I.x-=.8;"
       "I.z-=2.+u.x;"
       "I.yz=C(e.x)*I.yz;"
       "float g=A(I-vec3(0),.7,.3,.2),G=A(I-vec3(0,-.8,0),.2,.35,.3);"
       "I=v;"
       "I.x+=1.;"
       "I.z-=2.+u.y;"
       "I.yz=C(e.y)*I.yz;"
       "g=min(g,A(I-vec3(0),.7,.3,.2));"
       "G=min(G,A(I-vec3(0,-.8,0),.2,.35,.3));"
       "I=v;"
       "I.x-=1.;"
       "I.z-=4.+u.z;"
       "I.yz=C(e.z)*I.yz;"
       "g=min(g,A(I-vec3(0),.7,.3,.2));"
       "G=min(G,A(I-vec3(0,-.8,0),.2,.35,.3));"
       "I=v;"
       "I.x+=1.;"
       "I.z-=4.+u.w;"
       "I.yz=C(e.w)*I.yz;"
       "g=min(g,A(I-vec3(0),.7,.3,.2));"
       "G=min(G,A(I-vec3(0,-.8,0),.2,.35,.3));"
       "vec3 E=v+vec3(0,-2,-1.2);"
       "E.xz=C((f*s.y-.5)*.25*m.y+l.x)*E.xz;"
       "E.zy=C(sin(t*s.y)*.25*m.y-l.y)*E.zy;"
       "float F=length(E-vec3(0,-1.3,-1.2))-1.;"
       "F=C(F,length(E-vec3(0))-.5,1.8);"
       "vec3 H=E;"
       "H*=vec3(.7,1,.7);"
       "float J=length(E-vec3(0,.35,-.1))-.55;"
       "J-=(cos(E.z*8.+E.y*4.5+E.x*4.)+cos(E.z*4.+E.y*6.5+E.x*8.))*.05;"
       "J=C(J,i,.1);"
       "H=E;"
       "H.yz=C(-.6)*H.yz;"
       "H.x=abs(v.x)-.8;"
       "H*=vec3(.3,1,.4);"
       "H-=vec3(0,-.05-pow(H.x,2.)*5.,-.1);"
       "float K=length(H)-.15;"
       "K=D(K,-(length(H-vec3(0,-.1,0))-.12),.01);"
       "H.y*=.3;"
       "H.y-=-.11;"
       "float L=length(H)-.16;"
       "H=E;"
       "H.x=abs(E.x)-.4;"
       "float M=length(H*vec3(1,1,1.-p)-vec3(0,0,-1))-.3,N=abs(M)-.01;"
       "N=D(N,C(-abs(E.y+E.z*.025)+.25-smoothstep(.95,.96,b)*.3+cos(t)*.02,-E.z-1.-p*1.8,.2),.01);"
       "N=C(N,F,.02);"
       "F=min(F,N);"
       "H.x=abs(E.x)-.2;"
       "H.xz=C(-.45)*H.xz;"
       "F=D(F,-length(H-vec3(-.7,-1.2,-2.05))+.14*k,.1);"
       "F=C(F,D(H-vec3(-.7,-1.2,-1.94),vec2(.14*k,.05)),.05);"
       "float O=B(v-vec3(0,-.1,cos(v.y-.7)*.5),vec3(cos(t*s.z)*m.z,.2,5),vec3(0,2,4.9),.2);"
       "O-=(cos(v.z*8.+v.y*4.5+v.x*4.)+cos(v.z*4.+v.y*6.5+v.x*3.))*.02;"
       "O=C(i,O,.1);"
       "vec2 P=vec2(i,1);"
       "P=h(P,vec2(O,1));"
       "P=h(P,vec2(J,1));"
       "P.x=D(P.x,-L,.15);"
       "P=h(P,vec2(g,2));"
       "P=h(P,vec2(F,2));"
       "P=h(P,vec2(M,3));"
       "P=h(P,vec2(G,4));"
       "P=h(P,vec2(K,2));"
       "w=F;"
       "return P;"
     "}"
   "return vec2(i,1);"
 "}"
 "float E(vec3 v,vec2 y,float s)"
 "{"
   "vec3 m=abs(v);"
   "return max(m.z-y.y,D(D(v.x*.866025+v.y*.5,-v.x*.866025+v.y*.5,s),-v.y,s)-y.x*.5);"
 "}"
 "vec2 H(vec3 v)"
 "{"
   "v-=n;"
   "float y=E(v-vec3(0,7.5,-5),vec2(1.7,.1),.3);"
   "if(y<8.)"
     "{"
       "y=D(y,-E(v-vec3(0,7.5,-5.1),vec2(1.6,.1),.3),.001);"
       "float f=C(v-vec3(0,4,-5.1),vec3(.11,4,.08));"
       "vec3 m=v;"
       "m.y=abs(m.y-7.3)-.3;"
       "f=min(f,C(m-vec3(0,0,-5.05),vec3(.35,.1,.05)));"
       "vec2 i=vec2(f,5);"
       "i=h(i,vec2(y,6));"
       "return i;"
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
   "y=h(y,A(v));"
   "return y;"
 "}"
 "float C(vec3 v,vec3 y,float i,float x)"
 "{"
   "float f=0.,s=1.;"
   "for(int c=1;c<=2;c++)"
     "{"
       "float m=float(c)/2*i,d=I(v+m*y).x;"
       "f+=(m-d)*s;"
       "s*=.95;"
     "}"
   "return max(0.,1.-x*1.5*f);"
 "}"
 "float F(vec3 v,vec3 s)"
 "{"
   "vec3 m=1./s;"
   "float c=9e7,f;"
   "vec2 d=g(v-y-vec3(0,3,-2),s,vec3(3,3,7),m);"
   "if(d.y>0.)"
     "{"
       "f=max(d.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "vec3 t=v+s*f;"
           "float o=h(vec2(t.y,0),G(t)).x;"
           "f+=o;"
           "if(f>d.y||abs(o)<.001)"
             "break;"
         "}"
       "if(f<d.y)"
         "c=f;"
     "}"
   "d=g(v-z-vec3(0,5,-5),s,vec3(1.5,5,1),m);"
   "if(d.y>0.)"
     "{"
       "f=max(d.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=E(v+s*f).x;"
           "f+=t;"
           "if(f>d.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<d.y)"
         "c=min(c,f);"
     "}"
   "d=g(v-n-vec3(0,5,-5),s,vec3(1.5,5,1),m);"
   "if(d.y>0.)"
     "{"
       "f=max(d.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=H(v+s*f).x;"
           "f+=t;"
           "if(f>d.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<d.y)"
         "c=min(c,f);"
     "}"
   "d=g(v-x-vec3(0,5,0),s,vec3(2,5,1),m);"
   "if(d.y>0.)"
     "{"
       "f=max(d.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=F(v+s*f).x;"
           "f+=t;"
           "if(f>d.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<d.y)"
         "c=min(c,f);"
     "}"
   "d=g(v-i-vec3(0,3,2),s,vec3(4,4,5),m);"
   "if(d.y>0.)"
     "{"
       "f=max(d.x,0.);"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=D(v+s*f).x;"
           "f+=t;"
           "if(f>d.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<d.y)"
         "c=min(c,f);"
     "}"
   "f=-(v.y+.4)*m.y;"
   "if(f>0.&&length((v+s*f).xz-i.xz)<10.)"
     "{"
       "for(int a=0;a<128;a++)"
         "{"
           "float t=A(v+s*f).x;"
           "f+=t;"
           "if(f>d.y||abs(t)<.001)"
             "break;"
         "}"
       "if(f<1e2)"
         "c=min(c,f);"
     "}"
   "f=-v.y*m.y;"
   "if(f>0.)"
     "c=min(c,f);"
   "return c;"
 "}"
 "vec3 J(vec3 v)"
 "{"
   "vec2 y=vec2(1e-4,0);"
   "float m=I(v).x;"
   "vec3 f;"
   "f.x=m-I(v-y.xyy).x;"
   "f.y=m-I(v-y.yxy).x;"
   "f.z=m-I(v-y.yyx).x;"
   "return normalize(f);"
 "}"
 "float D(vec3 v,vec3 y,float m,float x)"
 "{"
   "float f=1.,s=m;"
   "for(int i=0;i<64;i++)"
     "{"
       "float c=I(v+y*s).x;"
       "f=min(f,30.*c/s);"
       "s+=c;"
       "if(f<1e-4||s>x)"
         "break;"
     "}"
   "return clamp(f,0.,1.);"
 "}"
 "float E(vec2 v,float y,float x,float s)"
 "{"
   "v.x=abs(v.x);"
   "float f=(y-x)/s,c=sqrt(1.-f*f),m=dot(v,vec2(-f,c));"
   "return m<0.?"
     "length(v)-y:"
     "m>c*s?"
       "length(v-vec2(0,s))-x:"
       "dot(v,vec2(c,f))-y;"
 "}"
 "vec3 A(vec3 v,vec3 m,vec3 y,vec3 f,vec2 s)"
 "{"
   "vec2 c=I(y);"
   "float i=smoothstep(0.,.3,r.y)+.1,a=C(y,f,.15,1.);"
   "a*=C(y,f,1.,.1)*.5;"
   "float o=D(y,r,.08,50.),l=clamp(1.+dot(m,f),0.,5.);"
   "vec3 H=vec3(1,.8,.7)*max(dot(f,r),0.)*pow(vec3(o),vec3(1,1.2,1.5)),u=vec3(1,.8,.7)*.1*max(dot(f,-r),0.)*a,P=vec3(.5)*mix(C(y,m,.3,.75),C(y,r,.3,.75),.5),F=vec3(1)*max(dot(reflect(m,f),r),0.),G=vec3(0),N=vec3(.4,.45,.5)*a,b=vec3(0),J=vec3(0);"
   "if(c.y==0.)"
     "J=vec3(3),P*=0.,F*=0.;"
   "else"
     " if(c.y==1.)"
       "J=vec3(.4),P*=l*.5+.5,b=vec3(.35),F=pow(F,vec3(4))*l*.25;"
     "else"
       " if(c.y==4.)"
         "J=vec3(.025),P*=0.,F=pow(F,vec3(80))*l*10.;"
       "else"
         " if(c.y==3.)"
           "{"
             "P*=.5;"
             "vec3 U=normalize(d+(h(vec3(t,t*.5,t*1.5))*2.-1.)*.01),k=cross(U,vec3(0,1,0)),K=cross(U,k);"
             "k=cross(K,U);"
             "vec3 O=f.z*U+f.x*k+f.y*K,L=m.z*d+m.x*k+m.y*K;"
             "vec2 B=L.xy/L.z*length(O.xy)/length(v-y)*.4;"
             "O.xy-=B*smoothstep(.01,0.,dot(O,m));"
             "float M=.2+p*.5,Q=length(O.xy),R=atan(O.x,O.y);"
             "vec3 S=mix(vec3(.5,.3,.1),vec3(0,.8,1),smoothstep(.16,.3,Q)*.3+cos(R*15.)*.04);"
             "float T=smoothstep(-.9,1.,h(vec3(Q*10.,R*30.+cos(Q*50.+h(vec3(R))*50.),0)));"
             "T+=smoothstep(-.9,1.,h(vec3(Q*10.,R*40.+cos(Q*30.+h(vec3(R))*50.)*2.,0)));"
             "J=S*(T*.5+.5)*smoothstep(.3,.29,Q);"
             "J*=vec3(1,.8,.7)*pow(max(0.,dot(normalize(vec3(3,1,-1)),O)),8.)*3e2+.5;"
             "float V=smoothstep(M,M+.02,Q);"
             "J*=V;"
             "J+=pow(F,vec3(800))*3;"
             "J=mix(J,vec3(.8),smoothstep(.29,.3,Q));"
             "J=mix(S*.3,J,smoothstep(0.,.05,abs(Q-.3)+.01));"
             "vec3 W=normalize(vec3(1,1.5,-1)),X=vec3(-W.x,W.y*.5,W.z);"
             "f=mix(normalize(f+(d+f)*4.),f,smoothstep(.3,.32,Q));"
             "G=g(reflect(m,f),W,X)*mix(.15,.2,V)*sqrt(l)*2.5;"
             "I(y);"
             "J*=smoothstep(0.,.015,w)*.4+.6;"
             "float Y=abs(sin(R*5.))-smoothstep(.15,.7,Q)*4.;"
             "Y=smoothstep(.449,.45,Y);"
             "vec3 Z=mix(vec3(0),vec3(.75,.5,1)*.5,Y);"
             "Z=mix(vec3(.7,.7,0),Z,smoothstep(.06,.1,Q));"
             "Z*=smoothstep(135.2,135.6,t);"
             "J+=Z;"
             "F*=0.;"
           "}"
         "else"
           " if(c.y==5.)"
             "J=vec3(.85,.95,1),P*=0.,F=pow(F,vec3(8))*l*2.;"
           "else"
             " if(c.y==6.)"
               "{"
                 "vec3 O=y-n;"
                 "P*=0.;"
                 "F=pow(F,vec3(8))*l*20.;"
                 "if(f.z>.5)"
                   "{"
                     "float Q=E(O-vec3(0,7.5,-5),vec2(1.3,.2),.01);"
                     "J=vec3(1.5,0,0);"
                     "float k=smoothstep(.13,.1295,distance(O,vec3(0,7.1,-4.9)));"
                     "k+=smoothstep(.005,0.,E(O.xy-vec2(0,7.34),.06,.14,1.));"
                     "J=mix(J,vec3(2),smoothstep(.005,0.,Q));"
                     "J=mix(J,vec3(0),k);"
                   "}"
                 "else"
                   " J=vec3(.85,.95,1);"
               "}"
             "else"
               " if(c.y==7.)"
                 "{"
                   "vec3 O=y-z;"
                   "P*=0.;"
                   "F=pow(F,vec3(8))*l*10.;"
                   "if(f.z>.5)"
                     "{"
                       "J=vec3(0,0,1.5);"
                       "O.y-=7.4;"
                       "float Q=C(O-vec3(0,.1,-5),vec3(.8,.8,1)),k=0.;"
                       "O.xy=C(.8)*O.xy;"
                       "k+=smoothstep(.01,0.,E(O.xy-vec2(-.04,-.6),.1,.05,1.));"
                       "k+=smoothstep(.01,0.,E(O.xy-vec2(-.04,.5),.16,.135,.15));"
                       "k*=smoothstep(0.,.01,E(O.xy-vec2(-.12,.56),.001,.02,.2));"
                       "k*=smoothstep(0.,.01,E(O.xy-vec2(0,.56),.001,.02,.2));"
                       "O.xy=C(-1.6)*O.xy;"
                       "k+=smoothstep(.01,0.,E(O.xy-vec2(.04,-.6),.1,.05,1.));"
                       "k+=smoothstep(.01,0.,E(O.xy-vec2(.04,.5),.16,.1,.15));"
                       "J=mix(J,vec3(2),smoothstep(.01,0.,Q));"
                       "J=mix(J,vec3(0),k);"
                     "}"
                   "else"
                     " J=vec3(1);"
                 "}"
               "else"
                 " if(c.y==8.)"
                   "{"
                     "vec3 O=y-x;"
                     "O.x+=cos(.775+t)*3.1*.2;"
                     "O.y-=2.8;"
                     "O.zy=C(.75)*O.zy;"
                     "J=mix(vec3(2,.75,0),vec3(2,2,0),smoothstep(0.,.45,length(O-vec3(0,.3,0))))*1.8;"
                     "P=vec3(.01);"
                     "F*=0.;"
                   "}"
                 "else"
                   " if(c.y==10.)"
                     "J=vec3(0,.05,0),F*=l;"
                   "else"
                     " if(c.y==9.)"
                       "{"
                         "vec3 O=y-x;"
                         "O.x+=cos(.775+t)*3.1*.2;"
                         "O.y-=2.8;"
                         "O.zy=C(.75)*O.zy;"
                         "J=mix(vec3(1)+.5,vec3(.75,.5,1),smoothstep(.5,1.1,length(O-vec3(0,.3,0))))*2.;"
                         "P*=0.;"
                         "F=pow(F,vec3(4))*l;"
                       "}"
                     "else"
                       " if(c.y==11.)"
                         "J=vec3(1),H*=vec3(.1)*l,N*=vec3(.1)*l,u*=0.,P*=0.,F=pow(F,vec3(100))*l*2.;"
                       "else"
                         " if(c.y==12.)"
                           "{"
                             "J=vec3(1,.01,.01)*.3;"
                             "float k=l*l;"
                             "H*=vec3(3);"
                             "N*=vec3(2)*k;"
                             "P*=0.;"
                             "F=vec3(1,.3,.3)*pow(F,vec3(500))*5.;"
                           "}"
                         "else"
                           " if(c.y==2.)"
                             "J=vec3(1,.7,.5),N*=vec3(1,.75,.75),P=pow(P,vec3(.5,2.5,5)+2.)*2.,F=pow(F,vec3(4))*l*.02;"
   "vec3 O=(J*(N+H*.5+u*2.+P*2.)+G+F*o+b)*i;"
   "float Q=length(y-v);"
   "O=mix(O,A(m,s,i),smoothstep(90.,1e2,Q));"
   "O=clamp(O,0.,1.);"
   "if(c.y==0.)"
     "{"
       "float k=length(s)*.5,U=cos(atan(s.x,s.y)*15.-t*3.-k*30.*e.y);"
       "vec3 K=mix(vec3(1,.5,0),vec3(.8,.5,1),(cos(k*5.+t*5.)*.5+.5)*e.y);"
       "O=mix(O,mix(K,vec3(1),smoothstep(-k,k,U)),e.x);"
     "}"
   "return O;"
 "}"
 "float F(vec2 v,float y,float m)"
 "{"
   "vec2 f=vec2(.81,-.59),s=vec2(-f.x,f.y);"
   "v.x=abs(v.x);"
   "v-=2.*max(dot(f,v),0.)*f;"
   "v-=2.*max(dot(s,v),0.)*s;"
   "v.x=abs(v.x);"
   "v.y-=y;"
   "vec2 c=m*vec2(-f.y,f.x)-vec2(0,1);"
   "float x=clamp(dot(v,c)/dot(c,c),0.,y);"
   "return length(v-c*x)*sign(v.y*c.x-v.x*c.y);"
 "}"
 "void main()"
 "{"
   "vec2 m=gl_FragCoord.xy/v,y=m*2.-1.;"
   "y.x*=v.x/v.y;"
   "vec3 s=c,x=a,z=A(s,x)*normalize(vec3(y,o-length(y)*u));"
   "float i=F(s,z);"
   "vec3 d=s+z*i,P=J(d),r=A(s,z,d,P,y);"
   "{"
     "vec2 l=y*5.;"
     "l.x=abs(l.x-.3)-1.5;"
     "l.y-=1.4;"
     "l=C(t*5.)*l;"
     "float k=1.4+.2*sin(t*20.);"
     "k*=smoothstep(.5,1.,e.x);"
     "float n=F(l,k,.5);"
     "vec3 O=mix(vec3(1,.6,0),vec3(1,.2,0),smoothstep(-.1,.6,F(l,k*.5,.5)))*1.3;"
     "r=mix(r,O,smoothstep(0.,-.01,n)*e.x);"
   "}"
   "r=pow(r,vec3(1./2.2));"
   "r=pow(r,vec3(1,1.05,1.1));"
   "r*=smoothstep(0.,10.,t);"
   "float n=length(gl_FragCoord.xy/v.xx-vec2(.5,.3)),l=max(.137,smoothstep(157.,156.,t));"
   "r*=smoothstep(l,l-.005,n);"
   "float O=n,Q=smoothstep(.135,.136,O)*smoothstep(157.,158.,t);"
   "O=fract(23.*pow(O,.25));"
   "O-=smoothstep(.95,.99,O);"
   "vec3 k=mix(vec3(1,.6,0),vec3(1,0,0),pow(O,1.));"
   "r=mix(r,k,Q);"
   "r/=1.+pow(length(m*2.-1.),4.)*.04;"
   "r*=smoothstep(162.,161.,t);"
   "f=vec4(r,1);"
 "}";

const char *mouton_vert =
 "#version 150\n"
 "in vec4 O;"
 "out vec3 m,s,y,x,z,n,i,r,c,a,d;"
 "out vec2 l,e;"
 "out float b,o,p,u,k;"
 "uniform float t;"
 "void main()"
 "{"
   "gl_Position=O;"
   "float v=t;"
   "y=vec3(0);"
   "z=vec3(9e7);"
   "x=vec3(9e7);"
   "n=vec3(9e7);"
   "i=vec3(9e7);"
   "o=2.;"
   "b=max(fract(t*.333),fract(t*.123+.1));"
   "e=vec2(0);"
   "r=normalize(vec3(3.5,1,-1));"
   "s=vec3(1);"
   "u=0.;"
   "l=vec2(0);"
   "k=1.;"
   "p=0.;"
   "if(v<10.)"
     "m=vec3(1,.2,1),s=vec3(1,1,.5),d=normalize(vec3(0,.45,1)),l.y=.25,o=4.,c=vec3(0,2.5,-3.7),a=vec3(0,3,0);"
   "else"
     " if(v<20.)"
       "{"
         "float f=v-10.;"
         "m=vec3(1,.2,.25);"
         "s=vec3(1,1,2);"
         "d=normalize(vec3(0,.5,1));"
         "l.y=.25;"
         "o=4.;"
         "c=vec3(5,.5,0);"
         "a=vec3(0,.5,1);"
       "}"
     "else"
       " if(v<30.)"
         "{"
           "float f=v-20.;"
           "m=vec3(1,.2,.25);"
           "s=vec3(1,1,2);"
           "d=normalize(vec3(0,.5,1));"
           "l.y=.25;"
           "o=2.;"
           "c=vec3(5.+f*.5,2,f*.5);"
           "a=vec3(0,2,0);"
         "}"
       "else"
         " if(v<50.)"
           "{"
             "float f=v-30.;"
             "m=vec3(1,.2,.25);"
             "s=vec3(1,1,2);"
             "d=normalize(vec3(0,.5,1));"
             "l.y=.25;"
             "float J=f*.35+.3;"
             "r=normalize(vec3(cos(J),sin(J),-.3));"
             "o=1.5;"
             "c=vec3(22,2,f*.6-10.);"
             "a=vec3(0,2,f*.6-10.);"
           "}"
         "else"
           " if(v<55.)"
             "{"
               "float f=v-50.,F=smoothstep(2.,2.5,f);"
               "l.y=mix(.25,0.,F);"
               "m=vec3(1.-F,.2*(1.-F),1);"
               "s=vec3(1,1,.5);"
               "d=normalize(vec3(F*.3,.3-F*.3,1));"
               "p=smoothstep(4.6,4.8,f)*.2;"
               "o=4.;"
               "c=vec3(0,3,-4);"
               "a=vec3(0,3,0);"
               "if(f>3.)"
                 "b=max(fract(t*.333),fract(t*.333+.08));"
             "}"
           "else"
             " if(v<58.)"
               "{"
                 "float f=v-55.;"
                 "y=vec3(0);"
                 "z=vec3(-5,0,-8);"
                 "d=normalize(vec3(.3,0,1));"
                 "p=.2;"
                 "m=vec3(0,0,1);"
                 "s=vec3(3,1.5,6);"
                 "float J=smoothstep(0.,.5,f);"
                 "o=mix(4.,3.,J);"
                 "c=vec3(0,3,-4);"
                 "a=mix(vec3(0,3,0),vec3(-5,5,-9),J);"
               "}"
             "else"
               " if(v<65.)"
                 "{"
                   "float f=v-58.;"
                   "e.x=smoothstep(0.,.5,f);"
                   "m=vec3(0);"
                   "b=0.;"
                   "d=normalize(vec3(.3,0,1));"
                   "c=mix(vec3(0,3,-4),vec3(0,2,-6),e.x);"
                   "a=vec3(0,3,0);"
                   "o=mix(4.,3.,e.x)+smoothstep(0.,7.,f)*.5;"
                 "}"
               "else"
                 " if(v<70.)"
                   "{"
                     "float f=v-65.;"
                     "d=normalize(vec3(0,0,1));"
                     "y=vec3(0,0,-f*3.-2.);"
                     "z=vec3(-5,0,-8);"
                     "m=vec3(1,1,.5);"
                     "s=vec3(3,1.5,8)*1.5;"
                     "c=vec3(16,5,9);"
                     "a=vec3(3,5,-2.-f);"
                     "o=3.;"
                   "}"
                 "else"
                   " if(v<80.)"
                     "{"
                       "float f=v-70.;"
                       "m=vec3(1);"
                       "s=vec3(3,1.5,8);"
                       "float J=mod(f,8.),F=smoothstep(.5,1.,J)*smoothstep(2.8,2.5,J)-smoothstep(4.,4.5,J)*smoothstep(5.8,5.5,J)+cos(t)*.2;"
                       "d=normalize(vec3(F,cos(t*.5)*.1+.1,1));"
                       "u=.3;"
                       "o=2.5;"
                       "c=vec3(2.75,1,-5.25);"
                       "a=vec3(0,2.3,0);"
                       "float P=mod(f,2.);"
                       "k+=smoothstep(.5,.6,P)*smoothstep(.7,.6,P)*.3;"
                       "P=mod(f+.3,3.);"
                       "k+=smoothstep(.5,.6,P)*smoothstep(.7,.6,P)*.3;"
                     "}"
                   "else"
                     " if(v<85.)"
                       "{"
                         "float f=v-80.,F=smoothstep(1.,3.,f);"
                         "m=vec3(0,1.-F*.5,1);"
                         "s=vec3(3,1.5,6);"
                         "d=normalize(vec3(F*.5,.3-F*.45,1));"
                         "o=4.;"
                         "c=vec3(0,3,-4);"
                         "a=vec3(0,3,0);"
                         "if(f>3.)"
                           "b=max(fract(t*.333),fract(t*.333+.08));"
                       "}"
                     "else"
                       " if(v<89.)"
                         "{"
                           "float f=v-85.;"
                           "y=vec3(0);"
                           "n=vec3(-5,0,-8);"
                           "d=normalize(vec3(.5,-.15,1));"
                           "m=vec3(0,.5,1);"
                           "s=vec3(3,1.5,6);"
                           "float J=smoothstep(0.,1.,f);"
                           "o=mix(4.,3.,J);"
                           "c=vec3(0,3,-4);"
                           "a=mix(vec3(0,3,0),vec3(-5,5,-9),J);"
                         "}"
                       "else"
                         " if(v<97.)"
                           "{"
                             "float f=v-89.;"
                             "y=vec3(0,0,-11);"
                             "n=vec3(-5,0,-8);"
                             "d=normalize(mix(vec3(1,-.5,1),vec3(0,.5,1),smoothstep(2.8,3.2,f)));"
                             "d=normalize(mix(d,vec3(1,-.5,1),smoothstep(6.5,7.,f)));"
                             "l.y=smoothstep(3.,3.5,f)*.6;"
                             "l.x=smoothstep(3.,3.5,f)*smoothstep(8.,6.,f)*.25*sin(f*3.);"
                             "m=vec3(1,.2,.5);"
                             "s=vec3(0,.2,1);"
                             "c=vec3(-3,4.8,-30);"
                             "a=vec3(-3,4,0);"
                             "o=3.5;"
                           "}"
                         "else"
                           " if(v<107.)"
                             "{"
                               "float f=v-98.,F=smoothstep(6.,9.,f);"
                               "y=vec3(0,0,f*.25-11.);"
                               "n=vec3(-2,0,-8);"
                               "d=normalize(vec3(-.5,.25-F,1));"
                               "l.y=.5-F;"
                               "m=vec3(1,.2,.5);"
                               "s=vec3(-1,1,1)*.5;"
                               "c=vec3(18,5,-5);"
                               "a=vec3(-5,5,-6);"
                               "o=3.;"
                             "}"
                           "else"
                             " if(v<109.)"
                               "{"
                                 "float f=v-107.;"
                                 "m=vec3(0);"
                                 "s=vec3(0);"
                                 "n=vec3(0,0,-8);"
                                 "a=mod(f,2.)<1.?"
                                   "(c=vec3(0,2,-8),vec3(0,3,0)):"
                                   "(c=vec3(0,5.5,2),vec3(0,5.75,0));"
                                 "d=normalize(vec3(0,-.1,1));"
                                 "o=3.+f*.1;"
                               "}"
                             "else"
                               " if(v<116.)"
                                 "{"
                                   "float f=v-109.,F=sin(min(f,5.));"
                                   "m=vec3(0);"
                                   "s=vec3(0);"
                                   "d=normalize(vec3(F*.7,0,1));"
                                   "d=normalize(mix(d,vec3(-.3,.2,1),smoothstep(5.2,5.4,f)));"
                                   "l.x=F*.25;"
                                   "p=smoothstep(6.,6.2,f)*.2;"
                                   "y=vec3(0,(smoothstep(6.,6.2,f)-smoothstep(6.2,6.4,f))*.4,0);"
                                   "o=3.5;"
                                   "c=vec3(0,2,-8);"
                                   "a=vec3(0,3,0);"
                                 "}"
                               "else"
                                 " if(v<125.)"
                                   "{"
                                     "float f=v-116.;"
                                     "y=vec3(9e7);"
                                     "n=vec3(-2,0,-8);"
                                     "x=vec3(5,0,-20);"
                                     "float J=smoothstep(.5,1.5,f);"
                                     "o=mix(3.5,5.,J);"
                                     "c=vec3(0,5.5,2);"
                                     "a=mix(vec3(-.5,5.75,0),vec3(5,2,-20),J);"
                                     "e.x=J*.3;"
                                   "}"
                                 "else"
                                   " if(v<137.)"
                                     "{"
                                       "float f=v-125.;"
                                       "m=vec3(.1);"
                                       "s=vec3(.2);"
                                       "o=2.8+f*.15;"
                                       "int J=int(f);"
                                       "if(J%4==1)"
                                         "n=vec3(0,0,-8),c=vec3(2.5,2,-1),a=vec3(1,5.25,-8),o=2.8+pow(f*.3,1.2);"
                                       "else"
                                         " if(J%4==3)"
                                           "x=vec3(4,0,-8),c=vec3(0,5.5,2),a=vec3(4,3,-8),e.x=.3+.2/12.,e.y=f/12.;"
                                         "else"
                                           " c=vec3(0,2.4,-8),a=vec3(0,3,0);"
                                       "float F=smoothstep(.3,.7,fract(f));"
                                       "if(J%4==0)"
                                         "F=1.-F;"
                                       "l.x=-F*.1;"
                                       "d=normalize(mix(vec3(.1,-.25,1),vec3(-.2,.2,1),F));"
                                       "d=normalize(d+vec3(cos(f*10.),cos(f*5.),1)*.01);"
                                     "}"
                                   "else"
                                     " if(v<140.)"
                                       "{"
                                         "float f=v-137.;"
                                         "m=vec3(0,.1,0);"
                                         "s=vec3(0,.5,0);"
                                         "c=vec3(0,2.4,-8);"
                                         "a=vec3(0,3,0);"
                                         "l.x=-.1;"
                                         "l.y=sin(f*2.)*.1;"
                                         "p=smoothstep(0.,3.,f)*.1;"
                                         "d=normalize(vec3(-.2,.2,1));"
                                         "o=3.2-f*.15;"
                                         "e.x=.1;"
                                         "e.y=5.;"
                                       "}"
                                     "else"
                                       " if(v<150.)"
                                         "{"
                                           "float f=v-140.;"
                                           "d=normalize(vec3(0,0,1));"
                                           "y=vec3(0,0,-f*2.-2.);"
                                           "x=vec3(0,-.5,-30);"
                                           "m=vec3(1,1,.5);"
                                           "s=vec3(3,1.5,8);"
                                           "float J=smoothstep(0.,10.,f);"
                                           "c=vec3(-2,3.5,mix(-10.,-33.,J));"
                                           "a=vec3(2,2,-3.-f*2.);"
                                           "o=3.;"
                                         "}"
                                       "else"
                                         " if(v<155.)"
                                           "{"
                                             "float f=v-150.;"
                                             "d=normalize(vec3(0,0,1));"
                                             "y=vec3(0,(1.-smoothstep(.3,.25,f))*-4.8,-22.-f*2.);"
                                             "x=vec3(2,0,-30);"
                                             "m=vec3(1,1,.5);"
                                             "s=vec3(3,1.5,8);"
                                             "c=vec3(-20,6,-13)+vec3(cos(f*72.),cos(f*64.),sin(f*48.))*3.*smoothstep(.3,.31,f)*smoothstep(.7,.1,f);"
                                             "a=vec3(3,2,-23);"
                                             "o=mix(4.,4.2,smoothstep(0.,5.,f));"
                                             "i=vec3(0,smoothstep(.3,.2,f)*13.,-22);"
                                           "}"
                                         "else"
                                           "{"
                                             "float f=v-155.;"
                                             "d=normalize(vec3(0,0,1));"
                                             "y=vec3(9e7);"
                                             "n=vec3(-1,0,-8);"
                                             "x=vec3(1,0,-25);"
                                             "a=vec3(2,3.6,-18);"
                                             "c=vec3(5,5,2);"
                                             "float J=smoothstep(1.5,2.,f);"
                                             "o=2.5+J*4.2;"
                                             "i=vec3(7,0,-20);"
                                           "}"
 "}";

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 P=vec2(1280,720);"
 "uniform sampler2D K;"
 "void main()"
 "{"
   "vec2 y=1./P,v=gl_FragCoord.xy*y;"
   "vec4 s=vec4(v,v-y*.5);"
   "vec3 c=textureLod(K,s.zw,0.).xyz,m=textureLod(K,s.zw+vec2(1,0)*y.xy,0.).xyz,d=textureLod(K,s.zw+vec2(0,1)*y.xy,0.).xyz,x=textureLod(K,s.zw+vec2(1)*y.xy,0.).xyz,F=textureLod(K,s.xy,0.).xyz,a=vec3(.299,.587,.114);"
   "float i=dot(c,a),J=dot(m,a),O=dot(d,a),z=dot(x,a),t=dot(F,a),o=min(t,min(min(i,J),min(O,z))),n=max(t,max(max(i,J),max(O,z)));"
   "vec2 l=vec2(-(i+J-O-z),i+O-J-z);"
   "float k=1./(min(abs(l.x),abs(l.y))+1./128.);"
   "l=min(vec2(8),max(vec2(-8),l*k))*y.xy;"
   "vec3 r=.5*(textureLod(K,s.xy+l*(1./3.-.5),0.).xyz+textureLod(K,s.xy+l*(2./3.-.5),0.).xyz),G=r*.5+.25*(textureLod(K,s.xy+l*-.5,0.).xyz+textureLod(K,s.xy+l*.5,0.).xyz);"
   "float p=dot(G,a);"
   "f=p<o||p>n?"
     "vec4(r,1):"
     "vec4(G,1);"
 "}";

#endif // SHADERS_INL_
