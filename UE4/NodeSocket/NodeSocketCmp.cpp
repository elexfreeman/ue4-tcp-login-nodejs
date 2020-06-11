// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeSocketCmp.h"

// Sets default values for this component's properties
UNodeSocketCmp::UNodeSocketCmp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	// set the name of the socket
	ClientSocketName = FString(TEXT("ue4-tcp-client"));

	// reset the socket
	ClientSocket = nullptr;

	// maximum buffer size
	BufferMaxSize = 2 * 1024 * 1024;	// 2 Mb

	// Assign events

}


// Called when the game starts
void UNodeSocketCmp::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UNodeSocketCmp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UNodeSocketCmp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("UNodeSocketCmp End Play"));	
	CloseSocket();
}





/**
 * Connects to server
 */
void UNodeSocketCmp::ConnectToServer(const FString& InIP, const int32 InPort)
{

	// we form the connection address
	RemoteAdress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	UE_LOG(LogTemp, Log, TEXT("TCP address try to connect <%s:%d>"), *InIP, InPort);

	bool bIsValid;
	RemoteAdress->SetIp(*InIP, bIsValid);
	RemoteAdress->SetPort(InPort);

	// we check the validity of the connection address
	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("TCP address is invalid <%s:%d>"), *InIP, InPort);
		return;
	}

	// Get the socket subsystem
	ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, ClientSocketName, false);

	// Set the size of the send / receive buffer
	ClientSocket->SetSendBufferSize(BufferMaxSize, BufferMaxSize);
	ClientSocket->SetReceiveBufferSize(BufferMaxSize, BufferMaxSize);

	bIsConnected = ClientSocket->Connect(*RemoteAdress);

	// if you connected Broadcast event
	if (bIsConnected)
	{
		OnConnected.Broadcast();
		// we say that we are ready to receive data
		bShouldReceiveData = true;
	}


	// Data listener
	ClientConnectionFinishedFuture = Async(EAsyncExecution::Thread, [&]()
		{
			uint32 BufferSize = 0;
			TArray<uint8> ReceiveBuffer;
			FString ResultString;

			// we start an endless loop for receiving data
			while (bShouldReceiveData)
			{
				// if there is data
				if (ClientSocket->HasPendingData(BufferSize))
				{
					// set buffer size
					ReceiveBuffer.SetNumUninitialized(BufferSize);

					int32 Read = 0;
					ClientSocket->Recv(ReceiveBuffer.GetData(), ReceiveBuffer.Num(), Read);

					// send buffer to event
					OnReceivedBytes.Broadcast(ReceiveBuffer);

					// send string to event
					FString msgStr = fBytesToString(ReceiveBuffer);
					OnReceivedStr.Broadcast(msgStr);

					// log message
					UE_LOG(LogTemp, Log, TEXT("Reserve data: %s"), *(fBytesToString(ReceiveBuffer)));

				}
				// skip 1 tick
				ClientSocket->Wait(ESocketWaitConditions::WaitForReadOrWrite, FTimespan(1));
			}
		}
	);
}

/**
 * Closes socket
 * */
void UNodeSocketCmp::CloseSocket()
{
	// if there is a socket
	if (ClientSocket)
	{
		// stop receiving data
		bShouldReceiveData = false;

		// end the connection
		ClientConnectionFinishedFuture.Get();
		ClientSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ClientSocket);
		ClientSocket = nullptr;
	}
}

/**
 * Sends bytes to the server
 * */
bool UNodeSocketCmp::Emit(const TArray<uint8>& Bytes)
{
	bool resp = false;

	// check if there is a connection
	if (ClientSocket && ClientSocket->GetConnectionState() == SCS_Connected)
	{
		int32 BytesSent = 0; // how many bytes sent
		resp = ClientSocket->Send(Bytes.GetData(), Bytes.Num(), BytesSent);
	}
	return resp;
}

/**
 * Sends bytes to the server
 * */
bool UNodeSocketCmp::EmitStr(const FString& str)
{
	bool resp = false;

	// check if there is a connection
	if (ClientSocket && ClientSocket->GetConnectionState() == SCS_Connected)
	{
		int32 BytesSent = 0; // how many bytes sent
		// convert bytes
		TArray<uint8> Bytes = fStringToBytes(str);
		resp =  ClientSocket->Send(Bytes.GetData(), Bytes.Num(), BytesSent);
	}
	return resp;
}


/**
* Converts bytes to strings
*/
FString UNodeSocketCmp::fBytesToString(const TArray<uint8>& InArray)
{
	FString ResultString;
	FFileHelper::BufferToString(ResultString, InArray.GetData(), InArray.Num());
	return ResultString;
}


/**
* Converts strings to bytes
*/
TArray<uint8> UNodeSocketCmp::fStringToBytes(FString InString)
{
	TArray<uint8> ResultBytes;
	ResultBytes.Append((uint8*)TCHAR_TO_UTF8(*InString), InString.Len());
	return ResultBytes;
}



void UNodeSocketCmp::fTestP()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("fTestP"));

}







