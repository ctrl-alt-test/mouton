#version 150

out vec4 fragColor;


#define AA 1

//----------------------------------------------------------------------
// Vertex/Fragment IO
//----------------------------------------------------------------------
in vec3 animationAmp;
in vec3 animationSpeed;
in vec2 headRot;
in vec3 sheepPos;    
in vec3 panelPos;
in vec3 flowerPos;
in vec3 panelWarningPos;
in vec3 sunDir;
in vec3 camPos;
in vec3 camTa;
in float camFocal;
in float blink;
in vec3 eyeDir;
in float eyesSurprise;
in float excited;
in float fishEyeFactor;
in float noseSize;


//----------------------------------------------------------------------
// KodeLife Shadertoy mimic
//----------------------------------------------------------------------
uniform vec2 iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform int iFrame;

void mainImage(out vec4, in vec2);
void main(void) { mainImage(fragColor,gl_FragCoord.xy); }

//----------------------------------------------------------------------
// Maths function
//----------------------------------------------------------------------
#define saturate(x) clamp(x,0.,1.)
#define PI 3.141592653589

float hash(float p);
float hash1( vec2 p );
vec3 hash3(vec3 p);
float noise( in vec3 x );

mat3 lookat(vec3 ro, vec3 ta);
mat2 rot(float v);


// ---------------------------------------------
// Distance field toolbox
// ---------------------------------------------
float box( vec3 p, vec3 b );
float cappedCone( vec3 p, float h, float r1, float r2 );
float cappedTorus(in vec3 p, in vec2 sc, in float ra, in float rb);
float capsule( vec3 p, vec3 a, vec3 b, float r );
float torus( vec3 p, vec2 t );
float ellipsoid( vec3 p, vec3 r);
float smin( float d1, float d2, float k );
float smax( float a, float b, float k );
float triangle( vec3 p, vec2 h, float r );
float UnevenCapsule2d( vec2 p, float r1, float r2, float h );
float star2d(in vec2 p, in float r, in float rf);


// ---------------------------------------------
// Distance field 
// ---------------------------------------------
vec2 map(vec3 p);
float trace(vec3 ro, vec3 rd, vec2 nf);
vec3 normal(vec3 p);
float shadow( vec3 ro, vec3 rd, float mint, float tmax );

// Materials
#define GROUND 0.
#define COTON 1.
#define SKIN 2.
#define EYE 3.
#define CLOGS 4.
#define METAL 5.
#define PANEL 6.
#define PANEL_FOOD 7.
#define PISTIL 8.
#define PETAL 9.
#define TIGE 10.



vec2 dmin(vec2 a, vec2 b) {
    return a.x<b.x ? a : b;
}

vec2 moda (vec2 p, float per)
{
    float a = atan(p.y,p.x);
    float l = length(p);
    a = mod(a-per/2.,per)-per/2.;
    return vec2 (cos(a),sin(a))*l;
}

vec2 flower(vec3 p) {

    p -= flowerPos;
    vec3 pr = p;
    pr.x += cos(3.1*.25+iTime)*3.1*.2;
    pr.y -= 2.8;
    pr.zy = rot(.75) * pr.zy;
    float pistil = ellipsoid(pr-vec3(0.,.3,0.), vec3(1.,.2+cos(pr.x*150.)*sin(pr.z*150.)*.05,1.)*.25);
    if (pistil < 5.) {
        vec2 dmat = vec2(pistil, PISTIL);
        
        vec3 pp = pr;
        pp.xz = moda(pp.xz, PI*.2);
        float petals = ellipsoid(pp-vec3(0.5,.2+sin(pp.x*2.)*.15,0.), vec3(2.,.1+sin(pp.z*50.)*.02,.75)*.25);
        if (petals < dmat.x) {
            dmat = vec2(petals, PETAL);
        }
        
        float tige = max(length(p.xz + vec2(cos(p.y*.25+iTime)*p.y*.2,-.075) )-smoothstep(3.1,0., p.y)*.1-0.02, p.y-3.1);
        if (tige < dmat.x) {
            dmat = vec2(tige, TIGE);
        }
        
        return dmat;
    }
    return vec2(999999., GROUND);
}

