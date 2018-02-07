local _format = string.format
local _remove = table.remove
local _assert = assert

--GM指令
function CGMMgr:Ctor()
end

--收到GM指令
function CGMMgr:OnGMCmdReq(nSession, sCmd)
	local tArgs = string.Split(sCmd, ' ')
	local sCmdName = _assert(tArgs[1])

	local nCharID, sCharName, sAccount = 0, "", ""
	local sInfo = _format("执行指令:%s [charid:%d,charname:%s,account:%s]", sCmd, nCharID, sCharName, sAccount)
	LuaTrace(sInfo)

	local oFunc = _assert(CGMMgr[sCmdName], "找不到指令:["..sCmdName.."]")
	_remove(tArgs, 1)
	oFunc(self, nSession, tArgs)
end

-----------------指令列表-----------------

--重载脚本
CGMMgr["reload"] = function(self, nSession, tArgs)
	if #tArgs == 0 then
		local bRes = gfReloadAll()
		LuaTrace("重载所有脚本 "..(bRes and "成功!" or "失败!"))

	elseif #tArgs == 1 then
		local sFileName = tArgs[1]
		local bRes = gfReloadScript(sFileName, "LogServer")
		LuaTrace("重载脚本 '"..sFileName.."' ".. (bRes and "成功!" or "失败!"))

	else
		_assert(false, "reload 参数错误")
	end
end


goGMMgr = goGMMgr or CGMMgr:new()