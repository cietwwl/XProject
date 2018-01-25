﻿#include "DropItemMgr.h"

LUNAR_IMPLEMENT_CLASS(DropItemMgr)
{
	LUNAR_DECLARE_METHOD(DropItemMgr, CreateDropItem),
	LUNAR_DECLARE_METHOD(DropItemMgr, GetDropItem),
	{0, 0}
};


DropItemMgr::DropItemMgr()
{
}

DropItem* DropItemMgr::CreateDropItem(const GAME_OBJID& oID, int nConfID, const char* psName, int nAliveTime, int nCamp)
{
	DropItem* poDropItem = GetDropItemByID(oID);
	if (poDropItem != NULL)
	{
		XLog(LEVEL_ERROR, "CreateDropItem: %lld exist\n", oID.llID);
		return NULL;
	}
	poDropItem = XNEW(DropItem);
	poDropItem->Init(oID, nConfID, psName, nAliveTime, nCamp);
	m_oDropItemMap[oID.llID] = poDropItem;
	return poDropItem;
}

DropItem* DropItemMgr::GetDropItemByID(const GAME_OBJID& oID)
{
	DropItemIter iter = m_oDropItemMap.find(oID.llID);
	if (iter != m_oDropItemMap.end())
	{
		return iter->second;
	}
	return NULL;
}

void DropItemMgr::UpdateDropItems(int64_t nNowMS)
{
	static int nLastUpdateTime = 0;
	if (nLastUpdateTime == (int)time(0))
	{
		return;
	}
	nLastUpdateTime = (int)time(0);

	DropItemIter iter = m_oDropItemMap.begin();
	DropItemIter iter_end = m_oDropItemMap.end();
	for (; iter != iter_end; )
	{
		DropItem* poDropItem = iter->second;
		if (poDropItem->IsTimeToCollected(nNowMS))
		{
			iter = m_oDropItemMap.erase(iter);
			 LuaWrapper::Instance()->FastCallLuaRef<void>("OnObjCollected", 0, "ii", poDropItem->GetID().llID, poDropItem->GetType());
			SAFE_DELETE(poDropItem);
			continue;
		}
		if (poDropItem->GetScene() != NULL)
		{
			poDropItem->Update(nNowMS);
		}
		iter++;
	}	
}




////////////////////////lua export///////////////////////
void RegClassDropItem()
{
	REG_CLASS(DropItem, false, NULL); 
	REG_CLASS(DropItemMgr, false, NULL); 
}

int DropItemMgr::CreateDropItem(lua_State* pState)
{
	int64_t nObjID = luaL_checkinteger(pState, 1);
	int nConfID = (int)luaL_checkinteger(pState, 2);
	const char* psName = luaL_checkstring(pState, 3);
	int nAliveTime  = (int)luaL_checkinteger(pState, 4);
	int nCamp = (int)luaL_checkinteger(pState, 5);
	DropItem* poDropItem = CreateDropItem(nObjID, nConfID, psName, nAliveTime, nCamp);
	if (poDropItem != NULL)
	{
		Lunar<DropItem>::push(pState, poDropItem);
		return 1;
	}
	return 0;
}

int DropItemMgr::GetDropItem(lua_State* pState)
{
	int64_t nObjID = luaL_checkinteger(pState, 1);
	DropItem* poDropItem = GetDropItemByID(nObjID);
	if (poDropItem != NULL)
	{
		Lunar<DropItem>::push(pState, poDropItem);
		return 1;
	}
	return 0;
}