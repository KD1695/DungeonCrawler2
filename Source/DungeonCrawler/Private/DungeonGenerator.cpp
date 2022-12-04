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
	TArray<AActor*> childActors;
	startRoom->GetAllChildActors(childActors, true);
	auto params = FActorSpawnParameters();
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for(int i=0; i<childActors.Num(); i++)
	{
		auto doorObj = Cast<ADoor>(childActors[i]);
		if(!doorObj)
			continue;
		
		if(!doorObj->isEntrance)
		{
			if(currentLimiterValue < roomLimiter)
			{
				Algo::RandomShuffle(single_out_rooms);
				auto nextRoom = GetWorld()->SpawnActor<ARoomBase>(single_out_rooms[0], doorObj->GetActorLocation(), doorObj->GetActorRotation(), params);
				if(nextRoom)
				{
					//Generate Content
					TArray<AActor*> overlaps;
					Cast<UBoxComponent>(nextRoom->GetComponentByClass(UBoxComponent::StaticClass()))->GetOverlappingActors(overlaps, ARoomBase::StaticClass());
					if(overlaps.Num()>1)
					{
						//destroy and wall
						nextRoom->Destroy();
						doorObj->SetWall(true);
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
					doorObj->SetWall(true);
				}
			}
			else
			{
				auto nextRoom = GetWorld()->SpawnActor<ARoomBase>(end_rooms[0], doorObj->GetActorLocation(), doorObj->GetActorRotation(), params);
				if(nextRoom)
				{
					//Generate Content
					TArray<AActor*> overlaps;
					Cast<UBoxComponent>(nextRoom->GetComponentByClass(UBoxComponent::StaticClass()))->GetOverlappingActors(overlaps, ARoomBase::StaticClass());
					if(overlaps.Num()>1)
					{
						//destroy and wall
						nextRoom->Destroy();
						doorObj->SetWall(true);
					}
				}
				else
				{
					//create wall
					doorObj->SetWall(true);
				}
			}
		}
	}

	if(roomsToGenerate.Num() > 0)
	{
		Algo::RandomShuffle(roomsToGenerate);
		GenerateDungeon(roomsToGenerate.Pop(true));
	}
}

