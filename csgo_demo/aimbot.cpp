#include "aimbot.h"

void CalAngle(vec3 FOV, vec3 headpos, vec2& CalcLocalAngle, vec2 calLocalAngleDiff)
{
	vec2 local_angle;
	local_angle.y = mem.readmemory<float>(offsets.clientbase + offsets.m_fViewAngle + 0x0);
	local_angle.x = mem.readmemory<float>(offsets.clientbase + offsets.m_fViewAngle + 0x4);

	if (headpos.x >= FOV.x && headpos.y >= FOV.y) {
		CalcLocalAngle.x = (float)((double)atan2(headpos.y - FOV.y, headpos.x - FOV.x)* 180/3.1415);

	}else if (headpos.x <= FOV.x && headpos.y >= FOV.y) 
	{
		CalcLocalAngle.x = 180 - (float)((double)atan2(headpos.y - FOV.y, FOV.x - headpos.x ) * 180 / 3.1415);
	}
	else if (headpos.x <= FOV.x && headpos.y <= FOV.y)
	{
		CalcLocalAngle.x = - 180 + (float)((double)atan2(FOV.y - headpos.y , FOV.x - headpos.x  ) * 180 / 3.1415);
	}
	else if (headpos.x >= FOV.x && headpos.y <= FOV.y)
	{
		CalcLocalAngle.x = -(float)((double)atan2(FOV.y - headpos.y, FOV.x - headpos.x) * 180 / 3.1415);
	}
	float distance = sqrt((headpos.x - FOV.x) * (headpos.x - FOV.x) + (headpos.y - FOV.y) * (headpos.y - FOV.y));
	if (headpos.z >= FOV.z) {
		CalcLocalAngle.y = -(float)((double)atan2(headpos.z - FOV.z , distance) * 180 / 3.1415);
	}
	if (headpos.z <= FOV.z) {
		CalcLocalAngle.y = (float)((double)atan2(FOV.z - headpos.z , distance) * 180 / 3.1415);
	}

	calLocalAngleDiff.x = local_angle.x - calLocalAngleDiff.x;

	if(calLocalAngleDiff.x > 180) {
		calLocalAngleDiff.x = 360 - calLocalAngleDiff.x;
	}

	if (calLocalAngleDiff.x < 180) {
		calLocalAngleDiff.x = 360 + calLocalAngleDiff.x;
	}

	calLocalAngleDiff.y = local_angle.y - calLocalAngleDiff.y;

}
