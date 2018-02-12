// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_IceBlocks.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ACPP_IceBlocks::ACPP_IceBlocks()
	: Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IceBlockMesh"));
}


ACPP_IceBlocks::ACPP_IceBlocks(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	m_Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IceBlockMesh"));
	m_Root->OnComponentHit.AddDynamic(this, &ACPP_IceBlocks::OnHitActor);
	m_Root->OnComponentBeginOverlap.AddDynamic(this, &ACPP_IceBlocks::BeginOverlapActor);
}

// Called when the game starts or when spawned
void ACPP_IceBlocks::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACPP_IceBlocks::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_IceBlocks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Collision
void ACPP_IceBlocks::OnHitActor(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	OnHitActorEvent(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void ACPP_IceBlocks::BeginOverlapActor(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	BeginOverlapActorEvent(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}


void ACPP_IceBlocks::OnHitActorEvent_Implementation(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

}

void ACPP_IceBlocks::BeginOverlapActorEvent_Implementation(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{

}