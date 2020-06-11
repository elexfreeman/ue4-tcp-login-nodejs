// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "TestEventsComp.h"
#include "Engine/World.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "MySource/myTestEvents.h"
#include "./NodeSocket/NodeSocketCmp.h"
#include "./DB/DBComp.h"

#include "TopDown1PlayerController.generated.h"


UCLASS()
class ATopDown1PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDown1PlayerController();

	UPROPERTY(BluePrintReadWrite, Category = AA)
	UmyTestEvents* myTestEvents;
	
	// --------------------------------------------
	//					Network

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
	UNodeSocketCmp* vNodeSocketCmp;

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
	FString sServerAddress = TEXT("127.0.0.1");

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
	int32 nServerPort = 3007;


	// --------------------------------------------
	//					DB
	UPROPERTY(BluePrintReadWrite, Category = "AA_DB")
	UDBComp * vUDBComp;


protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	bool bOk = true;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void onMouseRBClick();


};


