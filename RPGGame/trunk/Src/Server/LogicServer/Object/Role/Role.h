﻿#ifndef __ROLE_H__
#define __ROLE_H__

#include "Server/LogicServer/Object/Actor.h"

class Role : public Actor
{
public:
	LUNAR_DECLARE_CLASS(Role);

public:
	Role();
	virtual ~Role();

public:
	void Init(int nObjID, int nConfID, const char* psName);

public:
	virtual void Update(int64_t nNowMS);
	virtual void OnEnterScene(Scene* poScene, int nAOIID, const Point& oPos);
	virtual void AfterEnterScene();
	virtual void OnLeaveScene();

public:
	void RoleStartRunHandler(Packet* poPakcet);
	void RoleStopRunHandler(Packet* poPacket);

private:
	DISALLOW_COPY_AND_ASSIGN(Role);


//////////////lua export////////////
};

#endif