vec2 panelFood(vec3 p) {
    p -= panelPos;
    float pan = box(p-vec3(0.,7.5,-5.), vec3(1.,1., 0.1));
    if (pan < 7.) {
        pan = smax(pan, -box(p-vec3(0.,7.5,-5.1), vec3(.9,.9,.1)), .001);
    
        float tube = box(p-vec3(0.,4.,-5.1), vec3(.1,4.,.1));
        vec3 pp = p;
        pp.y = abs(pp.y-7.3)-.3;
        tube = min(tube, box(pp-vec3(0.,0.,-5.05), vec3(.35,.1,.05)));
        
        
        vec2 dmat = vec2(tube, METAL);
        dmat = dmin(dmat, vec2(pan,PANEL_FOOD));
        return dmat;
    }else {
        return vec2(999999., GROUND);
    }
}
vec2 panelWarning(vec3 p) {
    p -= panelWarningPos;
    float pan = triangle(p-vec3(0.,7.5,-5.), vec2(1.7,.1), .3);
    if (pan < 8.) {
        pan = smax(pan, -triangle(p-vec3(0.,7.5,-5.1), vec2(1.6,.1), .3), .001);
        
        float tube = box(p-vec3(0.,4.,-5.1), vec3(.1,4.,.1));
        vec3 pp = p;
        pp.y = abs(pp.y-7.3)-.3;
        tube = min(tube, box(pp-vec3(0.,0.,-5.05), vec3(.35,.1,.05)));
        
        
        vec2 dmat = vec2(tube, METAL);
        dmat = dmin(dmat, vec2(pan,PANEL));
        return dmat;
    } else {
        return vec2(999999., GROUND);
    }
}

