// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlatformColor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTPROJECT_API UPlatformColor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlatformColor();

	//funció que crida el personatge per realitzar els canvis de color
	void checkColor(FString color);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:	
	
	// Color de la paret
	UPROPERTY(EditAnywhere)
	FString myColor = "None";

	//Mesh de la paret
	UStaticMeshComponent* myStaticMesh;

	//Material no Transparent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UMaterial* NonTrans;

	//Material Transparent
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UMaterial* Trans;

	//Primitive component
	UPrimitiveComponent* Primitive = nullptr;
};
		

