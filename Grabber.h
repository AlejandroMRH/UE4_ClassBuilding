// Alejandro Montenegro Reyes

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	void GrabFunc();
	void ReleaseFunc();
	void FindPhysicsHandleFunc();
	void SetupInputComponentFunc();
	FHitResult GetFirstPhysicBodyInReachFunc() const;

	//return line trace end
	FVector GetPlayerReach() const;

	//Get Player location IN world
	FVector GetPlayerWorldPos() const;
};
