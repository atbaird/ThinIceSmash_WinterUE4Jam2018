// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CPP_BaseGeneralWidget.generated.h"

/**
 * 
 */
UCLASS()
class THINICESMASH_API UCPP_BaseGeneralWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* m_Widget = nullptr;
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ChangeOwningWidget(UUserWidget* widget);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void ActivateHover();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void DeactivateHover();
	
	
};
