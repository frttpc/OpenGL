  #version 330 core

in vec3 vertex_position;
in vec3 vertex_normal;
in vec2 vertex_uv;

uniform int u_frame;
uniform sampler2D u_texture;
uniform vec3 u_light_pos;
uniform vec3 u_light_color;
uniform vec3 u_view_pos;

out vec4 FragColor;

void main()
{
	// diff light
	vec3 norm = normalize(vertex_normal);
	vec3 lightDir = normalize(u_light_pos - vertex_position);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_light_color;

	// ambient light
	vec3 ambientLight = vec3(0.2,0.2,0.2);

	// texture
	vec3 surfaceColor = texture(u_texture, vertex_uv).rgb;

	// specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_view_pos - vertex_position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * u_light_color;

	// final color
	vec3 color = surfaceColor * (ambientLight + diffuse + specular);

	FragColor = vec4(color, 1.0f);
}
