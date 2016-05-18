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
#include <typeinfo>

class RayTracer
{
public:
	int max_depth;
	//rgbf shootRay(scene&, Ray, int);
	rgbf shootRay(scene&, Ray, int, 
			bool is_light 	=false, 
			Ray oldRay 	=Ray(vector3(0, 0, 0), vector3(0, 0, 0)), 
			light* lig 	=new light(vector3(0, 0, 0), rgbf(0, 0, 0), 0),
		  scene_object* oldobj 	=NULL); //Default values for non-shadows


	RayTracer(int depth)
	{
		max_depth = depth;
	}
};

rgbf cubecolour(vector3& pos)
{
	
}

rgbf shade(scene_object* obj, vector3& pos, vector3& dir, vector3& olddir, light* lig)
{
	float k_d = obj->k_diff;
	float k_s = obj->k_spec;	
	float I_s = lig->intensity;
	
	vector3 L = !dir;
	
	vector3 n = obj->surface_normal(pos); //here we are
	vector3 R = n * 2 * fmax(0, L * n) - L;
	
	float diff = k_d * I_s * fmax(0, L * n);
	float spec = k_s * I_s * pow(fmax(0, -!olddir * R), obj->shininess);
	
	//return rgbf(0, 0, 0.5);
	return obj->ambient_colour + (obj->altcol(pos) * diff) ;//+ (lig->colour * spec);
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

//Recursive function (merging old shootRay and shadpixel)
rgbf RayTracer::shootRay(scene& scene1, Ray ray, int depth, bool is_light, Ray oldRay, light* lig, scene_object* oldobj)
{
	//if is_light then shootRay is a shadow ray

	//Workout closest intersection and object

	float t = 0; //ray parameter
	scene_object* objp;   //pointer to object of intersection

	for (int i = 0; i < scene1.objects_num; i++)
	{
		//Work out t for given object
		//This part can be optimised to search certain objects in order
		//to save calling intersect(ray) for useless objects
		float temp = scene1.objects[i]->intersect(ray); //intersection with object

		if ((temp < t || t == 0) && temp > 0) //if (temp is shorter than t or t is currently 0) and temp is non-zero
		{
			t = temp;
			objp = scene1.objects[i];
		}
	}

	if (t == 0) //No hit
	{
		if (is_light) //No hit with light ray.
		{	
			//No objects in way of sending light to source
			//Illumination model			

			//**
			// 19:07 18 May 2016 shade is giving segmentation fault
			//**
			
			return shade(oldobj, ray.position, ray.direction, oldRay.direction, lig);
			//return rgbf(0.5, 0, 0.5);
		}
		else
		{
			return rgbf(0, 0, 0); //Returns black (background colour)
		}
	}
	else
	{
	
		//case where there is a hit but is also a light ray
		//for now shade as shadow but in future advanced reflections
	
		if (is_light)
		{
			return objp->ambient_colour;
		}

		//Depending on objp properties we will reflect refract and cast shadow rays

		rgbf colour; // colour of pixel to return


		//point of intersecion
		vector3 pos = ray.direction * t + ray.position;


		//Go through every light in the scene and
		//shoot a shadow ray.
		//This should be optimised for lights in significant
		//proximity
		for (int i = 0; i < scene1.lights_num; i++)
		{	
			//Light ray with correction factor to avoid rounding bugs
			Ray lightRay(pos + objp->surface_normal(pos) * 1E-6, scene1.lights[i]->position - pos);
			//Add to pixel colour according to illumination model
			colour += shootRay(scene1, lightRay, depth, true, ray, scene1.lights[i], objp);
		}

		return colour; //Return pixel colour
	}
}

/*rgbf RayTracer::shootRay(scene& scene1, Ray ray, int depth)
{
	float t = 0;
	int index;

	for (int i = 0; i < scene1.objects_num; i++)
	{
		float temp = scene1.objects[i]->intersect(ray);
		if (temp < t || t == 0)
			if (temp > 0) { t = temp; index = i; }

	}
	if (t == 0)
	{
		return rgbf(0, 0, 0); //returns black
	}
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
		c  = pixelshade(scene1, ray, t, index);
	}

	return c;
	
}*/

rgbf Trace(scene& sce, Ray ray, int d)
{
	return rgbf(0, 0, 0);
}



