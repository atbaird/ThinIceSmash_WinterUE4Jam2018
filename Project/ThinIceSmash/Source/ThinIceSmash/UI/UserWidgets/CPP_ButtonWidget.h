// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/CPP_BaseGeneralWidget.h"
#include "CPP_ButtonWidget.generated.h"
/**
 * 
 */
UCLASS()
class THINICESMASH_API UCPP_ButtonWidget : public UCPP_BaseGeneralWidget
{
	GENERATED_BODY()
	
protected:

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Activate();

};
