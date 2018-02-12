// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ThinIceSmashPlayerController.h"
#include "../FunctionLibraries/CPP_PlayerCharacterFunctionLib.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "../HUD/CPP_GameHUD.h"


//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------
//Inits
void ACPP_ThinIceSmashPlayerController::InitHUD()
{
	if (m_MyHud != nullptr)
		return;

	m_MyHud = Cast<ACPP_GameHUD>(GetHUD());
}

void ACPP_ThinIceSmashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("UIActionConfirm", EInputEvent::IE_Pressed, this, &ACPP_ThinIceSmashPlayerController::UIConfirmPressed);
	InputComponent->BindAction("UIActionConfirm", EInputEvent::IE_Released, this, &ACPP_ThinIceSmashPlayerController::UIConfirmReleased);
	InputComponent->BindAction("GamePause", EInputEvent::IE_Pressed, this, &ACPP_ThinIceSmashPlayerController::GamePausedPressed);
	InputComponent->BindAction("GamePause", EInputEvent::IE_Released, this, &ACPP_ThinIceSmashPlayerController::GamePausedReleased);
	InputComponent->BindAxis("GameForward", this, &ACPP_ThinIceSmashPlayerController::GameForwardFunc);
	InputComponent->BindAxis("GameRight", this, &ACPP_ThinIceSmashPlayerController::GameRightFunc);
	InputComponent->BindAxis("UIUp", this, &ACPP_ThinIceSmashPlayerController::UIUpFunc);
}

//-----------------------------------------------------------
//-----------------------------------------------------------
//-----------------------------------------------------------
//Controls
void ACPP_ThinIceSmashPlayerController::UIConfirmPressed()
{
	InitHUD();
	if (m_MyHud != nullptr)
	{
		UCPP_BaseUserWidget* widget = m_MyHud->GetCurrentWidgetFocusingOn();
		if (widget != nullptr)
		{
			widget->ConfirmPressed();
		}
	}
}

void ACPP_ThinIceSmashPlayerController::UIConfirmReleased()
{
	InitHUD();
	if (m_MyHud != nullptr)
	{
		UCPP_BaseUserWidget* widget = m_MyHud->GetCurrentWidgetFocusingOn();
		if (widget != nullptr)
		{
			widget->ConfirmReleased();
		}
	}
}

void ACPP_ThinIceSmashPlayerController::GamePausedPressed()
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		InitHUD();
		if (m_MyHud != nullptr)
		{
			if (m_MyHud->GetCurrentWidgetFocusingOn() != nullptr)
				return;
		}
		if (pawn->Implements<UPlayerCharacterInput>())
		{
			IPlayerCharacterInput::Execute_PausePressed(pawn);
		}
	}
}

void ACPP_ThinIceSmashPlayerController::GamePausedReleased()
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		InitHUD();
		if (m_MyHud != nullptr)
		{
			if (m_MyHud->GetCurrentWidgetFocusingOn() != nullptr)
				return;
		}

		if (pawn->Implements<UPlayerCharacterInput>())
		{
			IPlayerCharacterInput::Execute_PauseReleased(pawn);
		}
	}
}

void ACPP_ThinIceSmashPlayerController::GameForwardFunc(float Axis)
{
	if (m_DisableBackwardsInput && Axis < 0.0f)
	{
		Axis = 0.0f;
	}
	if (m_DisableForwardsInput && Axis > 0.0f)
	{
		Axis = 0.0f;
	}

	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		InitHUD();
		if (m_MyHud != nullptr)
		{
			if (m_MyHud->GetCurrentWidgetFocusingOn() != nullptr)
				return;
		}

		if (pawn->Implements<UPlayerCharacterInput>())
		{
			IPlayerCharacterInput::Execute_Forward(pawn, Axis);
		}
	}
}

void ACPP_ThinIceSmashPlayerController::GameRightFunc(float Axis)
{
	APawn* pawn = GetPawn();
	if (pawn != nullptr)
	{
		InitHUD();
		if (m_MyHud != nullptr)
		{
			if (m_MyHud->GetCurrentWidgetFocusingOn() != nullptr)
				return;
		}

		if (pawn->Implements<UPlayerCharacterInput>())
		{
			IPlayerCharacterInput::Execute_Right(pawn, Axis);
		}
	}
}

void ACPP_ThinIceSmashPlayerController::UIUpFunc(float Axis)
{
	float PreviousUpInput = m_UIUpInput;
	m_UIUpInput = Axis;
	InitHUD();
	if (m_MyHud != nullptr)
	{
		UCPP_BaseUserWidget* widget = m_MyHud->GetCurrentWidgetFocusingOn();
		if (widget != nullptr)
		{
			FString text = FString::SanitizeFloat(m_UIUpInput) + " " + FString::SanitizeFloat(Axis);

			if (PreviousUpInput >= m_UIUPPressedSensitivity && m_UIUpInput < m_UIUPPressedSensitivity)
			{
				widget->UpReleased();
			}
			else if (PreviousUpInput < m_UIUPPressedSensitivity && m_UIUpInput >= m_UIUPPressedSensitivity)
			{
				widget->UpPressed();
			}

			if (PreviousUpInput <= -m_UIUPPressedSensitivity && m_UIUpInput > -m_UIUPPressedSensitivity)
			{
				widget->DownReleased();
			}
			else if(PreviousUpInput > -m_UIUPPressedSensitivity && m_UIUpInput <= -m_UIUPPressedSensitivity)
			{
				widget->DownPressed();
			}
			
		}
	}
}