// Fill out your copyright notice in the Description page of Project Settings.


#include "DBComp.h"

// Sets default values for this component's properties
UDBComp::UDBComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}



// Called when the game starts
void UDBComp::BeginPlay()
{
	Super::BeginPlay();

	// we get the tcp component
	//this->vPlayerCtrl = (ATopDown1PlayerController *)GetWorld()->GetFirstPlayerController();
	//this->vNodeSocketCmp = this->vPlayerCtrl->vNodeSocketCmp;

	//this->vGameMode = (ATopDown1GameMode *)GetWorld()->GetAuthGameMode();
	//this->vNodeSocketCmp = this->vGameMode->vNodeSocketCmp;


	this->vNodeSocketCmp->OnReceivedStr.AddDynamic(this, &UDBComp::fOnServerMsgClb);


}


// Called every frame
void UDBComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UDBComp::fOnUserLoginReq(FString sLogin, FString sPswd)
{
	// we form a request to the server
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);

	data->SetStringField("login", sLogin);
	data->SetStringField("pswd", sPswd);

	request->SetStringField("sClientToken", FString(TEXT("")));
	request->SetStringField("sRoute", FString(TEXT("user_login_req")));

	request->SetObjectField("data", data);

	FString requestStr;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&requestStr);
	FJsonSerializer::Serialize(request.ToSharedRef(), Writer);

	// send request
	this->vNodeSocketCmp->EmitStr(requestStr);

}



void UDBComp::fOnUserLoginResp(FString msg)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("fOnUserLoginResp"));

	bool bRespOk = fIsMsgOk(msg);

	// parsing response from server

	// check the correctness of the answer
	if (bRespOk)
	{
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
		TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
		FJsonSerializer::Deserialize(JsonReader, request);

		TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);
		TSharedPtr<FJsonObject> user = MakeShareable(new FJsonObject);

		data = request->GetObjectField("data");
		user = data->GetObjectField("user");

		UserData.sToken = data->GetStringField("token");
		UserData.id = user->GetIntegerField("id");
		UserData.sUserName = user->GetStringField("user_name");
		UserData.sLogin = user->GetStringField("login");
		UserData.nIsLoginCorrect = 1;
	}
	else
	{
		UserData.nIsLoginCorrect = -1;
	}

	onUserLoginEvent.Broadcast(UserData.sToken, bRespOk);
}