// return [distance, material]
vec2 sheep(vec3 p) {
    p -= sheepPos;
    float time = mod(iTime, 1.);
    time = smoothstep(0., 1., abs(time * 2. - 1.));

    p.y -= 1.;
    p.z -= -2.;

    
    // Body
    float tb = iTime*animationSpeed.x;
    vec3 bodyMove = vec3(cos(tb*PI),cos(tb*PI*2.)*.1,0.)*.025*animationAmp.x;
    float body = length(p*vec3(1.,1.,.9)-vec3(0.,1.5,2.75)-bodyMove)-2.;
    
    if (body < 3.) {
        float n = (pow(noise((p-bodyMove)*2.)*.5+.5, .75)*2.-1.);
        body = body + .05 - n*.2;


        // Legs
        float t = mod(iTime*animationSpeed.x,2.);
        float l = smoothstep(0.,.5,t) * smoothstep(1.,.5,t);
        vec4 legsRot = vec4(0.);
        vec4 legsPos = vec4(0.);
        float a = smoothstep(0.,.5,t);
        float b = smoothstep(.5,1.,t);
        float c = smoothstep(1.,1.5,t);
        float d = smoothstep(1.5,2.,t);
        legsRot.z = a * (1.-a);
        legsRot.x = b * (1.-b);
        
        legsRot.w = c * (1.-c);
        legsRot.y = d * (1.-d);
          
        //legsPos += smoothstep(0.,2.,t);
        legsPos += t*.5;
        legsPos.x -= b;
        legsPos.z -= a;
        legsPos.y -= d;
        legsPos.w -= c;
        legsPos *= animationAmp.x;
        
        vec3 pl = p;
        pl.x -= .8;
        pl.z -= 2. + legsPos.x;
        pl.yz = rot(legsRot.x) * pl.yz;
        float legs = cappedCone(pl-vec3(0.,0.,0.), .7, .3, .2);
        float clogs = cappedCone(pl-vec3(0.,-0.8,0.), .2, .35, .3);

        pl = p;
        pl.x += 1.;
        pl.z -= 2. + legsPos.y;
        pl.yz = rot(legsRot.y) * pl.yz;
        legs = min(legs, cappedCone(pl-vec3(0.,0.,0.), .7, .3, .2));
        clogs = min(clogs, cappedCone(pl-vec3(0.,-0.8,0.), .2, .35, .3));

        pl = p;
        pl.x -= 1.;
        pl.z -= 4. + legsPos.z;
        pl.yz = rot(legsRot.z) * pl.yz;
        legs = min(legs, cappedCone(pl-vec3(0.,0.,0.), .7, .3, .2));
        clogs = min(clogs, cappedCone(pl-vec3(0.,-0.8,0.), .2, .35, .3));

        pl = p;
        pl.x += 1.;
        pl.z -= 4. + legsPos.w;
        pl.yz = rot(legsRot.w) * pl.yz;
        legs = min(legs, cappedCone(pl-vec3(0.,0.,0.), .7, .3, .2));
        clogs = min(clogs, cappedCone(pl-vec3(0.,-0.8,0.), .2, .35, .3));

        
        // Head
        vec3 ph = p + vec3(0., -2., -1.2);
        ph.xz = rot((time*animationSpeed.y - 0.5)*0.25*animationAmp.y+headRot.x) * ph.xz;
        ph.zy = rot(sin(iTime*animationSpeed.y)*0.25*animationAmp.y-headRot.y) * ph.zy;

        float head = length(ph-vec3(0.,-1.3,-1.2)) - 1.;
        head = smin(head, length(ph-vec3(0.,0.,0.)) - .5, 1.8);

        // ears
        vec3 pp = ph;
        pp.yz = rot(-.6) * pp.yz;
        pp.x = abs(p.x)-.8;
        pp *= vec3(.3,1.,.4);
        pp -= vec3(0.,-0.05 - pow(pp.x,2.)*5.,-.1);
        float ears = length(pp)-.15;
        ears = smax(ears, -(length(pp-vec3(0.,-.1,0.))-.12), .01);

        //eyes
        pp = ph;
        pp.x = abs(ph.x)-.4;
        float eyes = length(pp*vec3(1.,1.,1.-eyesSurprise)-vec3(0.,0.,-1.)) - .3;

        // nostrils
        pp.x = abs(ph.x)-.2;
        pp.xz = rot(-.45) * pp.xz;
        float nostrils = torus(pp-vec3(-0.7,-1.2,-2.), vec2(.15*noseSize,.05));



        // hair & tail
        pp = p;
        pp *= vec3(.7,1.,.7);
        float hairTail = length(pp-vec3(0.,2.4,0.7))-.4;
        hairTail = smin(hairTail, capsule(p-vec3(0.,0.,cos(p.y-.7)*.5),vec3(cos(iTime*animationSpeed.z)*animationAmp.z,.2,5.), vec3(0.,2.,4.9), .2), 0.2);
        hairTail -= (pow(noise(p*2.)*.5+.5, .75)*2.-1.)*.1;

        // Union
        vec2 dmat = vec2( body, COTON);
        dmat = dmin(dmat, vec2( hairTail, COTON));
        dmat = dmin(dmat, vec2(legs, SKIN));
        dmat = dmin(dmat, vec2(head, SKIN));
        dmat = dmin(dmat, vec2(eyes, EYE));
        dmat = dmin(dmat, vec2(nostrils, SKIN));
        dmat = dmin(dmat, vec2(clogs, CLOGS));
        dmat = dmin(dmat, vec2(ears, SKIN));
        
        return dmat;
    } else {
        return vec2(body, COTON);
    }
}


vec2 map(vec3 p) {
    vec2 dmat = vec2(p.y, GROUND);
    
    dmat = dmin(dmat, sheep(p));
    dmat = dmin(dmat, flower(p));
    dmat = dmin(dmat, panelFood(p));
    dmat = dmin(dmat, panelWarning(p));
    
    return dmat;
}

