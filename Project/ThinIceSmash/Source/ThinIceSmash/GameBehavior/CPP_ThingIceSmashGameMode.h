// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../PlayerCharacters/CPP_BasePlayerCharacter.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "../Pillars/CPP_BasePillar.h"
#include "CPP_ThingIceSmashGameMode.generated.h"

/**
 * 
 */

class UCPP_ThinIceSmashGameInstance;
class ACPP_CameraActor;
class APlayerStart;

USTRUCT(BlueprintType)
struct FSTRUCT_TableAndHeightAtWhichToUse : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadwrite, EditAnywhere)
		float m_DistanceFallen;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UDataTable* m_PillarMeshes;

};

UCLASS()
class THINICESMASH_API ACPP_ThingIceSmashGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	//Variables

	//-------------------------------------------------
	//Subclasses

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<ACPP_BasePlayerCharacter> m_ClassOfMainCharacter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<ACPP_CameraActor> m_CameraActorClass;

	UPROPERTY(BlueprintReadWrite)
		APlayerStart* m_PlayerStart = nullptr;

	UPROPERTY(BlueprintReadWrite)
	ACPP_BasePlayerCharacter* m_Character = nullptr;

	UPROPERTY(BlueprintReadWrite) 
		ACPP_CameraActor* m_Camera = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UCPP_ThinIceSmashGameInstance* m_GameInstance = nullptr;

	UPROPERTY(BlueprintReadWrite)
		FVector m_CurrentCameraCenterPosition = FVector(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite)
		FRotator m_CurrentCameraRotation = FRotator(0.0f, 0.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite)
		float m_DistanceTravelled = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_DistanceBetweenEachPillar = 4000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_AmountOfDistanceToTravelBeforeIncreaseSpeed = 5000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_StartZPos = 20.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_SpawnZPosIfGameStart = -8000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_DestroyZPosIfGameStart = 10000.0f;

	//-------------------------------------------------
	//Speed

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_MinZSpeed = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_MaxZSpeed = 10000.0f;

	UPROPERTY(BlueprintReadWrite)
		float m_ZSpeed = 1000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_IntervalToIncreaseZSpeedBy = 1000.0f;

	UPROPERTY(BlueprintReadWrite)
		float m_DistanceForNextSet = 0.0f;

	UPROPERTY(BlueprintReadWrite)
		int32 m_AmountOfIceShattered = 0;

	UPROPERTY(BlueprintReadWrite)
	bool m_IsThereANextSet = false;

	//-------------------------------------------------
	//Pillars

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<ACPP_BasePillar>> m_PillarsToSpawn;

	UPROPERTY(BlueprintReadWrite)
		TArray<ACPP_BasePillar*> m_PillarActors;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual ACPP_BasePillar* SpawnPillar(FVector Location, FRotator rotation);

	//Init

	UFUNCTION(BlueprintCallable)
	virtual void OnBeginPlay();

	virtual void Tick(float DeltaTime) override;

	virtual void UpdatePillarPosition(float DeltaTime);

	UFUNCTION(BlueprintCallable)
		virtual void OnTick(float DeltaTime);
	
	UFUNCTION(BlueprintCallable)
		virtual void InitPlayerStart();

	UFUNCTION(BlueprintCallable)
	virtual void InitGameInstance();

	UFUNCTION(BlueprintCallable)
		virtual void InitCamera();

public:
	//Game start

	UFUNCTION(BlueprintCallable)
		virtual void StartGame();

	UFUNCTION(BlueprintCallable)
		virtual void RestartGame();

	UFUNCTION(BlueprintCallable)
		virtual void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable)
		virtual void SpawnMainCharacter();

	UFUNCTION(BlueprintCallable)
		virtual void IncrementAmountOfIceShattered();


	//Getters

	FVector GetCameraCenterPosition();

	FRotator GetCameraRotation();


	UFUNCTION(BlueprintCallable)
		float GetDistanceTravelled();

	UFUNCTION(BlueprintCallable)
		int32 GetAmountOfIceShattered();
};
