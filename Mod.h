// Copyright James Puleo 2020
// Copyright HLOH 2020

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once
#include <ISmmPlugin.h>
#include <memory>
#include <LibFruit/Types.h>
#include <LibFruit/Memory/Detour/Virtual.h>

#if defined WIN32 && !defined snprintf
#define snprintf _snprintf
#endif

namespace HLOH
{
    class Mod : public ISmmPlugin, public IMetamodListener
    {
    public:
        const char* GetDescription() override
        {
            return "Taking any damage will kill you";
        }

        const char* GetName() override
        {
            return "Half-Life One Hit";
        }

        const char* GetLogTag() override
        {
            return "HLOH";
        }

        const char* GetAuthor() override
        {
            return "James Puleo";
        }

        const char* GetURL() override
        {
            return "https://jame.xyz";
        }
        const char* GetLicense() override
        {
            return "GNU GPLv3";
        }

        const char* GetVersion() override
        {
            return "1.0.0";
        }

        const char* GetDate() override
        {
            return __DATE__;
        }

        bool Load(PluginId, ISmmAPI* , char* error, size_t maxlen, bool late) override;
        bool Unload(char* error, size_t maxlen) override;
        bool Pause(char* error, size_t maxlen) override;
        bool Unpause(char* error, size_t maxlen) override;

        typedef bool(__thiscall *IsPlayer_fn)(void*);
        typedef int(__thiscall *OnTakeDamage_fn)(void*, void*);
        typedef void(__thiscall *CommitSuicide_fn)(void*, bool, bool);

        // Windows indexes for Half-Life 2.
        // Different mods and platforms may vary.
        static constexpr u32 m_on_take_damage_index = 62;
        static constexpr u32 m_is_player_index = 80;
        static constexpr u32 m_commit_suicide_index = 438;
    private:
        bool initialize_detours();
        bool uninitialize_detours();
        static int __thiscall detour_on_take_damage(void* this_ptr, void* damage_info);

        IVEngineServer* m_engine_server;
        std::shared_ptr<LibFruit::Detour::SmartVirtual<void*, OnTakeDamage_fn>> m_on_take_damage_detour;
    };

    extern Mod g_Mod;

    PLUGIN_GLOBALVARS();
}
