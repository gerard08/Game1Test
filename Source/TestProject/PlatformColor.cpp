// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformColor.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UPlatformColor::UPlatformColor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	//Creem els materials transparent i no transparent
	NonTrans = CreateDefaultSubobject<UMaterial>(TEXT("NonTrans"));
	Trans = CreateDefaultSubobject<UMaterial>(TEXT("Trans"));
	// ...
}


// Called when the game starts
void UPlatformColor::BeginPlay()
{
	Super::BeginPlay();

	//Agafem l'actor al que estem associats
	UActorComponent* myActor = GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass());

	//Fem un cast per aconseguir el mesh del nostre actor
	myStaticMesh = Cast<UStaticMeshComponent>(myActor);

	//si n'hi ha
	if (myStaticMesh)
	{
		//Posem el material a no transparent
		myStaticMesh->SetMaterial(0, NonTrans);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Our Actor have no Static mesh"));

	TArray<UPrimitiveComponent*> Comp;
	GetOwner()->GetComponents<UPrimitiveComponent>(Comp);

	Primitive = Comp[0];

	Primitive->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Block);
	Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
}


void UPlatformColor::checkColor(FString color)
{
	//Si tenim mesh
	if (myStaticMesh)
	{
		//Si el color que ens passa el personatge és el mateix que el nostre
		if (color == myColor)
		{
			//canviem el material a transparent
			myStaticMesh->SetMaterial(0, Trans);
			
		}
		//sino
		else
		{
			//posem el material no transparent
			myStaticMesh->SetMaterial(0, NonTrans);
		}
	}
	//else UE_LOG(LogTemp, Warning, TEXT("FUCK THE NULL PoINTER"))
}

void UPlatformColor::IA_checkColor(FString color)
{
	//Si tenim mesh
	if (myStaticMesh)
	{
		//Si el color que ens passa el personatge és el mateix que el nostre
		if (color == myColor)
		{
			//desactivem colisions
			Primitive->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Ignore);
			Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
			//permetem visibilitat
			Primitive->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
			Primitive->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Ignore);
			Primitive->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
			//visibility, camera and bullets
		}
		//sino
		else
		{
			//Activem colisions
			Primitive->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Block);
			Primitive->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
			Primitive->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Block);
			Primitive->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
			Primitive->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
		}
	}
	//else UE_LOG(LogTemp, Warning, TEXT("FUCK THE NULL PoINTER"))
}

