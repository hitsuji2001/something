#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 textCoord;
uniform vec4 outColor;
uniform sampler2D oTexture;

void main() {
  FragColor = texture(oTexture, textCoord) * (vertexColor + outColor);
  //vec4(0.03f, 0.62f, 0.27f, 1.0f);
}
