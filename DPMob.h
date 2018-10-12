#pragma once
#include "DPObject.h"
#include <string>
class DPMob :
	public DPObject
{
public:
	DPMob();
	virtual ~DPMob();

private:
	int m_Hp;
	int m_Mana;
	int m_AttackMeeleValue;
	int m_AttackRangedValue;
	int m_MagickaValue;
	std::string m_Name;
	char m_Level;
		
};