vec3 skyColor(vec3 rd, vec2 uv, float night) {
    vec3 col = vec3(1.);
    
    float vdots = max(dot(rd, sunDir), 0.);
    
    col += vec3(1.,.7,.3) * pow(vdots,1.);
    col += vec3(1.,.5,.1) * pow(vdots,52.);
    
    col = vec3(1.) * night * night;
    
    // mon
    vec2 moonPos = vec2(cos(iTime*.7+2.3), sin(iTime*.7+2.3) );
    float moon = smoothstep(0.201,0.2, length(uv-moonPos));
    moon *= smoothstep(0.2,0.201, length(uv-moonPos-vec2(.1,0.025)));
    moon += smoothstep(1.,0., length(uv-moonPos))*.02;
    moon *= smoothstep(.5,.0, sunDir.y);
    
    // stars
    vec2 p = uv*200.;
    vec2 fp = fract(p)-.5;
    vec2 ip = floor(p);
    vec3 rnd = hash3(vec3(abs(ip),abs(ip.x)));
    float s = rnd.z*.1;
    moon += smoothstep(s,0.+s*.01, length(fp+rnd.xy-.5) ) *(cos(iTime*3.+rnd.z*3.14+rnd.x+rnd.y)*.5+.5);
    
    
    col += moon*smoothstep(.5,-1., sunDir.y);
    
    return col;
}

float fastAO( in vec3 pos, in vec3 nor, float maxDist, float falloff ) {
    float occ = 0.0;
    float sca = 1.0;
    
    const int NBITE = 2;
    for( int i=1; i<=NBITE; i++ )
    {
        float h = float(i)/NBITE * maxDist;
        float d = map( pos + h*nor ).x;
        occ += (h-d)*sca;
        sca *= .95;
    }
    return saturate(1.0 - falloff*1.5*occ);
}

vec2 boxIntersection( in vec3 ro, in vec3 rd, vec3 boxSize, vec3 m) 
{
    vec3 n = m*ro;
    vec3 k = abs(m)*boxSize;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;
    float tN = max( max( t1.x, t1.y ), t1.z );
    float tF = min( min( t2.x, t2.y ), t2.z );
    if( tN>tF || tF<0.0) return vec2(-1.0); // no intersection
    return vec2( tN, tF );
}

float fastTrace(vec3 ro, vec3 rd) {

    vec3 m = 1.0/rd;
    float result = 9999.;
    
    // Sheep intersection
    vec2 nf = boxIntersection(ro-sheepPos-vec3(0.,3.,-2.),rd, vec3(3.,3.,7.), m);
    if (nf.y>0.) {
        float t = max(nf.x,0.);
        for(int i=0; i<128; i++) {
            vec3 p = ro + rd * t;
            float d = dmin(vec2(p.y,GROUND),sheep(p)).x; // BUGS : at 23secondes without ground SDF ?!
            t += d;
            if (t > nf.y) break;
            if (abs(d) < 0.001) break;
        }
        if (t < nf.y)
            result = t; 
    }
    
    // Panels
    {
        vec2 nf = boxIntersection(ro-panelPos-vec3(0.,5.,-5.),rd, vec3(1.5,5.,1.), m);
        if (nf.y>0.) {
            float t = max(nf.x,0.);
            for(int i=0; i<128; i++) {
                float d = panelFood(ro+rd*t).x;
                t += d;
                if (t > nf.y) break;
                if (abs(d) < 0.001) break;
            }
            if (t < nf.y)
                result = min(result,t); 
        }
    }
    {
        vec2 nf = boxIntersection(ro-panelWarningPos-vec3(0.,5.,-5.),rd, vec3(1.5,5.,1.), m);
        if (nf.y>0.) {
            float t = max(nf.x,0.);
            for(int i=0; i<128; i++) {
                float d = panelWarning(ro+rd*t).x;
                t += d;
                if (t > nf.y) break;
                if (abs(d) < 0.001) break;
            }
            if (t < nf.y)
                result = min(result,t); 
        }
    }
    
    // Flower
    {
        vec2 nf = boxIntersection(ro-flowerPos-vec3(0.,5.,0.),rd, vec3(2.,5.,1.), m);
        if (nf.y>0.) {
            float t = max(nf.x,0.);
            for(int i=0; i<128; i++) {
                float d = flower(ro+rd*t).x;
                t += d;
                if (t > nf.y) break;
                if (abs(d) < 0.001) break;
            }
            if (t < nf.y)
                result = min(result,t); 
        }
    }
    
    // Ground intersection
    {
        float t = -(ro.y)/rd.y;// -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
        if (t>0.) result = min(result,t);
    }
    
    return result;
}

