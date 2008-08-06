#include <dmzEventConsts.h>
#include <dmzEventModule.h>
#include "dmzEventModuleCommonBasic.h"
#include <dmzObjectModule.h>
#include <dmzObjectConsts.h>
#include <dmzRuntimeDefinitions.h>
#include <dmzRuntimePluginFactoryLinkSymbol.h>
#include <dmzRuntimePluginInfo.h>

dmz::EventModuleCommonBasic::EventModuleCommonBasic (
      const PluginInfo &Info,
      Config &local) :
      Plugin (Info),
      EventModuleCommon (Info),
      _log (Info),
      _eventMod (0),
      _objMod (0),
      _defaultObjectHandle (0),
      _defaultEventHandle (0),
      _sourceHandle (0),
      _targetHandle (0),
      _munitionsHandle (0) {

   _init (local);
}


dmz::EventModuleCommonBasic::~EventModuleCommonBasic () {

}


// Plugin Interface
void
dmz::EventModuleCommonBasic::update_plugin_state (
      const PluginStateEnum State,
      const UInt32 Level) {

   if (State == PluginStateInit) {

   }
   else if (State == PluginStateStart) {

   }
   else if (State == PluginStateStop) {

   }
   else if (State == PluginStateShutdown) {

   }
}



void
dmz::EventModuleCommonBasic::discover_plugin (
      const PluginDiscoverEnum Mode,
      const Plugin *PluginPtr) {

   if (Mode == PluginDiscoverAdd) {

      if (!_eventMod) { _eventMod = EventModule::cast (PluginPtr); }
      if (!_objMod) { _objMod = ObjectModule::cast (PluginPtr); }
   }
   else if (Mode == PluginDiscoverRemove) {

      if (_eventMod && (_eventMod == EventModule::cast (PluginPtr))) { _eventMod = 0; }
      if (_objMod && (_objMod == ObjectModule::cast (PluginPtr))) { _objMod = 0; }
   }
}


// EventModuleCommon Interface
dmz::Handle
dmz::EventModuleCommonBasic::create_launch_event (const Handle ObjectHandle) {

   Handle result (0);

   if (_eventMod && _objMod) {

   }

   return result;
}


dmz::Handle
dmz::EventModuleCommonBasic::create_detonation_event (const Handle ObjectHandle) {

   Handle result (0);

   if (_detonationType && _eventMod && _objMod) {

      result = _eventMod->start_event (_detonationType, EventLocal);

      if (result) {

         _eventMod->store_object_handle (result, _munitionsHandle, ObjectHandle);

         _eventMod->end_event (result);
      }
   }

   return result;
}


dmz::Handle
dmz::EventModuleCommonBasic::create_collision_event (
            const Handle SourceHandle,
            const Handle TargetHandle) {

   Handle result (0);

   if (_eventMod && _objMod) {

   }

   return result;
}


void
dmz::EventModuleCommonBasic::_init (Config &local) {

   RuntimeContext *context (get_plugin_runtime_context ());
   Definitions defs (context, &_log);

   _defaultObjectHandle = defs.create_named_handle (ObjectAttributeDefaultName);
   _defaultEventHandle = defs.create_named_handle (EventAttributeDefaultName);

   _sourceHandle = defs.create_named_handle (EventAttributeSourceName);
   _targetHandle = defs.create_named_handle (EventAttributeTargetName);
   _munitionsHandle = defs.create_named_handle (EventAttributeMunitionsName);

   defs.lookup_event_type (EventLaunchName, _launchType);
   defs.lookup_event_type (EventDetonationName, _detonationType);
   defs.lookup_event_type (EventCollisionName, _collisionType);
}


extern "C" {

DMZ_PLUGIN_FACTORY_LINK_SYMBOL dmz::Plugin *
create_dmzEventModuleCommonBasic (
      const dmz::PluginInfo &Info,
      dmz::Config &local,
      dmz::Config &global) {

   return new dmz::EventModuleCommonBasic (Info, local);
}

};