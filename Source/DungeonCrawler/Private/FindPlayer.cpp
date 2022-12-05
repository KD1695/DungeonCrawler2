// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayer.h"

#include "MobAI.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

const FName PLAYER_LOCATION_BB_TAG = "PlayerLocation";

UFindPlayer::UFindPlayer()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const Controller = Cast<AMobAI>(OwnerComp.GetAIOwner());

	FVector playerLocation = player->GetActorLocation();
	if(SearchRandom)
	{
		FNavLocation Location;
		UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if(NavigationSystem->GetRandomPointInNavigableRadius(playerLocation, SearchRadius, Location, nullptr))
		{
			Controller->GetBlackboard()->SetValueAsVector(PLAYER_LOCATION_BB_TAG, Location.Location);
		}
	}
	else
	{
		Controller->GetBlackboard()->SetValueAsVector(PLAYER_LOCATION_BB_TAG, playerLocation);
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
