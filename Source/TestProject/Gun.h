// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Particles/ParticleSystem.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class TESTPROJECT_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		UParticleSystem* Flash;

	UPROPERTY(EditAnywhere)
		float MaxRange = 100.f;

	UPROPERTY(EditAnywhere)
		UParticleSystem* Paret;

	UPROPERTY(EditAnywhere)
		float Damage = 10.f;
};
