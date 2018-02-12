// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../GameBehavior/CPP_ThinIceSmashPlayerController.h"
#include "../UI/CPP_BaseGeneralWidget.h"
#include "CPP_UIFunctionLibrary.generated.h"

/**
 * 
 */


 //!----------------------------------------------------------------
 //Interface UI Input
UINTERFACE(BlueprintType)
class THINICESMASH_API UUIInput : public UInterface
{
	GENERATED_BODY()
};

class THINICESMASH_API IUIInput
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UpPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void UpReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DownPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DownReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ConfirmPressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ConfirmReleased();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnOpen(ACPP_ThinIceSmashPlayerController* controller);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnClose();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ReceiveButtonClicked(UCPP_BaseGeneralWidget* buttonWidget);
};

//!----------------------------------------------------------------
//UCPP_UIFunctionLibrary
UCLASS()
class THINICESMASH_API UCPP_UIFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	
	
};
