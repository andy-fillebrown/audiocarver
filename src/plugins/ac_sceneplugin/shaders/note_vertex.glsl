
uniform float x;
uniform float y;
uniform float z;

uniform vec3 offset;
uniform vec3 scale;

void main(void)
{
    vec3 pos;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    pos *= scale;
    pos += offset;
    gl_Position = pos;
}
