#pragma once

#include "CoreMinimal.h"

#include "FUserStruct.generated.h"


USTRUCT(BlueprintType)
struct FUserStruct
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA_User")
    FString sUserName = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA_User")
    int32 id = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA_User")
    FString sLogin = "";
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA_User")
    FString sToken = "";


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AA_User")
    int32 nIsLoginCorrect = 0; // 0 - undefined, -1 - invalid, 1 - valid


};
