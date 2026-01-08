#include "../include/ray.h"
#include "../include/canvas.h"

int main(){

	// Scene setup 
	//============================================================================================
	
	// Objects

	int sphere_count = 2;
	Sphere *sp = (Sphere*)malloc(sphere_count * sizeof(Sphere));
	
	//diffuse sphere
	Vec4 sp1_org = {10.0, 10.0, 10.0, 0.0}; float radius_sp1 = 5.0f; Vec3 sp1_color = {255, 123, 234}; 
	Material mat1 = {sp1_color, 0.1, 0.2, 0.3, 0.4};
	sp[0] = {sp1_org, radius_sp1, mat1};
	
	//specular sphere
	Vec4 sp2_org = {}; float radius_sp2 = 9.0f; Vec3 sp2_color = {45, 200, 7};
	Material mat2 = {sp2_color, 0.8, 0.4, 0.1, 0.2};
	sp[1] = {sp2_org, radius_sp2, mat2};

	//Lights, Camera
	Camera cam; cam.origin = {0.0, 0.0, 0.0, 0.0};
	int light_count = 1;
	Light l = {{10.0f, 0.0f, 20.0f, 0.0f}, {200, 200, 200}};  	

	//Action
	SceneConfig scene = {0, nullptr, sphere_count, sp, cam, light_count, lights};
	

}