#include "dmzLuaPluginTimedReset.h"
#include <dmzLuaModule.h>
#include <dmzRuntimeConfigToTypesBase.h>
#include <dmzRuntimePluginFactoryLinkSymbol.h>
#include <dmzRuntimePluginInfo.h>


dmz::LuaPluginTimedReset::LuaPluginTimedReset (const PluginInfo &Info, Config &local) :
      Plugin (Info),
      TimeSlice (
         Info,
         TimeSliceTypeSystemTime,
         TimeSliceModeRepeating,
         config_to_float64 ("time.value", local, 6.0)),
      _luaMod (0),
      _log (Info) {

   _init (local);
}


dmz::LuaPluginTimedReset::~LuaPluginTimedReset () {

}


// Plugin Interface
void
dmz::LuaPluginTimedReset::discover_plugin (
      const PluginDiscoverEnum Mode,
      const Plugin *PluginPtr) {

   if (Mode == PluginDiscoverAdd) {

      if (!_luaMod) { _luaMod = LuaModule::cast (PluginPtr); }
   }
   else if (Mode == PluginDiscoverRemove) {

      if (_luaMod && (_luaMod == LuaModule::cast (PluginPtr))) { _luaMod = 0; }
   }
}


// TimeSlice Interface
void
dmz::LuaPluginTimedReset::update_time_slice (const Float64 TimeDelta) {

   _log.error << "Reseting Lua" << endl;
   if (_luaMod) { _luaMod->reset_lua (); }
}


void
dmz::LuaPluginTimedReset::_init (Config &local) {

}


extern "C" {

DMZ_PLUGIN_FACTORY_LINK_SYMBOL dmz::Plugin *
create_dmzLuaPluginTimedReset (
      const dmz::PluginInfo &Info,
      dmz::Config &local,
      dmz::Config &global) {

   return new dmz::LuaPluginTimedReset (Info, local);
}

};
