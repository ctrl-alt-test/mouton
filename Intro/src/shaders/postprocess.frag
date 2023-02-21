#version 150
out vec4 fragColor;
const vec2 iResolution = vec2(1280.,720.);

uniform sampler2D prevPass;
uniform float iTime;

/*
vec3 hash3(vec3 p) {
    uvec3 x = uvec3((p)*100000.);
    const uint k = 1103515245U; 
    x = ((x>>8U)^x.yzx)*k;
    x = ((x>>8U)^x.yzx)*k;
    x = ((x>>8U)^x.yzx)*k;
    
    return vec3(x)*(1.0/float(0xffffffffU))-.5;
}


float simplex3d(vec3 p) {
    const float F3 =  0.3333333;
    const float G3 =  0.1666667;

     vec3 s = floor(p + dot(p, vec3(F3)));
     vec3 x = p - s + dot(s, vec3(G3));
     
     vec3 e = step(vec3(0.0), x - x.yzx);
     vec3 i1 = e*(1.0 - e.zxy);
     vec3 i2 = 1.0 - e.zxy*(1.0 - e);
        
     vec3 x1 = x - i1 + G3;
     vec3 x2 = x - i2 + 2.0*G3;
     vec3 x3 = x - 1.0 + 3.0*G3;
     
     vec4 w, d;
     
     w.x = dot(x, x);
     w.y = dot(x1, x1);
     w.z = dot(x2, x2);
     w.w = dot(x3, x3);
     
     w = max(0.6 - w, 0.0);
     
     d.x = dot(hash3(s), x);
     d.y = dot(hash3(s + i1), x1);
     d.z = dot(hash3(s + i2), x2);
     d.w = dot(hash3(s + 1.0), x3);
     
     w *= w;
     w *= w;
     d *= w;
     
     return dot(d, vec4(52.0));
}
*/

vec2 uv;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float rand(float c){
    return rand(vec2(c,1.0));
}

float randomLine(float seed)
{
    float b = 0.01 * rand(seed);
    float a = rand(seed+1.0);
    float c = rand(seed+2.0) - 0.5;
    float mu = rand(seed+3.0);
    
    float l = 1.0;
    
    if ( mu > 0.2)
        l = pow(  abs(a * uv.x + b * uv.y + c ), 1.0/16.0 );
    else
        l = 2.0 - pow( abs(a * uv.x + b * uv.y + c), 1.0/8.0 );             
    
    return mix(0.5, 1.0, l);
}

// Generate some blotches.
float randomBlotch(float seed)
{
    float x = rand(seed);
    float y = rand(seed+1.0);
    float s = 0.01 * rand(seed+2.0);
    
    vec2 p = vec2(x,y) - uv;
    p.x *= iResolution.x / iResolution.y;
    float a = atan(p.y,p.x);
    float v = 1.0;
    float ss = s*s * (sin(6.2831*a*x)*0.1 + 1.0);
    
    if ( dot(p,p) < ss ) v = 0.2;
    else
        v = pow(dot(p,p) - ss, 1.0/16.0);
    
    return mix(0.3 + 0.2 * (1.0 - (s / 0.02)), 1.0, v);
}


void main(void)
{
    // Set frequency of global effect (12 / second).
    float t = float(int(iTime * 12));

    vec2 invRes = 1./iResolution;
    uv = gl_FragCoord.xy * invRes;
    // Jumping image
    if (rand(t) < .01) uv += vec2(0.1);
    // Get some image movement
    vec2 suv = uv + 0.004 * vec2( rand(t), rand(t + 23.0));
    vec2 offset = (suv*2.-1.)*invRes.x*.5;

    
    // chromatic aberration
    vec3 col = texture(prevPass,suv+offset).rgb;
    

    //col.r = texture(prevPass,suv+offset).r;
    //col.g = texture(prevPass,suv).g;
    //col.b = texture(prevPass,suv-offset).b;
    
    // filmic grain
    /*
    vec3 grain = vec3(simplex3d(vec3( gl_FragCoord.xy * invRes.y * 250., iTime*5.)));
    float luminance = dot(col, vec3(0.2126,0.7152,0.0722));
    col += (grain) * (1.-pow(luminance,.25)) * .1;
    */

    // fade in
    col *= smoothstep(0.,10., iTime);
    
    const float endTime = 160.;

    {
    // Circle to black
    float circle = length(gl_FragCoord.xy/iResolution.xx - vec2(.5,.3));
    float t2 = max(.137, smoothstep(endTime+1., endTime, iTime));
    col *= smoothstep(t2, t2-.005, circle);

    // Looney tunes
    float f = circle;
    float alpha = smoothstep(0.135, .136, f) * smoothstep(endTime+1., endTime+2., iTime);
    f = fract(23. * pow(f, .25));
    f -= smoothstep(0.95, 0.99, f);
    vec3 col2 = mix(vec3(1.,.6,.0), vec3(1.,.0,0.), pow(f,1.));
    col = mix(col, col2, alpha);
    }
    
    // Create a time-varying vignetting effect
    float vI = 16.0 * (uv.x * (1.0-uv.x) * uv.y * (1.0-uv.y));
    vI *= mix( 0.7, 1.0, rand(t + 0.5));
    
    // Add additive flicker
    //vI += 0. + 0.2 * rand(t+8.);
        
    // Add a fixed vignetting (independent of the flicker)
    vI *= pow(16.0 * uv.x * (1.0-uv.x) * uv.y * (1.0-uv.y), 0.14);

    int l = int(8.0 * rand(t+7.0));
    int s = int( max(8.0 * rand(t+18.0) -2.0, 0.0 ));
    for (int i = 1; i < 8; i++) {
        if ( i < l ) vI *= randomLine( t+6.0+17.* i);
        if ( i < s ) vI *= randomBlotch( t+6.0+19.* i);
    }

    // Show the image modulated by the defects
    col *= vI;
    // Add some grain
    col *= 1.0+(rand(uv+t*.01)-.2)*.15;

    // Monochrome
    float luma = dot( vec3(0.2126, 0.7152, 0.0722), col);
    col = luma * vec3(0.7, 0.7, 0.7);
    // col = mix(col, luma * vec3(0.7, 0.7, 0.7), 1.); // desaturated

    col.b = pow(col.r, 0.9); // slightly blue-ish

    // Fade out
    col *= smoothstep(endTime+5., endTime+4., iTime);

    fragColor = vec4(col,1.);
}
