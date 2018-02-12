// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPP_ThinIceSmashGameInstance.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMainMenuRuleOnEnter : uint8
{
	MainMenuRule_MainMenu,
	MainMenuRule_Restarting
};

UCLASS()
class THINICESMASH_API UCPP_ThinIceSmashGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	int32 m_IdxOfCharacter = 0;

	UPROPERTY(BlueprintReadWrite)
		EMainMenuRuleOnEnter m_RuleForMainMenu = EMainMenuRuleOnEnter::MainMenuRule_MainMenu;
public:

	//Setters

	UFUNCTION(BlueprintCallable)
	virtual void SetIndexOfCharacter(int32 character);

	UFUNCTION(BlueprintCallable)
		virtual void SetRuleForMainMenu(EMainMenuRuleOnEnter rule);

	//Getters

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual int32 GetIndexOfCharacter();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		virtual EMainMenuRuleOnEnter GetMainMenuRule();
};