// /!\ Not energy conservative!
vec3 shade(vec3 ro, vec3 rd, vec3 p, vec3 n, vec2 uv) {
    vec2 dmat = map(p);
    
    
    float night = smoothstep(0.,.3, sunDir.y)+.1;
    
    float ao = fastAO(p, n, .15, 1.);
    ao *= fastAO(p, n, 1., .1)*.5;
    
    float shad = shadow(p, sunDir, .08, 50.);
    float fre = saturate(1.0+dot(rd,n));
    
    vec3 diff = vec3(1.,.8,.7) * max(dot(n,sunDir), 0.) * pow(vec3(shad), vec3(1.,1.15,1.25));
    vec3 bnc = vec3(1.,.8,.7)*.1 * max(dot(n,-sunDir), 0.) * ao;
    vec3 sss = vec3(.5) * fastAO(p, rd, .3, .5);
    vec3 spe = vec3(1.) * max(dot(reflect(rd,n), sunDir),0.);
    
    //sss = vec3(1.) * calcSSS(p,rd);
    vec3 amb = vec3(.4,.45,.5)*1. * ao;
    vec3 emi = vec3(0.);
    
    vec3 albedo = vec3(0.);
    if(dmat.y == GROUND) {
        albedo = vec3(3.);
        sss = vec3(0.);
        spe = vec3(0.);
    } else if (dmat.y == COTON) {
        albedo = vec3(.4);
        sss *= vec3(1.) *(fre*.5+.5);
        emi = vec3(.35);
        spe = pow(spe, vec3(4.))*fre*.5;
    } else if (dmat.y == CLOGS) {
        albedo = vec3(.025);
        sss = vec3(0.);
        spe = vec3(0.);
    } else if (dmat.y == EYE) {
        sss *= .7;
        albedo = vec3(1.);
        float ndz = dot(n, normalize(vec3(0.,0.,1.)));
        float nde = dot(n, eyeDir);
        albedo *= smoothstep(-0.953,-.952, nde-eyesSurprise/2.);
        if (ndz > 0. || blink > .95) dmat.y = SKIN;
        spe = pow(spe, vec3(80.))*fre;
    } else if(dmat.y == METAL) {
        albedo = vec3(1.);
        sss = vec3(0.);
        spe = pow(spe, vec3(8.))*fre*2.;
    } else if(dmat.y == PANEL) {
        vec3 p = p-panelWarningPos;
        sss = vec3(0.);
        spe = pow(spe, vec3(8.))*fre*2.;
        
        if (n.z > .5) {
            albedo = vec3(1.5,0.,0.);
            float tri = triangle(p-vec3(0.,7.5,-5.), vec2(1.3,.2), .01);
            float symbol = smoothstep(0.15,0.1495, distance(p,vec3(0.,7.1,-4.9)));
            symbol += smoothstep(0.005,0.,UnevenCapsule2d(p.xy-vec2(0.,7.4), .06,.12,1.));
            albedo = mix(albedo, vec3(1.5), smoothstep(0.005,.0, tri));
            albedo = mix(albedo, vec3(0.), symbol);
        } else {
            albedo = vec3(1.);
        }
    } else if(dmat.y == PANEL_FOOD) {
        vec3 p = p-panelPos;
        sss = vec3(0.);
        spe = pow(spe, vec3(8.))*fre*2.;
        if (n.z > .5) {
            albedo = vec3(0.,0.,1.5);
            p.y -= 7.4;
            float squ = box(p-vec3(0.,.1,-5.), vec3(0.8,.8, 1));
            float symbol = 0.;
            p.xy = rot(.8) * p.xy;
            float x = .04;
            symbol += smoothstep(0.01,0.,UnevenCapsule2d(p.xy-vec2(-x,-.6), .1,.05,1.));
            symbol += smoothstep(0.01,0.,UnevenCapsule2d(p.xy-vec2(-x,.5), .16,.135,0.15));
            symbol *= smoothstep(0.,0.01,UnevenCapsule2d(p.xy-vec2(-x-.08,.56), .001,.02,0.2));
            symbol *= smoothstep(0.,0.01,UnevenCapsule2d(p.xy-vec2(-x+.04,.56), .001,.02,0.2));
            p.xy = rot(-1.6) * p.xy;
            symbol += smoothstep(0.01,0.,UnevenCapsule2d(p.xy-vec2(x,-.6), .1,.05,1.));
            symbol += smoothstep(0.01,0.,UnevenCapsule2d(p.xy-vec2(x,.5), .16,.1,0.15));
            albedo = mix(albedo, vec3(1.5), smoothstep(0.01,.0, squ));
            albedo = mix(albedo, vec3(0.), symbol);
        } else {
            albedo = vec3(1.);
        }
    } else if (dmat.y == PISTIL) {
        vec3 pr = p - flowerPos;
        pr.x += cos(3.1*.25+iTime)*3.1*.2;
        pr.y -= 2.8;
        pr.zy = rot(.75) * pr.zy;
        albedo = mix(vec3(2.,.75,.0), vec3(2.,2.,.0), smoothstep(0.,.45, length(pr-vec3(0.,.3,0.))))*2.;
        sss = vec3(0.01);
        spe = vec3(0.);
    } else if (dmat.y == TIGE) {
        albedo = vec3(0.,.1,.0);
        sss *= vec3(1.);
        spe *= vec3(1.)*fre;
    } else if (dmat.y == PETAL) {
        vec3 pr = p - flowerPos;
        pr.x += cos(3.1*.25+iTime)*3.1*.2;
        pr.y -= 2.8;
        pr.zy = rot(.75) * pr.zy;
        albedo = mix(vec3(1.,1.,1.)+.5, vec3(.75,0.5,1.), smoothstep(0.6,1., length(pr-vec3(0.,.3,0.))))*2.;
       // albedo = vec3(1.,1.,1.)*3.;
        sss *=0.0;
        spe = pow(spe, vec3(4.))*fre*1.0;
    }
    if (dmat.y == SKIN) {
        albedo = vec3(1.,.7,.5)*1.;
        sss = pow(sss, vec3(.5,2.5,8.0)+2.)*2.;// * fre;// * pow(fre, 1.);
        spe = pow(spe, vec3(4.))*fre*.02;
    }
    
    vec3 col =  (albedo * (amb*1. + diff*.5 + bnc*2. + sss*2. + spe*1.)  + emi) *  night;//* (saturate(sunDir.y)*.95+.05);
    //col = diff;//diff + bnc + amb + sss;
    //col = albedo * spe;
    // fog
    float t = length(p-ro);
    col = mix(col, skyColor(rd,uv, night), smoothstep(90.,100.,t));

    // Excited background
    if(dmat.y == GROUND) {
        float theta = cos(atan(uv.x, uv.y)*15.+iTime);
        float r = length(uv)*.3;
        col = mix(col,  mix(vec3(1.,0.5,00), vec3(1.,1.,1.0), smoothstep(-r, r, theta)), excited);
    }

    return saturate(col);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 invRes = vec2(1.) / iResolution.xy;
    
    
    vec3 tot = vec3(0.);
    for (int i = 0; i < AA; i++)
    for (int j = 0; j < AA; j++) {
        vec2 offset = vec2(i, j) / float(AA) - .5;
        vec2 uv = (fragCoord + offset) * invRes;
        vec2 v = uv*2.-1.;
        v.x *= iResolution.x * invRes.y;
        
        // Setup ray
        vec3 ro = camPos;
        vec3 ta = camTa;
        vec3 rd = lookat(ro, ta) * normalize(vec3(v,camFocal - length(v)*fishEyeFactor));
        
        // Trace
        #if 0
        float t = fastTrace(ro,rd);
        #else
        float t = trace(ro, rd, vec2(1.5, 100.));
        #endif
        vec3 p = ro + rd * t;
        vec3 n = normal(p);
        vec3 col = shade(ro, rd, p, n, v);
        
        // Excited stars
        {
            vec2 p = v*5.;
            p.x = abs(p.x+.0)-1.5;
            p.y -= 1.4;
            p = rot(iTime*5.) * p;
            col = mix(col, mix(vec3(1.,.8,0.1), vec3(1.), smoothstep(-.1,.5,v.y)), smoothstep(0.,-0.01, star2d(p, 1.7, .5)) * excited);
        }
        
        tot += col;
    }
    
    tot /= AA*AA;
    

    
    fragColor = vec4(tot,1.) * smoothstep(0., 10., iTime);
    
}





