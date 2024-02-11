// Request GLSL 3.3
#Version 330

// Tex coord input from vertex shader
in vec2 fragTexCoord;

// This corresponds to the output color to the color buffer
out vec4 outColor;

// this is used for the texture sampling
uniform sampler2D uTexture;

void main()
{
	//Sample color from texture
	outColor = texture(uTexture, fragTexCoord);
}