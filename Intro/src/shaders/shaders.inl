// Generated with Shader Minifier 1.3.3 (https://github.com/laurentlb/Shader_Minifier/)
#ifndef SHADERS_INL_
# define SHADERS_INL_
# define VAR_a_position "M"
# define VAR_animationAmp "m"
# define VAR_animationSpeed "y"
# define VAR_anvilPos "n"
# define VAR_blink "e"
# define VAR_camFocal "u"
# define VAR_camPos "c"
# define VAR_camTa "a"
# define VAR_excited "p"
# define VAR_eyeDir "d"
# define VAR_eyesSurprise "o"
# define VAR_fishEyeFactor "w"
# define VAR_flowerPos "x"
# define VAR_fragColor "f"
# define VAR_headRot "l"
# define VAR_iTime "t"
# define VAR_noseSize "k"
# define VAR_panelPos "z"
# define VAR_panelWarningPos "i"
# define VAR_prevPass "L"
# define VAR_sheepPos "s"
# define VAR_sunDir "r"

const char *mouton_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 v=vec2(1280,720);"
 "in vec3 m,y,s,x,z,i,n,r,c,a,d;"
 "in vec2 l;"
 "in float e,u,o,p,w,k;"
 "uniform float t;"
 "const float U=acos(-1.);"
 "vec2 h(vec2 i,vec2 y)"
 "{"
   "return i.x<y.x?"
     "i:"
     "y;"
 "}"
 "vec2 g(vec2 v,float i)"
 "{"
   "float y=atan(v.y,v.x),s=length(v);"
   "y=mod(y-i/2.,i)-i/2.;"
   "return vec2(cos(y),sin(y))*s;"
 "}"
 "vec2 g(vec3 i,vec3 v,vec3 m,vec3 t)"
 "{"
   "vec3 y=t*i,x=abs(t)*m,c=-y-x,d=-y+x;"
   "float a=max(max(c.x,c.y),c.z),s=min(min(d.x,d.y),d.z);"
   "return a>s||s<0.?"
     "vec2(-1):"
     "vec2(a,s);"
 "}"
 "vec3 g(vec3 v)"
 "{"
   "uvec3 y=uvec3(v*1e5);"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "y=(y>>8U^y.yzx)*1103515245U;"
   "return vec3(y)*(1./float(-1U));"
 "}"
 "vec3 g(vec3 v,vec2 m,float y)"
 "{"
   "vec3 f=vec3(1);"
   "float i=max(dot(v,r),0.);"
   "f+=vec3(1,.7,.3)*pow(i,1.);"
   "f+=vec3(1,.5,.1)*pow(i,52.);"
   "f=vec3(1)*y*y;"
   "vec2 x=vec2(cos(t*.7+2.4),sin(t*.7+2.4)*.75);"
   "float s=smoothstep(.151,.15,length(m-x));"
   "s*=smoothstep(.15,.1501,length(m-x-vec2(.1,.025)));"
   "s+=exp(-length(m-x)*2.)*.1;"
   "s*=smoothstep(.5,0.,r.y);"
   "vec2 c=m*2e2,a=fract(c)-.5,d=floor(c);"
   "vec3 l=g(vec3(abs(d),abs(d.x)));"
   "float z=l.z*.1;"
   "s+=smoothstep(z,z*.01,length(l.xy-.5+a))*(cos(t*l.y+l.z*3.14)*.5+.5);"
   "f+=s*smoothstep(.5,-1.,r.y);"
   "return f;"
 "}"
 "float h(float v)"
 "{"
   "return fract(v*17.*fract(v*.3183099));"
 "}"
 "float C(vec3 v)"
 "{"
   "vec3 m=floor(v),s=fract(v),y=s*s*s*(s*(s*6.-15.)+10.);"
   "float i=m.x+317.*m.y+157.*m.z,x=h(i),c=h(i+1.),d=h(i+317.),a=h(i+318.),f=h(i+157.),z=h(i+158.),u=h(i+474.),t=h(i+475.);"
   "return-1.+2.*(x+(c-x)*y.x+(d-x)*y.y+(f-x)*y.z+(x-c-d+a)*y.x*y.y+(x-d-f+u)*y.y*y.z+(x-c-f+z)*y.z*y.x+(-x+c+d-a+f-z-u+t)*y.x*y.y*y.z);"
 "}"
 "vec2 B(vec3 v)"
 "{"
   "v.xz-=n.xz;"
   "v.y-=-n.y;"
   "float y=v.y+smoothstep(1.,20.,length(v.xz));"
   "return y<.4?"
     "(y-=pow((C(v*.7+1.)*.5+C(v*1.7+1e2)*.3+C(v*2.7+1e2)*.1)*.5+.5,3.)*.45*(1.-exp(-(t-150.)*4.))+.03,vec2(y,12)):"
     "vec2(9e7,0);"
 "}"
 "mat3 B(vec3 v,vec3 y)"
 "{"
   "const vec3 i=vec3(0,1,0);"
   "vec3 x=normalize(y-v),c=normalize(cross(x,normalize(i)));"
   "return mat3(c,cross(c,x),x);"
 "}"
 "mat2 A(float v)"
 "{"
   "float y=cos(v),x=sin(v);"
   "return mat2(y,x,-x,y);"
 "}"
 "float A(vec3 v,vec3 x)"
 "{"
   "vec3 y=abs(v)-x;"
   "return length(max(y,0.))+min(max(y.x,max(y.y,y.z)),0.);"
 "}"
 "vec2 D(vec3 v)"
 "{"
   "v-=n;"
   "v.xz=A(1.)*v.xz;"
   "float y=pow(clamp(v.y-1.,.004,1.),.5),f=A(v-vec3(0,1,0),vec3(1.5-y,1,2.5-y));"
   "if(f<10.)"
     "{"
       "f=min(f,A(v-vec3(0,3,0),vec3(2,1,3)));"
       "float i=length((v.yz-vec2(4.5,3))*vec2(1,.8))-2.;"
       "i=max(i,abs(v.x)-.5);"
       "i=max(i,v.y-3.5);"
       "f=min(f,i);"
       "vec2 x=vec2(f-.1,11);"
       "return x;"
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
       "float i=A(v-vec3(0,4,-5.1),vec3(.11,4,.08));"
       "vec2 f=vec2(i,5);"
       "f=h(f,vec2(y,7));"
       "return f;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "float A(vec3 v,float y,float i,float x)"
 "{"
   "vec2 m=vec2(length(v.xz),v.y),c=vec2(x,y),t=vec2(x-i,2.*y),d=vec2(m.x-min(m.x,m.y<0.?"
     "i:"
     "x),abs(m.y)-y),f=m-c+t*clamp(dot(c-m,t)/dot(t,t),0.,1.);"
   "return(f.x<0.&&d.y<0.?"
     "-1.:"
     "1.)*sqrt(min(dot(d,d),dot(f,f)));"
 "}"
 "float B(vec3 v,vec3 x,vec3 m,float y)"
 "{"
   "vec3 i=v-x,c=m-x;"
   "float s=clamp(dot(i,c)/dot(c,c),0.,1.);"
   "return length(i-c*s)-y;"
 "}"
 "float C(vec3 v,vec2 y)"
 "{"
   "vec2 i=vec2(length(v.xy)-y.x,v.z);"
   "return length(i)-y.y;"
 "}"
 "float D(vec3 v,vec3 y)"
 "{"
   "float i=length(v/y),x=length(v/(y*y));"
   "return i*(i-1.)/x;"
 "}"
 "vec2 F(vec3 v)"
 "{"
   "v-=x;"
   "vec3 y=v;"
   "y.x+=cos(.775+t)*3.1*.2;"
   "y.y-=2.8;"
   "y.zy=A(.7)*y.zy;"
   "float i=D(y-vec3(0,.3,0),vec3(1,.2+cos(y.x*150.)*sin(y.z*150.)*.05,1)*.25);"
   "if(i<5.)"
     "{"
       "vec2 m=vec2(i,8);"
       "vec3 f=y;"
       "f.xz=g(f.xz,U*.2);"
       "float c=D(f-vec3(.5,.2+sin(f.x*2.)*.2,0),vec3(2,.1+sin(f.z*40.)*.02,.75)*.25);"
       "if(c<m.x)"
         "m=vec2(c,9);"
       "float d=max(length(v.xz+vec2(cos(v.y*.25+t)*v.y*.2,-.075))-smoothstep(3.1,0.,v.y)*.05-.02,v.y-3.1);"
       "if(d<m.x)"
         "m=vec2(d,10);"
       "return m;"
     "}"
   "return vec2(9e7,0);"
 "}"
 "float A(float v,float i,float y)"
 "{"
   "float x=clamp(.5+.5*(i-v)/y,0.,1.);"
   "return mix(i,v,x)-y*x*(1.-x);"
 "}"
 "float B(float v,float y,float i)"
 "{"
   "i*=1.4;"
   "float m=max(i-abs(v-y),0.);"
   "return max(v,y)+m*m*m/(6.*i*i);"
 "}"
 "vec2 G(vec3 v)"
 "{"
   "v-=s;"
   "float i=mod(t,1.);"
   "i=smoothstep(0.,1.,abs(i*2.-1.));"
   "v.y-=1.;"
   "v.z-=-2.;"
   "float c=t*y.x;"
   "vec3 x=vec3(cos(c*U),cos(c*U*2.)*.1,0)*.025*m.x;"
   "float f=length(v*vec3(1,1,.825)-vec3(0,1.5,2.55)-x)-2.;"
   "if(f<3.)"
     "{"
       "float d=pow(C((v-x-vec3(.05,0,0))*2.)*.5+.5,.75)*2.-1.;"
       "f=f+.05-d*.2;"
       "float a=mod(t*y.x,2.);"
       "vec4 u=vec4(0),r=vec4(0);"
       "float z=smoothstep(0.,.5,a),n=smoothstep(.5,1.,a),p=smoothstep(1.,1.5,a),w=smoothstep(1.5,2.,a);"
       "u.z=z*(1.-z);"
       "u.x=n*(1.-n);"
       "u.w=p*(1.-p);"
       "u.y=w*(1.-w);"
       "r+=a*.5;"
       "r.x-=n;"
       "r.z-=z;"
       "r.y-=w;"
       "r.w-=p;"
       "r*=m.x;"
       "vec3 e=v;"
       "e.x-=.8;"
       "e.z-=2.+r.x;"
       "e.yz=A(u.x)*e.yz;"
       "float g=A(e-vec3(0),.7,.3,.2),G=A(e-vec3(0,-.8,0),.2,.35,.3);"
       "e=v;"
       "e.x+=1.;"
       "e.z-=2.+r.y;"
       "e.yz=A(u.y)*e.yz;"
       "g=min(g,A(e-vec3(0),.7,.3,.2));"
       "G=min(G,A(e-vec3(0,-.8,0),.2,.35,.3));"
       "e=v;"
       "e.x-=1.;"
       "e.z-=4.+r.z;"
       "e.yz=A(u.z)*e.yz;"
       "g=min(g,A(e-vec3(0),.7,.3,.2));"
       "G=min(G,A(e-vec3(0,-.8,0),.2,.35,.3));"
       "e=v;"
       "e.x+=1.;"
       "e.z-=4.+r.w;"
       "e.yz=A(u.w)*e.yz;"
       "g=min(g,A(e-vec3(0),.7,.3,.2));"
       "G=min(G,A(e-vec3(0,-.8,0),.2,.35,.3));"
       "vec3 I=v+vec3(0,-2,-1.2);"
       "I.xz=A((i*y.y-.5)*.25*m.y+l.x)*I.xz;"
       "I.zy=A(sin(t*y.y)*.25*m.y-l.y)*I.zy;"
       "float D=length(I-vec3(0,-1.3,-1.2))-1.;"
       "D=A(D,length(I-vec3(0))-.5,1.8);"
       "vec3 E=I;"
       "E*=vec3(.7,1,.7);"
       "float F=length(I-vec3(0,.35,-.1))-.55;"
       "F-=(cos(I.z*8.+I.y*4.5+I.x*4.)+cos(I.z*4.+I.y*6.5+I.x*8.))*.05;"
       "F=A(F,f,.1);"
       "E=I;"
       "E.yz=A(-.6)*E.yz;"
       "E.x=abs(v.x)-.8;"
       "E*=vec3(.3,1,.4);"
       "E-=vec3(0,-.05-pow(E.x,2.)*5.,-.1);"
       "float H=length(E)-.15;"
       "H=B(H,-(length(E-vec3(0,-.1,0))-.12),.01);"
       "E=I;"
       "E.x=abs(I.x)-.4;"
       "float J=length(E*vec3(1,1,1.-o)-vec3(0,0,-1))-.3;"
       "E.x=abs(I.x)-.2;"
       "E.xz=A(-.45)*E.xz;"
       "float K=C(E-vec3(-.7,-1.2,-2),vec2(.15*k,.05)),L=B(v-vec3(0,-.1,cos(v.y-.7)*.5),vec3(cos(t*y.z)*m.z,.2,5),vec3(0,2,4.9),.2);"
       "L-=(cos(v.z*8.+v.y*4.5+v.x*4.)+cos(v.z*4.+v.y*6.5+v.x*3.))*.02;"
       "L=A(f,L,.1);"
       "vec2 M=vec2(f,1);"
       "M=h(M,vec2(L,1));"
       "M=h(M,vec2(F,1));"
       "M=h(M,vec2(g,2));"
       "M=h(M,vec2(D,2));"
       "M=h(M,vec2(J,3));"
       "M=h(M,vec2(K,2));"
       "M=h(M,vec2(G,4));"
       "M=h(M,vec2(H,2));"
       "return M;"
     "}"
   "return vec2(f,1);"
 "}"
 "float C(vec3 v,vec2 y,float i)"
 "{"
   "vec3 m=abs(v);"
   "return max(m.z-y.y,B(B(v.x*.866025+v.y*.5,-v.x*.866025+v.y*.5,i),-v.y,i)-y.x*.5);"
 "}"
 "vec2 H(vec3 v)"
 "{"
   "v-=i;"
   "float y=C(v-vec3(0,7.5,-5),vec2(1.7,.1),.3);"
   "if(y<8.)"
     "{"
       "y=B(y,-C(v-vec3(0,7.5,-5.1),vec2(1.6,.1),.3),.001);"
       "float f=A(v-vec3(0,4,-5.1),vec3(.11,4,.08));"
       "vec3 m=v;"
       "m.y=abs(m.y-7.3)-.3;"
       "f=min(f,A(m-vec3(0,0,-5.05),vec3(.35,.1,.05)));"
       "vec2 x=vec2(f,5);"
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
   "float f=0.,s=1.;"
   "for(int c=1;c<=2;c++)"
     "{"
       "float m=float(c)/2*i,a=I(v+m*y).x;"
       "f+=(m-a)*s;"
       "s*=.95;"
     "}"
   "return max(0.,1.-x*1.5*f);"
 "}"
 "float E(vec3 v,vec3 y)"
 "{"
   "vec3 m=1./y;"
   "float f=9e7,c;"
   "vec2 e=g(v-s-vec3(0,3,-2),y,vec3(3,3,7),m);"
   "if(e.y>0.)"
     "{"
       "c=max(e.x,0.);"
       "for(int u=0;u<128;u++)"
         "{"
           "vec3 d=v+y*c;"
           "float a=h(vec2(d.y,0),G(d)).x;"
           "c+=a;"
           "if(c>e.y||abs(a)<.001)"
             "break;"
         "}"
       "if(c<e.y)"
         "f=c;"
     "}"
   "e=g(v-z-vec3(0,5,-5),y,vec3(1.5,5,1),m);"
   "if(e.y>0.)"
     "{"
       "c=max(e.x,0.);"
       "for(int u=0;u<128;u++)"
         "{"
           "float d=E(v+y*c).x;"
           "c+=d;"
           "if(c>e.y||abs(d)<.001)"
             "break;"
         "}"
       "if(c<e.y)"
         "f=min(f,c);"
     "}"
   "e=g(v-i-vec3(0,5,-5),y,vec3(1.5,5,1),m);"
   "if(e.y>0.)"
     "{"
       "c=max(e.x,0.);"
       "for(int u=0;u<128;u++)"
         "{"
           "float d=H(v+y*c).x;"
           "c+=d;"
           "if(c>e.y||abs(d)<.001)"
             "break;"
         "}"
       "if(c<e.y)"
         "f=min(f,c);"
     "}"
   "e=g(v-x-vec3(0,5,0),y,vec3(2,5,1),m);"
   "if(e.y>0.)"
     "{"
       "c=max(e.x,0.);"
       "for(int u=0;u<128;u++)"
         "{"
           "float d=F(v+y*c).x;"
           "c+=d;"
           "if(c>e.y||abs(d)<.001)"
             "break;"
         "}"
       "if(c<e.y)"
         "f=min(f,c);"
     "}"
   "e=g(v-n-vec3(0,3,2),y,vec3(4,4,5),m);"
   "if(e.y>0.)"
     "{"
       "c=max(e.x,0.);"
       "for(int u=0;u<128;u++)"
         "{"
           "float d=D(v+y*c).x;"
           "c+=d;"
           "if(c>e.y||abs(d)<.001)"
             "break;"
         "}"
       "if(c<e.y)"
         "f=min(f,c);"
     "}"
   "c=-(v.y+.4)*m.y;"
   "if(c>0.&&length((v+y*c).xz-n.xz)<10.)"
     "{"
       "c=-c;"
       "for(int u=0;u<128;u++)"
         "{"
           "vec3 d=v+y*c;"
           "float a=min(d.y,B(d).x);"
           "c+=a;"
           "if(c>e.y||abs(a)<.001)"
             "break;"
         "}"
       "if(c<1e2)"
         "f=min(f,c);"
     "}"
   "c=-v.y*m.y;"
   "if(c>0.)"
     "f=min(f,c);"
   "return f;"
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
 "float D(vec3 v,vec3 y,float m,float i)"
 "{"
   "float f=1.,c=m;"
   "for(int u=0;u<64;u++)"
     "{"
       "float s=I(v+y*c).x;"
       "f=min(f,30.*s/c);"
       "c+=s;"
       "if(f<1e-4||c>i)"
         "break;"
     "}"
   "return clamp(f,0.,1.);"
 "}"
 "float E(vec2 v,float y,float i,float x)"
 "{"
   "v.x=abs(v.x);"
   "float c=(y-i)/x,f=sqrt(1.-c*c),m=dot(v,vec2(-c,f));"
   "return m<0.?"
     "length(v)-y:"
     "m>f*x?"
       "length(v-vec2(0,x))-i:"
       "dot(v,vec2(f,c))-y;"
 "}"
 "vec3 A(vec3 v,vec3 y,vec3 m,vec3 f,vec2 c)"
 "{"
   "vec2 u=I(m);"
   "float s=smoothstep(0.,.3,r.y)+.1,a=C(m,f,.15,1.);"
   "a*=C(m,f,1.,.1)*.5;"
   "float l=D(m,r,.08,50.),n=clamp(1.+dot(y,f),0.,5.);"
   "vec3 M=vec3(1,.8,.7)*max(dot(f,r),0.)*pow(vec3(l),vec3(1,1.2,1.5)),G=vec3(1,.8,.7)*.1*max(dot(f,-r),0.)*a,w=vec3(.5)*mix(C(m,y,.3,.75),C(m,r,.3,.75),.5),F=vec3(1)*max(dot(reflect(y,f),r),0.),k=vec3(.4,.45,.5)*a,L=vec3(0),H=vec3(0);"
   "if(u.y==0.)"
     "H=vec3(3),w=vec3(0),F=vec3(0);"
   "else"
     " if(u.y==1.)"
       "H=vec3(.4),w*=vec3(1)*(n*.5+.5),L=vec3(.35),F=pow(F,vec3(4))*n*.25;"
     "else"
       " if(u.y==4.)"
         "H=vec3(.025),w=vec3(0),F=pow(F,vec3(80))*n*10.;"
       "else"
         " if(u.y==3.)"
           "{"
             "w*=.5;"
             "H=vec3(1);"
             "float J=dot(f,normalize(vec3(0,0,1))),B=dot(f,d),h=smoothstep(-.953,-.952,B-o/2.);"
             "H*=h;"
             "F*=h;"
             "if(J>0.||e>.95)"
               "u.y=2.;"
             "F=pow(F,vec3(80))*n*3.;"
           "}"
         "else"
           " if(u.y==5.)"
             "H=vec3(1),w=vec3(0),F=pow(F,vec3(8))*n*2.;"
           "else"
             " if(u.y==6.)"
               "{"
                 "vec3 J=m-i;"
                 "w=vec3(0);"
                 "F=pow(F,vec3(8))*n*10.;"
                 "if(f.z>.5)"
                   "{"
                     "float B=C(J-vec3(0,7.5,-5),vec2(1.3,.2),.01);"
                     "H=vec3(1.5,0,0);"
                     "float U=smoothstep(.13,.1295,distance(J,vec3(0,7.1,-4.9)));"
                     "U+=smoothstep(.005,0.,E(J.xy-vec2(0,7.34),.06,.14,1.));"
                     "H=mix(H,vec3(2),smoothstep(.005,0.,B));"
                     "H=mix(H,vec3(0),U);"
                   "}"
                 "else"
                   " H=vec3(1);"
               "}"
             "else"
               " if(u.y==7.)"
                 "{"
                   "vec3 J=m-z;"
                   "w=vec3(0);"
                   "F=pow(F,vec3(8))*n*10.;"
                   "if(f.z>.5)"
                     "{"
                       "H=vec3(0,0,1.5);"
                       "J.y-=7.4;"
                       "float B=A(J-vec3(0,.1,-5),vec3(.8,.8,1)),U=0.;"
                       "J.xy=A(.8)*J.xy;"
                       "float K=.04;"
                       "U+=smoothstep(.01,0.,E(J.xy-vec2(-K,-.6),.1,.05,1.));"
                       "U+=smoothstep(.01,0.,E(J.xy-vec2(-K,.5),.16,.135,.15));"
                       "U*=smoothstep(0.,.01,E(J.xy-vec2(-K-.08,.56),.001,.02,.2));"
                       "U*=smoothstep(0.,.01,E(J.xy-vec2(-K+.04,.56),.001,.02,.2));"
                       "J.xy=A(-1.6)*J.xy;"
                       "U+=smoothstep(.01,0.,E(J.xy-vec2(K,-.6),.1,.05,1.));"
                       "U+=smoothstep(.01,0.,E(J.xy-vec2(K,.5),.16,.1,.15));"
                       "H=mix(H,vec3(2),smoothstep(.01,0.,B));"
                       "H=mix(H,vec3(0),U);"
                     "}"
                   "else"
                     " H=vec3(1);"
                 "}"
               "else"
                 " if(u.y==8.)"
                   "{"
                     "vec3 J=m-x;"
                     "J.x+=cos(.775+t)*3.1*.2;"
                     "J.y-=2.8;"
                     "J.zy=A(.75)*J.zy;"
                     "H=mix(vec3(2,.75,0),vec3(2,2,0),smoothstep(0.,.45,length(J-vec3(0,.3,0))))*1.8;"
                     "w=vec3(.01);"
                     "F=vec3(0);"
                   "}"
                 "else"
                   " if(u.y==10.)"
                     "H=vec3(0,.05,0),w*=vec3(1),F*=vec3(1)*n;"
                   "else"
                     " if(u.y==9.)"
                       "{"
                         "vec3 J=m-x;"
                         "J.x+=cos(.775+t)*3.1*.2;"
                         "J.y-=2.8;"
                         "J.zy=A(.75)*J.zy;"
                         "H=mix(vec3(1)+.5,vec3(.75,.5,1),smoothstep(.5,1.1,length(J-vec3(0,.3,0))))*2.;"
                         "w*=0.;"
                         "F=pow(F,vec3(4))*n;"
                       "}"
                     "else"
                       " if(u.y==11.)"
                         "H=vec3(1),M*=vec3(.1)*n,k*=vec3(.1)*n,G*=vec3(0)*n,w=vec3(0),F=pow(F,vec3(100))*n*2.;"
                       "else"
                         " if(u.y==12.)"
                           "{"
                             "H=vec3(1,.01,.01)*.3;"
                             "float J=n*n;"
                             "M*=vec3(3);"
                             "k*=vec3(2)*J;"
                             "G*=vec3(1);"
                             "w*=vec3(0);"
                             "F=vec3(1,.3,.3)*pow(F,vec3(500))*5.;"
                           "}"
   "if(u.y==2.)"
     "H=vec3(1,.7,.5),k*=vec3(1,.75,.75),w=pow(w,vec3(.5,2.5,5)+2.)*2.,F=pow(F,vec3(4))*n*.02;"
   "vec3 J=(H*(k+M*.5+G*2.+w*2.)+F*l+L)*s;"
   "float B=length(m-v);"
   "J=mix(J,g(y,c,s),smoothstep(90.,1e2,B));"
   "if(u.y==0.)"
     "{"
       "float U=cos(atan(c.x,c.y)*15.+t*3.),K=length(c)*.5;"
       "J=mix(J,mix(vec3(1,.5,0),vec3(1),smoothstep(-K,K,U)),p);"
     "}"
   "return clamp(J,0.,1.);"
 "}"
 "float D(vec2 v,float y,float m)"
 "{"
   "const vec2 f=vec2(.809016994375,-.587785252292),c=vec2(-f.x,f.y);"
   "v.x=abs(v.x);"
   "v-=2.*max(dot(f,v),0.)*f;"
   "v-=2.*max(dot(c,v),0.)*c;"
   "v.x=abs(v.x);"
   "v.y-=y;"
   "vec2 i=m*vec2(-f.y,f.x)-vec2(0,1);"
   "float x=clamp(dot(v,i)/dot(i,i),0.,y);"
   "return length(v-i*x)*sign(v.y*i.x-v.x*i.y);"
 "}"
 "void main()"
 "{"
   "vec2 y=vec2(1)/v,m=gl_FragCoord.xy*y,i=m*2.-1.;"
   "i.x*=v.x*y.y;"
   "vec3 x=c,d=a,s=B(x,d)*normalize(vec3(i,u-length(i)*w));"
   "float H=E(x,s);"
   "vec3 F=x+s*H,z=J(F),e=A(x,s,F,z,i);"
   "{"
     "vec2 r=i*5.;"
     "r.x=abs(r.x-.3)-1.5;"
     "r.y-=1.4;"
     "r=A(t*5.)*r;"
     "float n=1.4+.2*sin(t*20.);"
     "n*=smoothstep(.5,1.,p);"
     "float l=D(r,n,.5);"
     "vec3 M=mix(vec3(1,.6,0),vec3(1,.2,0),smoothstep(-.1,.6,D(r,n*.5,.5)))*1.3;"
     "e=mix(e,M,smoothstep(0.,-.01,l)*p);"
   "}"
   "e/=1.+pow(length(m*2.-1.),4.)*.04;"
   "f=vec4(pow(e,vec3(1./2.2)),1);"
 "}";

