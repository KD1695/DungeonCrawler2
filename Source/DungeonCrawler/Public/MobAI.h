// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "MobAI.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API AMobAI : public AAIController
{
	GENERATED_BODY()

public:
	AMobAI();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	UBlackboardComponent* GetBlackboard() const;

	void SetDisabledState(bool _isDisabled);

	UFUNCTION(BlueprintCallable)
	void OnSenseUpdated(TArray<AActor*> const& Actors);

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UBlackboardComponent* Blackboard;

	UPROPERTY(EditAnywhere, Category="AI", meta=(AllowPrivateAccess = "true"))
	UAISenseConfig_Sight* Config_Sight;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	bool IsDisabled;

	void SetupPerceptionSystem();
};
