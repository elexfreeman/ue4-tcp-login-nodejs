// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GeneratedCodeHelpers.h"
#include "Engine/ObjectLibrary.h"

#include "Async/Async.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Networking.h"

#include "Misc/FileHelper.h"
#include "IPAddress.h"
#include "HAL/ThreadSafeBool.h"

#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "../DB/User/FUserStruct.h"


#include "NodeSocketCmp.generated.h"





typedef TSharedPtr<FString, ESPMode::ThreadSafe> FStringReaderPtr;

// when there was a connection to the server
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNetEventS); 

// when did you get the bytes
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNetMsgEvent, const TArray<uint8>&, Bytes);


// 
// when did you get the string
UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNetMsgEventStr, const  FString&, Msg);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWN1_API UNodeSocketCmp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNodeSocketCmp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// наш сокет подключения
	FSocket * ClientSocket;

	// can receive data safe for thread
	FThreadSafeBool bShouldReceiveData;

	// 
	TFuture<void> ClientConnectionFinishedFuture;

	// server address
	TSharedPtr<FInternetAddr> RemoteAdress;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
		

	// received bytes from the server
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FNetMsgEvent OnReceivedBytes;

	// received a line from the server
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable, BlueprintCallable)
	FNetMsgEventStr OnReceivedStr;

	// runs when connected to the server
	FNetEventS OnConnected;


	/**
	 * Converts bytes to string
	 */
	FString fBytesToString(const TArray<uint8>& InArray); 


	/**
	 * Converts string to bytes
	 */
	TArray<uint8> fStringToBytes(FString InString);



	// connection name
	FString ClientSocketName;

	// buffer size in bytes
	int32 BufferMaxSize;

	// sign that connected
	bool bIsConnected;


	/**
	 * Connects over TCP to the server
	 *
	 * @param InIP ip4 address where we connect
	 * @param InPort TCP connection port
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
	void ConnectToServer(const FString& InIP = TEXT("127.0.0.1"), const int32 InPort = 3000);

	/**
	 * Closes the connection
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
	void CloseSocket();

	/**
	 * Sends bytes to the server
	 *
	 * @param Message	Bytes
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
	bool Emit(const TArray<uint8>& Bytes);


	/**
	 * Sends a string to the server
	 *
	 * @param Message	Bytes
	 */
	UFUNCTION(BlueprintCallable, Category = "AA")
	bool EmitStr(const FString& str);


	// ----------------------------------------------



	void fTestP();
		


};
