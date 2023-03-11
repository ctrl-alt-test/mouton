#version 150
out vec4 fragColor;
const vec2 iResolution = vec2(1280.,720.);

//----------------------------------------------------------------------
// Vertex/Fragment IO
//----------------------------------------------------------------------
in vec3 animationAmp;
in vec3 animationSpeed;
in vec3 sheepPos;    
in vec3 flowerPos;
in vec3 panelPos;
in vec3 panelWarningPos;
in vec3 anvilPos;
in vec3 sunDir;
in vec3 camPos;
in vec3 camTa;
in vec3 eyeDir;
in vec2 headRot;
in float blink;
in float camFocal;
in float eyesSurprise;
in vec2 excited;
in float fishEyeFactor;
in float noseSize;


//----------------------------------------------------------------------
// KodeLife Shadertoy mimic
//----------------------------------------------------------------------
uniform float iTime;


//----------------------------------------------------------------------
// Maths function
//----------------------------------------------------------------------

const float PI = acos(-1.);
const float INFINITE = 9e7;

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
const float GROUND = 0.;
const float COTON = 1.;
const float SKIN = 2.;
const float EYE = 3.;
const float CLOGS = 4.;
const float METAL = 5.;
const float PANEL = 6.;
const float PANEL_FOOD = 7.;
const float PISTIL = 8.;
const float PETAL = 9.;
const float TIGE = 10.;
const float BLACK_METAL = 11.;
const float BLOOD = 12.;

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

vec2 blood(vec3 p) {
    p.xz -= anvilPos.xz;
    p.y -= -anvilPos.y;
    float d = p.y+smoothstep(1.,20.,length(p.xz));
    if (d < .4) {
        d -= pow((noise(p*.7+1.)*.5+noise(p*1.7+100.)*.3+noise(p*2.7+100.)*.1)*.5+.5, 3.)*.45 * (1.-exp(-(iTime-150.)*4.))+.03;
        return vec2(d, BLOOD);
    }
    return vec2(INFINITE, GROUND);
}


vec2 anvil(vec3 p) {
    p -= anvilPos;
    p.xz = rot(1.)*p.xz;
    float h = pow(clamp(p.y-1.,0.004,1.),.5);
    float d = box(p-vec3(0.,1.,0.), vec3(1.5-h,1.,2.5-h));
    if (d<10.) {
        d = min(d, box(p-vec3(0.,3.,0.), vec3(2.,1.,3.)));
        
        float d2 = length((p.yz-vec2(4.5,3.))*vec2(1.,.8))-2.;
        d2 = max(d2, abs(p.x)-.5);
        d2 = max(d2, p.y-3.5);
        d = min(d, d2);
        vec2 dmat = vec2(d-.1, BLACK_METAL);
        
        return dmat;
    }
    return vec2(INFINITE,GROUND);
}

vec2 flower(vec3 p) {

    p -= flowerPos;
    vec3 pr = p;
    pr.x += cos(3.1*.25+iTime)*3.1*.2;
    pr.y -= 2.8;
    pr.zy = rot(.7) * pr.zy;
    float pistil = ellipsoid(pr-vec3(0.,.3,0.), vec3(1.,.2+cos(pr.x*150.)*sin(pr.z*150.)*.05,1.)*.25);
    if (pistil < 5.) {
        vec2 dmat = vec2(pistil, PISTIL);
        
        vec3 pp = pr;
        pp.xz = moda(pp.xz, PI*.2);
        float petals = ellipsoid(pp-vec3(0.5,.2+sin(pp.x*2.)*.2,0.), vec3(2.,.1+sin(pp.z*40.)*.02,.75)*.25);
        if (petals < dmat.x) {
            dmat = vec2(petals, PETAL);
        }
        
        float tige = max(length(p.xz + vec2(cos(p.y*.25+iTime)*p.y*.2+0.02,-.1) )-smoothstep(3.1,0., p.y)*.05-0.02, p.y-3.1);
        if (tige < dmat.x) {
            dmat = vec2(tige, TIGE);
        }
        
        return dmat;
    }
    return vec2(INFINITE, GROUND);
}

