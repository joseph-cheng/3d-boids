#version 330 core

layout (lines) in;
layout (triangle_strip, max_vertices = 12) out;

uniform mat4 proj_mat;
uniform mat4 view_mat;

out vec3 fColor;

void main() {
    vec3 pos = gl_in[0].gl_Position.xyz;
    vec3 vel = gl_in[1].gl_Position.xyz;
    vec3 normalized_vel = normalize(vel)/100.0;
    vec3 base_vector_up = normalize(vec3(1.0, 1.0, -1 * (normalized_vel.x + normalized_vel.y)/normalized_vel.z))/200.0;
    vec3 base_vector_right = normalize(cross(normalized_vel, base_vector_up))/200.0;

    vec4 tip = proj_mat * view_mat * vec4(pos + normalized_vel, 1.0);
    vec4 base1 = proj_mat * view_mat * vec4(pos - normalized_vel + base_vector_up + base_vector_right, 1.0);
    vec4 base2 = proj_mat * view_mat * vec4(pos - normalized_vel - base_vector_up + base_vector_right, 1.0);
    vec4 base3 = proj_mat * view_mat * vec4(pos - normalized_vel - base_vector_up - base_vector_right, 1.0);
    vec4 base4 = proj_mat * view_mat * vec4(pos - normalized_vel + base_vector_up - base_vector_right, 1.0);

    fColor = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = base4;
    EmitVertex();

    gl_Position = base3;
    EmitVertex();

    gl_Position = base1;
    EmitVertex();

    gl_Position = base2;
    EmitVertex();

    fColor = vec3(1.0f, 0.0f, 0.0f);
    gl_Position = tip;
    EmitVertex();

    fColor = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = base3;
    EmitVertex();

    fColor = vec3(1.0f, 0.0f, 0.0f);
    gl_Position = tip;
    EmitVertex();

    fColor = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = base4;
    EmitVertex();

    fColor = vec3(1.0f, 0.0f, 0.0f);
    gl_Position = tip;
    EmitVertex();

    fColor = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = base1;
    EmitVertex();

    fColor = vec3(1.0f, 0.0f, 0.0f);
    gl_Position = tip;
    EmitVertex();

    fColor = vec3(1.0f, 1.0f, 1.0f);
    gl_Position = base2;
    EmitVertex();


}

