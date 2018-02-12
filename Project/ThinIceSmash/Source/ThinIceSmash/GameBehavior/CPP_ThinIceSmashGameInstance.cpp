// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ThinIceSmashGameInstance.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Setters
void UCPP_ThinIceSmashGameInstance::SetIndexOfCharacter(int32 character)
{
	m_IdxOfCharacter = character;
}

void UCPP_ThinIceSmashGameInstance::SetRuleForMainMenu(EMainMenuRuleOnEnter rule)
{
	m_RuleForMainMenu = rule;
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Getters
int32 UCPP_ThinIceSmashGameInstance::GetIndexOfCharacter()
{
	return m_IdxOfCharacter;
}

EMainMenuRuleOnEnter UCPP_ThinIceSmashGameInstance::GetMainMenuRule()
{
	return m_RuleForMainMenu;
}