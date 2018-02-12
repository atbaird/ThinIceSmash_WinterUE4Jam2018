// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BasePawn.h"


// Sets default values
ACPP_BasePawn::ACPP_BasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_BasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_BasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_BasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

