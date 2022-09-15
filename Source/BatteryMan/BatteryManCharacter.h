// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BatteryManCharacter.generated.h"

UCLASS()
class BATTERYMAN_API ABatteryManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABatteryManCharacter();

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	USphereComponent* Collector;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

public:
	UPROPERTY(EditAnywhere)
	float CollectorRadius = 40.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//Called when 'move forward' keybind is pressed
	void MoveForward(float Value);

	//Called when 'move right' keybind is pressed
	void MoveRight(float Value);

public:
	//Called when player needs to be hurt/Damaged
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

public:
	UFUNCTION()
	void OnCollectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	UPROPERTY(BlueprintReadWrite)
	float StoredPower = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InitialStoredPower = 200.0f;

};
