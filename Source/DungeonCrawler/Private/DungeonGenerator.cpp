// Fill out your copyright notice in the Description page of Project Settings.


#include "DungeonGenerator.h"

#include "Door.h"
#include "Algo/RandomShuffle.h"

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
	currentLimiterValue = 0;
	GenerateDungeon(start_room);
}

// Called every frame
void ADungeonGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonGenerator::GenerateDungeon(ARoomBase* startRoom)
{
	auto gateArray = startRoom->GetComponentsByClass(UChildActorComponent::StaticClass());
	auto params = FActorSpawnParameters();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	for(int i=0; i<gateArray.Num(); i++)
	{
		auto gate1 = Cast<UChildActorComponent>(gateArray[i]);
		auto actorObj = Cast<ADoor>(gate1->GetChildActor());
		if(!actorObj->isEntrance)
		{
			if(currentLimiterValue < roomLimiter)
			{
				Algo::RandomShuffle(single_out_rooms);
				auto nextRoom = GetWorld()->SpawnActor<ARoomBase>(single_out_rooms[0], gate1->GetComponentLocation(), gate1->GetComponentRotation(), params);
				if(nextRoom)
				{
					//Generate Content
					TArray<AActor*> overlaps;
					Cast<UBoxComponent>(nextRoom->GetComponentByClass(UBoxComponent::StaticClass()))->GetOverlappingActors(overlaps, ARoomBase::StaticClass());
					if(overlaps.Num()>1)
					{
						//destroy and wall
						nextRoom->Destroy();
						Cast<ADoor>(gate1->GetChildActor())->SetWall(true);
					}
					else
					{
						currentLimiterValue++;
						roomsToGenerate.Add(nextRoom);
					}
				}
				else
				{
					//create wall
					Cast<ADoor>(gate1->GetChildActor())->SetWall(true);
				}
			}
			else
			{
				auto nextRoom = GetWorld()->SpawnActor<ARoomBase>(end_rooms[0], gate1->GetComponentLocation(), gate1->GetComponentRotation(), params);
				if(nextRoom)
				{
					//Generate Content
					TArray<AActor*> overlaps;
					Cast<UBoxComponent>(nextRoom->GetComponentByClass(UBoxComponent::StaticClass()))->GetOverlappingActors(overlaps, ARoomBase::StaticClass());
					if(overlaps.Num()>1)
					{
						//destroy and wall
						nextRoom->Destroy();
						Cast<ADoor>(gate1->GetChildActor())->SetWall(true);
					}
				}
				else
				{
					//create wall
					Cast<ADoor>(gate1->GetChildActor())->SetWall(true);
				}
			}
		}
	}

	if(roomsToGenerate.Num() > 0)
		GenerateDungeon(roomsToGenerate.Pop(true));
}

