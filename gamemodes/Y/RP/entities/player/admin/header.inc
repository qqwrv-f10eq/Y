#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI_Players\y_text>
#include <YSI_Players\y_groups>
#include <YSI_Visual\y_commands>

new
	Group:AdminOnDuty
;

#define IsOnAdminDuty(%0) Group_GetPlayer(AdminOnDuty, %0)