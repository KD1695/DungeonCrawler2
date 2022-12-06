// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindPlayer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DUNGEONCRAWLER_API UFindPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindPlayer();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowProtectedAccess = "true"))
	bool SearchRandom = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Search", meta=(AllowProtectedAccess = "true"))
	float SearchRadius = 50.0f;
};
