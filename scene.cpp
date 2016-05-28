//#include "camera.cpp"
#include "scene_objects/scene_object.h"
#include <stdlib.h>
#include <vector>

typedef std::vector<scene_object*> objs_vec;
typedef std::vector<light*> ligs_vec;

class scene
{
public: //TODO Currently single object scene
	objs_vec objects;
	ligs_vec lights;
	int objects_num;
	int lights_num;

	void add_object(scene_object* obj);
	void add_light(light* lig);
	
	//TODO
	//Add remove support for objects

};

//Dynamic memory allocation - pain in the ass right here

void scene::add_light(light* lig)
{
	lights.push_back(lig);
	lights_num++;

	//*lights = (light *)malloc(lights_num * sizeof(light));
	//lights[lights_num++] = lig;
}

void scene::add_object(scene_object* obj)
{
	objects.push_back(obj);
	objects_num++;
	//*objects = (scene_object *)malloc(objects_num * sizeof(scene_object));
	//objects[objects_num++] = obj; //have objects_num increase whilst adding new object
}