// ---------------------------------------------
// Raytracing toolbox
// ---------------------------------------------
float trace(vec3 ro, vec3 rd, vec2 nf) {
    float t = nf.x;
    for(int i=0; i<128; i++) {
        float d = map(ro+rd*t).x;
        t += d;
        if (t > nf.y) break;
        if (abs(d) < 0.001) break;
    }
    
    return t;
}
vec3 normal(vec3 p) {
    vec2 eps = vec2(0.0001,0.0);
    float d = map(p).x;
    vec3 n;
    n.x = d - map(p - eps.xyy).x;
    n.y = d - map(p - eps.yxy).x;
    n.z = d - map(p - eps.yyx).x;
    
    return normalize(n);
}

// https://www.shadertoy.com/view/lsKcDD
float shadow( vec3 ro, vec3 rd, float mint, float tmax )
{
    float res = 1.0;
    float t = mint;
    
    for( int i=0; i<64; i++ )
    {
        float h = map( ro + rd*t ).x;
        res = min( res, 30.0*h/t );
        t += h;
        
        if( res<0.0001 || t>tmax ) break;
        
    }
    return clamp( res, 0.0, 1.0 );
}




// ---------------------------------------------
// Hash & Noise
// ---------------------------------------------
float hash( float p ) 
{
    return fract(sin(p)*43758.5453123);
}
vec3 hash3(vec3 p) {
    uvec3 x = uvec3((p)*100000.);
    const uint k = 1103515245U; 
    x = ((x>>8U)^x.yzx)*k;
    x = ((x>>8U)^x.yzx)*k;
    x = ((x>>8U)^x.yzx)*k;
    
    return vec3(x)*(1.0/float(0xffffffffU));
}

