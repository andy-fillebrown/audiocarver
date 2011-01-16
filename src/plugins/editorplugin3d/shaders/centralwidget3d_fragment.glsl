
uniform sampler2D Texture;
uniform vec2 screenOrigin;
uniform vec2 screenSize;

void main(void)
{
   gl_FragColor = texture2D(Texture, (gl_FragCoord.xy - screenOrigin) / screenSize);
   gl_FragColor.a = 0.5;
}
