// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

ADoor::ADoor()
{
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorMesh"));
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	box->AttachToComponent(doorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	box->SetRelativeLocation(FVector(0, -45, 100));
	box->SetBoxExtent(FVector(50, 45, 100));
}

void ADoor::Interact()
{
	Super::Interact();
	
}

UStaticMeshComponent* ADoor::GetDoorMeshComponent()
{
	return doorMesh;
}
