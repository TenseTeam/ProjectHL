// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/Generic/SaveSystem/SaveManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SSUtility.generated.h"

UCLASS()
class VUNDK_API USSUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static USaveManager* CurrentSaveManager;
	
public:
	static void Init(USaveManager* SaveManager);

	UFUNCTION(BlueprintPure, Category = "Save System")
	static USaveManager* GetSaveManager();
	
	UFUNCTION(BlueprintPure, Category = "Save System")
	static UDefaultSaveGame* GetSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save System")
	static void StartNewSaveGame();
	
	UFUNCTION(BlueprintCallable, Category = "Save System")
	static void ManualSave(UObject* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Save System")
	static void StartTimePlayedTimer();
	
private:
	static bool Check();
};
