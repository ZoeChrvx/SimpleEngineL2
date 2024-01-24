//Request GLSL 3.3
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

//Attribute 0 is position, 1 is tex coords;
layout(location = 0) in vec3 inPosition
layout(locaton = 1) in vec3 in TexCoord;

out vec2 fragTexCoord;

void main(){
	vec4 pos = vec4(inPosition,1.0);
	gl_Position = pos * uWorldTransform * uViewProj;

	//Pass along the texture coordinate to frag shader
	dragTexCoord = inTexCoord;
}