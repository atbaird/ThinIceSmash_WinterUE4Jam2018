// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ThinIceBlock.h"
#include "../GameBehavior/CPP_ThingIceSmashGameMode.h"
#include "../PlayerCharacters/CPP_BasePlayerCharacter.h"

void ACPP_ThinIceBlock::OnHitActorEvent_Implementation(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

}

void ACPP_ThinIceBlock::BeginOverlapActorEvent_Implementation(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	if (Cast<ACPP_BasePlayerCharacter>(OtherActor) != nullptr && !m_BrokenAlready)
	{
		m_BrokenAlready = true;
		ACPP_ThingIceSmashGameMode* gameMode = Cast<ACPP_ThingIceSmashGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode != nullptr)
		{
			gameMode->IncrementAmountOfIceShattered();
		}

		Break(OtherActor);
	}
}


void ACPP_ThinIceBlock::Break_Implementation(AActor* actor)
{

}