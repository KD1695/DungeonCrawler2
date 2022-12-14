// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RoomBase.generated.h"

UCLASS()
class DUNGEONCRAWLER_API ARoomBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void EnableNPCs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
