uniform double time;

#ifdef VERTEX

void main(void)
{
	vec4 v = vec4(gl_Vertex);
	v.z = sin(5.0*v.x + time*0.01)*0.25;
	gl_Position = gl_ModelViewProjectionMatrix * v;
}

#endif

#ifdef FRAGMENT

void main(void)
{
	gl_FragColor = vec4(0.4,0.4,0.8,1.0);
}

#endif