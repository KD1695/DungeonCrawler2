// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "RoomBase.h"

ADoor::ADoor()
{
	doorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorMesh"));
	wallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("wallMesh"));
	wallMesh->SetVisibility(false);
	wallMesh->AttachToComponent(doorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	box = CreateDefaultSubobject<UBoxComponent>(TEXT("box"));
	box->AttachToComponent(doorMesh, FAttachmentTransformRules::KeepRelativeTransform);
	box->SetRelativeLocation(FVector(0, -45, 100));
	box->SetBoxExtent(FVector(50, 45, 100));
}

void ADoor::Interact()
{
	Super::Interact();
	if(doorMesh->IsVisible())
	{
		int offset = isOpen ? -200 : 200;
		doorMesh->MoveComponent(FVector(0,0,offset), doorMesh->GetComponentRotation(), false);
		isOpen = !isOpen;
	}
	if(isOpen && isEntrance)
	{
		if(auto parentRoom = Cast<ARoomBase>(this->GetParentActor()))
		{
			parentRoom->EnableNPCs();
		}
	}
}

void ADoor::SetWall(bool wallState)
{
	wallMesh->SetVisibility(wallState, false);
	doorMesh->SetVisibility(!wallState, false);
}

UStaticMeshComponent* ADoor::GetDoorMeshComponent()
{
	return doorMesh;
}
