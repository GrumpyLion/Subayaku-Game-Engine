#version 420 

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;
layout(location=3) in vec3 Tangent;
layout(location=4) in vec3 Bitangent;
layout(location=5) in mat4 WMatrix;

out flat vec3 oNormal;
out vec3 oFragPos;
out vec2 oTexCoord;

out flat vec3 oColor;

layout (std140, binding = 1) uniform GlobalDynamicBuffer
{ 
  mat4 uPMatrix;
  mat4 uVMatrix;
  vec4 uCameraPos;
  vec2 uTime;
};

uniform sampler2D uNoise;
uniform sampler2D uColor;

float rand(vec2 co)
{
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

//https://thebookofshaders.com/11/
// Some useful functions
vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }

float snoise(vec2 v) {

    // Precompute values for skewed triangular grid
    const vec4 C = vec4(0.211324865405187,
                        // (3.0-sqrt(3.0))/6.0
                        0.366025403784439,  
                        // 0.5*(sqrt(3.0)-1.0)
                        -0.577350269189626,  
                        // -1.0 + 2.0 * C.x
                        0.024390243902439); 
                        // 1.0 / 41.0

    // First corner (x0)
    vec2 i  = floor(v + dot(v, C.yy));
    vec2 x0 = v - i + dot(i, C.xx);

    // Other two corners (x1, x2)
    vec2 i1 = vec2(0.0);
    i1 = (x0.x > x0.y)? vec2(1.0, 0.0):vec2(0.0, 1.0);
    vec2 x1 = x0.xy + C.xx - i1;
    vec2 x2 = x0.xy + C.zz;

    // Do some permutations to avoid
    // truncation effects in permutation
    i = mod289(i);
    vec3 p = permute(
            permute( i.y + vec3(0.0, i1.y, 1.0))
                + i.x + vec3(0.0, i1.x, 1.0 ));

    vec3 m = max(0.5 - vec3(
                        dot(x0,x0), 
                        dot(x1,x1), 
                        dot(x2,x2)
                        ), 0.0);

    m = m*m ;
    m = m*m ;

    // Gradients: 
    //  41 pts uniformly over a line, mapped onto a diamond
    //  The ring size 17*17 = 289 is close to a multiple 
    //      of 41 (41*7 = 287)

    vec3 x = 2.0 * fract(p * C.www) - 1.0;
    vec3 h = abs(x) - 0.5;
    vec3 ox = floor(x + 0.5);
    vec3 a0 = x - ox;

    // Normalise gradients implicitly by scaling m
    // Approximation of: m *= inversesqrt(a0*a0 + h*h);
    m *= 1.79284291400159 - 0.85373472095314 * (a0*a0+h*h);

    // Compute final noise value at P
    vec3 g = vec3(0.0);
    g.x  = a0.x  * x0.x  + h.x  * x0.y;
    g.yz = a0.yz * vec2(x1.x,x2.x) + h.yz * vec2(x1.y,x2.y);
    return 130.0 * dot(m, g);
}

void main()
{
	vec4 Pos = WMatrix * vec4(Position, 1.0);
	
	oTexCoord = Texcoord;
	vec2 waveCoords = Texcoord * vec2(3.5, 3.5) + uTime * vec2(0.0001, 0.0001);
	
	oFragPos = Position.xyz;
	Pos.y += snoise(waveCoords) * 2;
	
	Pos.xz += vec2((snoise(waveCoords)-0.5f) * 15 , (snoise(-waveCoords)-0.5f) * 15);
	
	gl_Position = uPMatrix * uVMatrix * Pos;
		
	float amount = texture(uNoise, waveCoords).x * 0.5f;
	
	vec3 col = texture(uColor, vec2(1.0 / 5.0, 0)).xyz;
	col = mix(col, texture(uColor, vec2(3.0 / 5.0, 0)).xyz, amount);
	
	float beachHeight = clamp(texture(uNoise, Texcoord * vec2(-1, 1)).r, 0.0, 1.0);
	
	if(beachHeight > 0.75 ||beachHeight < 0.7) beachHeight = 0;
	
	//col = mix(col, vec3(1,1,1), beachHeight);
	
	float r = rand(vec2(Position.x, Position.z)) * 0.25 + 0.7;
	col *= vec3(r, r, r);
	oColor = col;
	
	vec3 normal = vec3(0.0);
	
	float heightL = snoise(vec2(waveCoords.x-1, waveCoords.y));
	float heightR = snoise(vec2(waveCoords.x+1, waveCoords.y));
	float heightD = snoise(vec2(waveCoords.x , waveCoords.y-1));
	float heightU = snoise(vec2(waveCoords.x , waveCoords.y+1));
	
	normal = vec3(heightL - heightR, 2, heightD - heightU);
	normal = normalize(normal);
	
	oNormal = normal;
}