// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackPlayer.h"

#include "MobAI.h"
#include "MobCharacter.h"

UAttackPlayer::UAttackPlayer()
{
	NodeName = TEXT("Attack Player");
}

EBTNodeResult::Type UAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto const Controller = Cast<AMobAI>(OwnerComp.GetAIOwner());
	Cast<AMobCharacter>(Controller->GetCharacter())->AttackStart();
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
