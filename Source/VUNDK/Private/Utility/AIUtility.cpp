// Copyright VUNDK, Inc. All Rights Reserved.

#include "Utility/AIUtility.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"

void UAIUtility::SetPeripheralVisionAngle(UAIPerceptionComponent* PerceptionComponent, float PeripheralVisionAngle)
{
	if (!PerceptionComponent) return;
	
	UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(GetSenseConfig(PerceptionComponent, UAISense_Sight::StaticClass()));
	if (!SightConfig) return;
	
	UAISenseConfig_Sight* SightConfig_Sight = Cast<UAISenseConfig_Sight>(SightConfig);
	if (!SightConfig_Sight) return;
	
	SightConfig_Sight->PeripheralVisionAngleDegrees = PeripheralVisionAngle;
	PerceptionComponent->RequestStimuliListenerUpdate();
}

UAISenseConfig* UAIUtility::GetSenseConfig(UAIPerceptionComponent* PerceptionComponent, const TSubclassOf<UAISense> SenseClass)
{
	const FAISenseID SenseID = UAISense::GetSenseID(SenseClass);
	return PerceptionComponent->GetSenseConfig(SenseID);
}

void UAIUtility::SetSightRadius(UAIPerceptionComponent* PerceptionComponent, float SightRadius)
{
	if (!PerceptionComponent) return;
	
	UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(GetSenseConfig(PerceptionComponent, UAISense_Sight::StaticClass()));
	if (!SightConfig) return;
	
	UAISenseConfig_Sight* SightConfig_Sight = Cast<UAISenseConfig_Sight>(SightConfig);
	if (!SightConfig_Sight) return;
	
	SightConfig_Sight->SightRadius = SightRadius;
	PerceptionComponent->RequestStimuliListenerUpdate();
}

void UAIUtility::SetLoseSightRadius(UAIPerceptionComponent* PerceptionComponent, float LoseSightRadius)
{
	if (!PerceptionComponent) return;
	
	UAISenseConfig_Sight* SightConfig = Cast<UAISenseConfig_Sight>(GetSenseConfig(PerceptionComponent, UAISense_Sight::StaticClass()));
	if (!SightConfig) return;
	
	UAISenseConfig_Sight* SightConfig_Sight = Cast<UAISenseConfig_Sight>(SightConfig);
	if (!SightConfig_Sight) return;
	
	SightConfig_Sight->LoseSightRadius = LoseSightRadius;
	PerceptionComponent->RequestStimuliListenerUpdate();
}

void UAIUtility::RequestStimuliListenerUpdate(UAIPerceptionComponent* PerceptionComponent)
{
	PerceptionComponent->RequestStimuliListenerUpdate();
}
