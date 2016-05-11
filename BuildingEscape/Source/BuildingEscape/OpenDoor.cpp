// Copyright Alex HUnter 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate"), *(GetOwner()->GetName()))
	}

}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Poll the Trigger Volume
	//If the ActorThatOpens is in the volume,
	if (GetTotalMassOfActorsOnPlate() >= TriggerMass)
	{
	
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
	

}
//returns total mass in KG
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	if (!PressurePlate) {return 0.f;}

	//Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	float TotalMass = 0;
	//Iterate through them adding their masses
	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		//UE_LOG(LogTemp, Warning, TEXT("%s on plate"), *Actor->GetName())
	}
	//UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), TotalMass)
	return TotalMass;
}

