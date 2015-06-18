#include <Headers/stdafx.h>

extern const bool EE_MOBILE;
extern const bool EE_WEB;
extern const bool EE_PUBLISH;
extern const bool EE_ENGINE_EMBED;
extern CChar*   EE_PHYSX_DLL_PATH;
extern CChar*   EE_ENGINE_PATH;
extern CChar*   EE_PROJECT_PATH;
extern CChar*   EE_PROJECT_NAME;
extern CChar*   EE_APP_NAME;
extern const UID  EE_GUI_SKIN;
extern Secure*   EE_PROJECT_SECURE;

void EE_INIT(bool load_engine_data = true, bool load_project_data = true);
void EE_INIT_OBJ_TYPE();
