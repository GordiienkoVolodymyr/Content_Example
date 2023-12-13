#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Demo_Room_Component.generated.h"

USTRUCT(BlueprintType)
struct FRoom_ISM_Description
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	UStaticMesh *Mesh = 0;
};

USTRUCT(BlueprintType)
struct FRoom_ISM_Params
{
	GENERATED_USTRUCT_BODY()

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONTENTEXAMPLES_API UDemo_Room_Component : public USceneComponent
{
	GENERATED_BODY()

public:	
	UDemo_Room_Component();

};
