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
	//rgbf shootRay(scene&, Ray, int);
	rgbf shootRay(scene&, Ray&, int, 
			const bool& is_light 	=false, 
			Ray oldRay 	=Ray(vector3(0, 0, 0), vector3(0, 0, 0)), 
			light* lig 	=new light(vector3(0, 0, 0), rgbf(0, 0, 0), 0),
		  scene_object* oldobj 	=NULL); //Default values for non-shadows


	RayTracer(int depth)
	{
		max_depth = depth;
	}
};

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
	
	//return rgbf(0, 0, 0.5); //using altcol here
	return (obj->ambient_colour + (obj->altcol(pos) * diff) + (lig->colour * spec)) * (1-obj->transparency);
}

rgbf RayTracer::shootRay(scene& scene1, Ray& ray, int depth, const bool& is_light, Ray oldRay, light* lig, scene_object* oldobj)
{
	//Initialise pixel colour
	rgbf colour = rgbf(0, 0, 0); //Background colour
	
	////Intersect all objects
	
	float t = 0; //ray parameter
	scene_object* objp;   //pointer to object of intersection

	for (int i = 0; i < scene1.objects_num; i++)
	{
		if (scene1.objects[i] == oldobj) continue; //Self intersection fix
		
		float temp = scene1.objects[i]->intersect(ray); //intersection with object

		if ((temp < t || t == 0) && temp > 0) //if (temp is shorter than t or t is currently 0) and temp is non-zero
		{
			t = temp;
			objp = scene1.objects[i];
		}
	}

	////
	//if (is_light) std::cout << t << std::endl;
	////
	//Lighting bug is due to ray over extending and colliding with objects in back ground rather than just light.

			

	if (is_light)
	{
		//std::cout << (lig->position - ray.position).norm() << '\t' << t * ray.direction.norm() <<std::endl;
		//std::cout << ray.direction.norm();

		//if (oldobj != objp && objp->transparent)

		if (t == 0 
			|| t * ray.direction.norm() > (lig->position - ray.position).norm() 
			|| (oldobj != objp && objp->transparent))
		{	
			float k_d = oldobj->k_diff;
			float k_s = oldobj->k_spec;	
			float I_s = lig->intensity;
	
			vector3 L = !ray.direction;
	
			vector3 n = oldobj->surface_normal(ray.position); //here we are
			//vector3 R = n * 2 * fmax(0, L * n) - L;
			vector3 R = n * 2 * (L * n) - L;
	
			float diff = k_d * I_s * fmax(0, L * n);
			float spec = k_s * I_s * pow(fmax(0, -!oldRay.direction * R), oldobj->shininess);
	
			//return rgbf(0, 0, 0.5); //using altcol here
			return (
				oldobj->ambient_colour //ambient
				+ (oldobj->altcol(ray.position) * diff) //diffuse 
				+ (lig->colour * spec) //specular
				) * (1-oldobj->transparency) //object transperncy terms
				* (objp->transparent ? objp->transparency : 1); //Shadow transparency term
		}
		else
		{
			return oldobj->ambient_colour;
		}
	}

	//If  an intersection is found
	if (t > 0 && !is_light)
	{
		vector3 pos = ray.direction * t + ray.position;

		for (int i = 0; i < scene1.lights_num; i++)
		{	
			//Ray lightRay(pos, scene1.lights[i]->position - pos);
			//Shoot shadow ray
			
			float eps = 0; //Shadow self intersection correct
			//Was previously ommited but some objects self shadow
			Ray lightRay = Ray(pos + objp->surface_normal(pos) * eps, scene1.lights[i]->position - pos);
		

			colour += shootRay(scene1, lightRay, depth + 1, true, ray, scene1.lights[i], objp);
		}

		if (depth < max_depth)
		{
			vector3 n = objp->surface_normal(pos);

			if (objp->reflective) //Add refelective components
			{
				Ray refRay(pos, ray.direction - n * (n * ray.direction) * 2);
				colour += shootRay(scene1, refRay, depth + 1, is_light, ray, lig, objp)
					 	* objp->I_refl;
			}

			if (objp->transparent) //Add refractive components
			{
				//Old model
				float d = n * ray.direction; //Make sure that no numerical errors as d < 1
				float r = objp->refindex; //refractive index ratio
				float k = r * r * (1 - d * d);
				Ray refRay(pos,  ray.direction * r - n * (r * d + sqrt(1 - k)));
				colour += shootRay(scene1, refRay, depth + 1, is_light, ray, lig, objp) 
					* objp->I_refr;
				
				/*
				//Refraction model with material dependant ref indexes
				rgbf col(0, 0, 0); //Initialise empty colour
				float ref_indexes[3] = { 0.9, 0.8, 0.7 }; //temp sol to objp's ref indexes for rgb

				for(int i = 0; i < 3; i++)
				{
					float d = fmin(1.0, n * ray.direction); //Make sure that no numerical errors as d < 1
					float r = ref_indexes[i]; //refractive index ratio
					float k = r * r * (1 - d * d);
					Ray refRay(pos, ray.direction * r + n * (r * d + sqrt(1 - k)));
					col[i] = (shootRay(scene1, refRay, depth + 1, is_light, ray, lig, objp) 
						* objp->I_refr)[i];
				}

				colour += col; */
			}
		}
	}
	else
	{
		colour += rgbf(0.6, 0.6, 1); //Sky colour
	}

	return colour;
}
