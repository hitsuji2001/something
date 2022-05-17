#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
uniform vec4 outColor;

void main() {
  FragColor = vertexColor + outColor;
  //vec4(0.03f, 0.62f, 0.27f, 1.0f);
}
