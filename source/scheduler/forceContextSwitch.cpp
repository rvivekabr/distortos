/**
 * \file
 * \brief forceContextSwitch() definition
 *
 * \author Copyright (C) 2014-2016 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * \date 2016-01-02
 */

#include "distortos/internal/scheduler/forceContextSwitch.hpp"

#include "distortos/architecture/InterruptUnmaskingLock.hpp"
#include "distortos/architecture/requestContextSwitch.hpp"

namespace distortos
{

namespace internal
{

/*---------------------------------------------------------------------------------------------------------------------+
| global functions
+---------------------------------------------------------------------------------------------------------------------*/

void forceContextSwitch()
{
	architecture::requestContextSwitch();
	architecture::InterruptUnmaskingLock interruptUnmaskingLock;
}

}	// namespace internal

}	// namespace distortos
