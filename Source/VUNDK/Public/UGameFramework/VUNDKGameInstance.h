// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VUNDKGameInstance.generated.h"

UCLASS()
class VUNDK_API UVUNDKGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category = "Save System")
	FName SaveMasterID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Navigation")
	bool bTabNavigation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Navigation")
	bool bAnalogNavigation = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Navigation")
	bool bKeyNavigation = true;
	
public:
	virtual void Init() override;
	UFUNCTION(BlueprintCallable, Category = "Save System")
	void SetSaveMasterID(const FName NewSaveMasterID);

private:
	void SetSlateNavigationConfigs() const;
};
