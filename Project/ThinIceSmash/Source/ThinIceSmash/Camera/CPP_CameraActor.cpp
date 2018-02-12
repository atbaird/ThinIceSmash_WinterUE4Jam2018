// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_CameraActor.h"
#include <Runtime/Engine/Classes/Engine/Engine.h>

//--------------------------------------------------------
//--------------------------------------------------------
//--------------------------------------------------------
//Init
void ACPP_CameraActor::InitGameMode()
{
	if (m_GameMode != nullptr)
		return;
	m_GameMode = Cast<ACPP_ThingIceSmashGameMode>(GetWorld()->GetAuthGameMode());
}


void ACPP_CameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InitGameMode();
	FRotator rotation = FRotator(0.0f, 0.0f, 0.0f);
	FVector center = FVector(0.0f, 0.0f, 0.0f);
	if (m_CharacterToFollow != nullptr)
	{
		rotation = m_CharacterToFollow->GetFinalRotation();
		center = m_CharacterToFollow->GetActorLocation();
	}
	else
	{
		rotation = m_GameMode->GetCameraRotation();
		center = m_GameMode->GetCameraCenterPosition();
	}
	FVector location = center
		+ (FRotationMatrix(rotation).GetScaledAxis(EAxis::X) * m_DistanceFromCharacterForwardToMaintain)
		+ (FRotationMatrix(rotation).GetScaledAxis(EAxis::Z) * m_DistanceFromCharacterUpToMaintain);
	SetActorLocationAndRotation(location, rotation);
}

void ACPP_CameraActor::SetCharacterToFollow(ACPP_BasePlayerCharacter* character)
{
	m_CharacterToFollow = character;
}