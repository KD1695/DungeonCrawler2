// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RoomBase.h"
#include "GameFramework/Actor.h"
#include "DungeonGenerator.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ADungeonGenerator : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Base Rooms", DisplayName="Single Out Rooms")
	TArray<UClass*> node_rooms;

	UPROPERTY(EditAnywhere, Category="Base Rooms", DisplayName="End Rooms")
	TArray<UClass*> end_rooms;

	UPROPERTY(EditAnywhere, Category="Base Rooms", DisplayName="Start Room")
	ARoomBase* start_room;

	UPROPERTY(EditAnywhere, Category="Generation Settings", DisplayName="Limiter Value")
	int roomLimiter;
	int currentLimiterValue = 0;
	TArray<ARoomBase*> roomsToGenerate;

	UPROPERTY(EditAnywhere, Category="Room Content", DisplayName="AI Character Class")
	UClass* MobAICharacterClass;
	
public:	
	// Sets default values for this actor's properties
	ADungeonGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void GenerateDungeon(ARoomBase* startRoom);
};
