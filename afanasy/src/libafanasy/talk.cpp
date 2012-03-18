#include "talk.h"

#include <stdio.h>

#include "environment.h"
#include "address.h"
#include "msg.h"

using namespace af;

Talk::Talk():
   Client( Client::GetEnvironment, 0)
{
   name = af::Environment::getUserName() + "@" + af::Environment::getHostName() + ":" + address.generatePortString();
}

Talk::Talk( Msg * msg):
   Client( Client::DoNotGetAnyValues, 0)
{
   read( msg);
}

Talk::~Talk()
{
}

void Talk::readwrite( Msg * msg)
{
   rw_int32_t( id,            msg);
   rw_int64_t( time_launch,   msg);
   rw_int64_t( time_update,   msg);
   rw_int64_t( time_register, msg);
   rw_String ( name,          msg);
   rw_String ( username,      msg);
   rw_String ( version,       msg);
   address.readwrite( msg);
}

void Talk::generateInfoStream( std::ostringstream & stream, bool full) const
{
   if( full )
   {
      stream << name << " (id=" << getId() << "):";
      stream << "\n Launched At: " << af::time2str( time_launch);
      stream << "\n Registered At: " << af::time2str( time_register);
      stream << "\n Version: " << version;
      stream << "\n Last Update At: " << af::time2str( time_update);
   }
   else
   {
      stream << name << "[" << id << "]";
      stream << " v'" << version << "' ";
      address.generateInfoStream( stream, full);
   }
}
