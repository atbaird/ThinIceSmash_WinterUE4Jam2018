// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BasePlayerCharacter.h"
#include "../GameBehavior/CPP_ThingIceSmashGameMode.h"
#include "../GameBehavior/CPP_ThinIceSmashGameInstance.h"
#include "../GameBehavior/CPP_ThinIceSmashGameSession.h"
#include "../GameBehavior/CPP_ThinIceSmashGameState.h"
#include "../GameBehavior/CPP_ThinIceSmashPlayerController.h"
#include "../GameBehavior/CPP_ThinIceSmashPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../HUD/CPP_GameHUD.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>


// Sets default values
ACPP_BasePlayerCharacter::ACPP_BasePlayerCharacter()
	: Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UCharacterMovementComponent* comp = GetCharacterMovement();
	if (comp != nullptr)
	{
		comp->GravityScale = 0.0f;
	}

}

// Called when the game starts or when spawned
void ACPP_BasePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	UCharacterMovementComponent* comp = GetCharacterMovement();
	if (comp != nullptr)
	{
		comp->GravityScale = 0.0f;
	}
	InitGameMode();
	InitGameInstance();

	m_HeightToMaintain = GetActorLocation().Z;
}

void ACPP_BasePlayerCharacter::InitGameMode()
{
	if (m_GameMode == nullptr)
	{
		m_GameMode = Cast<ACPP_ThingIceSmashGameMode>(GetWorld()->GetAuthGameMode());
	}
}

void ACPP_BasePlayerCharacter::InitGameInstance()
{
	if (m_GameInstance == nullptr)
	{
		m_GameInstance = Cast<UCPP_ThinIceSmashGameInstance>(GetGameInstance());
	}
}

// Called every frame
void ACPP_BasePlayerCharacter::Tick(float DeltaTime)
{
	if (m_GameStarted && !m_JumpedOutFromPillar)
	{
		UpdateDistanceOutFromPillar(DeltaTime);
	}

	UpdateRotation(DeltaTime);
	FRotator rotation = FRotator(0.0f, m_RotationOutFromPillar, 0.0f);
	FVector dir = FRotationMatrix(rotation).GetScaledAxis(EAxis::X);
	dir.Normalize();
	FVector location = (dir * m_DistanceOutFromCenterOfPillar)
		+ FVector(0.0f, 0.0f, m_HeightToMaintain);
	m_FinalRotation = FRotator(m_pitch, m_RotationOutFromPillar, 0.0f);
	SetActorLocationAndRotation(location, m_FinalRotation);



	Super::Tick(DeltaTime);
}


void ACPP_BasePlayerCharacter::UpdateRotation(float DeltaTime)
{
	m_RotationOutFromPillar += DeltaTime * m_RotationSpeed * m_RightLeftAxis;
	while(m_RotationOutFromPillar >= 360.0f)
	{
		m_RotationOutFromPillar -= 360.0f;
	}
	while(m_RotationOutFromPillar < 0.0f)
	{
		m_RotationOutFromPillar += 360.0f;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(m_RotationOutFromPillar));
}

void ACPP_BasePlayerCharacter::UpdateDistanceOutFromPillar(float DeltaTime)
{
	if (m_DistanceOutFromCenterOfPillar >= m_MaxDistanceOutFromCenterOfPillar)
	{
		if (!m_JumpedOutFromPillar)
			m_JumpedOutFromPillar = true;
		m_pitch = -90.0f;
		m_Falling = true;
		return;
	}

	m_DistanceOutFromCenterOfPillar += DeltaTime * m_MovementSpeedToGetOutFromCenterOfPillar;
	float distanceForPitchTest = m_DistanceOutFromCenterOfPillar - m_PointAtWhichStartFalling;
	float distanceFromStartFallingToMax = m_MaxDistanceOutFromCenterOfPillar - m_PointAtWhichStartFalling;
	if (distanceForPitchTest >= 0.0f && distanceForPitchTest < distanceFromStartFallingToMax
		&& distanceFromStartFallingToMax != 0.0f)
	{
		m_pitch = (distanceForPitchTest / distanceFromStartFallingToMax) * -90.0f;
		m_Falling = true;
	}

	if (m_DistanceOutFromCenterOfPillar >= m_MaxDistanceOutFromCenterOfPillar)
	{
		m_DistanceOutFromCenterOfPillar = m_MaxDistanceOutFromCenterOfPillar;
		m_JumpedOutFromPillar = true;
		m_pitch = -90.0f;
		m_Falling = true;
	}
}

void ACPP_BasePlayerCharacter::NotifyOfStart()
{
	m_GameStarted = true;
}

// Called to bind functionality to input
void ACPP_BasePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACPP_BasePlayerCharacter::KillPlayer()
{
	if (!m_Falling)
		return;
	m_RightLeftAxis = 0.0f;
	ACPP_ThinIceSmashPlayerController* controller = Cast<ACPP_ThinIceSmashPlayerController>(GetController());
	m_Falling = false;
	if (controller != nullptr)
	{
		ACPP_GameHUD* hud = Cast<ACPP_GameHUD>(controller->GetHUD());
		if (hud != nullptr)
		{
			hud->OpenEndGameWidget();
		}
	}

	if (m_CrashSoundCue != nullptr)
		UGameplayStatics::PlaySound2D(GetWorld(), m_CrashSoundCue, 1.0f, 1.0f, 0.0f);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Setters
void ACPP_BasePlayerCharacter::SetHeightToMaintain(float height)
{
	m_HeightToMaintain = height;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Getters
float ACPP_BasePlayerCharacter::GetHeightToMaintain()
{
	return m_HeightToMaintain;
}

FRotator ACPP_BasePlayerCharacter::GetFinalRotation()
{
	return m_FinalRotation;
}

bool ACPP_BasePlayerCharacter::GetIsFalling()
{
	return m_Falling;
}

bool ACPP_BasePlayerCharacter::ShouldBeRunning()
{
	return m_GameStarted;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//IPlayerCharacterInput
void ACPP_BasePlayerCharacter::Forward_Implementation(float axis)
{
	m_ForwardBackAxis = axis;
}

void ACPP_BasePlayerCharacter::Right_Implementation(float axis)
{
	m_RightLeftAxis = axis;
}

void ACPP_BasePlayerCharacter::PausePressed_Implementation()
{

}

void ACPP_BasePlayerCharacter::PauseReleased_Implementation()
{

}