const char *mouton_vert =
 "#version 150\n"
 "in vec4 M;"
 "out vec3 m,y,s,x,z,i,n,r,c,a,d;"
 "out vec2 l;"
 "out float e,u,o,p,w,k;"
 "uniform float t;"
 "void main()"
 "{"
   "gl_Position=M;"
   "float v=t;"
   "s=vec3(0);"
   "z=vec3(9e7);"
   "x=vec3(9e7);"
   "i=vec3(9e7);"
   "n=vec3(9e7);"
   "u=2.;"
   "e=max(fract(t*.333),fract(t*.123+.1));"
   "p=0.;"
   "r=normalize(vec3(3.5,1,-1));"
   "y=vec3(1);"
   "w=0.;"
   "l=vec2(0);"
   "k=1.;"
   "o=0.;"
   "if(v<10.)"
     "m=vec3(1,.2,1),y=vec3(1,1,.5),d=normalize(vec3(0,.5,1)),l.y=.25,u=4.,c=vec3(0,2.5,-3.7),a=vec3(0,3,0);"
   "else"
     " if(v<20.)"
       "{"
         "float f=v-10.;"
         "m=vec3(1,.2,.25);"
         "y=vec3(1,1,2);"
         "d=normalize(vec3(0,.5,1));"
         "l.y=.25;"
         "u=4.;"
         "c=vec3(5,.5,0);"
         "a=vec3(0,.5,1);"
       "}"
     "else"
       " if(v<30.)"
         "{"
           "float f=v-20.;"
           "m=vec3(1,.2,.25);"
           "y=vec3(1,1,2);"
           "d=normalize(vec3(0,.5,1));"
           "l.y=.25;"
           "u=2.;"
           "c=vec3(5.+f*.5,2,f*.5);"
           "a=vec3(0,2,0);"
         "}"
       "else"
         " if(v<50.)"
           "{"
             "float f=v-30.;"
             "m=vec3(1,.2,.25);"
             "y=vec3(1,1,2);"
             "d=normalize(vec3(0,.5,1));"
             "l.y=.25;"
             "float J=f*.35+.3;"
             "r=normalize(vec3(cos(J),sin(J),-.3));"
             "u=1.5;"
             "c=vec3(22,2,f*.6-10.);"
             "a=vec3(0,2,f*.6-10.);"
           "}"
         "else"
           " if(v<55.)"
             "{"
               "float f=v-50.,F=smoothstep(2.,2.5,f);"
               "l.y=mix(.25,0.,F);"
               "m=vec3(1.-F,.2*(1.-F),1);"
               "y=vec3(1,1,.5);"
               "d=normalize(vec3(F*.3,.3-F*.3,1));"
               "o=smoothstep(4.6,4.8,f)*.2;"
               "u=4.;"
               "c=vec3(0,3,-4);"
               "a=vec3(0,3,0);"
               "if(f>3.)"
                 "e=max(fract(t*.333),fract(t*.333+.08));"
             "}"
           "else"
             " if(v<58.)"
               "{"
                 "float f=v-55.;"
                 "s=vec3(0);"
                 "z=vec3(-5,0,-8);"
                 "d=normalize(vec3(.3,0,1));"
                 "o=.2;"
                 "m=vec3(0,0,1);"
                 "y=vec3(3,1.5,6);"
                 "float F=smoothstep(0.,.5,f);"
                 "u=mix(4.,3.,F);"
                 "c=vec3(0,3,-4);"
                 "a=mix(vec3(0,3,0),vec3(-5,5,-9),F);"
               "}"
             "else"
               " if(v<65.)"
                 "{"
                   "float f=v-58.;"
                   "p=smoothstep(0.,.5,f);"
                   "m=vec3(0);"
                   "e=0.;"
                   "d=normalize(vec3(.3,0,1));"
                   "c=mix(vec3(0,3,-4),vec3(0,2,-6),p);"
                   "a=vec3(0,3,0);"
                   "u=mix(4.,3.,p)+smoothstep(0.,7.,f)*.5;"
                 "}"
               "else"
                 " if(v<70.)"
                   "{"
                     "float f=v-65.;"
                     "d=normalize(vec3(0,0,1));"
                     "s=vec3(0,0,-f*3.-2.);"
                     "z=vec3(-5,0,-8);"
                     "m=vec3(1,1,.5);"
                     "y=vec3(3,1.5,8)*1.5;"
                     "c=vec3(16,5,9);"
                     "a=vec3(3,5,-2.-f);"
                     "u=3.;"
                   "}"
                 "else"
                   " if(v<80.)"
                     "{"
                       "float f=v-70.;"
                       "m=vec3(1);"
                       "y=vec3(3,1.5,8);"
                       "float F=mod(f,8.),H=smoothstep(.5,1.,F)*smoothstep(2.8,2.5,F)-smoothstep(4.,4.5,F)*smoothstep(5.8,5.5,F)+cos(t)*.2;"
                       "d=normalize(vec3(H,cos(t*.5)*.1+.1,1));"
                       "w=.3;"
                       "u=2.5;"
                       "c=vec3(2.75,1,-5.25);"
                       "a=vec3(0,2.3,0);"
                       "float J=mod(f,2.);"
                       "k+=smoothstep(.5,.6,J)*smoothstep(.7,.6,J)*.3;"
                       "J=mod(f+.3,3.);"
                       "k+=smoothstep(.5,.6,J)*smoothstep(.7,.6,J)*.3;"
                     "}"
                   "else"
                     " if(v<85.)"
                       "{"
                         "float f=v-80.,F=smoothstep(1.,3.,f);"
                         "m=vec3(0,1.-F*.5,1);"
                         "y=vec3(3,1.5,6);"
                         "d=normalize(vec3(F*.5,.3-F*.45,1));"
                         "u=4.;"
                         "c=vec3(0,3,-4);"
                         "a=vec3(0,3,0);"
                         "if(f>3.)"
                           "e=max(fract(t*.333),fract(t*.333+.08));"
                       "}"
                     "else"
                       " if(v<89.)"
                         "{"
                           "float f=v-85.;"
                           "s=vec3(0);"
                           "i=vec3(-5,0,-8);"
                           "d=normalize(vec3(.5,-.15,1));"
                           "m=vec3(0,.5,1);"
                           "y=vec3(3,1.5,6);"
                           "float F=smoothstep(0.,1.,f);"
                           "u=mix(4.,3.,F);"
                           "c=vec3(0,3,-4);"
                           "a=mix(vec3(0,3,0),vec3(-5,5,-9),F);"
                         "}"
                       "else"
                         " if(v<97.)"
                           "{"
                             "float f=v-89.;"
                             "s=vec3(0,0,-11);"
                             "i=vec3(-5,0,-8);"
                             "d=normalize(mix(vec3(1,-.5,1),vec3(0,.5,1),smoothstep(3.,3.5,f)));"
                             "d=normalize(mix(d,vec3(1,-.5,1),smoothstep(6.5,7.,f)));"
                             "l.y=smoothstep(3.,3.5,f)*.6;"
                             "l.x=smoothstep(3.,3.5,f)*smoothstep(8.,6.,f)*.25*sin(f*3.);"
                             "m=vec3(1,.2,.5);"
                             "y=vec3(0,.2,1);"
                             "c=vec3(-3,4.8,-30);"
                             "a=vec3(-3,4,0);"
                             "u=3.5;"
                           "}"
                         "else"
                           " if(v<107.)"
                             "{"
                               "float f=v-98.,F=smoothstep(6.,9.,f);"
                               "s=vec3(0,0,f*.25-11.);"
                               "i=vec3(-2,0,-8);"
                               "d=normalize(vec3(-.5,.25-F,1));"
                               "l.y=.5-F;"
                               "m=vec3(1,.2,.5);"
                               "y=vec3(-1,1,1)*.5;"
                               "c=vec3(18,5,-5);"
                               "a=vec3(-5,5,-6);"
                               "u=3.;"
                             "}"
                           "else"
                             " if(v<109.)"
                               "{"
                                 "float f=v-107.;"
                                 "m=vec3(0);"
                                 "y=vec3(0);"
                                 "i=vec3(0,0,-8);"
                                 "a=mod(f,2.)<1.?"
                                   "(c=vec3(0,2,-8),vec3(0,3,0)):"
                                   "(c=vec3(0,5.5,2),vec3(0,5.75,0));"
                                 "d=normalize(vec3(0,-.1,1));"
                                 "u=3.+f*.1;"
                               "}"
                             "else"
                               " if(v<116.)"
                                 "{"
                                   "float f=v-109.,F=sin(min(f,5.));"
                                   "m=vec3(0);"
                                   "y=vec3(0);"
                                   "d=normalize(vec3(F*.7,0,1));"
                                   "d=normalize(mix(d,vec3(-.3,.2,1),smoothstep(5.2,5.4,f)));"
                                   "l.x=F*.25;"
                                   "o=smoothstep(6.,6.2,f)*.2;"
                                   "s=vec3(0,(smoothstep(6.,6.2,f)-smoothstep(6.2,6.4,f))*.4,0);"
                                   "u=3.5;"
                                   "c=vec3(0,2,-8);"
                                   "a=vec3(0,3,0);"
                                 "}"
                               "else"
                                 " if(v<125.)"
                                   "{"
                                     "float f=v-116.;"
                                     "s=vec3(9e7);"
                                     "i=vec3(-2,0,-8);"
                                     "x=vec3(5,0,-20);"
                                     "float F=smoothstep(.5,1.5,f);"
                                     "u=mix(3.5,5.,F);"
                                     "c=vec3(0,5.5,2);"
                                     "a=mix(vec3(-.5,5.75,0),vec3(5,2,-20),F);"
                                     "p=F*.3;"
                                   "}"
                                 "else"
                                   " if(v<137.)"
                                     "{"
                                       "float f=v-125.;"
                                       "m=vec3(.1);"
                                       "y=vec3(.2);"
                                       "u=2.8+f*.15;"
                                       "int F=int(f);"
                                       "if(F%4==1)"
                                         "i=vec3(0,0,-8),c=vec3(2.5,2,-1),a=vec3(1,5.25,-8),u=2.8+pow(f*.3,1.2);"
                                       "else"
                                         " if(F%4==3)"
                                           "x=vec3(4,0,-8),c=vec3(0,5.5,2),a=vec3(4,3,-8),p=.3;"
                                         "else"
                                           " c=vec3(0,2.4,-8),a=vec3(0,3,0);"
                                       "float H=smoothstep(.3,.7,fract(f));"
                                       "if(F%4==0)"
                                         "H=1.-H;"
                                       "l.x=-H*.1;"
                                       "d=normalize(mix(vec3(.1,-.25,1),vec3(-.2,.2,1),H));"
                                       "d=normalize(d+vec3(cos(f*10.),cos(f*5.),1)*.01);"
                                     "}"
                                   "else"
                                     " if(v<140.)"
                                       "{"
                                         "float f=v-137.;"
                                         "m=vec3(0,.1,0);"
                                         "y=vec3(0,.5,0);"
                                         "c=vec3(0,2.4,-8);"
                                         "a=vec3(0,3,0);"
                                         "l.x=-.1;"
                                         "l.y=sin(f*2.)*.1;"
                                         "o=smoothstep(0.,3.,f)*.1;"
                                         "d=normalize(vec3(-.2,.2,1));"
                                         "u=3.2-f*.15;"
                                       "}"
                                     "else"
                                       " if(v<150.)"
                                         "{"
                                           "float f=v-140.;"
                                           "d=normalize(vec3(0,0,1));"
                                           "s=vec3(0,0,-f*2.-2.);"
                                           "x=vec3(0,-.5,-30);"
                                           "m=vec3(1,1,.5);"
                                           "y=vec3(3,1.5,8);"
                                           "float F=smoothstep(0.,10.,f);"
                                           "c=vec3(-2,3.5,mix(-10.,-33.,F));"
                                           "a=vec3(2,2,-3.-f*2.);"
                                           "u=3.;"
                                         "}"
                                       "else"
                                         " if(v<155.)"
                                           "{"
                                             "float f=v-150.;"
                                             "d=normalize(vec3(0,0,1));"
                                             "s=vec3(0,-smoothstep(.05,.1,f)*4.5,-22);"
                                             "x=vec3(2,0,-30);"
                                             "m=vec3(1,1,.5);"
                                             "y=vec3(3,1.5,8);"
                                             "c=vec3(-20,6,-13)+vec3(cos(f*72.),cos(f*64.),sin(f*48.))*3.*smoothstep(.09,.1,f)*smoothstep(.7,.1,f);"
                                             "a=vec3(3,2,-23);"
                                             "u=mix(4.,4.2,smoothstep(0.,5.,f));"
                                             "float F=smoothstep(.1,0.,f)*13.;"
                                             "n=vec3(0,F,-22);"
                                           "}"
                                         "else"
                                           "{"
                                             "float f=v-155.;"
                                             "d=normalize(vec3(0,0,1));"
                                             "s=vec3(9e7);"
                                             "i=vec3(-1,0,-8);"
                                             "x=vec3(1,0,-25);"
                                             "a=vec3(2,3.8,-18);"
                                             "c=vec3(5,5,2);"
                                             "float F=smoothstep(1.5,2.,f);"
                                             "u=2.5+F*3.5;"
                                             "n=vec3(7,0,-20);"
                                             "p=F*.5;"
                                           "}"
 "}";

