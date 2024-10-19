// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Features/Gameplay/InventorySystem/Base/ItemBase.h"
#include "ItemDataBase.generated.h"

UCLASS(Abstract, Blueprintable, BlueprintType)
class VUNDK_API UItemDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	TSubclassOf<UItemBase> ItemClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	FString ItemName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data", meta=(MultiLine="true"))
	FText ItemDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	FSlateBrush ItemIcon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	bool bIsUnique;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	bool bIsConsumable;

	FORCEINLINE FName GetItemID() const
	{
		const int32 Hash = GetTypeHash(GetFName()) + GetTypeHash(ItemName);
		const FString Hex = FString::Printf(TEXT("%08X"), Hash);
		return FName(*Hex);
	}
};
