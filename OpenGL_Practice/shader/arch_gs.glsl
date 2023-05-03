#version 330 core
layout (lines) in;
layout (triangle_strip, max_vertices = 24) out;

uniform mat4 mvp;
uniform float radius;
uniform vec4 color;

out vec3 gColor;

// 2 - 3
// | \ |
// 0 - 1

void emit(vec4 p0, vec4 p1) {
    gl_Position = mvp * p0;
    EmitVertex();
    gl_Position = mvp * p1;
    EmitVertex();
}

void main() {
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;

    float alpha = radians(180.0f) / 8.0f;
    vec4 offset;

    // Draw Arch
    for (int i = 0; i <= 8; ++i) {
        float cur_alpha = i * alpha;
        offset = vec4(0.0f, -radius + radius * sin(cur_alpha), -radius * cos(cur_alpha), 0.0f);
        vec3 tcolor = color.rgb;
        gColor = tcolor + sin(cur_alpha) * (vec3(1.0f, 1.0f, 1.0f) - tcolor);
        emit(p0 + offset, p1 + offset);
    }

    // Draw Body
    gColor = color.rgb;
    float height = 1.0f;

    p0 += offset, p1 += offset;
    emit(p0 + vec4(0.0f, height, 0.0f, 0.0f), p1 + vec4(0.0f, height, 0.0f, 0.0f));

    p0.y += height, p1.y += height;
    emit(p0 - vec4(0.0f, 0.0f, 2 * radius, 0.0f), p1 - vec4(0.0f, 0.0f, 2 * radius, 0.0f));

    p0.z -= 2 * radius, p1.z -= 2 * radius;
    emit(p0 - vec4(0.0f, height, 0.0f, 0.0f), p1 - vec4(0.0f, height, 0.0f, 0.0f));

    EndPrimitive();
}
