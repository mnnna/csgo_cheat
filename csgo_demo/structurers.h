#pragma once
#include<Windows.h>
using namespace std;

struct vec3 {
	float x;
	float y;
	float z;
};

struct vec2 {
	float x;
	float y;
};

struct vec4 {
	float x;
	float y;
	float z;
	float w;
};

#define BONE_HEAD 6
#define BONE_NECK 12 //²±×Ó

#define BONE_LEFT_SHOULDER 8 //×ó¼ç
#define BONE_RIGHT_SHOULDER 13 //ÓÒ¼ç

#define BONE_LEFT_ELBOW 9 //×ó¼ç
#define BONE_RIGHT_ELBOW 14 //ÓÒÖâ

#define BONE_LEFT_HAND 38 //×óÊÖ
#define BONE_RIGHT_HAND 16 //ÓÒÊÖ

#define BONE_CROSS 0

#define BONE_LEFT_KNEE 23 //×óÏ¥
#define BONE_RIGHT_KNEE 26 //ÓÒÏ¥

#define BONE_LEFT_FOOT 30 //×ó½Å
#define BONE_RIGHT_FOOT 32 //ÓÒ½Å