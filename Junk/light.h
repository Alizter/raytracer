//Light source

class Light
{
public:
	vector3 position;
	rgbf colour;
	float intensity;
	Light(vector3, rgbf, float);
};

Light::Light()
{
	
}
