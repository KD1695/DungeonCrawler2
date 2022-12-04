// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAI.h"
#include "MobCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName IS_DISABLED_BB_TAG = "IsDisabled";

AMobAI::AMobAI()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/BT_Mob.BT_Mob'"));
	if(obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTreeComp"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AMobAI::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void AMobAI::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(Blackboard)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent* AMobAI::GetBlackboard() const
{
	return Blackboard;
}

void AMobAI::SetDisabledState(bool _isDisabled)
{
	IsDisabled = _isDisabled;
	Blackboard->SetValueAsBool(IS_DISABLED_BB_TAG, IsDisabled);
}
