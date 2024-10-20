// Copyright VUNDK, Inc. All Rights Reserved.

#include "UGameFramework/VUNDKGameInstance.h"
#include "Framework/Application/NavigationConfig.h"

void UVUNDKGameInstance::Init()
{
	Super::Init();
	SetSlateNavigationConfigs();
}

void UVUNDKGameInstance::SetSaveMasterID(const FName NewSaveMasterID)
{
	SaveMasterID = NewSaveMasterID;
}

void UVUNDKGameInstance::SetSlateNavigationConfigs() const
{
	FNavigationConfig& NavigationConfig = *FSlateApplication::Get().GetNavigationConfig();
	NavigationConfig.bTabNavigation = bTabNavigation;
	NavigationConfig.bAnalogNavigation = bAnalogNavigation;
	NavigationConfig.bKeyNavigation = bKeyNavigation;
}
