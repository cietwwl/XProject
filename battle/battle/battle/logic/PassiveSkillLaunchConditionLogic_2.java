package com.nucleus.logic.core.modules.battle.logic;

import org.springframework.stereotype.Service;

@Service
public class PassiveSkillLaunchConditionLogic_2 extends AbstractPassiveSkillLaunchConditionLogic {

	@Override
	public AbstractPassiveSkillLaunchCondition newInstance() {
		return new PassiveSkillLaunchCondition_2();
	}

}