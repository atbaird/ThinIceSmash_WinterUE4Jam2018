// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/CoreUObject/Public/UObject/Interface.h"
#include "CPP_PlayerCharacterFunctionLib.generated.h"

/**
 * 
 */

//!----------------------------------------------------------------
//Interface Player Character Input
UINTERFACE(BlueprintType)
class THINICESMASH_API UPlayerCharacterInput : public UInterface
{
	GENERATED_BODY()
};

class THINICESMASH_API IPlayerCharacterInput
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Forward(float axis);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Right(float axis);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PausePressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PauseReleased();

};

//!----------------------------------------------------------------
//Function Library Player Character
UCLASS()
class THINICESMASH_API UCPP_PlayerCharacterFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	
	
};
