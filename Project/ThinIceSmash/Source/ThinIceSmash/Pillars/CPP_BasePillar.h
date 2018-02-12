// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/DataTable.h"
#include "CPP_BasePillar.generated.h"

class ACPP_BasePillar;
USTRUCT()
struct FSTRUCT_PillarSpawningData : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACPP_BasePillar> m_PillarSubClass;
};

UCLASS()
class THINICESMASH_API ACPP_BasePillar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_BasePillar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
