#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D sceneTexture;
uniform sampler2D brightnessTexture;
uniform float exposure;

const float A = 0.15;
const float B = 0.50;
const float C = 0.10;
const float D = 0.20;
const float E = 0.02;
const float F = 0.30;
const float W = 11.2;
const vec3 GAMMA_CONSTANT = vec3(1.0f / 2.2);

const float CxB = 0.05;
const float DxE = 0.004;
const float DxF = 0.06;
const float EdF = 0.066;
const float toneMap = 0.7257960451;
const float WHITE_SCALE = 1.0f / 0.7257960451;
//const vec3 Uncharted2TonemapW = vec3(0.7257960451); // vec3(P2TM(W));

float P2TM(float x)
{
	// Original Formula: ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
	return (((x * A * x) + (x * CxB) + DxE) / ((x * A * x) + (x * B) + DxF)) - EdF;
}

vec3 Uncharted2Tonemap(vec3 value)
{
	return vec3(P2TM(value.r), P2TM(value.g), P2TM(value.b));
}

void main()
{
	vec3 hdrColor = texture(sceneTexture, TexCoords).rgb;
	//vec3 bloomColor = texture(brightnessTexture, TexCoords).rgb;
	//hdrColor += bloomColor; // additive blending

    vec3 curr = Uncharted2Tonemap(exposure * hdrColor);
    vec3 toneMappedColor = curr * WHITE_SCALE;

	//Gamma correction
	vec3 correctedColor = pow(toneMappedColor, GAMMA_CONSTANT);
	FragColor = vec4(correctedColor, 1.0f);
}
