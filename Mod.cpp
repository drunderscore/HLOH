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

#include "Mod.h"
#include <LibFruit/Memory/ObjectPointer.h>

namespace HLOH
{
    Mod g_Mod;

    PLUGIN_EXPOSE(HLOH::Mod, HLOH::g_Mod);
    bool Mod::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool)
    {
        PLUGIN_SAVEVARS();

        GET_V_IFACE_CURRENT(GetEngineFactory, m_engine_server, IVEngineServer, INTERFACEVERSION_VENGINESERVER);

        if(!initialize_detours())
        {
            if(error && maxlen)
                strcpy_s(error, maxlen, "Failed to initialize detours. Are you in-game?");

            return false;
        }

        return true;
    }

    bool Mod::initialize_detours()
    {
        if(m_on_take_damage_detour)
            return true;

        for(int i = 0; i < m_engine_server->GetEntityCount(); i++)
        {
            auto edict = m_engine_server->PEntityOfEntIndex(i);
            if(!edict || !edict->GetNetworkable())
                continue;

            if(auto ent = edict->GetNetworkable()->GetBaseEntity())
            {
                if(LibFruit::ObjectPointer(ent).vtable()->vtable_entry_as_function<Mod::IsPlayer_fn>(Mod::m_is_player_index)(ent))
                {
                    Mod::m_on_take_damage_detour = std::make_shared<LibFruit::Detour::SmartVirtual<void*, OnTakeDamage_fn>>(ent, Mod::m_on_take_damage_index, Mod::detour_on_take_damage);
                    return true;
                }
            }
        }

        return false;
    }

    bool Mod::uninitialize_detours()
    {
        if(!m_on_take_damage_detour)
            return true;

        m_on_take_damage_detour = nullptr;
        return true;
    }

    int __thiscall Mod::detour_on_take_damage(void* this_ptr, void*)
    {
        LibFruit::ObjectPointer(this_ptr).vtable()->vtable_entry_as_function<Mod::CommitSuicide_fn>(Mod::m_commit_suicide_index)(this_ptr, false, true);
        return 9999;
    }

    bool Mod::Unload(char*, size_t)
    {
        uninitialize_detours();
        return true;
    }

    bool Mod::Pause(char*, size_t)
    {
        return true;
    }

    bool Mod::Unpause(char*, size_t)
    {
        return true;
    }
}
