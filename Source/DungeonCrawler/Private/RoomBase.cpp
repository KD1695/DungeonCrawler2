// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomBase.h"

#include "MobCharacter.h"

// Sets default values
ARoomBase::ARoomBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARoomBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoomBase::EnableNPCs()
{
	TArray<AActor*> childActors;
	this->GetAllChildActors(childActors, true);
	for(int i=0; i<childActors.Num(); i++)
	{
		if(auto MobCharacter = Cast<AMobCharacter>(childActors[i]))
		{
			MobCharacter->SetDisableState(false);
		}
	}
}

