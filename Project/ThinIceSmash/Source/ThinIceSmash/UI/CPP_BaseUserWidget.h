// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../FunctionLibraries/CPP_UIFunctionLibrary.h"
#include "CPP_BaseUserWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMenuAction : uint8
{
	MenuAction_Nothing,
	MenuAction_Start,
	MenuAction_Restart,
	MenuAction_Quit,
	MenuAction_Resume,
	MenuAction_Custom
};

UCLASS()
class THINICESMASH_API UCPP_BaseUserWidget : public UUserWidget, public IUIInput
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ACPP_ThinIceSmashPlayerController* m_OwningController = nullptr;
	int m_CurrentIndex = 0;

	bool m_Open = false;
	bool m_InitOnce = false;
	bool m_UpIsDown = false;
	bool m_DownIsDown = false;

	UPROPERTY(BlueprintReadWrite)
	TArray<UCPP_BaseGeneralWidget*> m_InteractableWidgets;

	UPROPERTY(BlueprintReadWrite)
		TArray<EMenuAction> m_InteractableWidgetActions;
	
public:
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	virtual void Tick(FGeometry MyGeometry, float InDeltaTime);
protected:
	void UpdateSelection();

public:

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void UnhoverAllButtons();

	UFUNCTION(BlueprintCallable)
		void UnhoverCurrentButton();

	UFUNCTION(BlueprintCallable)
		void HoverCurrentButton();

	UFUNCTION(BlueprintCallable)
		void ChangeButtonIndex(int index);

	UFUNCTION(BlueprintCallable)
		void CycleSelectionUp();

	UFUNCTION(BlueprintCallable)
		void CycleSelectionDown();


	//-----------------------------------------------------------------------------
	//Menu Actions

	UFUNCTION(BlueprintCallable)
		virtual void MenuActionStartGame();

	UFUNCTION(BlueprintCallable)
		virtual void MenuActionRestartGame();

	UFUNCTION(BlueprintCallable)
		virtual void MenuActionQuit();

	UFUNCTION(BlueprintCallable)
		virtual void MenuActionResume();

	//-----------------------------------------------------------------------------
	//Events

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void MenuActionCustom(UCPP_BaseGeneralWidget* widget, int32 idxInList);

	//Call on beginplay/construct
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void InitFunctionallity();

	//Call on beginplay/construct
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void LoadUpListOfButtons();

	//-----------------------------------------------------------------------------
	//Interface UI Input

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
