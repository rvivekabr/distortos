#
# file: distortosTest.elf-sources.cmake
#
# author: Copyright (C) 2018 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
#
# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

target_sources(distortosTest.elf PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/CallOnceFunctionTypesTestCase.cpp
		${CMAKE_CURRENT_LIST_DIR}/CallOnceOperationsTestCase.cpp
		${CMAKE_CURRENT_LIST_DIR}/callOnceTestCases.cpp)
