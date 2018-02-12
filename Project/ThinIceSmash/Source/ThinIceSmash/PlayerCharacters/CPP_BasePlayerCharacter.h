// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../FunctionLibraries/CPP_PlayerCharacterFunctionLib.h"
#include "Runtime/Engine/Classes/Sound/SoundCue.h"
#include "CPP_BasePlayerCharacter.generated.h"

class ACPP_ThingIceSmashGameMode;
class UCPP_ThinIceSmashGameInstance;

UCLASS()
class THINICESMASH_API ACPP_BasePlayerCharacter : public ACharacter, public IPlayerCharacterInput
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_BasePlayerCharacter();

protected:
	UPROPERTY(BlueprintReadWrite)
		FRotator m_FinalRotation;

	UPROPERTY(BlueprintReadwrite)
	ACPP_ThingIceSmashGameMode* m_GameMode;

	UPROPERTY(BlueprintReadWrite)
	UCPP_ThinIceSmashGameInstance* m_GameInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USoundCue* m_CrashSoundCue = nullptr;

	UPROPERTY(BlueprintReadWrite)
		float m_HeightToMaintain = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		float m_RightLeftAxis = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		float m_ForwardBackAxis = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		float m_RotationOutFromPillar = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_RotationSpeed = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_BaseDiveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_AdditionalDiveSpeedAllowed;

	UPROPERTY(BlueprintReadWrite)
		float m_CurrentAdditionalDiveSpeedAllowed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_DistanceOutFromCenterOfPillar = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_MaxDistanceOutFromCenterOfPillar = 1200.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_MovementSpeedToGetOutFromCenterOfPillar = 1200.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_PointAtWhichStartFalling = 1000.0f;

	UPROPERTY(BlueprintReadWrite)
		float m_pitch = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		bool m_GameStarted = false;

	UPROPERTY(BlueprintReadWrite)
		bool m_JumpedOutFromPillar = false;

	UPROPERTY(BlueprintReadWrite)
		bool m_Falling = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitGameMode();

	void InitGameInstance();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateRotation(float DeltaTime);

	void UpdateDistanceOutFromPillar(float DeltaTime);

	void NotifyOfStart();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void KillPlayer();
	
	//Setters

	UFUNCTION(BlueprintCallable)
	void SetHeightToMaintain(float height);

	//Getters

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetHeightToMaintain();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FRotator GetFinalRotation();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool GetIsFalling();

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool ShouldBeRunning();

	//-----------------------------------------------------------------------------
	//IPlayerCharacterInput
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Forward(float axis);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Right(float axis);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PausePressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PauseReleased();

};
