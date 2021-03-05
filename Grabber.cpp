// Alejandro Montenegro Reyes

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	// You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleFunc();
	SetupInputComponentFunc();	
}

void UGrabber::SetupInputComponentFunc()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("GrabShit", IE_Pressed, this, &UGrabber::GrabFunc);
		InputComponent->BindAction("GrabShit", IE_Released, this, &UGrabber::ReleaseFunc);
	}
}

void UGrabber::FindPhysicsHandleFunc()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle  == nullptr)
	{
		//no code need here physics handle found
	}
}

void UGrabber::GrabFunc()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Press"));

	FHitResult HitResult = GetFirstPhysicBodyInReachFunc();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	//try to reach and grab collision physics objects
	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
						(
							ComponentToGrab,
							NAME_None,
							GetPlayerReach()
						);
	}
	
}

void UGrabber::ReleaseFunc()
{
	PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
	
	//if physics handle is attyach
		//move object being hold

}

FHitResult UGrabber::GetFirstPhysicBodyInReachFunc() const
{
	//Draw Line debug from player to objet to reach
	DrawDebugLine
		(
			GetWorld(),
			GetPlayerWorldPos(),
			GetPlayerReach(),
			FColor(0, 255, 0),
			false,
			0.f,
			0.f,
			5.f
		);
	
	FHitResult Hit;
	// Ray-cast out to detrminated distance
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
					(
						OUT Hit,
						GetPlayerWorldPos(),
						GetPlayerReach(),
						FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
						TraceParams
					);
	return Hit;
}

FVector UGrabber::GetPlayerWorldPos() const
{
	FRotator PlayerViewRotation;
	FVector PlayerViewLocation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
												(
													OUT PlayerViewLocation, 
													OUT PlayerViewRotation
												);

	return PlayerViewLocation;
}

FVector UGrabber::GetPlayerReach() const
{
	FRotator PlayerViewRotation;
	FVector PlayerViewLocation;
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
												(
													OUT PlayerViewLocation, 
													OUT PlayerViewRotation
												);

	return PlayerViewLocation + PlayerViewRotation.Vector() * Reach;
}