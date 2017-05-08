#version 120

varying vec2 texCoord0;
uniform sampler2D sampler;

varying vec3 normal0;

void main()
{
    gl_FragColor = vec4(0.8, 0.75, 0.8, 1.0) * clamp(dot(-vec3(0,0,1), normal0), 0.0, 1.0); //   texture2D(sampler, texCoord0)
}