float hash1( float n )
{
    return fract( n*17.0*fract( n*0.3183099 ) );
}

float noise( in vec3 x )
{
    vec3 p = floor(x);
    vec3 w = fract(x);
    
    #if 1
    vec3 u = w*w*w*(w*(w*6.0-15.0)+10.0);
    #else
    vec3 u = w*w*(3.0-2.0*w);
    #endif
    


    float n = p.x + 317.0*p.y + 157.0*p.z;
    
    float a = hash1(n+0.0);
    float b = hash1(n+1.0);
    float c = hash1(n+317.0);
    float d = hash1(n+318.0);
    float e = hash1(n+157.0);
    float f = hash1(n+158.0);
    float g = hash1(n+474.0);
    float h = hash1(n+475.0);

    float k0 =   a;
    float k1 =   b - a;
    float k2 =   c - a;
    float k3 =   e - a;
    float k4 =   a - b - c + d;
    float k5 =   a - c - e + g;
    float k6 =   a - b - e + f;
    float k7 = - a + b + c - d + e - f - g + h;

    return -1.0+2.0*(k0 + k1*u.x + k2*u.y + k3*u.z + k4*u.x*u.y + k5*u.y*u.z + k6*u.z*u.x + k7*u.x*u.y*u.z);
}


// ---------------------------------------------
// Math
// ---------------------------------------------
mat3 lookat(vec3 ro, vec3 ta)
{
    const vec3 up = vec3(0.,1.,0.);
    vec3 fw = normalize(ta-ro);
    vec3 rt = normalize( cross(fw, normalize(up)) );
    return mat3( rt, cross(rt, fw), fw );
}

