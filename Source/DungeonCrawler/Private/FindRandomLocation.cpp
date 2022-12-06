// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"

#include "MobAI.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName LOCATION_BB_TAG = "LocationToGo";

UFindRandomLocation::UFindRandomLocation()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Controller = Cast<AMobAI>(OwnerComp.GetAIOwner());
	auto const Npc = Controller->GetPawn();

	FVector const origin = Npc->GetActorLocation();
	FNavLocation location;
	UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(NavigationSystem->GetRandomPointInNavigableRadius(origin, SearchRadius, location, nullptr))
	{
		Controller->GetBlackboard()->SetValueAsVector(FName(LOCATION_BB_TAG), location.Location);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
