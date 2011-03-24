
uniform sampler2D texture;
uniform vec2 screenOrigin;
uniform vec2 screenSize;

void main(void)
{
    gl_FragColor = texture2D(texture, (gl_FragCoord.xy - screenOrigin) / screenSize);
}
