#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec4 vertexColor;
out vec2 textCoord;

void main() {
  gl_Position = vec4(aPos, 1.0f);
  vertexColor = vec4(aColor, 1.0f);
  textCoord = vec2(aTextCoord.x, 1.0f - aTextCoord.y);
  // vec4(0.91f, 0.37f, 0.36f, 1.0f);
}
