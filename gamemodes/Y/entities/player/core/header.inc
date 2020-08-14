#if defined _inc_header
	#undef _inc_header
#endif

#define Player. OO_TYPE(PLAYER,Player)

#include <YSI_Players\y_groups>

new
	Group:DeveloperGroup
;

#define IsDeveloper(%0) Group_GetPlayer(DeveloperGroup, %0)