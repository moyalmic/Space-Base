#version 140

uniform float time;                   
uniform sampler2D texSampler; 

in vec2 fragmentUV;   

out vec4 fragColor;             

uniform ivec2 pattern = ivec2(4, 4);

uniform float frameDuration;


vec4 sampleTexture(int frame) {

  vec2 offset = vec2(1.0) / vec2(pattern);

  vec2 texCoordBase = fragmentUV / vec2(pattern);
  vec2 texCoord = texCoordBase + vec2(frame % pattern.x, pattern.y - 1 - (frame / pattern.x)) * offset;

  return texture(texSampler, texCoord);
}

void main() {

  int frame = int(time / frameDuration);

 
  fragColor = sampleTexture(frame);
}
