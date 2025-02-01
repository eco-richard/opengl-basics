#version 330 core

in vec4 v_col;
in vec2 tex_coord;

out vec4 color;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
};

uniform sampler2D tex;
uniform DirectionalLight directional_light;

void main() {
    vec4 ambient_color = vec4(directional_light.color, 1.0f) * directional_light.ambientIntensity;

    color = texture(tex, tex_coord) * ambient_color;
}
