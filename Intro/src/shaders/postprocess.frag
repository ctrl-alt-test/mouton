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
    
    l = pow(abs(a * uv.x + b * uv.y + c ), 1.0/16.0 );
    
    return mix(0.5, 1.0, mu > 0.2 ? l : 2. - l);
}

void main(void)
{
    // Set frequency of global effect (12 / second).
    float t = int(iTime * 12) / 12.;

    vec2 invRes = 1./iResolution;
    uv = gl_FragCoord.xy * invRes;
    // Jumping image
    if (rand(t) < .01) uv += vec2(0.1);
    // Get some image movement
    vec2 suv = uv + 0.004 * vec2( rand(t), rand(t + 23.0));
    suv += (suv*2.-1.)*invRes.x*.5;

    const float errorFreq = 20.;
    float errorRange = .004;
    vec2 uvs1 = suv; // + vec2(0. * errorRange * sin(errorFreq * suv.y), .0 * errorRange * sin(errorFreq * suv.x));
    float edge = pow(texture(prevPass, uvs1).r,1.);

    vec2 err = errorRange * vec2(sin(errorFreq * suv.y + 1.), sin(errorFreq * suv.x + 3.));
    edge *= mix(  pow(texture(prevPass, suv + err).r,0.7), 1., smoothstep(0.0, 0.006, length(err)));

    err = errorRange * vec2(sin(errorFreq * suv.y + 2.), sin(errorFreq * suv.x + 1.));
    edge *= mix(  pow(texture(prevPass, suv + err).r,0.7), 1., smoothstep(0.0, 0.005, length(err)));

    float col = texture(prevPass,suv).g;
    col *= edge;
    
    // fade in
    col *= smoothstep(0.,10., t);
    
    const float endTime = 160.;

    // Circle to black
    float circle = length(gl_FragCoord.xy/iResolution.xx - vec2(.5,.3));
    float t2 = max(.137, smoothstep(endTime+1., endTime, t));
    col *= smoothstep(t2, t2-.005, circle);

    // Looney tunes
    float f = circle;
    float alpha = smoothstep(0.135, .136, f) * smoothstep(endTime+1., endTime+2., t);
    f = fract(23. * pow(f, .25));
    f -= smoothstep(0.95, 0.99, f);
    float col2 = mix(.55, .35, pow(f,1.));
    col = mix(col, col2, alpha);
    
    // vignetting
    float vI = 12.0 * (uv.x * (1.0-uv.x) * uv.y * (1.0-uv.y));
    vI = smoothstep(0., .5, vI);

    int l = int(8. * rand(t+7.) - 1.);
    int s = int(8. * rand(t+18.) - 2.);
    for (int i = 0; i < 8; i++) {
        if (i < l) vI *= randomLine(t + i);
    }
    col *= vI;
    col -= rand(uv+t)*.05; // grain

    // Fade out
    col *= smoothstep(endTime+5., endTime+4., t);

    fragColor = vec4(col, col, col, 1.);
}

