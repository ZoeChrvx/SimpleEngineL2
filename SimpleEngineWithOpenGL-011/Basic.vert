//Request GLSL 3.3
 #version 330

 in vec inPosition;

 void main()
 {
	gl_Position = vec4(inPosition,1.0);
 }