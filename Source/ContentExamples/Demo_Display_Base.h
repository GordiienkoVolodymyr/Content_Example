#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Demo_Display_Base.generated.h"

UCLASS()
class CONTENTEXAMPLES_API ADemo_Display_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	ADemo_Display_Base();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

};
