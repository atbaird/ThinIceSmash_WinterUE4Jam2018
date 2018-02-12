// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BaseActor.h"


// Sets default values
ACPP_BaseActor::ACPP_BaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_BaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

