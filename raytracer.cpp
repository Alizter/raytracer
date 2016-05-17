//This should process a block of memory
//and return the colour data on it

//Ray tracing algorithm
//For each pixel on the screen
//	shoot a ray through the pixel
//	
//	for each object in the scene
//		intersect the ray with the pixel
//	let t be the shortest ray intersection
//	shoot a ray from ray(t) in a reflective direction

#include "scene.cpp"

class RayTracer
{
public:
	int max_depth;
	rgbf shootRay(scene&, Ray, int);

	RayTracer(int depth)
	{
		max_depth = depth;
	}
};

rgbf shade(scene_object* obj, vector3 pos, vector3 dir, vector3 olddir, light* lig)
{
	float k_d = obj->k_diff;
	float k_s = obj->k_spec;	
	float I_s = lig->intensity;
	
	vector3 L = !dir;
	vector3 n = obj->surface_normal(pos);
	vector3 R = n * 2 * fmax(0, L * n) - L;
	
	float diff = k_d * I_s * fmax(0, L * n);
	float spec = k_s * I_s * pow(fmax(0, -!olddir * R), obj->shininess);
	
	return obj->ambient_colour + (obj->natrual_colour * diff) ;//+ (lig->colour * spec);
}

rgbf pixelshade(scene& scene1, Ray ray, float t, int index)
{
	//Base colour
	rgbf c(0, 0, 0);

	vector3 pos = ray.direction * t + ray.position;

	//lighting goes here
	for (int k = 0; k < scene1.lights_num; k++)
	{
		int is_gt0 = 0;
		Ray lightRay(pos + scene1.objects[index]->surface_normal(pos) * 1E-3, scene1.lights[k]->position - pos);

		for (int i = 0; i < scene1.objects_num; i++)
		{
			is_gt0 += (int)(scene1.objects[i]->intersect(lightRay) > 0);
		}
		
		c = c + (is_gt0 ? scene1.objects[index]->ambient_colour : shade(scene1.objects[index], 
			lightRay.position, lightRay.direction, ray.direction, scene1.lights[k]));
	}

	return c;
}

rgbf RayTracer::shootRay(scene& scene1, Ray ray, int depth)
{
	float t = 0;
	int index;

	for (int i = 0; i < scene1.objects_num; i++)
	{
		float temp = scene1.objects[i]->intersect(ray);
		if (temp < t || t == 0)
			if (temp > 0) { t = temp; index = i; }

		//if (t > 0 && (temp == 0 || t < temp)) { t = temp; index = i; } 
	}

	//std::cout << t << std::endl;
	
	if (t == 0)
	{
		//Infinite ray
		//return rgbf(0.529,0.808, 0.922);
		return rgbf(0, 0, 0); //returns black
	}

	//if (depth < max_depth && scene1.objects[index]->reflective)
	//{
		//Reflect ray
	//	vector3 pos = ray.direction * t + ray.position;
	//	vector3 n = scene1.objects[index]->surface_normal(pos);
	//	vector3 dir = ray.direction - n * (n * ray.direction);
	//	Ray newRay = Ray(pos+n*1E-6, dir);
	//	
	//	return pixelshade(scene1, ray, t, index) + shootRay(scene1, newRay, depth + 1); //Work out reflection
//  //May have self intersection here offset maybe necessery
	//}
	//else
	//{
	rgbf c;
	if (scene1.objects[index]->transparent && depth < max_depth)
	{
		//Snells law
		vector3 pos = ray.direction * t + ray.position;
		vector3 n = scene1.objects[index]->surface_normal(pos);
		
		float d = - n * ray.direction;
		float r = 0.9; //refractive index;
		
		float k = r*r*(1-d*d);

		Ray newRay(pos - n * 1E-6, ray.direction * r - n * (r*d + sqrt(1-k)));
		c = shootRay(scene1, newRay, depth + 1);
	}
	else
	{


		//rgbf c  = scene1.objects[index]->natrual_colour;
		c  = pixelshade(scene1, ray, t, index);
		//vector3 p = !(ray.position + ray.direction * t);
		//rgbf c = rgbf(p.x, p.y, p.z);
	}

	return c;
	//}
}

rgbf Trace(scene& sce, Ray ray, int d)
{
	return rgbf(0, 0, 0);
}



