// Fill out your copyright notice in the Description page of Project Settings.


#include "StopAttackPlayer.h"

#include "MobAI.h"
#include "MobCharacter.h"

UStopAttackPlayer::UStopAttackPlayer()
{
	NodeName = "Stop Attacking Player";
}

EBTNodeResult::Type UStopAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Controller = Cast<AMobAI>(OwnerComp.GetAIOwner());
	Cast<AMobCharacter>(Controller->GetCharacter())->AttackStop();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