const char *fxaa_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 K=vec2(1280,720);"
 "uniform sampler2D L;"
 "vec3 E(vec4 v,sampler2D f,vec2 y)"
 "{"
   "vec3 i=textureLod(f,v.zw,0.).xyz,c=textureLod(f,v.zw+vec2(1,0)*y.xy,0.).xyz,m=textureLod(f,v.zw+vec2(0,1)*y.xy,0.).xyz,F=textureLod(f,v.zw+vec2(1)*y.xy,0.).xyz,x=textureLod(f,v.xy,0.).xyz,d=vec3(.299,.587,.114);"
   "float s=dot(i,d),a=dot(c,d),u=dot(m,d),z=dot(F,d),H=dot(x,d),w=min(H,min(min(s,a),min(u,z))),e=max(H,max(max(s,a),max(u,z)));"
   "vec2 J;"
   "J.x=-(s+a-u-z);"
   "J.y=s+u-a-z;"
   "float n=1./(min(abs(J.x),abs(J.y))+1./128.);"
   "J=min(vec2(8),max(vec2(-8),J*n))*y.xy;"
   "vec3 t=.5*(textureLod(f,v.xy+J*(1./3.-.5),0.).xyz+textureLod(f,v.xy+J*(2./3.-.5),0.).xyz),M=t*.5+.25*(textureLod(f,v.xy+J*-.5,0.).xyz+textureLod(f,v.xy+J*.5,0.).xyz);"
   "float l=dot(M,d);"
   "return l<w||l>e?"
     "t:"
     "M;"
 "}"
 "void main()"
 "{"
   "vec2 y=1./K,v=gl_FragCoord.xy*y;"
   "vec4 i=vec4(v,v-y*.5);"
   "vec3 c=E(i,L,y);"
   "f=vec4(c,1);"
 "}";

const char *postprocess_frag =
 "#version 150\n"
 "out vec4 f;"
 "const vec2 N=vec2(1280,720);"
 "uniform sampler2D L;"
 "uniform float t;"
 "void main()"
 "{"
   "vec2 y=1./N,v=gl_FragCoord.xy*y,c=(v*2.-1.)*y.x*.5;"
   "vec3 i;"
   "i.x=texture(L,v+c).x;"
   "i.y=texture(L,v).y;"
   "i.z=texture(L,v-c).z;"
   "i*=smoothstep(0.,10.,t);"
   "float m=length(gl_FragCoord.xy/N.xx-vec2(.5,.3)),x=max(.137,smoothstep(157.,156.,t));"
   "i*=smoothstep(x,x-.005,m);"
   "float d=m,F=smoothstep(.135,.136,d)*smoothstep(157.,158.,t);"
   "d=fract(23.*pow(d,.25));"
   "d-=smoothstep(.95,.99,d);"
   "vec3 a=mix(vec3(1,.6,0),vec3(1,0,0),pow(d,1.));"
   "i=mix(i,a,F);"
   "i*=smoothstep(162.,161.,t);"
   "f=vec4(i,1);"
 "}";

#endif // SHADERS_INL_
