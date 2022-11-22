// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API ADoor : public AInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* doorMesh;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* wallMesh;
	
	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UBoxComponent* box;

public:
	UPROPERTY(EditAnywhere, Category="Gate Setting", DisplayName="Set Entrance")
	bool isEntrance = false;
	ADoor();
	virtual void Interact() override;
	void SetWall(bool wallState);
	UStaticMeshComponent* GetDoorMeshComponent();
};
