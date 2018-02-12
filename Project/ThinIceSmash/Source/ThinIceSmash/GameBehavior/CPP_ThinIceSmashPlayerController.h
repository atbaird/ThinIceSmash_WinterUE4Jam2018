// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPP_ThinIceSmashPlayerController.generated.h"

/**
 * 
 */

class ACPP_GameHUD;

UCLASS()
class THINICESMASH_API ACPP_ThinIceSmashPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	ACPP_GameHUD* m_MyHud = nullptr;
	float m_UIUpInput = 0.0f;
	float m_UIUPPressedSensitivity = 0.2f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool m_DisableBackwardsInput = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool m_DisableForwardsInput = false;

public:

	//-----------------------------------------------------------
	//Inits
	void InitHUD();


	virtual void SetupInputComponent() override;
	

	//-----------------------------------------------------------
	//Controls

	UFUNCTION(BlueprintCallable)
	virtual void UIConfirmPressed();

	UFUNCTION(BlueprintCallable)
	virtual void UIConfirmReleased();

	UFUNCTION(BlueprintCallable)
	virtual void GamePausedPressed();

	UFUNCTION(BlueprintCallable)
	virtual void GamePausedReleased();

	UFUNCTION(BlueprintCallable)
	virtual void GameForwardFunc(float Axis);

	UFUNCTION(BlueprintCallable)
	virtual void GameRightFunc(float Axis);

	UFUNCTION(BlueprintCallable)
	virtual void UIUpFunc(float Axis);

};
