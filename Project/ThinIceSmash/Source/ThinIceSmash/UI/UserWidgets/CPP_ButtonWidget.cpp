// Fill out your copyright notice in the Description page of Project Settings.

#include "CPP_ButtonWidget.h"
#include "../../FunctionLibraries/CPP_UIFunctionLibrary.h"

void UCPP_ButtonWidget::Activate_Implementation()
{
	if (m_Widget != nullptr)
	{
		if (m_Widget->GetClass()->ImplementsInterface(UUIInput::StaticClass()))
		{
			IUIInput::Execute_ReceiveButtonClicked(m_Widget, this);
		}
	}
}