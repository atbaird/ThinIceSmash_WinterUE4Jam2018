// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "../GameBehavior/CPP_ThingIceSmashGameMode.h"
#include "CPP_CameraActor.generated.h"

/**
 * 
 */

class ACPP_BasePlayerCharacter;

UCLASS()
class THINICESMASH_API ACPP_CameraActor : public ACameraActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ACPP_BasePlayerCharacter* m_CharacterToFollow = nullptr;

	UPROPERTY(BlueprintReadWrite)
	ACPP_ThingIceSmashGameMode* m_GameMode = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_DistanceFromCharacterForwardToMaintain = -500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_DistanceFromCharacterUpToMaintain = 100.0f;

public:
	
protected:
	//Init

	void InitGameMode();

	virtual void Tick(float DeltaTime) override;
public:
	UFUNCTION(BlueprintCallable)
		virtual void SetCharacterToFollow(ACPP_BasePlayerCharacter* character);
	
};
