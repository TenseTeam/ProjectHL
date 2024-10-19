// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataBase.h"
#include "Engine/DataAsset.h"
#include "InventoryRegistry.generated.h"

UCLASS(NotBlueprintable, BlueprintType)
class VUNDK_API UInventoryRegistry : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory System|Registry")
	TArray<UItemDataBase*> RegisteredItems;
};
