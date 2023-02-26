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

    if (centerDepth > .999 && sampleDepth > .999) return 1.;
    
    // Less sensitive when it's far away; more edge details when it's closer.
    float sensitivity = mix(1.3, .4, centerDepth);
    
    float distNormal = distance(centerNormal, sampleNormal) * sensitivity;
    if (distNormal > 0.15) return mix(0.6, 1., smoothstep(0.15, 1., distNormal));

    float diffDepth = abs(centerDepth - sampleDepth) * sensitivity;
    bool isSameDepth = min(centerDepth,sampleDepth) / max(centerDepth,sampleDepth) > 0.85;
    //isSameDepth = true;

    return isSameDepth ? 1.0 : 0.6;
//    return 1.;
}

void main(void) 
{
    float width = 0.0009;
    vec4 sample0 = texture(prevPass, gl_FragCoord.xy / iResolution.xy);
    vec4 sample1 = texture(prevPass, gl_FragCoord.xy / iResolution.xy + vec2(width, width));
    vec4 sample2 = texture(prevPass, gl_FragCoord.xy / iResolution.xy + vec2(-width, -width));
    vec4 sample3 = texture(prevPass, gl_FragCoord.xy / iResolution.xy + vec2(-width, width));
    vec4 sample4 = texture(prevPass, gl_FragCoord.xy / iResolution.xy + vec2(width, -width));
    
    float edge = checkSame(sample1, sample2) * checkSame(sample3, sample4);
    
    // edge, base color, depth
    fragColor = vec4(edge, sample0.w, sample0.z, 1.);
    //fragColor = vec4(edge, sample0.w, sample0.z, 1.);
}

