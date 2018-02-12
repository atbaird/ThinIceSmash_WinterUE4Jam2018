// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_SolidIceBlock.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "../PlayerCharacters/CPP_BasePlayerCharacter.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


void ACPP_SolidIceBlock::OnHitActorEvent_Implementation(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
}

void ACPP_SolidIceBlock::BeginOverlapActorEvent_Implementation(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	ACPP_BasePlayerCharacter* character = Cast<ACPP_BasePlayerCharacter>(OtherActor);

	if (character != nullptr)
	{
		FVector actorLoc = character->GetActorLocation();
		FVector closestPoint;
		OverlappedComponent->GetClosestPointOnCollision(actorLoc, closestPoint);
		FVector otherClosestPoint = actorLoc;
		FVector closestPointDifference = otherClosestPoint - closestPoint;
		FVector normalizedDiff = closestPointDifference;
		normalizedDiff.Normalize();
		if (normalizedDiff.Z > 0.1f)
		{
			KillPlayer(character);
		}
		else
		{
			character->SetActorLocation(character->GetActorLocation() + closestPointDifference);
		}

	}
}

void ACPP_SolidIceBlock::KillPlayer_Implementation(ACPP_BasePlayerCharacter* character)
{
	if (character == nullptr)
		return;
	character->KillPlayer();
}