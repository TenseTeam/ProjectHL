// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "QuestBase.h"
#include "QuestSequencial.generated.h"

UCLASS(NotBlueprintable, BlueprintType)
class VUNDK_API UQuestSequencial : public UQuestBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Quest System")
	TArray<UTaskData*> TasksByIndex;

private:
	int32 CurrentTaskIndex = 0;
	
public:
	virtual void Init(UQuestData* InitData, const FQuestEntryData& EntryData) override;
	virtual void LoadSaveData(FQuestSaveData QuestSaveData) override;
	virtual void AchieveQuestTask(const UTaskData* TaskDataKey, const bool bFullyAchieve) override;
	virtual void ResetQuest() override;
	virtual FQuestSaveData CreateQuestSaveData() const override;
	
	UFUNCTION(BlueprintPure, Category = "Quest System")
	int32 GetCurrentTaskIndex() const;

	UFUNCTION(BlueprintPure, Category = "Quest System")
	int32 GetTaskIndex(UTaskData* TaskDataKey) const;
};
