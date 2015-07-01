#version 300 es
uniform mat4 affine_matrix; // linear: x y z 1
uniform mat4 quadratic_matrix; // quadratic: x^2 y^2 xy 0

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 color;
smooth out vec4 theColor;

void main(){
	vec4 a = vec4(position, 0.0, 0.0); 
	a.z = 0.0; 
	a.w = 1.0; 
	vec4 b; 
	b.x = a.x*a.x; 
	b.y = a.y*a.y; 
	b.z = a.x*a.y; 
	b.w = 0.0; 
	gl_Position = affine_matrix * a + quadratic_matrix * b; 
   theColor = color;
}