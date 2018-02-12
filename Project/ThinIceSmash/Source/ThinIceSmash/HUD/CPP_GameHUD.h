// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "../UI/CPP_BaseUserWidget.h"
#include "CPP_GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class THINICESMASH_API ACPP_GameHUD : public AHUD
{
	GENERATED_BODY()
protected:
	//-----------------------------------------------------
	//Classes

	//UCPP_BaseUserWidget; Widget class for the main menu.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UCPP_BaseUserWidget> m_MainMenuWidgetClass;

	//UCPP_BaseUserWidget; Widget class for the pause menu.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UCPP_BaseUserWidget> m_PauseMenuWidgetClass;

	//UCPP_BaseUserWidget; Widget class for the Game HUD.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UCPP_BaseUserWidget> m_GameHUDClass;

	//UCPP_BaseUserWidget; Widget class for the end game menu.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<UCPP_BaseUserWidget> m_EndGameWidgetClass;


	//-----------------------------------------------------
	//Variables

	UPROPERTY(BlueprintReadWrite)
		UCPP_BaseUserWidget* m_CurrentWidgetFocusingOn = nullptr;

	//Current reference to the main menu.
	UPROPERTY(BlueprintReadWrite)
	UCPP_BaseUserWidget* m_MainMenuWidget = nullptr;

	//Current reference to the pause menu.
	UPROPERTY(BlueprintReadWrite)
	UCPP_BaseUserWidget* m_PauseMenuWidget = nullptr;

	//Current reference to the Game HUD.
	UPROPERTY(BlueprintReadWrite)
		UCPP_BaseUserWidget* m_GameHUDWidget = nullptr;

	//Current reference to the end game menu.
	UPROPERTY(BlueprintReadWrite)
		UCPP_BaseUserWidget* m_EndGameMenuWidget = nullptr;
public:

	//-----------------------------------------------------
	//Current Widget focusing on

	UFUNCTION(BlueprintCallable)
		void ChangeCurrentWidget(UCPP_BaseUserWidget* newWidget);


	//-----------------------------------------------------
	//Open Widgets

	UFUNCTION(BlueprintCallable)
		void OpenPauseMenuWidget();

	UFUNCTION(BlueprintCallable)
		void OpenMainMenuWidget();

	UFUNCTION(BlueprintCallable)
		void OpenEndGameWidget();

	UFUNCTION(BlueprintCallable)
		void OpenGameHUDWidget();


	//-----------------------------------------------------
	//Inits

	//Initializes the pause menu and returns it's reference.
	UFUNCTION(BlueprintCallable)
	UCPP_BaseUserWidget* InitPauseMenuWidget();

	//Initializes the main menu and returns it's reference.
	UFUNCTION(BlueprintCallable)
	UCPP_BaseUserWidget* InitMainMenuWidget();

	//Initializes the game hud widget and returns it's reference.
	UFUNCTION(BlueprintCallable)
		UCPP_BaseUserWidget* InitGameHUDWidget();

	//Initialize the end game widget and returns it's reference.
	UFUNCTION(BlueprintCallable)
		UCPP_BaseUserWidget* InitEndGameWidget();

	//-----------------------------------------------------
	//Getters

	//Returns the reference to the currently focused widget.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCPP_BaseUserWidget* GetCurrentWidgetFocusingOn();
	
	//Returns the pause menu widget reference.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCPP_BaseUserWidget* GetPauseMenuWidget();

	//Returns the main menu widget reference.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UCPP_BaseUserWidget* GetMainMenuWidget();
	
	//Returns the game hud widget reference.
	UFUNCTION(BlueprintCallable, BlueprintPure)
		UCPP_BaseUserWidget* GetGameHUDWidget();

	//Returns the end game menu widget reference
	UFUNCTION(BlueprintCallable, BlueprintPure)
		UCPP_BaseUserWidget* GetEndGameWidget();
};
