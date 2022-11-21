// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"

// Sets default values
ADungeonGenerator::ADungeonGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonGenerator::BeginPlay()
{
	Super::BeginPlay();
	auto gateArray = start_room->GetComponentsByClass(UChildActorComponent::StaticClass());
	auto params = FActorSpawnParameters();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	for(int i=0; i<gateArray.Num(); i++)
	{
		auto gate1 = Cast<UChildActorComponent>(gateArray[i]);
		GetWorld()->SpawnActor<ARoomBase>(single_out_rooms[0], gate1->GetComponentLocation(), gate1->GetComponentRotation(), params);
	}
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

