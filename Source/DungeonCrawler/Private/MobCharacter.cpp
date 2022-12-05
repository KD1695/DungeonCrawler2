// Fill out your copyright notice in the Description page of Project Settings.


#include "MobCharacter.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"

void AMobCharacter::SetDisableState(bool _IsDisabled)
{
	IsDisabled = _IsDisabled;
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
