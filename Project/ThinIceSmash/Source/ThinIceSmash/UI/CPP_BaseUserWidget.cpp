// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_BaseUserWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "UserWidgets/CPP_ButtonWidget.h"
#include "../GameBehavior/CPP_ThingIceSmashGameMode.h"
#include "Kismet/KismetSystemLibrary.h"

bool UCPP_BaseUserWidget::Initialize()
{
	return Super::Initialize();
}

void UCPP_BaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
}

void UCPP_BaseUserWidget::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);
	UpdateSelection();
}

void UCPP_BaseUserWidget::UpdateSelection()
{

}

void UCPP_BaseUserWidget::Init()
{
	if (m_InitOnce)
		return;
	m_InitOnce = true;
	InitFunctionallity();
	LoadUpListOfButtons();
	UnhoverAllButtons();
	ChangeButtonIndex(0);
}


void UCPP_BaseUserWidget::UnhoverAllButtons()
{
	for (int idx = 0; idx < m_InteractableWidgets.Num(); idx++)
	{
		if (m_InteractableWidgets[idx] != nullptr)
		{
			m_InteractableWidgets[idx]->DeactivateHover();
		}
	}
}

void UCPP_BaseUserWidget::UnhoverCurrentButton()
{
	if (m_InteractableWidgets.Num() > 0 && m_CurrentIndex >= 0 && m_CurrentIndex < m_InteractableWidgets.Num())
	{
		if (m_InteractableWidgets[m_CurrentIndex] != nullptr)
		{
			m_InteractableWidgets[m_CurrentIndex]->DeactivateHover();
		}
	}
}

void UCPP_BaseUserWidget::HoverCurrentButton()
{
	if (m_InteractableWidgets.Num() > 0 && m_CurrentIndex >= 0 && m_CurrentIndex < m_InteractableWidgets.Num())
	{
		if (m_InteractableWidgets[m_CurrentIndex] != nullptr)
		{
			m_InteractableWidgets[m_CurrentIndex]->ActivateHover();
		}
	}
}

void UCPP_BaseUserWidget::ChangeButtonIndex(int index)
{
	UnhoverCurrentButton();
	m_CurrentIndex = index;
	HoverCurrentButton();
}

void UCPP_BaseUserWidget::CycleSelectionUp()
{
	if (m_InteractableWidgets.Num() <= 1)
		return;
	UnhoverCurrentButton();

	m_CurrentIndex++;
	if (m_CurrentIndex >= m_InteractableWidgets.Num() || m_CurrentIndex < 0)
	{
		m_CurrentIndex = 0;
	}

	HoverCurrentButton();
}

void UCPP_BaseUserWidget::CycleSelectionDown()
{
	if (m_InteractableWidgets.Num() <= 1)
		return;
	UnhoverCurrentButton();

	m_CurrentIndex--;
	if (m_CurrentIndex >= m_InteractableWidgets.Num() || m_CurrentIndex < 0)
	{
		m_CurrentIndex = m_InteractableWidgets.Num() - 1;
	}

	HoverCurrentButton();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Menu Actions
void UCPP_BaseUserWidget::MenuActionStartGame()
{
	ACPP_ThingIceSmashGameMode* gameMode = Cast<ACPP_ThingIceSmashGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode != nullptr)
	{
		gameMode->StartGame();
	}
}

void UCPP_BaseUserWidget::MenuActionRestartGame()
{
}

void UCPP_BaseUserWidget::MenuActionQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit);
}

void UCPP_BaseUserWidget::MenuActionResume()
{

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Events
void UCPP_BaseUserWidget::MenuActionCustom_Implementation(UCPP_BaseGeneralWidget* widget, int32 idxInList)
{

}

void UCPP_BaseUserWidget::InitFunctionallity_Implementation()
{

}

void UCPP_BaseUserWidget::LoadUpListOfButtons_Implementation()
{
	for (int idx = 0; idx < m_InteractableWidgets.Num(); idx++)
	{
		if (m_InteractableWidgets[idx] != nullptr)
		{
			m_InteractableWidgets[idx]->ChangeOwningWidget(this);
		}
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Interface UI Input
void UCPP_BaseUserWidget::UpPressed_Implementation()
{
	m_UpIsDown = true;
	CycleSelectionUp();
}

void UCPP_BaseUserWidget::UpReleased_Implementation()
{
	m_UpIsDown = false;
}

void UCPP_BaseUserWidget::DownPressed_Implementation()
{
	m_DownIsDown = true;
	CycleSelectionDown();
}

void UCPP_BaseUserWidget::DownReleased_Implementation()
{
	m_DownIsDown = false;
}

void UCPP_BaseUserWidget::ConfirmPressed_Implementation()
{
}

void UCPP_BaseUserWidget::ConfirmReleased_Implementation()
{
	if (m_CurrentIndex < 0 || m_CurrentIndex >= m_InteractableWidgets.Num())
		return;
	UCPP_BaseGeneralWidget* widget = m_InteractableWidgets[m_CurrentIndex];
	if (widget == nullptr)
		return;

	UCPP_ButtonWidget* buttonWidget = Cast<UCPP_ButtonWidget>(widget);
	if (buttonWidget != nullptr)
	{
		buttonWidget->Activate();
		return;
	}
}


void UCPP_BaseUserWidget::OnOpen_Implementation(ACPP_ThinIceSmashPlayerController* controller)
{
	m_OwningController = controller;
	m_Open = true;
	m_UpIsDown = false;
	m_DownIsDown = false;
	Init();
	UnhoverAllButtons();
	ChangeButtonIndex(0);
}


void UCPP_BaseUserWidget::OnClose_Implementation()
{
	m_OwningController = nullptr;
	m_Open = false;
}


void UCPP_BaseUserWidget::ReceiveButtonClicked_Implementation(UCPP_BaseGeneralWidget* buttonWidget)
{
	for (int idx = 0; idx < m_InteractableWidgets.Num(); idx++)
	{
		UCPP_BaseGeneralWidget* widget = m_InteractableWidgets[idx];
		if (widget != nullptr && widget == buttonWidget)
		{
			if (idx >= m_InteractableWidgetActions.Num())
				return;

			switch (m_InteractableWidgetActions[idx])
			{
			case EMenuAction::MenuAction_Nothing:
				break;
			case EMenuAction::MenuAction_Start:
				MenuActionStartGame();
				break;
			case EMenuAction::MenuAction_Restart:
				MenuActionRestartGame();
				break;
			case EMenuAction::MenuAction_Quit:
				MenuActionQuit();
				break;
			case EMenuAction::MenuAction_Resume:
				MenuActionResume();
				break;
			case EMenuAction::MenuAction_Custom:
				MenuActionCustom(buttonWidget, idx);
				break;
			default:
				break;
			}

			return;
		}
	}
}