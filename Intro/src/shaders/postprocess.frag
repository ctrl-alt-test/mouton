#version 150
out vec4 fragColor;
const vec2 iResolution = vec2(1280.,720.);

uniform sampler2D prevPass;
uniform float iTime;

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
    
    l = pow(  abs(a * uv.x + b * uv.y + c ), 1.0/16.0 );
    //if ( mu > 0.2)
        
    // else
//         l = 2.0 - pow( abs(a * uv.x + b * uv.y + c), 1.0/16.0 );             
    
    return mix(0.5, 1.0, mu > 0.2 ? l : 2. - l);
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

    float col = texture(prevPass,suv+offset).r;

    // fade in
    col *= smoothstep(0.,10., iTime);
    
    const float endTime = 160.;

    // Circle to black
    float circle = length(gl_FragCoord.xy/iResolution.xx - vec2(.5,.3));
    float t2 = max(.137, smoothstep(endTime+1., endTime, iTime));
    col *= smoothstep(t2, t2-.005, circle);

    // Looney tunes
    float f = circle;
    float alpha = smoothstep(0.135, .136, f) * smoothstep(endTime+1., endTime+2., iTime);
    f = fract(23. * pow(f, .25));
    f -= smoothstep(0.95, 0.99, f);
    float col2 = mix(.55, .35, pow(f,1.));
    col = mix(col, col2, alpha);
    
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

    col *= .7;

    // Fade out
    col *= smoothstep(endTime+5., endTime+4., iTime);

    fragColor = vec4(col, col, col, 1.);
}
