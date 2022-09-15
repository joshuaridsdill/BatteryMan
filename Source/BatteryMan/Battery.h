// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickable.h"
#include "Battery.generated.h"

UCLASS()
class BATTERYMAN_API ABattery : public AActor, public IPickable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattery();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerMin = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float PowerMax = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power")
	float Power = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifeTime")
	float LifeTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LifeTime")
	float LifeTimeMin = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LifeTime")
	float LifeTimeMax = 10.0f;
};
