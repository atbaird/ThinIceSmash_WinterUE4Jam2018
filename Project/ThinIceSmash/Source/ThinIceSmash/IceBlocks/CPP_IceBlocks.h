// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_IceBlocks.generated.h"

UCLASS()
class THINICESMASH_API ACPP_IceBlocks : public AActor
{
	GENERATED_BODY()
	
protected:

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent * m_Root = nullptr;

	// Sets default values for this actor's properties
	ACPP_IceBlocks();

	ACPP_IceBlocks(const FObjectInitializer& ObjectInitializer);
protected:

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	//Collision
private:
	UFUNCTION()
	void OnHitActor(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void BeginOverlapActor(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnHitActorEvent(UPrimitiveComponent* HitComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void BeginOverlapActorEvent(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

public:
	
};
