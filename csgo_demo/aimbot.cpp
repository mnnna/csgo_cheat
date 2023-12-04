#include "aimbot.h"


void AimBot()
{
	vec3 Local_FOV, entitypos3;
	vec2 calLocalAngle, calLocalAngleDiff;
	vec2 targetAngle;

	int tmpTargetAngleSUM = CONFIG_FOV, target_health = 0;
	DWORD64 target = 0x0;


	DWORD64 localplayer = mem.readmemory<DWORD64>(offsets.clientbase + offsets.deLocalPlayer);
	DWORD localteam = mem.readmemory<DWORD64>(localplayer + offsets.m_iTeamNum);


	if (localplayer) {
		mem.readbone(localplayer, BONE_HEAD, Local_FOV);

		for (int i = 0; i < 32; i++) {
			DWORD64 entity = mem.readmemory<DWORD64>(offsets.clientbase + offsets.dwEntityList + i * 0x8);

			if (localplayer == entity) { continue; }
			if (entity == 0) { continue; }

			DWORD teamid = mem.readmemory<BYTE>(entity + offsets.m_iTeamNum);
			if (config.team || (teamid != 2 && teamid != 3)) { continue; };
			if (teamid != localteam) {

				DWORD entityHealth = mem.readmemory<DWORD>(entity + offsets.mHealth);
				if (0 < entityHealth && entityHealth <= 100) {
					mem.readbone(entity, BONE_HEAD, entitypos3);
					CalAngle(Local_FOV, entitypos3, calLocalAngle, calLocalAngleDiff);
					if( fabs(calLocalAngleDiff.x) <= CONFIG_FOV/2 && fabs(calLocalAngleDiff.y) <= CONFIG_FOV / 2 ){
						int tmpAngleSum = fabs(calLocalAngleDiff.x) + fabs(calLocalAngleDiff.y);
						if (tmpAngleSum < tmpTargetAngleSUM  ) {
							tmpTargetAngleSUM = tmpAngleSum;
							target = entity;
							targetAngle = calLocalAngle;
							target_health = entityHealth;

						}
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_LBUTTON) < 0 && localplayer != 0) {
			if (target != 0 && target_health > 0 && target_health <= 100 ) {
				mem.writememory(offsets.clientbase + offsets.m_fViewAngle, targetAngle.y);
				mem.writememory(offsets.clientbase + offsets.m_fViewAngle, targetAngle.x);
			}
		}
	}
}

void CalAngle(vec3 FOV, vec3 headpos, vec2& CalcLocalAngle, vec2& calLocalAngleDiff)
{
	vec2 local_angle;
	local_angle.y = mem.readmemory<float>(offsets.clientbase + offsets.m_fViewAngle + 0x0);
	local_angle.x = mem.readmemory<float>(offsets.clientbase + offsets.m_fViewAngle + 0x4);

	if (headpos.x >= FOV.x && headpos.y >= FOV.y) //第一象限
	{
		CalcLocalAngle.x = (float)((double)atan2(headpos.y - FOV.y, headpos.x - FOV.x) * 180 / 3.1415); //弧度
	}
	if (headpos.x <= FOV.x && headpos.y >= FOV.y) //第二象限
	{
		CalcLocalAngle.x = 180 - (float)((double)atan2(headpos.y - FOV.y, FOV.x - headpos.x) * 180 / 3.1415); //弧度
	}
	if (headpos.x <= FOV.x && headpos.y <= FOV.y) //第三象限
	{
		CalcLocalAngle.x = -180 + (float)((double)atan2(FOV.y - headpos.y, FOV.x - headpos.x) * 180 / 3.1415); //弧度
	}
	if (headpos.x >= FOV.x && headpos.y <= FOV.y) //第四象限
	{
		CalcLocalAngle.x = -(float)((double)atan2(FOV.y - headpos.y, headpos.x - FOV.x) * 180 / 3.1415); //弧度
	}
	float 平面直线距离 = sqrt((headpos.x - FOV.x) * (headpos.x - FOV.x) + (headpos.y - FOV.y) * (headpos.y - FOV.y));
	//高低朝向
	if (headpos.z >= FOV.z) //上方
	{
		CalcLocalAngle.y = -(float)((double)atan2(headpos.z - FOV.z, 平面直线距离) * 180 / 3.1415); //弧度
	}
	if (headpos.z <= FOV.z) //下方
	{
		CalcLocalAngle.y = (float)((double)atan2(FOV.z - headpos.z, 平面直线距离) * 180 / 3.1415); //弧度
	}
	//计算水平朝向角度差 
	calLocalAngleDiff.x = local_angle.x - CalcLocalAngle.x;
	if (calLocalAngleDiff.x > 180) {
		calLocalAngleDiff.x -= 360;
	}
	if (calLocalAngleDiff.x < -180) {
		calLocalAngleDiff.x += 360;
	}
	//高低朝向角度差
	calLocalAngleDiff.y = CalcLocalAngle.y - local_angle.y;

}
