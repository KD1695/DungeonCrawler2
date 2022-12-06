// Fill out your copyright notice in the Description page of Project Settings.


#include "MobAI.h"
#include "MobCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

const FName IS_DISABLED_BB_TAG = "IsDisabled";
const FName IS_PLAYER_FOUND_BB_TAG = "IsPlayerFound";

AMobAI::AMobAI()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/AI/BT_Mob.BT_Mob'"));
	if(obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BTreeComp"));
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	SetupPerceptionSystem();
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

void AMobAI::OnSenseUpdated(TArray<AActor*> const& Actors)
{
	for(int i=0; i<Actors.Num(); i++)
	{
		if(auto actor = Cast<ADungeonCrawlerCharacter>(Actors[i]))
		{
			if(actor->Controller->IsPlayerController())
				GetBlackboard()->SetValueAsBool(IS_PLAYER_FOUND_BB_TAG, true);
		}
	}
}

void AMobAI::SetupPerceptionSystem()
{
	Config_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	Config_Sight->SightRadius = 400;
	Config_Sight->LoseSightRadius = Config_Sight->SightRadius + 50;
	Config_Sight->PeripheralVisionAngleDegrees = 90;
	Config_Sight->SetMaxAge(5);
	Config_Sight->AutoSuccessRangeFromLastSeenLocation = 600;
	Config_Sight->DetectionByAffiliation.bDetectEnemies = true;
	Config_Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Config_Sight->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*Config_Sight->GetSenseImplementation());
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AMobAI::OnSenseUpdated);
	GetPerceptionComponent()->ConfigureSense(*Config_Sight);
}
