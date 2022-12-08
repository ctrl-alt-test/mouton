#version 150
out vec4 fragColor;
#define iResolution vec2(1280.,720.)

uniform float iTime;


uniform sampler2D prevPass;

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
     
     /* 3. return the sum of the four surflets */
     return dot(d, vec4(52.0));
}


void main(void)
{
    vec2 invRes = 1./iResolution;
    vec2 uv = gl_FragCoord.xy * invRes;
    vec2 offset = (uv*2.-1.)*invRes.x*.5;
    
    // chromatic aberration
    vec3 col;
    col.r = texture(prevPass,uv+offset).r;
    col.g = texture(prevPass,uv).g;
    col.b = texture(prevPass,uv-offset).b;
    
    // filmic grain
    vec3 grain = vec3(simplex3d(vec3( gl_FragCoord.xy * invRes.y * 250., iTime*5.)));
    float luminance = dot(col, vec3(0.2126,0.7152,0.0722));
    col += (grain) * (1.-pow(luminance,.5)) * .05;
    
    // fade in & fade out
    col *= smoothstep(0.,10., iTime);
    col = mix(col, vec3(1.), smoothstep(158., 160., iTime));
    
    
    fragColor = vec4(col,1.);
}