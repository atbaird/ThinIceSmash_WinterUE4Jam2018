// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IceBlocks/CPP_IceBlocks.h"
#include "CPP_ThinIceBlock.generated.h"

/**
 * 
 */
UCLASS()
class THINICESMASH_API ACPP_ThinIceBlock : public ACPP_IceBlocks
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
		bool m_BrokenAlready = false;
public:

protected:
	virtual void OnHitActorEvent_Implementation(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;

	virtual void BeginOverlapActorEvent_Implementation(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult) override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Break(AActor* actor);
};
