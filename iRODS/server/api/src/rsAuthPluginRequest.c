


// =-=-=-=-=-=-=-
// eirods includes
#include "authPluginRequest.h"
#include "eirods_native_auth_object.h"
#include "eirods_auth_object.h"
#include "eirods_auth_factory.h"
#include "eirods_auth_plugin.h"
#include "eirods_auth_manager.h"
#include "eirods_auth_constants.h"
#include "eirods_pluggable_auth_scheme.h"

void _rsSetAuthRequestGetChallenge( const char* );

/// =-=-=-=-=-=-=-
/// @brief auth request api call which will delegate the
///        request to the correct plugin given the requested
///        auth scheme in the input struct
int rsAuthPluginRequest(
    rsComm_t*           _comm,
    authPluginReqInp_t* _req_inp,
    authRequestOut_t**  _req_out ) {
    // =-=-=-=-=-=-=-
    // check our incoming params
    if( !_comm ) {
        rodsLog( LOG_ERROR, "rsAuthPluginRequest - null comm pointer" );
        return SYS_INVALID_INPUT_PARAM;

    } else if( !_req_inp ) {
        rodsLog( LOG_ERROR, "rsAuthPluginRequest - null input pointer" );
        return SYS_INVALID_INPUT_PARAM;

    }

    // =-=-=-=-=-=-=-
    // check the auth scheme
    std::string auth_scheme = eirods::AUTH_NATIVE_SCHEME;
    if( _req_inp->auth_scheme_ &&
        strlen( _req_inp->auth_scheme_ ) > 0 ) {
        auth_scheme = _req_inp->auth_scheme_;
    }

    // =-=-=-=-=-=-=-
    // store the scheme in a singleton for use in the following rsAuthResponse call
    eirods::pluggable_auth_scheme& plug_a = eirods::pluggable_auth_scheme::get_instance();
    plug_a.set( auth_scheme );

    // =-=-=-=-=-=-=-
    // handle old school memory allocation
    (*_req_out) = (authRequestOut_t*)malloc( sizeof( authRequestOut_t ) );
    (*_req_out)->challenge = (char*)malloc( CHALLENGE_LEN+2 );
   
    // =-=-=-=-=-=-=-
    // construct an auth object given the native scheme
    eirods::auth_object_ptr auth_obj;
    eirods::error ret = eirods::auth_factory( 
                            auth_scheme,
                            &_comm->rError,
                            auth_obj );
    if( !ret.ok() ){
        eirods::log( PASS( ret ) );
        return ret.code();
    }

    // =-=-=-=-=-=-=-
    // resolve an auth plugin given the auth object
    eirods::plugin_ptr ptr;
    ret = auth_obj->resolve( 
              eirods::AUTH_INTERFACE,
              ptr );
    if( !ret.ok() ){
        eirods::log( PASS( ret ) );
        return ret.code();
    }
    eirods::auth_ptr auth_plugin = boost::dynamic_pointer_cast< eirods::auth >( ptr );

    // =-=-=-=-=-=-=-
    // call client side init - 'establish creds'
    ret = auth_plugin->call< 
              authRequestOut_t* >( 
                  eirods::AUTH_AGENT_AUTH_REQUEST,
                  auth_obj,
                  (*_req_out) );
    if( !ret.ok() ){
        eirods::log( PASS( ret ) );
        return ret.code();
    }

    // =-=-=-=-=-=-=-
    // cache the challenge so the below function can
    // access it
    _rsSetAuthRequestGetChallenge( (*_req_out)->challenge );

    // =-=-=-=-=-=-=-
    // win!
    return 0;

} // rsAuthPluginRequest 



