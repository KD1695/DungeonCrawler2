// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "StopAttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API UStopAttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UStopAttackPlayer();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
