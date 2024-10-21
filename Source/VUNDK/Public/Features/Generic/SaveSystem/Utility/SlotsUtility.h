// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/Generic/SaveSystem/SaveManager.h"
#include "Features/Generic/SaveSystem/Data/Enums/SaveTypeFilter.h"
#include "Features/Generic/SaveSystem/Data/Structs/SlotInfoData.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SlotsUtility.generated.h"

UCLASS()
class VUNDK_API USlotsUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
private:
	static USaveManager* CurrentSaveManager;

public:
	static void Init(USaveManager* SaveManager);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static bool DoesSlotFileExist(const FString& SlotName);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static bool DoesAnySlotFileExist();

	UFUNCTION(BlueprintPure, Category = "Save System")
	static bool TryGetSlotFileNames(TArray<FString>& OutSaveFiles, bool bWithExtension = true);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static int32 GetTotalSlots();

	UFUNCTION(BlueprintPure, Category = "Save System")
	static int32 GetTotalAutoSaveSlots();

	UFUNCTION(BlueprintPure, Category = "Save System")
	static int32 GetTotalManualSaveSlots();

	UFUNCTION(BlueprintPure, Category = "Save System")
	static bool TryGetSlotInfosOfType(TArray<FSlotInfoData>& OutSlotInfos, ESaveTypeFilter Type = ESaveTypeFilter::All);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static bool TryGetMostRecentSlotInfoData(FSlotInfoData& OutSlotData, ESaveTypeFilter Type = ESaveTypeFilter::All);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static bool TryGetMostAncientSlotInfoData(FSlotInfoData& OutSlotData, ESaveTypeFilter Type = ESaveTypeFilter::All);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static float GetMostRecentSlotInfoPlayedTime();
	
	static bool IsSlotNameValid(const FString& SlotName);
};
