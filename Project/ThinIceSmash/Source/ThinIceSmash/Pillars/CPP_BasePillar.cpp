// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BasePillar.h"


// Sets default values
ACPP_BasePillar::ACPP_BasePillar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BasePillar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_BasePillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

