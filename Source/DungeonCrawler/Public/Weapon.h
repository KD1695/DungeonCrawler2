// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class DUNGEONCRAWLER_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SwordMesh;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxComponent;
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