mat2 rot(float v) {
    float a = cos(v);
    float b = sin(v);
    return mat2(a,b,-b,a);
}


// ---------------------------------------------
// Distance field toolbox
// ---------------------------------------------
float box( vec3 p, vec3 b )
{
    vec3 q = abs(p) - b;
    return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}
float cappedCone( vec3 p, float h, float r1, float r2 )
{
  vec2 q = vec2( length(p.xz), p.y );
  vec2 k1 = vec2(r2,h);
  vec2 k2 = vec2(r2-r1,2.0*h);
  vec2 ca = vec2(q.x-min(q.x,(q.y<0.0)?r1:r2), abs(q.y)-h);
  vec2 cb = q - k1 + k2*clamp( dot(k1-q,k2)/dot(k2,k2), 0.0, 1.0 );
  float s = (cb.x<0.0 && ca.y<0.0) ? -1.0 : 1.0;
  return s*sqrt( min(dot(ca,ca),dot(cb,cb)) );
}
float cappedTorus(in vec3 p, in vec2 sc, in float ra, in float rb)
{
  p.x = abs(p.x);
  float k = (sc.y*p.x>sc.x*p.y) ? dot(p.xy,sc) : length(p.xy);
  return sqrt( dot(p,p) + ra*ra - 2.0*ra*k ) - rb;
}

float capsule( vec3 p, vec3 a, vec3 b, float r )
{
  vec3 pa = p - a, ba = b - a;
  float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
  return length( pa - ba*h ) - r;
}
float torus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xy)-t.x,p.z);
  return length(q)-t.y;
}
float ellipsoid( vec3 p, vec3 r )
{
  float k0 = length(p/r);
  float k1 = length(p/(r*r));
  return k0*(k0-1.0)/k1;
}

float smin( float d1, float d2, float k )
{
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h);
}

float smax( float a, float b, float k )
{
    k *= 1.4;
    float h = max(k-abs(a-b),0.0);
    return max(a, b) + h*h*h/(6.0*k*k);
}
float triangle( vec3 p, vec2 h, float r )
{
  vec3 q = abs(p);
  return max(q.z-h.y,smax(smax(p.x*0.866025+p.y*0.5, -p.x*0.866025+p.y*0.5, r),-p.y,r)-h.x*0.5);
}

float UnevenCapsule2d( vec2 p, float r1, float r2, float h )
{
    p.x = abs(p.x);
    float b = (r1-r2)/h;
    float a = sqrt(1.0-b*b);
    float k = dot(p,vec2(-b,a));
    if( k < 0.0 ) return length(p) - r1;
    if( k > a*h ) return length(p-vec2(0.0,h)) - r2;
    return dot(p, vec2(a,b) ) - r1;
}
float star2d(in vec2 p, in float r, in float rf)
{
    const vec2 k1 = vec2(0.809016994375, -0.587785252292);
    const vec2 k2 = vec2(-k1.x,k1.y);
    p.x = abs(p.x);
    p -= 2.0*max(dot(k1,p),0.0)*k1;
    p -= 2.0*max(dot(k2,p),0.0)*k2;
    p.x = abs(p.x);
    p.y -= r;
    vec2 ba = rf*vec2(-k1.y,k1.x) - vec2(0,1);
    float h = clamp( dot(p,ba)/dot(ba,ba), 0.0, r );
    return length(p-ba*h) * sign(p.y*ba.x-p.x*ba.y);
}
