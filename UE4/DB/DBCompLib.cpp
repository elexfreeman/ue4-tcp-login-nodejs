#include "DBComp.h"


bool UDBComp::fIsMsgOk(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	bool out = false;
	request->TryGetBoolField(TEXT("ok"), out);

	return out;

}

FString UDBComp::fGetRouteFromMsg(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	FString out;
	request->TryGetStringField("sRoute", out);

	return out;
}


// от серевера пришло сообщение
void UDBComp::fOnServerMsgClb(const FString& pMsg)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, *pMsg);


	
	// маршрут сообщения
	FString sRoute = fGetRouteFromMsg(pMsg);

	if (sRoute == "user_login_resp")
	{
		fOnUserLoginResp(pMsg);
	}
}