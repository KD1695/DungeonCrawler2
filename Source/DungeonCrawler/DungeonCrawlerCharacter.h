// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Weapon.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "DungeonCrawlerCharacter.generated.h"

UCLASS(config=Game)
class ADungeonCrawlerCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Camera boom positioning the minimap camera above the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* MiniMapCameraBoom;

	UPROPERTY(EditAnywhere, Category="Interaction", meta=( AllowPrivateAccess = "true"))
	USphereComponent* interactionSphere;

	UPROPERTY(BlueprintReadOnly, Category="Attack", meta=(AllowPrivateAccess = "true"))
	bool isReadyToAttack;

	UPROPERTY(BlueprintReadOnly, Category="Attack", meta=(AllowPrivateAccess = "true"))
	bool isAttacking;

	UPROPERTY(EditAnywhere, Category="Attack", meta=(AllowPrivateAccess = "true"))
	UChildActorComponent* WeaponChild;
	
	UPROPERTY(VisibleAnywhere, Category="Attack", meta=(AllowPrivateAccess = "true"))
	AWeapon* Weapon;

	UPROPERTY(EditAnywhere, Category="Attack", meta=(AllowPrivateAccess = "true"))
	UClass* WeaponClass;

public:
	ADungeonCrawlerCharacter();
	UClass* GetWeaponClass() const;
	void SetWeaponClass(UClass* weaponClass);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

protected:
	UPROPERTY(EditAnywhere, Category="Attack", meta=(AllowProtectedAccess = "true"))
	float health;
	
	UPROPERTY(EditAnywhere, Category="Attack", meta=(AllowProtectedAccess = "true"))
	float maxHealth;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	virtual void BeginPlay() override;

	void Interact();

	virtual void AttackStart();
	virtual void AttackStop();

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UPROPERTY(EditAnywhere, Category="Attack", meta=(AllowProtectedAccess = "true"))
    float attackDamage;
};

