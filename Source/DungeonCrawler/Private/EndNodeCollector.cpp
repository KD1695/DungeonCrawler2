// Fill out your copyright notice in the Description page of Project Settings.


#include "EndNodeCollector.h"

#include "DungeonCrawler/DungeonCrawlerCharacter.h"

AEndNodeCollector::AEndNodeCollector()
{
	collectPointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AEndNodeCollector::Interact()
{
	Super::Interact();
	if(auto character = Cast<ADungeonCrawlerCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter()))
	{
		if(isReceiver)
		{
			character->UseEndNodeCollection();
		}
		else
		{
			if(hasNodeToGive)
			{
				character->AddEndNodeCollection();
				hasNodeToGive = false;
			}
			
		}
	}
}
