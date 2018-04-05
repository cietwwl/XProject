package com.nucleus.logic.core.modules.battle.logic;

import com.nucleus.commons.annotation.GenIgnored;
import com.nucleus.logic.core.modules.battle.model.BattleSoldier;
import com.nucleus.logic.core.modules.battle.model.CommandContext;

/**
 * 己方存活战斗单位数量小于指定值
 * 
 * @author wgy
 *
 */
@GenIgnored
public class PassiveSkillLaunchCondition_30 extends AbstractPassiveSkillLaunchCondition {
	private int count;

	@Override
	public boolean launchable(BattleSoldier soldier, BattleSoldier target, CommandContext context, IPassiveSkill passiveSkill) {
		int called = soldier.team().aliveSoldiers().size();
		return called < count;
	}

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}

}