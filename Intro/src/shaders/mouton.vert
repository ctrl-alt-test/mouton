#version 150

in vec4 a_position;

out vec3 animationAmp; //(x = walking, y = head, z = tail)
out vec3 animationSpeed; //(x = walking, y = head, z = tail)
out vec3 sheepPos;
out vec3 flowerPos;
out vec3 panelPos;
out vec3 panelWarningPos;
out vec3 anvilPos;
out vec3 sunDir;
out vec3 camPos;
out vec3 camTa;
out vec3 eyeDir;
out vec2 headRot;
out float blink;
out float camFocal;
out float eyesSurprise;
out float excited;
out float fishEyeFactor;
out float noseSize;


uniform float iTime;

void main(void)
{
    gl_Position = a_position;
    
    float time = iTime;
    
    // Default stuff
    sheepPos = vec3(0.);
    panelPos = vec3(9999.);
    flowerPos = vec3(9999.);
    panelWarningPos = vec3(9999.);
    anvilPos = vec3(9999.);
    camFocal = 2.;
    blink = max(fract(iTime*.333), fract(iTime*.123+.1));
    excited = 0.;
    sunDir = normalize(vec3(3.5,1.,-1.));
    animationSpeed = vec3(1.,1.,1.);
    fishEyeFactor = 0.;
    headRot = vec2(0.);
    noseSize = 1.;
    eyesSurprise = 0.;
    
    
    // Timeline
    if (time < 10.) // Head zoom
    {
        animationAmp = vec3(1.,.2, 1.); // Slow walk
        animationSpeed = vec3(1.,1.,.5);
        eyeDir = normalize(vec3(0.,.5,1.)); // Tired
        headRot.y = .25;
        
        camFocal = 4.;
        camPos = vec3(0.,2.5, -3.7);
        camTa = vec3(0., 3., 0.);
    } else if (time < 20.) // Legs view
    {
        float time = time-10.;
        animationAmp = vec3(1.,.2, .25); // Slow walk
        animationSpeed = vec3(1.,1.,2.);
        eyeDir = normalize(vec3(0.,.5,1.)); // Tired
        headRot.y = .25;
        
        camFocal = 4.;
        camPos = vec3(5., .5, 0.);
        camTa = vec3(0., .5, 1.);
    } else if( time < 30.) { // Desert walking
        float time = time-20.;
        animationAmp = vec3(1.,.2, .25); // Slow walk
        animationSpeed = vec3(1.,1.,2.);
        eyeDir = normalize(vec3(0.,.5,1.)); // Tired
        headRot.y = .25;
        
        camFocal = 2.;
        camPos = vec3(-8., 2., time-10.);
        camTa = vec3(0., 2., time-10.);
    } else if( time < 50.) { // Day 'n night walking
        float time = time-30.;
        animationAmp = vec3(1.,.2, .25); // Slow walk
        animationSpeed = vec3(1.,1.,2.);
        eyeDir = normalize(vec3(0.,.5,1.)); // Tired
        headRot.y = .25;
        
        //float t = 1.-exp( -40.*pow(time/20.,10.) )*30.;
        float t = time*.35+.3;
        sunDir = normalize(vec3(cos(t), sin(t),-.3)); // Day night cycle
        
        camFocal = 1.5;
        camPos = vec3(22., 2., time*0.6-10.);
        camTa = vec3(0., 2., time*0.6-10.);
    } else if (time < 55.) { // Eye focus
        float time = time-50.;
        float t = smoothstep(2.,2.5,time);
        
        headRot.y = mix(.25, 0., t);
        
        animationAmp = vec3(1.-t,.2*(1.-t), 1.); // Slow walk
        animationSpeed = vec3(1.,1.,.5);
        
        eyeDir = normalize(vec3(t*.3,.3-t*.3,1.));
        eyesSurprise = smoothstep(4.6,4.8,time)*.2;
        
        camFocal = 4.;
        camPos = vec3(0.,3., -4.);
        camTa = vec3(0., 3., 0.);
        
        if (time > 3.)
            blink = max(fract(iTime*.333), fract(iTime*.333+.08));
    } else if (time < 58.) { // Panel food!
        float time = time-55.;
        sheepPos = vec3(9999.);
        panelPos = vec3(0.);
        camPos = vec3(10.,3.,5.);
        float transition = smoothstep(0.0,.25,time);
        camTa = mix(vec3(-3.,3.,20.), vec3(2., 3.8, 0.), transition);
        camFocal = 3.;
    } else if (time < 65.) { // Excited!
        float time = time-58.;
        float transition = smoothstep(0.,.25,time);
        
        animationAmp = vec3(0.,0.,0.);
        blink = 0.;
        eyeDir = normalize(vec3(.3,0.,1.));
        camPos = mix(vec3(0.,3.,-4.), vec3(0.,2.,-6.), transition);
        camTa = vec3(0., 3., 0.);
        camFocal = mix(4., 3., transition);
        excited = transition;
    } else if (time < 75.) { // Panel run
        float time = time-65.;
        eyeDir = normalize(vec3(0.,0.,1.));
        sheepPos = vec3(0.,0.,-time*2.-2.);
        panelPos = vec3(-5.,0.,-8.);
        animationAmp = vec3(1.,1.,.5);
        animationSpeed = vec3(3.,1.5,8.);
        camPos = vec3(16.,5.,9.);
        camTa = vec3(3., 5., -4.-time);
        camFocal = 3.;
    } else if (time < 85.) // Head exciting search
    {
        float time = time-75.;
        animationAmp = vec3(1.,1.,1.);
        animationSpeed = vec3(3.,1.5,8.);
        //eyeDir = normalize(vec3(pow(sin(time*1.),5.)*1.,cos(iTime*.5)*.1+.1,1.));
        
        float x = mod(time,8.);
        float lf = smoothstep(0.5,1.,x)*smoothstep(2.8,2.5,x) - smoothstep(4.,4.5,x)*smoothstep(5.8,5.5,x) + cos(iTime)*.2;
        eyeDir = normalize(vec3(lf,cos(iTime*.5)*.1+.1,1.));
        
        fishEyeFactor = .3;
        camFocal = 2.5;
        camPos = vec3(2.75,1., -5.25);
        camTa = vec3(0., 2.4, 0.);
        
        float t = mod(time, 2.);
        noseSize += smoothstep(0.5,.6,t)*smoothstep(0.7,.6,t)*.3;
        t = mod(time+.3, 3.);
        noseSize += smoothstep(0.5,.6,t)*smoothstep(0.7,.6,t)*.3;
    } else if (time < 90.) { // Eye focus
        float time = time-85.;
        float t = smoothstep(1.,3.,time);
        
        animationAmp = vec3(0.,1.*(1.-t*.5), 1.); // Slow walk
        animationSpeed = vec3(3.,1.5,6.);
        
        eyeDir = normalize(vec3(t*.5,.3-t*.45,1.));
        
        camFocal = 4.;
        camPos = vec3(0.,3., -4.);
        camTa = vec3(0., 3., 0.);
        
        if (time > 3.)
            blink = max(fract(iTime*.333), fract(iTime*.333+.08));
    } else if (time < 95.) { // Panel warning!
        sheepPos = vec3(0.);
        panelWarningPos = vec3(-5.,0.,-8.);
        
        eyeDir = normalize(vec3(.5,-0.15,1.));
        animationAmp = vec3(0.,0.5, 1.); // Slow walk
        animationSpeed = vec3(3.,1.5,6.);
        
        
        float time = time-90.;
        float transition = smoothstep(0.,1.,time);
        
        camFocal = mix(4., 3., transition);
        camPos = vec3(0.,3., -4.);
        
        camTa = mix(vec3(0., 3., 0.), vec3(-5., 5., -9.), transition);
    } else if (time < 103.) { // Panel moonwalk
        float time = time-95.;
        
        sheepPos = vec3(0.,0.,-11.);
        panelWarningPos = vec3(-5.,0.,-8.);
        
        eyeDir = normalize(mix(vec3(1.,-.5,1.), vec3(0.,.5,1.), smoothstep(2.5,4., time))); // Tired
        headRot.y = smoothstep(3.,5., time)*.5;
        headRot.x = smoothstep(4.,8., time)*.25*sin(time*3.);
        animationAmp = vec3(1.,.2,.5);
        animationSpeed = vec3(0.,.2,1.);
        camPos = vec3(-3.,4.8,-30.);
        camTa = vec3(-3., 4., 0.);
        camFocal = 3.5;
    } else if (time < 112.) { // Panel moonwalk
        float time = time-103.;
        float up = smoothstep(6.,9.,time);
        sheepPos = vec3(0.,0.,time*.5-11.);
        panelWarningPos = vec3(-2.,0.,-8.);
        eyeDir = normalize(vec3(-.5,.25-up,1.));
        headRot.y = .5-up*1.;
        animationAmp = vec3(1.,.2,.5);
        animationSpeed = vec3(-1.,1.,1.);
        camPos = vec3(18.,5.,-5.);
        camTa = vec3(-5., 5., -6.);
        camFocal = 3.;
    } else if (time < 116.) { // look at sign then flower
        float time = time-112.;
        animationAmp = vec3(0.);
        animationSpeed = vec3(0.);
        panelWarningPos = vec3(0.,0.,-8.);
        if (mod(time, 2.) < 1.) {
            camPos = vec3(0.,2., -8.);
            camTa = vec3(0., 3., 0.);
        } else {
            camPos = vec3(0.,5.5, 2.);
            camTa = vec3(0., 5.75, 0.);
        }
        eyeDir = normalize(vec3(0.,-.1,1.));
        camFocal = 3. + time*.1;
    } else if (time < 122.) { // looking around
        float time = time-116.;
        float t = sin(min(time,4.7));
        animationAmp = vec3(0.);
        animationSpeed = vec3(0.);
        
        eyeDir = normalize(vec3(t*.7,-smoothstep(6.,10.,time),1.));
        headRot.x = t * 0.25;
        eyesSurprise = smoothstep(5.6,5.8,time)*.2;
        
        camFocal = 3.5;
        camPos = vec3(0.,2., -8.);
        camTa = vec3(0., 3., 0.);

    } else if (time < 130.) { // sign -> flower
        float time = time-122.;
        sheepPos = vec3(9999.);
        panelWarningPos = vec3(-2.,0.,-8.);
        flowerPos = vec3(4.,0.,-20.);
        
        float transition = smoothstep(.5,2.5,time);
        camFocal = mix(3.5, 5., transition);
        camPos = vec3(0.,5.5, 2.);
        
        camTa = mix(vec3(-.5, 5.75, 0.), vec3(4., 2., -20.), transition);
        
    } else if (time < 142.) { // focus face / warning / flower
        float time = time-130.;
        float t = sin(clamp(time,0.,6.28));
        animationAmp = vec3(0.1);
        animationSpeed = vec3(0.2);

        int iTime = int(time);
        if (iTime % 4 == 1) { // sign
            panelWarningPos = vec3(0.,0.,-8.);
            camPos = vec3(0.,5.5, 2.);
            camTa = vec3(0., 5.75, 0.);
        } else if (iTime % 4 == 3) { // flower
            flowerPos = vec3(4.,0.,-8.);
            camPos = vec3(0.,5.5, 2.);
            camTa = vec3(4., 3., -8.);
        } else { // sheep
            camPos = vec3(0.,2.4, -8.);
            camTa = vec3(0., 3., 0.);
        }
        float p = smoothstep(0.,1.,fract(time));
        if (iTime % 4 == 0) p = 1. - p;
        headRot.x = -p*.1;
        eyeDir = normalize(mix(vec3(0.,-.2,1.), vec3(-.2,.2,1.), p));
        eyeDir = normalize(eyeDir + vec3(cos(time*10.),cos(time*5.),1.)*.01);
        // headRot.x = t * 0.25;
        
        camFocal = 2.8 + time*.15;
    } else if (time < 145.) { // decision taken
        float time = time-142.;
        float t = sin(clamp(time,0.,6.28));
        animationAmp = vec3(0.0,.1,0.);
        animationSpeed = vec3(0.,.5,0.);

        int iTime = int(time);
        camPos = vec3(0.,2.4, -8.);
        camTa = vec3(0., 3., 0.);

        headRot.x = -.1;
        headRot.y = sin(time*2.)*.1;
        eyesSurprise = smoothstep(0.,3.,time)*.1;
        eyeDir = normalize(vec3(-.2,.2,1.));
        
        camFocal = 3.2 - time*.15;
    } else if (time < 155.) { // Flower run
        float time = time-145.;
        eyeDir = normalize(vec3(0.,0.,1.));
        sheepPos = vec3(0.,0.,-time*2.-2.);
        panelWarningPos = vec3(-5.,0.,-8.);
        flowerPos = vec3(2.,0.,-30.);
        animationAmp = vec3(1.,1.,.5);
        animationSpeed = vec3(3.,1.5,8.);
        camPos = vec3(16.,5.,9.-time);
        camTa = vec3(3., 5., -3.-time*2.);
        camFocal = 3.+time*.1;
    } else if (time < 160.) { // Splash
        float time = time-155.;
        
        eyeDir = normalize(vec3(0.,0.,1.));
        sheepPos = vec3(0.,-smoothstep(0.05,0.1,time)*4.5,-22.);
        panelWarningPos = vec3(-5.,0.,-8.);
        flowerPos = vec3(2.,0.,-30.);
        animationAmp = vec3(1.,1.,.5);
        animationSpeed = vec3(3.,1.5,8.);
        
        camPos = vec3(16.+sin(time*.1)*3.,5.,-1.) + vec3(cos(iTime*50.))* smoothstep(0.1,0.2,time)* smoothstep(0.4,0.2,time);
        camTa = vec3(3., 5., -23.);
        camFocal = 4.;
        
        float fall = smoothstep(.1,0.,time)*13.;
        anvilPos = vec3(0.,fall+0.,-22.);
    }
}