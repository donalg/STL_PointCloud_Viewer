#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 Transform;

void main()
{
	gl_Position =  Transform * vec4(position, 1.0); // ftransform();
	texCoord0 = texCoord;
	normal0 = (Transform * vec4(normal, 0.0)).xyz;
}
