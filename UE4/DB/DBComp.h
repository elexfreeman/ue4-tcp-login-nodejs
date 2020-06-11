// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "./User/FUserStruct.h"
#include "../NodeSocket/NodeSocketCmp.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "../TopDown1GameMode.h"

#include "DBComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUserLoginEvent, FString, sToken, bool, bStatus);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN1_API UDBComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDBComp();

	// player controller
	ATopDown1GameMode * vGameMode = nullptr;

	// server connection component
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_Net")
	UNodeSocketCmp * vNodeSocketCmp;

	/**
	 * callback - called when a message has arrived from the server
	 * and sent to the appropriate handler
	*/
	UFUNCTION(BlueprintCallable, Category = "AA")
	void fOnServerMsgClb(const  FString& msg);


	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * check if everything is ok in the message
	*/
	bool fIsMsgOk(const FString& msg);

	/**
	 * Get route from server message
	 **/
	FString fGetRouteFromMsg(const FString& msg);



	// ----------------------------------------
	//				Router

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable, Category = "AA_User")
	FUserLoginEvent onUserLoginEvent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AA_User")
	FUserStruct UserData;

	// login to server
	UFUNCTION(BlueprintCallable, Category = "AA_User")
	void fOnUserLoginReq(FString sLogin, FString sPswd);

	// callback - from the server at login
	UFUNCTION(BlueprintCallable, Category = "AA_User")
	void fOnUserLoginResp(FString msg);

		
};
