// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_GameHUD.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Blueprint/WidgetLayoutLibrary.h"

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//Current Widget focusing on
void ACPP_GameHUD::ChangeCurrentWidget(UCPP_BaseUserWidget* newWidget)
{
	if (m_CurrentWidgetFocusingOn != nullptr)
	{
		m_CurrentWidgetFocusingOn->OnClose();
		m_CurrentWidgetFocusingOn->RemoveFromParent();
	}

	m_CurrentWidgetFocusingOn = newWidget;
	if (m_CurrentWidgetFocusingOn != nullptr)
	{
		ACPP_ThinIceSmashPlayerController* controller = Cast<ACPP_ThinIceSmashPlayerController>(GetWorld()->GetFirstPlayerController());
		m_CurrentWidgetFocusingOn->OnOpen(controller);
	}
}


//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//Open Widgets
void ACPP_GameHUD::OpenPauseMenuWidget()
{
	InitPauseMenuWidget();

	if (m_PauseMenuWidget != nullptr)
	{
		m_PauseMenuWidget->AddToViewport();
	}
	ChangeCurrentWidget(m_PauseMenuWidget);
}

void ACPP_GameHUD::OpenMainMenuWidget()
{
	InitMainMenuWidget();

	if (m_MainMenuWidget != nullptr)
	{
		m_MainMenuWidget->AddToViewport();
	}
	ChangeCurrentWidget(m_MainMenuWidget);
}

void ACPP_GameHUD::OpenEndGameWidget()
{
	InitEndGameWidget();

	if (m_EndGameMenuWidget != nullptr)
	{
		m_EndGameMenuWidget->AddToViewport();
	}
	ChangeCurrentWidget(m_EndGameMenuWidget);
}

void ACPP_GameHUD::OpenGameHUDWidget()
{
	//UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	InitGameHUDWidget();

	if (m_GameHUDWidget != nullptr)
	{
		m_GameHUDWidget->AddToViewport();
	}

	ChangeCurrentWidget(nullptr);
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//Inits
UCPP_BaseUserWidget* ACPP_GameHUD::InitPauseMenuWidget()
{
	if (m_PauseMenuWidget == nullptr && m_PauseMenuWidgetClass != nullptr)
	{
		m_PauseMenuWidget = CreateWidget<UCPP_BaseUserWidget>(GetGameInstance(), m_PauseMenuWidgetClass);
	}

	return m_PauseMenuWidget;
}

UCPP_BaseUserWidget* ACPP_GameHUD::InitMainMenuWidget()
{
	if (m_MainMenuWidget == nullptr && m_MainMenuWidgetClass != nullptr)
	{
		m_MainMenuWidget = CreateWidget<UCPP_BaseUserWidget>(GetGameInstance(), m_MainMenuWidgetClass);
	}

	return m_MainMenuWidget;
}

UCPP_BaseUserWidget* ACPP_GameHUD::InitGameHUDWidget()
{
	if (m_GameHUDWidget == nullptr && m_GameHUDClass != nullptr)
	{
		m_GameHUDWidget = CreateWidget<UCPP_BaseUserWidget>(GetGameInstance(), m_GameHUDClass);
	}

	return m_GameHUDWidget;
}

UCPP_BaseUserWidget* ACPP_GameHUD::InitEndGameWidget()
{
	if (m_EndGameMenuWidget == nullptr && m_EndGameWidgetClass != nullptr)
	{
		m_EndGameMenuWidget = CreateWidget<UCPP_BaseUserWidget>(GetGameInstance(), m_EndGameWidgetClass);
	}
	return m_EndGameMenuWidget;
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//Getters
UCPP_BaseUserWidget* ACPP_GameHUD::GetCurrentWidgetFocusingOn()
{
	return m_CurrentWidgetFocusingOn;
}

UCPP_BaseUserWidget* ACPP_GameHUD::GetPauseMenuWidget()
{
	return m_PauseMenuWidget;
}

UCPP_BaseUserWidget* ACPP_GameHUD::GetMainMenuWidget()
{
	return m_MainMenuWidget;
}

UCPP_BaseUserWidget* ACPP_GameHUD::GetGameHUDWidget()
{
	return m_GameHUDWidget;
}


UCPP_BaseUserWidget* ACPP_GameHUD::GetEndGameWidget()
{
	return m_EndGameMenuWidget;
}