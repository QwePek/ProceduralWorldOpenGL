#shader vertex
#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 textureCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	texCoord = textureCoord;
}

#shader fragment
#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D ourTexture1;

void main()
{
	//fragColor = mix(texture(ourTexture1, texCoord), texture(ourTexture2, vec2(1.0f - texCoord.x, texCoord.y)), 0.2f) *
		//vec4(verColor, 1.0f);
	fragColor = texture(ourTexture1, texCoord);
}