vec2 panelFood(vec3 p) {
    p -= panelPos;
    float pan = box(p-vec3(0.,7.5,-5.), vec3(.8,0.8, 0.1))-.2;
    if (pan < 7.) {
        pan = max(pan, (abs(p.z+5.)-.1));
    
        float tube = box(p-vec3(0.,4.,-5.1), vec3(.11,4.,.08));
        
        
        vec2 dmat = vec2(tube, METAL);
        dmat = dmin(dmat, vec2(pan,PANEL_FOOD));
        return dmat;
    }else {
        return vec2(INFINITE, GROUND);
    }
}
vec2 panelWarning(vec3 p) {
    p -= panelWarningPos;
    float pan = triangle(p-vec3(0.,7.5,-5.), vec2(1.7,.1), .3);
    if (pan < 8.) {
        pan = smax(pan, -triangle(p-vec3(0.,7.5,-5.1), vec2(1.6,.1), .3), .001);
        
        float tube = box(p-vec3(0.,4.,-5.1), vec3(.11,4.,.08));
        vec3 pp = p;
        pp.y = abs(pp.y-7.3)-.3;
        tube = min(tube, box(pp-vec3(0.,0.,-5.05), vec3(.35,.1,.05)));
        
        
        vec2 dmat = vec2(tube, METAL);
        dmat = dmin(dmat, vec2(pan,PANEL));
        return dmat;
    } else {
        return vec2(INFINITE, GROUND);
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
    float body = length(p*vec3(1.,1.,.825)-vec3(0.,1.5,2.55)-bodyMove)-2.;
    
    if (body < 3.) {
        float n = (pow(noise((p-bodyMove-vec3(0.05,.0,0.))*2.)*.5+.5, .75)*2.-1.);
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


        // hair 
        vec3 pp = ph;
        pp *= vec3(.7,1.,.7);
        float hair = length(ph-vec3(0.,0.35,-0.1))-.55;
        hair -= (cos(ph.z*8.+ph.y*4.5+ph.x*4.)+cos(ph.z*4.+ph.y*6.5+ph.x*8.))*.05;
        //hair -= (pow(noise(ph*3.+1.)*.5+.5, .75)*2.-1.)*.1;
        hair = smin(hair, body, 0.1);
        
        // ears
        pp = ph;
        pp.yz = rot(-.6) * pp.yz;
        pp.x = abs(p.x)-.8;
        pp *= vec3(.3,1.,.4);
        pp -= vec3(0.,-0.05 - pow(pp.x,2.)*5.,-.1);
        float ears = length(pp)-.15;
        ears = smax(ears, -(length(pp-vec3(0.,-.1,0.))-.12), .01);
        pp.y *= .3;
        pp.y -= -.11;
        float earsClip =  length(pp)-.16;
        
        //eyes
        pp = ph;
        pp.x = abs(ph.x)-.4;
        float eyes = length(pp*vec3(1.,1.,1.-eyesSurprise)-vec3(0.,0.,-1.)) - .3;

        // nostrils
        pp.x = abs(ph.x)-.2;
        pp.xz = rot(-.45) * pp.xz;
        head = smax(head, -length(pp-vec3(-0.7,-1.2,-2.05)) + .14*noseSize, .1);
        head = smin(head, torus(pp-vec3(-0.7,-1.2,-1.94), vec2(.14*noseSize,.05)), .05);

        // tail
        float tail =  capsule(p-vec3(0.,-.1,cos(p.y-.7)*.5),vec3(cos(iTime*animationSpeed.z)*animationAmp.z,.2,5.), vec3(0.,2.,4.9), .2);
        tail -= (cos(p.z*8.+p.y*4.5+p.x*4.)+cos(p.z*4.+p.y*6.5+p.x*3.))*.02;
        tail = smin(body, tail, .1);
        
        // Union
        vec2 dmat = vec2( body, COTON);
        dmat = dmin(dmat, vec2(tail, COTON));
        dmat = dmin(dmat, vec2(hair, COTON));
        dmat.x = smax(dmat.x, -earsClip, .15);
        dmat = dmin(dmat, vec2(legs, SKIN));
        dmat = dmin(dmat, vec2(head, SKIN));
        dmat = dmin(dmat, vec2(eyes, EYE));
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
    dmat = dmin(dmat, anvil(p));
    dmat = dmin(dmat, blood(p));
    
    return dmat;
}

vec3 skyColor(vec3 rd, vec2 uv, float night) {
    vec3 col = vec3(night * night);
    
    // mon
    vec2 moonPos = vec2(cos(iTime*.7+2.4), sin(iTime*.7+2.4)*.75 );
    float moonCircle = smoothstep(0.151,0.15, length(uv-moonPos));
    float moon = moonCircle * smoothstep(0.15,0.1501, length(uv-moonPos-vec2(.05,0.05))+0.004*noise(100.*vec3(uv-moonPos, 0.)));

    // stars
    vec2 p = rot(iTime*0.0002)*uv*200.;
    vec2 fp = fract(p)-.5;
    vec2 ip = floor(p);
    vec3 rnd = hash3(vec3(abs(ip),abs(ip.x)));
    float s = rnd.z*.06;

    col += vec3(1., 1., .1) * moon*smoothstep(.5,-1., sunDir.y);
    col += smoothstep(s,s*.01, length(fp+(rnd.xy-.5)) ) * (1.-moonCircle);
    col += exp(-length(uv-moonPos)*2.)*.1;
    
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
    return max(0.,1.0 - falloff*1.5*occ);
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
    float result = INFINITE;
    float t;
    
    // Sheep intersection
    vec2 nf = boxIntersection(ro-sheepPos-vec3(0.,3.,-2.),rd, vec3(3.,3.,7.), m);
    if (nf.y>0.) {
        t = max(nf.x,0.);
        for(int i=0; i<128; i++) {
            vec3 p = ro + rd * t;
            float d = dmin(vec2(p.y,GROUND),sheep(p)).x; // BUGS : at 23secondes without ground SDF ?!
            t += d;
            if (t > nf.y || abs(d) < 0.001) break;
        }
        if (t < nf.y)
            result = t; 
    }
    
    // Panels
    nf = boxIntersection(ro-panelPos-vec3(0.,5.,-5.),rd, vec3(1.5,5.,1.), m);
    if (nf.y>0.) {
        t = max(nf.x,0.);
        for(int i=0; i<128; i++) {
            float d = panelFood(ro+rd*t).x;
            t += d;
            if (t > nf.y || abs(d) < 0.001) break;
        }
        if (t < nf.y)
            result = min(result,t); 
    }

    nf = boxIntersection(ro-panelWarningPos-vec3(0.,5.,-5.),rd, vec3(1.5,5.,1.), m);
    if (nf.y>0.) {
        t = max(nf.x,0.);
        for(int i=0; i<128; i++) {
            float d = panelWarning(ro+rd*t).x;
            t += d;
            if (t > nf.y || abs(d) < 0.001) break;
        }
        if (t < nf.y)
            result = min(result,t); 
    }
    
    // Flower
    nf = boxIntersection(ro-flowerPos-vec3(0.,5.,0.),rd, vec3(2.,5.,1.), m);
    if (nf.y>0.) {
        t = max(nf.x,0.);
        for(int i=0; i<128; i++) {
            float d = flower(ro+rd*t).x;
            t += d;
            if (t > nf.y || abs(d) < 0.001) break;
        }
        if (t < nf.y)
            result = min(result,t); 
    }
    
    // Anvil
    // TODO: the 2nd vec3 is very approximative.
    nf = boxIntersection(ro-anvilPos-vec3(0.,3.,2.),rd, vec3(4.,4.,5.), m);
    if (nf.y>0.) {
        t = max(nf.x,0.);
        for(int i=0; i<128; i++) {
            float d = anvil(ro+rd*t).x;
            t += d;
            if (t > nf.y || abs(d) < 0.001) break;
        }
        if (t < nf.y)
            result = min(result,t); 
    }
    
    // Blood
    t = -(ro.y+.4) * m.y;// -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
    if (t > 0. && length((ro+rd*t).xz-anvilPos.xz)<10.) {
        for(int i=0; i<128; i++) {
            float d = blood(ro+rd*t).x;
            t += d;
            if (t > nf.y || abs(d) < 0.001) break;
        }
        if (t < 100.)
            result = min(result,t); 
    }
    
    // Ground intersection
    t = -(ro.y) * m.y;// -(dot(ro,p.xyz)+p.w)/dot(rd,p.xyz);
    if (t>0.) result = min(result,t);
    
    return result;
}

float blinnphong(float vdoth, float n)
{
    return pow(vdoth, n) * (n + 2.) / (8. * PI);
}

float specular(vec3 v, vec3 l, float size)
{
    vec3 h = normalize(l + v);
    float vdoth = clamp(dot(v, h), 0., 1.);
    return
        blinnphong(vdoth, 30./(1.+size)) * 2. +
        blinnphong(vdoth, 20000./(1.+size));
}

vec3 envmap(vec3 v, vec3 l, vec3 l2) {
    float spot = 0.;
    spot += specular(v, normalize(l + vec3(0., 0., 0.)), 0.);
    spot += specular(v, normalize(l + vec3(0.2, 0., 0.)), 2.);
    spot += specular(v, normalize(l + vec3(0.2, 0., 0.2)), 4.);
    spot += specular(v, l2, 20.) * .1;
    spot += specular(v, normalize(l2 + vec3(0.1, 0., 0.2)), 80.) * .5;
    spot /= 5.;
    
    vec3 color = mix(
        mix(vec3(.3,.3,0.), vec3(.1), smoothstep(-.7, .2, v.y)),
        vec3(0.3, 0.65, 1.), smoothstep(-.0, 1., v.y));
    color += spot * vec3(1., 0.9, .8);
    return color;
}

// /!\ Not energy conservative!
vec3 shade(vec3 ro, vec3 rd, vec3 p, vec3 n, vec2 uv) {
    vec2 dmat = map(p);
    
    
    float night = smoothstep(0.,.3, sunDir.y)+.1;
    
    float ao = fastAO(p, n, .15, 1.);
    ao *= fastAO(p, n, 1., .1)*.5;
    
    float shad = shadow(p, sunDir, .08, 50.);
    float fre = clamp(1.0+dot(rd,n), 0., 5.);
    
    vec3 diff = vec3(1.,.8,.7) * max(dot(n,sunDir), 0.) * pow(vec3(shad), vec3(1.,1.2,1.5));
    vec3 bnc = vec3(1.,.8,.7)*.1 * max(dot(n,-sunDir), 0.) * ao;
    vec3 sss = vec3(.5) * mix(fastAO(p, rd, .3, .75), fastAO(p, sunDir, .3, .75), 0.5);
    vec3 spe = vec3(1.) * max(dot(reflect(rd,n), sunDir),0.);
    vec3 envm = vec3(0.);
    
    //sss = vec3(1.) * calcSSS(p,rd);
    vec3 amb = vec3(.4,.45,.5)*1. * ao;
    vec3 emi = vec3(0.);
    
    vec3 albedo = vec3(0.);
    if(dmat.y == GROUND) {
        albedo = vec3(3.);
        sss *= 0.;
        spe *= 0.;
    } else if (dmat.y == COTON) {
        albedo = vec3(.4);
        sss *= fre*.5+.5;
        emi = vec3(.35);
        spe = pow(spe, vec3(4.))*fre*.25;
    } else if (dmat.y == CLOGS) {
        albedo = vec3(.025);
        sss *= 0.;
        spe = pow(spe, vec3(80.))*fre*20.;
    } else if (dmat.y == EYE) {
        sss *= .5;
        float ndz = dot(n, normalize(vec3(0.,0.,1.)));
        float nde = dot(n, eyeDir);
        float pupil = smoothstep(-0.953,-.952, nde-eyesSurprise/2.);
        
        vec3 pos = n + eyeDir;
        float center = smoothstep(.06, .1, length(pos));
        float dist = smoothstep(.15, 0.7, length(pos));

        float flower = abs(sin(atan(pos.y, pos.x) * 5.)) - dist*4.;
        flower = smoothstep(0.449, 0.45, flower);
        albedo = mix(vec3(0.), vec3(.75,0.5,1.)*.5, flower);
        albedo = mix(vec3(.7, .7, 0.), albedo, center);
        albedo *= smoothstep(135.2, 135.6, iTime);
        albedo = mix(albedo, vec3(.8), pupil);
        
        if (ndz > 0. || blink > .95) { 
            dmat.y = SKIN;
        } else {
            // Update the normals inside the pupil to get lots of reflections
            n = mix(normalize(n + (eyeDir + n)*4), n, pupil);
            vec3 light1 = normalize(vec3(1., 1.5, -1.));
            vec3 light2 = vec3(-light1.x, light1.y*.5, light1.z);
            envm = envmap(reflect(rd, n), light1, light2) * mix(.15, .2, pupil);
        }
        spe *= 0.;
        //spe = pow(spe, vec3(8.))*fre*2.;
    } else if(dmat.y == METAL) {
        albedo = vec3(.85,.95,1.);
        sss *= 0.;
        spe = pow(spe, vec3(8.))*fre*2.;
    } else if(dmat.y == PANEL) {
        vec3 p = p-panelWarningPos;
        sss *= 0.;
        spe = pow(spe, vec3(8.))*fre*20.;
        
        if (n.z > .5) {
            float tri = triangle(p-vec3(0.,7.5,-5.), vec2(1.3,.2), .01);
            albedo = vec3(1.5,0.,0.);
            float symbol = smoothstep(0.13,0.1295, distance(p,vec3(0.,7.1,-4.9)));
            symbol += smoothstep(0.005,0.,UnevenCapsule2d(p.xy-vec2(0.,7.34), .06,.14,1.));
            albedo = mix(albedo, vec3(2.), smoothstep(0.005,.0, tri));
            albedo = mix(albedo, vec3(0.), symbol);
        } else {
            albedo = vec3(.85,.95,1.);
        }
    } else if(dmat.y == PANEL_FOOD) {
        vec3 p = p-panelPos;
        sss *= 0.;
        spe = pow(spe, vec3(8.))*fre*10.;
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
            albedo = mix(albedo, vec3(2.), smoothstep(0.01,.0, squ));
            albedo = mix(albedo, vec3(0.), symbol);
        } else {
            albedo = vec3(1.);
        }
    } else if (dmat.y == PISTIL) {
        vec3 pr = p - flowerPos;
        pr.x += cos(3.1*.25+iTime)*3.1*.2;
        pr.y -= 2.8;
        pr.zy = rot(.75) * pr.zy;
        albedo = mix(vec3(2.,.75,.0), vec3(2.,2.,.0), smoothstep(0.,.45, length(pr-vec3(0.,.3,0.))))*1.8;
        sss = vec3(0.01);
        spe *= 0.;
    } else if (dmat.y == TIGE) {
        albedo = vec3(0.,.05,.0);
        spe *= fre;
    } else if (dmat.y == PETAL) {
        vec3 pr = p - flowerPos;
        pr.x += cos(3.1*.25+iTime)*3.1*.2;
        pr.y -= 2.8;
        pr.zy = rot(.75) * pr.zy;
        albedo = mix(vec3(1.,1.,1.)+.5, vec3(.75,0.5,1.), smoothstep(0.5,1.1, length(pr-vec3(0.,.3,0.))))*2.;
       // albedo = vec3(1.,1.,1.)*3.;
        sss *= 0.;
        spe = pow(spe, vec3(4.))*fre*1.0;
    } else if(dmat.y == BLACK_METAL) {
        albedo = vec3(1.);
        diff *= vec3(.1)*fre;
        amb *= vec3(.1)*fre;
        bnc *= 0.;
        sss *= 0.;
        spe = pow(spe, vec3(100.))*fre*2.;
    }  else if(dmat.y == BLOOD) {
        albedo = vec3(1.,.01,.01)*.3;
        float fre2 = fre*fre;
        diff *= vec3(3.);
        amb *= vec3(2.)*fre2;
        sss *= 0.;
        spe = vec3(1.,.3,.3) * pow(spe, vec3(500.))*5.;
    } 
    if (dmat.y == SKIN) {
        albedo = vec3(1.,.7,.5)*1.;
        amb *= vec3(1.,.75,.75);
        sss = pow(sss, vec3(.5,2.5,5.0)+2.)*2.;// * fre;// * pow(fre, 1.);
        spe = pow(spe, vec3(4.))*fre*.02;
    }
    
    vec3 col =  (albedo * (amb*1. + diff*.5 + bnc*2. + sss*2. ) + envm + spe*shad + emi) *  night;//* (saturate(sunDir.y)*.95+.05);
    // col = envm;
    //col = diff;//diff + bnc + amb + sss;
    //col = albedo * spe;
   //col = diff;
    //col = amb;
   // col = sss;
    // fog
    float t = length(p-ro);
    col = mix(col, skyColor(rd,uv, night), smoothstep(90.,100.,t));
    col = clamp(col,0.,1.);

    // Excited background
    if(dmat.y == GROUND) {
        float r = length(uv)*.5;
        float theta = cos(atan(uv.x, uv.y)*15.-iTime*3.-r*30.*excited.y);
        vec3 c = mix(vec3(1.,0.5,00), vec3(.8,0.5,1.), (cos(r*5.+iTime*5.)*.5+.5)*excited.y);
        //vec3 c = vec3(1.,0.5,00);
        col = mix(col,  mix(c, vec3(1.,1.,1.), smoothstep(-r, r, theta)), excited.x);
    }

    return col;
}

void main()
{
    vec2 invRes = vec2(1.) / iResolution;
    vec2 uv = (gl_FragCoord.xy) * invRes;
    vec2 v = uv*2.-1.;
    v.x *= iResolution.x * invRes.y;
        
    // Setup ray
    vec3 ro = camPos;
    vec3 ta = camTa;
    vec3 rd = lookat(ro, ta) * normalize(vec3(v,camFocal - length(v)*fishEyeFactor));
        
    // Trace
    float t = fastTrace(ro,rd);
    vec3 p = ro + rd * t;
    vec3 n = normal(p);
    vec3 col = shade(ro, rd, p, n, v);
        
    // Excited stars
    {
        vec2 p = v*5.;
        p.x = abs(p.x-.3)-1.5;
        p.y -= 1.4;
        p = rot(iTime*5.) * p;
        float size = 1.4+0.2*sin(iTime*20.);
        size *= smoothstep(0.5,1.,excited.x);
        float star = star2d(p, size, .5);
        vec3 starColor = mix(vec3(1.,.6,0.), vec3(1.,.2,0.), smoothstep(-.1,.6, star2d(p, size*.5, .5)))*1.3;
        col = mix(col, starColor, smoothstep(0.,-0.01, star) * excited.x);
    }

    // gamma correction
    fragColor = vec4( pow(col, vec3(1./2.2)), 1.);
    
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
   
    vec3 u = w*w*w*(w*(w*6.0-15.0)+10.0);
    


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
