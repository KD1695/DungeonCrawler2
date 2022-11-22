// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

ADoor::ADoor()
{
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorMesh"));
	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wallMesh"));
	wallMesh->SetVisibility(false);
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	box->AttachToComponent(doorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	box->SetRelativeLocation(FVector(0, -45, 100));
	box->SetBoxExtent(FVector(50, 45, 100));
}

void ADoor::Interact()
{
	Super::Interact();
	
}

void ADoor::SetWall(bool wallState)
{
	wallMesh->SetVisibility(wallState, false);
	//doorMesh->SetVisibility(!wallState, false);
}

UStaticMeshComponent* ADoor::GetDoorMeshComponent()
{
	return doorMesh;
}
