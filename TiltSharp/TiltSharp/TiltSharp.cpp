#include "PluginSDK.h"
#include "TiltSharp.h"

PluginSetup("TiltSharp");

#pragma region Events
void MenuItem()
{
    Menu = GPluginSDK->AddMenu("TiltSharp");
    Preferences = Menu->AddMenu("Preferences");
    EnableL = Preferences->CheckBox("Laughing", true);
    EnableMB = Preferences->CheckBox("Mastery Badge", false);
}

PLUGIN_EVENT(void) OnOrbwalkAfterAttack(IUnit* Source, IUnit* Target)
{
    if (EnableL->Enabled() && !GGame->IsChatOpen())
    {
        // GGame->Taunt(2); // Throws error for some reason
        GGame->Say("/l");   // Works fine
    }
    if (EnableMB->Enabled() && !GGame->IsChatOpen())
    {
        GGame->Say("/masterybadge");
    }

}

#pragma endregion

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
    PluginSDKSetup(PluginSDK);
    MenuItem();
    GEventManager->AddEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
}

PLUGIN_API void OnUnload()
{
    GEventManager->RemoveEventHandler(kEventOrbwalkAfterAttack, OnOrbwalkAfterAttack);
    Menu->Remove();
}