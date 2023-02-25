#version 150
out vec4 fragColor;
const vec2 iResolution = vec2(1280.,720.);

uniform sampler2D prevPass;

float checkSame(vec4 center, vec4 samplef)
{
    vec2 centerNormal = center.xy;
    float centerDepth = center.z;
    vec2 sampleNormal = samplef.xy;
    float sampleDepth = samplef.z;
    
    // Less sensitive when it's far away; more edge details when it's closer.
    float sensitivity = mix(1.2, 0.3, smoothstep(1., 25., centerDepth));
    
    vec2 diffNormal = abs(centerNormal - sampleNormal) * sensitivity;
    bool isSameNormal = (diffNormal.x + diffNormal.y) < 0.2;
    float diffDepth = abs(centerDepth - sampleDepth) * sensitivity;
    bool isSameDepth = diffDepth < 1.9;

    if (centerDepth > 35. && sampleDepth > 35.) return 1.;

    return (isSameNormal && isSameDepth) ? 1.0 : 0.7;
}

void main(void) 
{
    vec4 sample0 = texture(prevPass, gl_FragCoord.xy / iResolution.xy);
    vec4 sample1 = texture(prevPass, (gl_FragCoord.xy + vec2(1., 1.)) / iResolution.xy);
    vec4 sample2 = texture(prevPass, (gl_FragCoord.xy + vec2(-1., -1.)) / iResolution.xy);
    vec4 sample3 = texture(prevPass, (gl_FragCoord.xy + vec2(-1., 1.)) / iResolution.xy);
    vec4 sample4 = texture(prevPass, (gl_FragCoord.xy + vec2(1., -1.)) / iResolution.xy);
    
    float edge = checkSame(sample1, sample2) * checkSame(sample3, sample4);
    
    // edge, base color, depth
    fragColor = vec4(edge, sample0.w, sample0.z, 1.);
}
