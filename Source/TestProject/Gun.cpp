// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Creo el scene Component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("MySceneComponent"));
	//l'assigno com a root component
	SetRootComponent(Root);
	//Creo el mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh Component"));
	//l'assigno com a fill de root
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("Has disparat"));

	UGameplayStatics::SpawnEmitterAttached(Flash, Mesh, TEXT("GunSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (!OwnerPawn) return;

	AController* OwnerController = OwnerPawn->GetController();

	if (!OwnerController)return;

	FVector PlayerLocation;
	FRotator PlayerRotation;

	OwnerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	FVector End = PlayerLocation + PlayerRotation.Vector() * MaxRange;

	
	//DrawDebugCamera(GetWorld(), PlayerLocation, PlayerRotation, 90, 2, FColor::Red, true);

	FHitResult tocat;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	bool trobat = GetWorld()->LineTraceSingleByChannel(tocat, PlayerLocation, End, ECollisionChannel::ECC_GameTraceChannel1, TraceParams);

	if (trobat)
	{
		//UE_LOG(LogTemp, Warning, TEXT("TOCAT"));
		//DrawDebugPoint(GetWorld(), tocat.Location, 20, FColor::Red, true);
		FVector ShotDirection = -PlayerRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Paret, tocat.Location, ShotDirection.Rotation());

		FPointDamageEvent DamageEvent(Damage, tocat, ShotDirection, nullptr);

		AActor* TouchedActor = tocat.GetActor();
		if (TouchedActor)
		{
			TouchedActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	//else UE_LOG(LogTemp, Warning, TEXT("NO TOCAT"));
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	//GetOwner()->SetActorEnableCollision(false);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

