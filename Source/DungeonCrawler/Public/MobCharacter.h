// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DungeonCrawler/DungeonCrawlerCharacter.h"
#include "MobCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONCRAWLER_API AMobCharacter : public ADungeonCrawlerCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(AllowPrivateAccess = "true"))
	bool IsDisabled = false;

public:
	UFUNCTION(BlueprintCallable)
	void SetDisableState(bool _IsDisabled);
	//virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
