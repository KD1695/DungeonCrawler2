// Fill out your copyright notice in the Description page of Project Settings.


#include "MobCharacter.h"
#include "MobAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

const FName IS_DISABLED_BB_TAG = "IsDisabled";

void AMobCharacter::SetDisableState(bool _IsDisabled)
{
	IsDisabled = _IsDisabled;
	if(auto AIController = Cast<AMobAI>(this->GetController()))
	{
		AIController->GetBlackboard()->SetValueAsBool(IS_DISABLED_BB_TAG, IsDisabled);
	}
	CurrentTimeToRespawn = RespawnInterval;
}

void AMobCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(IsDisabled)
	{
		CurrentTimeToRespawn -= DeltaSeconds;
		if(CurrentTimeToRespawn < 0)
		{
			CurrentTimeToRespawn = RespawnInterval;
			SetDisableState(false);
		}
	}
}

void AMobCharacter::AttackStart()
{
	if(!IsDisabled)
		Super::AttackStart();
}

void AMobCharacter::AttackStop()
{
	Super::AttackStop();
}

float AMobCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                AActor* DamageCauser)
{
	health -= DamageAmount;
	if(health < 0)
	{
		SetDisableState(true);
	}
	return DamageAmount;
}

void AMobCharacter::SetupStimulus()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus Component"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}

AMobCharacter::AMobCharacter()
{
	SetupStimulus();
}
