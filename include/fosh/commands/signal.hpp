#ifndef FOSH_COMMAND_SIGNAL_HPP
#define FOSH_COMMAND_SIGNAL_HPP
/**---------------------------------------------------------------------------
 *
 * @file       signal.hpp
 * @brief      Generic Libfosh command to provide further command via signals
 *
 *             Use lepto signals to declare commands. This avoids to implement 
 *             a new class for simple commands over and over.
 *             Example:
 *                fosh.addCommand( new CCommandSignal("hello", "Hello world", hello ) );
 *
 * @date       20240821
 * @author     Maximilian Seesslen <src@seesslen.net>
 * @copyright  SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/command.hpp>
#include <lepto/signal.hpp>


/*--- Declaration ----------------------------------------------------------*/


class CCommandSignal: public CCommand
{
   private:
      CSignal<int, int, const char **> m_signal;

   public:

      #if IS_ENABLED( CONFIG_LEPTO_SIGNAL_FUNCTION )
       
      /** \brief  Constructor connecting the exec-signal to an function
       * 
       *          example: 
       *             new CCommandSignal( "hello", "Hello World"
       *                      , &hello )
       */
      CCommandSignal(const char *_name, const char *desc, int (*_funcPtr)( int, const char *[] ))
         :CCommand( _name, desc )
      {
         m_signal.connect( _funcPtr);
      }
      
      #endif // ? CONFIG_LEPTO_SIGNAL_FUNCTION
      
      /** \brief  Constructor connecting the exec-signal to an object slot
       * 
       *          example: 
       *             new CCommandSignal( "eraseflash", "Erase media flash"
       *                      , pCanDis, &CCanDis::eraseFlash )
       */
      template <class slotClass >
      CCommandSignal(const char *_name, const char *desc, slotClass *slotObject, int (slotClass::*_methodPtr)( int, const char ** ))
          :CCommand( _name, desc )
      {
         CONNECT_MPTR( m_signal, slotObject, _methodPtr );
         //m_signal.connect<Method>(slotObject, _methodPtr);
      }

      #if ! IS_ENABLED( CONFIG_FOSH_PSEUDO_VIRTUAL )
         virtual int exec(int argc, const char *argv[]) const override;
      #else
         int exec(int argc, const char *argv[]) const;
      #endif
};


#define CCommandSimpleSignal( _name, desc, slotObject, _methodPtr) \
   CCommandSimpleSignal_(_name, desc)->connect<_methodPtr>( slotObject, _methodPtr )

// Simple command signals saved 168 Bytes with 3 commands on "kudu"
#define CreateCommandSimpleSignal( _name, desc, slotObject, _methodPtr) \
   ( new CCommandSimpleSignal_(_name, desc) )->connect<_methodPtr>( slotObject, _methodPtr )

#define CreateCommandSignal( _name, desc, slotObject, _methodPtr) \
( new CCommandSignal(_name, desc, slotObject, _methodPtr ) )


class CCommandSimpleSignal_: public CCommand
{
   private:
      CSimpleSignal<int, int, const char **> m_signal;

   public:

      /** \brief  Constructor connecting the exec-signal to an object slot
       *
       *          example:
       *             new CCommandSignal( "eraseflash", "Erase media flash"
       *                      , pCanDis, &CCanDis::eraseFlash )
       */
      CCommandSimpleSignal_( const char *_name, const char *desc )
          :CCommand( _name, desc )
      {
         //CONNECT_MPTR( m_signal, slotObject, _methodPtr );
         // m_signal.connect<Method>(slotObject, _methodPtr);
      }
      
      template <auto Method, class slotClass >
      CCommandSimpleSignal_( const char *_name, const char *desc
               , slotClass *slotObject, int (slotClass::*_methodPtr)( int, const char ** ) )
         :CCommand( _name, desc )
      {
         m_signal.connect<Method>(slotObject, _methodPtr);
      }
      
      template <auto Method, class slotClass >
      CCommandSimpleSignal_ *connect(slotClass *slotObject, int (slotClass::*_methodPtr)( int, const char ** ) )
      {
          m_signal.connect<Method>(slotObject, _methodPtr);
          return( this );
      }

      #if ! IS_ENABLED( CONFIG_FOSH_PSEUDO_VIRTUAL )
         virtual int exec(int argc, const char *argv[]) const override;
      #else
         int exec(int argc, const char *argv[]) const;
      #endif
};


/*--- Fin ------------------------------------------------------------------*/
#endif // ? ! FOSH_COMMAND_SIGNAL_HPP
