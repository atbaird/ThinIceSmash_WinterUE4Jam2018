// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ThingIceSmashGameMode.h"
#include "CPP_ThinIceSmashPlayerController.h"
#include "CPP_ThinIceSmashGameInstance.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "../Camera/CPP_CameraActor.h"
#include "../HUD/CPP_GameHUD.h"

ACPP_BasePillar* ACPP_ThingIceSmashGameMode::SpawnPillar(FVector Location, FRotator rotation)
{
	if (m_PillarsToSpawn.Num() == 0)
		return nullptr;

	int ranIdx = FMath::RandRange(0, m_PillarsToSpawn.Num() - 1);
	FString contextString;

	AActor* actor = GetWorld()->SpawnActor(m_PillarsToSpawn[ranIdx], &Location, &rotation);
	ACPP_BasePillar* pillar = Cast<ACPP_BasePillar>(actor);

	return pillar;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Init
void ACPP_ThingIceSmashGameMode::BeginPlay()
{
	OnBeginPlay();
}

void ACPP_ThingIceSmashGameMode::OnBeginPlay()
{
	InitGameInstance();
	InitPlayerStart();
	InitCamera();
	ACPP_ThinIceSmashPlayerController* realController = Cast<ACPP_ThinIceSmashPlayerController>(GetWorld()->GetFirstPlayerController());

	if (realController != nullptr)
	{
		ACPP_GameHUD* hud = Cast<ACPP_GameHUD>(realController->GetHUD());
		if (hud != nullptr)
		{
			hud->OpenMainMenuWidget();
		}
		realController->SetViewTarget(m_Camera);
	}

	float startZ = m_StartZPos;
	InitPlayerStart();
	float x = 0.0f;
	float y = 0.0f;

	FRotator rotation = FRotator(0.0f, 0.0f, 0.0f);
	while (startZ >= m_SpawnZPosIfGameStart)
	{
		FVector loc = FVector();
		ACPP_BasePillar* pillar = SpawnPillar(FVector(x, y, startZ), rotation);
		m_PillarActors.Add(pillar);
		startZ -= m_DistanceBetweenEachPillar;
	}
}

void ACPP_ThingIceSmashGameMode::Tick(float DeltaTime)
{
	InitPlayerStart();
	OnTick(DeltaTime);
}

void ACPP_ThingIceSmashGameMode::OnTick(float DeltaTime)
{
	if (m_Camera != nullptr)
	{
		if (m_Character != nullptr)
		{
			m_CurrentCameraCenterPosition = m_Character->GetActorLocation();
			m_CurrentCameraRotation = m_Character->GetActorRotation();
		}
	}
	UpdatePillarPosition(DeltaTime);
}

void ACPP_ThingIceSmashGameMode::UpdatePillarPosition(float DeltaTime)
{
	if (m_Character == nullptr)
		return;
	if (!m_Character->GetIsFalling())
		return;

	float amtCanMove = m_ZSpeed * DeltaTime;
	float previousDistTravelled = m_DistanceTravelled;
	m_DistanceTravelled = m_DistanceTravelled + amtCanMove;

	if (m_ZSpeed != m_MaxZSpeed)
	{
		int32 howMuch = int32(floor(previousDistTravelled / m_AmountOfDistanceToTravelBeforeIncreaseSpeed));
		int32 newHowMuch = int32(floor(m_DistanceTravelled / m_AmountOfDistanceToTravelBeforeIncreaseSpeed));

		if (m_DistanceTravelled != 0.0f && howMuch != newHowMuch)
		{
			m_ZSpeed = m_ZSpeed + m_IntervalToIncreaseZSpeedBy;
			if (m_ZSpeed < 0.0f || m_ZSpeed >= m_MaxZSpeed)
			{
				m_ZSpeed = m_MaxZSpeed;
			}
		}
	}

	for (int idx = 0; idx < m_PillarActors.Num(); idx++)
	{
		ACPP_BasePillar* pillar = m_PillarActors[idx];
		if (pillar == nullptr)
		{
			m_PillarActors.RemoveAt(idx);
			idx--;
			continue;
		}

		FVector loc = pillar->GetActorLocation();
		float newZ = loc.Z + amtCanMove;
		pillar->SetActorLocation(FVector(loc.X, loc.Y, newZ));

		if (idx == 0)
		{
			if (newZ - m_DistanceBetweenEachPillar >= m_SpawnZPosIfGameStart)
			{
				ACPP_BasePillar* newPillar = SpawnPillar(FVector(loc.X, loc.Y, newZ - m_DistanceBetweenEachPillar), FRotator(0.0f, 0.0f, 0.0f));
				m_PillarActors.Insert(newPillar, idx);
				idx++;
				continue;
			}
		}

		if (newZ >= m_DestroyZPosIfGameStart)
		{
			pillar->Destroy();
			m_PillarActors.RemoveAt(idx);
			idx--;
		}
	}
}

void ACPP_ThingIceSmashGameMode::InitPlayerStart()
{
	if (m_PlayerStart != nullptr)
		return;

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		m_PlayerStart = Cast<APlayerStart>(actors[0]);

		if (m_PlayerStart != nullptr)
		{
			m_CurrentCameraRotation = m_PlayerStart->GetActorRotation();
			m_CurrentCameraCenterPosition = m_PlayerStart->GetActorLocation();
			m_StartZPos = m_CurrentCameraCenterPosition.Z - 80.0f;
			m_SpawnZPosIfGameStart = m_SpawnZPosIfGameStart + m_CurrentCameraCenterPosition.Z;
			m_DestroyZPosIfGameStart = m_DestroyZPosIfGameStart + m_CurrentCameraCenterPosition.Z;
		}
	}
}

