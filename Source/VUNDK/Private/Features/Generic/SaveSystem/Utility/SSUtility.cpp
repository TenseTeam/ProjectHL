// Copyright VUNDK, Inc. All Rights Reserved.

#include "Features/Generic/SaveSystem/Utility/SSUtility.h"

USaveManager* USSUtility::CurrentSaveManager = nullptr;

void USSUtility::Init(USaveManager* SaveManager)
{
	CurrentSaveManager = SaveManager;
}

USaveManager* USSUtility::GetSaveManager()
{
	return CurrentSaveManager;
}

UDefaultSaveGame* USSUtility::GetSaveGame()
{
	if (!Check()) return nullptr;
	return CurrentSaveManager->GetSaveGameInstance();
}

void USSUtility::StartNewSaveGame()
{
	if (!Check()) return;
	CurrentSaveManager->StartNewSaveGame();
}

void USSUtility::ManualSave(UObject* Instigator)
{
	if (!CurrentSaveManager) return;
	CurrentSaveManager->ManualSave(Instigator);
}

void USSUtility::StartTimePlayedTimer()
{
	if (!Check()) return;
	CurrentSaveManager->StartTimePlayedTimer();
}

bool USSUtility::Check()
{
	return CurrentSaveManager != nullptr;
}
