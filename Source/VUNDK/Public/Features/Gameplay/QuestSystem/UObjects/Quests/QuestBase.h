// Copyright VUNDK, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Features/Gameplay/QuestSystem/Data/DataAssets/QuestData.h"
#include "Features/Gameplay/QuestSystem/Data/Enums/QuestStatus.h"
#include "Features/Gameplay/QuestSystem/Data/Structs/QuestEntryData.h"
#include "Features/Gameplay/QuestSystem/Data/Structs/QuestSaveData.h"
#include "UObject/Object.h"
#include "QuestBase.generated.h"

class UTaskBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestCompleted);

UCLASS(Abstract, BlueprintType)
class VUNDK_API UQuestBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	UQuestData* QuestData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TMap<UTaskData*, UTaskBase*> AllTasks;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	bool bIsQuestCompleted;
	UPROPERTY(BlueprintAssignable, Category = "Quest System")
	FOnQuestCompleted OnQuestCompleted;

private:
	EQuestType QuestType;
	EQuestStatus QuestStatus;
	FQuestEntryData QuestEntryData;

public:
	virtual void Init(UQuestData* InitData, const FQuestEntryData& EntryData);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	virtual FQuestSaveData CreateQuestSaveData() const;
	
	UFUNCTION(BlueprintCallable, Category = "Quest System")
	virtual void LoadSaveData(FQuestSaveData QuestSaveData);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	virtual void AchieveQuestTask(const UTaskData* TaskDataKey, const bool bFullyAchieve = false);

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	void AchieveAllTasks(const bool bFullyAchieve = false) const;

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	bool IsTaskAchieved(const UTaskData* TaskDataKey) const;

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	UTaskBase* GetTask(const UTaskData* TaskDataKey) const;

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	UTaskBase* GetTaskByFName(const FName TaskName) const;

	void SetQuestStatus(EQuestStatus Status);

	UFUNCTION(BlueprintPure, Category = "Quest System")
	EQuestStatus GetQuestStatus() const;

	UFUNCTION(BlueprintPure, Category = "Quest System")
	EQuestType GetQuestType() const;

	UFUNCTION(BlueprintCallable, Category = "Quest System")
	virtual void ResetQuest();

protected:
	bool AreAllTasksAchieved() const;
};