void ACPP_ThingIceSmashGameMode::InitGameInstance()
{
	if (m_GameInstance != nullptr)
		return;

	m_GameInstance = Cast<UCPP_ThinIceSmashGameInstance>(GetGameInstance());
}

void ACPP_ThingIceSmashGameMode::InitCamera()
{
	if (m_Camera != nullptr)
		return;

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_CameraActor::StaticClass(), actors);

	if (actors.Num() > 0)
	{
		m_Camera = Cast<ACPP_CameraActor>(actors[0]);
	}
	else
	{
		if (m_CameraActorClass == nullptr)
			return;
		if (GetWorld() == nullptr)
			return;

		FVector location;
		FRotator rotation;
		AActor* camera = GetWorld()->SpawnActor(m_CameraActorClass, &location, &rotation);
		m_Camera = Cast<ACPP_CameraActor>(camera);
	}
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Game start
void ACPP_ThingIceSmashGameMode::StartGame()
{
	ACPP_ThinIceSmashPlayerController* realController = Cast<ACPP_ThinIceSmashPlayerController>(GetWorld()->GetFirstPlayerController());
	m_ZSpeed = m_MinZSpeed;
	if (realController != nullptr)
	{
		int32 idxOfCharacter = 0;
		m_DistanceTravelled = 0.0f;

		InitGameInstance();

		if (m_GameInstance != nullptr)
		{
			if (m_GameInstance->GetMainMenuRule() == EMainMenuRuleOnEnter::MainMenuRule_MainMenu)
			{
				m_GameInstance->SetIndexOfCharacter(idxOfCharacter);
			}
		}

		SpawnMainCharacter();
		ACPP_ThinIceSmashPlayerController* controller = Cast<ACPP_ThinIceSmashPlayerController>(GetWorld()->GetFirstPlayerController());

		ACPP_GameHUD* hud = Cast<ACPP_GameHUD>(controller->GetHUD());
		if (hud != nullptr)
		{
			hud->OpenGameHUDWidget();
		}

		if (m_Character != nullptr)
		{
			m_Character->NotifyOfStart();
		}
	}
}

void ACPP_ThingIceSmashGameMode::RestartGame()
{
	ACPP_ThinIceSmashPlayerController* realController = Cast<ACPP_ThinIceSmashPlayerController>(GetWorld()->GetFirstPlayerController());

	if (realController != nullptr)
	{
		m_DistanceTravelled = 0.0f;
		InitGameInstance();
		if (m_GameInstance != nullptr)
		{
			m_GameInstance->SetRuleForMainMenu(EMainMenuRuleOnEnter::MainMenuRule_Restarting);
		}
	}
}

void ACPP_ThingIceSmashGameMode::ReturnToMainMenu()
{
	ACPP_ThinIceSmashPlayerController* realController = Cast<ACPP_ThinIceSmashPlayerController>(GetWorld()->GetFirstPlayerController());

	if (realController != nullptr)
	{

		InitGameInstance();
		if (m_GameInstance != nullptr)
		{
			m_GameInstance->SetRuleForMainMenu(EMainMenuRuleOnEnter::MainMenuRule_MainMenu);
		}
	}
}

void ACPP_ThingIceSmashGameMode::SpawnMainCharacter()
{
	if (m_Character != nullptr || m_ClassOfMainCharacter == nullptr)
	{
		return;
	}
	InitPlayerStart();

	FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f);
	FRotator spawnRotation = FRotator(0.0f, 0.0f, 0.0f);
	if (m_PlayerStart != nullptr)
	{
		spawnLocation = m_PlayerStart->GetActorLocation();
		spawnRotation = m_PlayerStart->GetActorRotation();
	}

	FActorSpawnParameters spawnParams;
	UWorld* world = GetWorld();

	AActor* player = GetWorld()->SpawnActor(m_ClassOfMainCharacter, &spawnLocation, &spawnRotation, spawnParams);
	ACPP_BasePlayerCharacter* playerChar = Cast<ACPP_BasePlayerCharacter>(player);
	if (playerChar != nullptr)
	{
		APlayerController* controller = world->GetFirstPlayerController();
		m_Character = playerChar;
		InitCamera();
		if (controller != nullptr)
		{
			controller->Possess(playerChar);
			controller->SetViewTarget(m_Camera);
		}
		if (m_Camera != nullptr)
		{
			m_Camera->SetCharacterToFollow(m_Character);
		}
	}

}

void ACPP_ThingIceSmashGameMode::IncrementAmountOfIceShattered()
{
	m_AmountOfIceShattered++;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
//--------------------------------------------------------------------
//Getters

FVector ACPP_ThingIceSmashGameMode::GetCameraCenterPosition()
{
	return m_CurrentCameraCenterPosition;
}

FRotator ACPP_ThingIceSmashGameMode::GetCameraRotation()
{
	return m_CurrentCameraRotation;
}


float ACPP_ThingIceSmashGameMode::GetDistanceTravelled()
{
	return m_DistanceTravelled;
}


int32 ACPP_ThingIceSmashGameMode::GetAmountOfIceShattered()
{
	return m_AmountOfIceShattered;
}