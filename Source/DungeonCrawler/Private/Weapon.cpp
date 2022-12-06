// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "MobCharacter.h"
#include "DungeonCrawler/DungeonCrawlerCharacter.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwordMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	SwordMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	BoxComponent->AttachToComponent(SwordMesh, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isAttacking)
	{
		TArray<AActor*> overlappingActors;
		BoxComponent->GetOverlappingActors(overlappingActors, AMobCharacter::StaticClass());
		for(int i=0; i<overlappingActors.Num(); i++)
		{
			if(auto mob = Cast<AMobCharacter>(overlappingActors[i]))
			{
				mob->TakeDamage(5, FDamageEvent(UDamageType::StaticClass()), GetWorld()->GetFirstPlayerController(), this);
			}
		}
	}
}

void AWeapon::Init()
{
	
}

void AWeapon::SetIsAttacking(bool _isAttacking)
{
	isAttacking = _isAttacking;
}

