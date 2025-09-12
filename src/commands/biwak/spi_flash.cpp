/**---------------------------------------------------------------------------
 *
 * @file       spi_flash.cpp
 * @brief      Libfosh command for spi flash
 *
 *             Just prints some informaation like JEDEC ID.
 *
 *  \date      20240821
 *  \author    Maximilian Seesslen <mes@seesslen.net>
 *  \copyright SPDX-License-Identifier: Apache-2.0
 *
 *--------------------------------------------------------------------------*/


/*--- Includes -------------------------------------------------------------*/


#include <fosh/commands/biwak/spi_flash.hpp>


/*--- Implementation -------------------------------------------------------*/


int CCommandSf::exec(int argc, const char *argv[]) const /* virtual */
{
   printf( "Id: 0x%X\n", m_sf.readId() );
   printf( "Jedec-Id: 0x%X\n", m_sf.readJId() );
   printf( "Size: %d\n", m_sf.size() );

   return(0);
}


void CCommandSf::printHelp() const
{
   printf("Usage: \n");
}


/*--- Fin ------------------------------------------------------------------*/
