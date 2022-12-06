// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "EndNodeCollector.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API AEndNodeCollector : public AInteractable
{
	GENERATED_BODY()
	bool hasNodeToGive = true;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess = "true"))
	bool isReceiver = false;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* collectPointMesh;

	AEndNodeCollector();
	virtual void Interact() override;
};
