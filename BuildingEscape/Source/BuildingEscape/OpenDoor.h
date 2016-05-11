// Copyright Alex HUnter 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;
private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
		
	//UPROPERTY(EditAnywhere)
	//AActor* ActorThatOpens; //Remember pawn inherits from actor

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float TriggerMass = 100.f;
	
	AActor* Owner; //the owning door

	float GetTotalMassOfActorsOnPlate();
};
