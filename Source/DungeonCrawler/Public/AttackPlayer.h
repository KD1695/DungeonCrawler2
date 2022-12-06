// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AttackPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DUNGEONCRAWLER_API UAttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	UAttackPlayer();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
