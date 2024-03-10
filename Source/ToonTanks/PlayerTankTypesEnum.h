#include "PlayerTankTypesEnum.generated.h"

UENUM()
enum class ETankBodyTypes : uint8
{
     BaseBody = 0,
     ArmoredBody = 1,
};


UENUM()
enum class ETankTurretTypes : uint8
{
     BaseTurret = 0,
     AntiArmorTower = 1,
     MinigunTurret = 2
};


// UENUM(BlueprintType)