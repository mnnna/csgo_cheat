#pragma once
#include<Windows.h>
using namespace std;

class Config {

public:
	bool health = 1;
	bool bone = 0; 
	bool distance = 0; 
	bool team = 0;
	bool triggerbot = 0;  
	bool autoaim = 0;
};
extern Config config;

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
#define BONE_NECK 12 //����

#define BONE_LEFT_SHOULDER 8 //���
#define BONE_RIGHT_SHOULDER 13 //�Ҽ�

#define BONE_LEFT_ELBOW 9 //���
#define BONE_RIGHT_ELBOW 14 //����

#define BONE_LEFT_HAND 38 //����
#define BONE_RIGHT_HAND 16 //����

#define BONE_CROSS 0

#define BONE_LEFT_KNEE 23 //��ϥ
#define BONE_RIGHT_KNEE 26 //��ϥ

#define BONE_LEFT_FOOT 30 //���
#define BONE_RIGHT_FOOT 32 //�ҽ�

#define CONFIG_FOV 20